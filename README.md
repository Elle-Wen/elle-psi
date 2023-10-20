# Getting Started
- first follow install instructions on https://github.com/emp-toolkit/emp-sh2pc 

- the `test` directory should hold source code for files you want to run
- if you want to make a new file, go into `test/CMakeLists.txt` and append `add_test_case_with_run( <name of file> )`
- the `bin` directory will hold executables
- use the command `cmake . && make` from the project directory to compile
- after that, try these two commands: `./bin/test_millionaires 1 12345 20 & ./bin/test_millionaires 2 12345 15` and `./bin/test_millionaires 1 12345 75 & ./bin/test_millionaires 2 12345 34`
- go check out `test/millionaires.cpp` and see if you can understand it. Try some other inputs as well.
