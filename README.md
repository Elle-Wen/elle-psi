## Getting Started
- first follow install instructions on https://github.com/emp-toolkit/emp-sh2pc 

- the `test` directory should hold source code for files you want to run
- if you want to make a new file, go into `test/CMakeLists.txt` and append `add_test_case_with_run( <name of file> )`
- the `bin` directory will hold executables
- use the command `cmake . && make` from the project directory to compile
- after that, try these two commands: `./bin/test_millionaires 1 12345 20 & ./bin/test_millionaires 2 12345 15` and `./bin/test_millionaires 1 12345 75 & ./bin/test_millionaires 2 12345 34`
- go check out `test/millionaires.cpp` and see if you can understand it. Try some other inputs as well.

## naivePSI.cpp 

- This is a naive implementation of PSI algorithm using emp toolkit 
- The goal is to: 
    1. get familier with writing secure computation algorithm using emp toolkit
    2. generate graph for performance comparison that can be used in the future
- Higher level description of the naive method:
    * compare all pairs of elements (a,b) s.t. $a \in$ Alice and $b \in$ Bob
- flags:
    * "E": Given specific elements for both parties, print out the intersections
    * "S": Given size of the set, randomly generate elements and writes the number of AND gates (as a proxy of the running time) to a csv file
- performance benchmark
  ![image](https://github.com/Elle-Wen/elle-psi/assets/70612012/a6d10bed-7dc1-4176-8a4b-795d6368deda)
