/* ICCS227: Project 1: icsh
 * Name: Thanadet Udomsit
 * StudentID: 6580138
 */

#include <iostream>
#include "header/parser.h"
#include "header/builtins.h"
using namespace std;

int main(int argc, char* argv[]){
    int run = 1;
    string input;
	string last_command;

	// script mode
	if (argc > 1) {
		cout << argv[1] << endl;
		run = 0;
	}

	if (run) {
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
	}


	// interactive mode
    while (run) {
    	cout << "icsh$ ";
    	getline(cin, input);

    	if (input == "!!") {
    		if (last_command.empty()) {
    			continue;
    		}
    		cout << last_command << endl;
    		input = last_command;
    	}
    	else {
    		last_command = input;
    	}

    	// std::vector<std::string> tokens = input_parser(input);
    	auto tokens = input_parser(input);
    	builtin(tokens);
    }
}
