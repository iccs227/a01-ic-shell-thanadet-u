#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int builtin(vector<string> args) {

	int argc = args.size();

	if (argc == 0) {
		return 0;
	}
	string command = args[0];

	// TODO: get exit code then exit
	if (command == "exit") {
		if (argc == 2) {
			int exit_value = stoi(args[1]) & 0xFF;
			cout << "adios" << endl;
			exit(exit_value);
		}
		cout << "Invalid exitcode" << endl;
		cout << "bad command" << endl;
		return 0;

	}

	if (command == "echo") {
		if (argc <= 1) {
		}
		else {
			for (int i = 1; i < argc ; i++) {
				cout << args[i] << " ";
			}
			cout << ("\n");
		}
		return 0;
	}

	cout << "bad command" << endl;
	// Not a built-in command return -1
	return -1;

}
