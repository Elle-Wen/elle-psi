#include <emp-sh2pc/emp-sh2pc.h>
// compile with cmake . && make
using namespace emp;
using namespace std;

void test_millionaire(int number){
	// emp::Integer is a class that implements a secure integer for MPC
	// the constructor takes 3 arguments: <number of bits>, <value>, <party>
	Integer a(32, number, ALICE); // an integer initialized with party ALICE is only visible to party 1
	Integer b(32, number, BOB);   // similarly, if initialized with party BOB it is only visible to party 2
	// (ALICE and BOB are macros for 1 and 2 in the emp namespace)
	
	// emp::Bit is a class that implements a secure bit for MPC
	Bit res = a > b; // res is the output of securely comparing a and b in the circuit
	// the > operator on two emp::Integers invokes a circuit for comparison from the emp library
	
	// the reveal() method outputs a secured value
	cout << "ALICE has larger number?\t" << res.reveal<bool>() << endl;
	// res.reveal<bool>() lets the compiler know that we'd like to unmask the Bit res, which contains the result of the comparison, and that we'd like its type to be bool
}

void test_sum(int number) {
	// see if you can pattern match to write a circuit that sums two Integers from alice and bob, and then reveals the sum
	// note that the + operator is defined on emp::Integers
	Integer a(32, number, ALICE);
	Integer b(32, number, BOB);
	cout << "Sum of Alice and Bob\t" << (a+b).reveal<int>() << endl;
}


int main(int argc, char** argv) {
	if (argc <= 2) {
		cout << "Please supply proper arguments:" << endl;
		cout << "./<millionaires executable> <party> <port> <number>" << endl;
		return 0;
	}

	int port, party;
	parse_party_and_port(argv, &party, &port); // this is a function from emp
	// it just makes it so that when you run the following:
	// ./bin/millionaires 1 12345
	// it interprets the 1 as the party, and the 12345 as the port

	int num = 20; // default value for num
	if (argc > 3) {
		num = atoi(argv[3]);
	}

	// initialize emp::NetIO class, handles communication between the two parties

	NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);
	setup_semi_honest(io, party); // initialize circuit
	// tests go here 
	//test_millionaire(num);

	test_sum(num);

//	cout << CircuitExecution::circ_exec->num_and()<<endl; // gives the number of AND gates in the circuit

	finalize_semi_honest();
	delete io;
	return 0;
}
