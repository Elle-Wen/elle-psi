// given 2d points, compute the fuzzy PSI for 2 party computation // use mahanton distance -> use square 
#include <emp-sh2pc/emp-sh2pc.h>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace emp;
using namespace std;
void fuzzy(vector<int> &elements, Integer &distance, int party){ // 1d, naive PSI 
    vector<Bit> intersection; 
    for (size_t i = 0; i < elements.size(); i++){
        for (size_t j = 0; j < elements.size(); j++){
            Integer a(32, elements[i], ALICE); // assume same size for A and B
            Integer b(32, elements[j], BOB);
            Integer diff = a - b;
            Integer abs_diff = diff.abs();
            Bit inside = (distance >= abs_diff); 
            cout << "i,j: " << i << ", " << j << "\t=\t" << inside.reveal<bool>() << endl;
            intersection.push_back(inside);
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
        //expect argument: [party] [port] [epsilon] [elements-x] 
        // epsilon-ball 
        int port, party;
	    parse_party_and_port(argv, &party, &port);  
        NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);
        setup_semi_honest(io, party); // initialize circuit
        int64_t input_distance = atoi(argv[3]);
        Integer distance(32, input_distance, PUBLIC); 
        vector<int> elements;
        for (int i = 4; i < argc; ++i) {
            elements.push_back(atoi(argv[i]));
        } 
        fuzzy(elements, distance, party);
        finalize_semi_honest();
} 