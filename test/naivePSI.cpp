#include <emp-sh2pc/emp-sh2pc.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace emp;
using namespace std;
// run with ./bin/test_naivePSI 1 12345 1 2 3 ;./bin/test_naivePSI 2 12345 2 3 4
void naive(vector<int> &elements){

    vector<Bit> intersection; 
    for (size_t i = 0; i < elements.size(); i++){
        for (size_t j = 0; j < elements.size(); j++){
            Integer a(32, elements[i], ALICE); // assume same size for A and B
            Integer b(32, elements[j], BOB);
            Bit equal = (a == b); 
            //if (equal){ // people can observe and figure out info about a and b if don't use Bit 
            intersection.push_back(equal);
        }
    }
    for (size_t i = 0; i < intersection.size(); ++i){
        cout << "Encoded intersection\t" << intersection[i].reveal<bool>() << endl; 
    }// iterature through vector + reveal for each bit 
    }

int main(int argc, char** argv) {
    //expect argument: [party] [port] [elements]
    int port, party;
	parse_party_and_port(argv, &party, &port);  
    //for ./naivePSI 1 12345 
    // 1 is party, 12345 is port number 
    //now convert the input elements to a vector
    vector<int> elements;
    for (int i = 3; i < argc; ++i) {
        elements.push_back(atoi(argv[i]));
        } 
    cout << "o"<< endl;
    NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);
    cout << "hi"<< endl;
    setup_semi_honest(io, party); // initialize circuit
    naive(elements);
    finalize_semi_honest();
}