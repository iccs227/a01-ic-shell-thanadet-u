/* ICCS227: Project 1: icsh
 * Name: Thanadet Udomsit
 * StudentID: 6580138
 */

#include <iostream>
#include <fstream>
#include "header/parser.h"
#include "header/builtins.h"
using namespace std;

void runner(string& input, string& last_command);

int main(int argc, char* argv[]){
    string input;
	string last_command;

	// script mode
/*
NOTE: should !! return print out the last command and run it? (as according to milestone 1)
	but in milestone 2 the example doesnt print out the last command, it just runs it.
*/
	if (argc > 2) {
		cerr << "ERROR: Too many arguments" << endl;
		exit(1);
	}
	if (argc == 1) {
		ifstream file(argv[1]);
		if (!file.is_open()) {
			cerr << "ERROR: Could not open file " << argv[1] << endl;
			exit(1);
		}
		while (getline(file, input)) {
			runner(input, last_command);
		}
		file.close();
		exit(0);
	}

	cout << "\033[33;1;m\nWelcome to \n\033[0m";
	cout << " \033[33;1;m___  ________\033[0m  ________  ___  ___     \n";
	cout << "\033[33;1;m|\\  \\|\\   ____\\\033[0m|\\   ____\\|\\  \\|\\  \\    \n";
	cout << "\033[33;1;m\\ \\  \\ \\  \\___|\033[0m\\ \\  \\___|\\ \\  \\\\\\  \\   \n";
	cout << "\033[33;1;m \\ \\  \\ \\  \\    \033[0m\\ \\_____  \\ \\   __  \\  \n";
	cout << "\033[33;1;m  \\ \\  \\ \\  \\____\033[0m\\|____|\\  \\ \\  \\ \\  \\ \n";
	cout << "\033[33;1;m   \\ \\__\\ \\_______\\\033[0m____\\_\\  \\ \\__\\ \\__\\ \n";
	cout << "\033[33;1;m    \\|__|\\|_______|\033[0m\\_________\\|__|\\|__| \n";
	cout << "                  \\|_________|         \n";
	cout << "                                       \n";


	// interactive mode
    while (true) {
    	cout << "icsh$ ";
    	getline(cin, input);
    	runner(input, last_command);
    }
}

void runner(string& input, string& last_command) {
	if (input == "!!") {
		if (last_command.empty()) {
			return;
		}
		cout << last_command << endl;
		input = last_command;
	}
	else {
		last_command = input;
	}
	auto tokens = input_parser(input);
	builtin(tokens);

}
