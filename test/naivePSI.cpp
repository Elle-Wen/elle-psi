#include <emp-sh2pc/emp-sh2pc.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
using namespace emp;
using namespace std;
// run with ./bin/test_naivePSI 1 12345 E 1 2 3 & ./bin/test_naivePSI 2 12345 E 2 3 4
// ./bin/test_naivePSI 1 12345 S 100 & ./bin/test_naivePSI 2 12345 S 100
// processes are hapenning at the same time, not one after the other 
// if want only one party, just pass the party argument in our function and use "if" to check (but two party has to be aggreed to reveal)
void naive(vector<int> &elements, int party){
    vector<Bit> intersection; 
    for (size_t i = 0; i < elements.size(); i++){
        for (size_t j = 0; j < elements.size(); j++){
            Integer a(32, elements[i], ALICE); // assume same size for A and B
            Integer b(32, elements[j], BOB);
            Bit equal = (a == b); 
            cout << "i,j: " << i << ", " << j << "\t=\t" << equal.reveal<bool>() << endl;
            //if (equal){ // people can observe and figure out info about a and b if don't use Bit 
            intersection.push_back(equal);
        }
    }
    for (size_t i = 0; i < intersection.size(); ++i){
        bool intersection_bit = intersection[i].reveal<bool>();
        if (party == ALICE){
            cout << "Encoded intersection for\t" << intersection_bit << endl; // also print i, j
        }
    }
}

int main(int argc, char** argv) {
    //expect argument: 
    //[party] [port] [flag-E] [elements] -> given specific elements, output intersection 
    //[party] [port] [flag-S] [size] -> given size, in addition to output intersection, output number of AND gates and writs it to a csv file
    int port, party;
	parse_party_and_port(argv, &party, &port);  
    //for ./naivePSI 1 12345 
    // 1 is party, 12345 is port number 
    vector<int> elements;
    char flag = *argv[3];
    int size = -1; 
    if (flag == 'E'){
        //now convert the input elements to a vector
        for (int i = 4; i < argc; ++i) {
            elements.push_back(atoi(argv[i]));
        } 
    }
    else if (flag == 'S'){
        size = atoi(argv[4]);
        random_device rd;  // Obtain a random number from hardware
        mt19937 gen(rd()); // Seed the generator
        // Define the range for random integers
        int lower_limit = 1;
        int upper_limit = 100;
        // Create a vector to store the generated random integers
        for (int i = 0; i < size; ++i) {
        uniform_int_distribution<int> distribution(lower_limit, upper_limit);
        int random_number = distribution(gen);
        elements.push_back(random_number);
        }
    }
    else{
        cout << "Invalid flag" << endl;
    }
    
    NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);
    setup_semi_honest(io, party); // initialize circuit
    naive(elements, party);
    // write size vs. AND gate number to a csv file 
    if (flag =='S' and party == ALICE){
        int num_and = CircuitExecution::circ_exec->num_and();
        cout << num_and <<endl; // gives the number of AND gates in the circuit (real limiting factor, proxy for speed)
        const string filename = "naive_size_time_benchmark.csv";
        ofstream outputFile(filename, ios::app); // Open in append mode
        // Check if the file is successfully opened
        if (outputFile.is_open()) {
            // Write data to the CSV file
            outputFile << size << "," << num_and << "\n";
            // Close the file stream
            outputFile.close();
            cout << "Data has been written to " << filename << endl;
        } else {
            cerr << "Error opening the file: " << filename << endl;
        }
    }
    finalize_semi_honest();
}