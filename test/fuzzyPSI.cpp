#include <emp-sh2pc/emp-sh2pc.h>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace emp;
using namespace std;

void fuzzy_1d(vector<int> &elements, Integer &distance, int party){ // 1d, naive PSI 
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

void fuzzy_2d(vector<vector<int>> &elements, Integer &distance, int party){
    vector<Bit> intersection;
    for (size_t i = 0; i < elements.size(); i++){
        for (size_t j = 0; j < elements.size(); j++){
            Integer a(32, elements[i][0], ALICE); // assume same size for A and B
            Integer b(32, elements[j][0], BOB);
            Integer diff_x = a - b;
            Integer abs_diff_x = diff_x.abs();
            Integer c(32, elements[i][1], ALICE); // assume same size for A and B
            Integer d(32, elements[j][1], BOB);
            Integer diff_y = c - d;
            Integer abs_diff_y = diff_y.abs();
            Integer sum = abs_diff_x + abs_diff_y;
            Bit inside = (distance >= sum); 
            cout << "i,j: " << i << ", " << j << "\t=\t" << inside.reveal<bool>() << endl;
            intersection.push_back(inside);
        }
    }
}

void fuzzy_3d (vector<vector<int>> &elements, Integer &distance, int party){
    vector<Bit> intersection;
    for (size_t i = 0; i < elements.size(); i++){
        for (size_t j = 0; j < elements.size(); j++){
            Integer a(32, elements[i][0], ALICE); // assume same size for A and B
            Integer b(32, elements[j][0], BOB);
            Integer diff_x = a - b;
            Integer abs_diff_x = diff_x.abs();
            Integer c(32, elements[i][1], ALICE); // assume same size for A and B
            Integer d(32, elements[j][1], BOB);
            Integer diff_y = c - d;
            Integer abs_diff_y = diff_y.abs();
            Integer e(32, elements[i][2], ALICE); // assume same size for A and B
            Integer f(32, elements[j][2], BOB);
            Integer diff_z = e - f;
            Integer abs_diff_z = diff_z.abs();
            Integer sum = abs_diff_x + abs_diff_y + abs_diff_z;
            Bit inside = (distance >= sum); 
            cout << "i,j: " << i << ", " << j << "\t=\t" << inside.reveal<bool>() << endl;
            intersection.push_back(inside);
        }
    }
    
}
int main(int argc, char** argv) {
        //expect argument: [party] [port] [distance] [elements-x] [elements-y] [elements-z]
        // manhattan distance 
        int port, party;
	    parse_party_and_port(argv, &party, &port);  
        NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);
        setup_semi_honest(io, party); // initialize circuit
        int64_t input_distance = atoi(argv[3]);
        Integer distance(32, input_distance, PUBLIC); 
        vector<vector<int>> elements;
        for (int i = 4; i < argc; i+=3) {
            vector<int> coordinate = {atoi(argv[i]), atoi(argv[i+1]), atoi(argv[i+2])};
            elements.push_back(coordinate);
        } 
        fuzzy_3d(elements, distance, party);
        finalize_semi_honest();
} 