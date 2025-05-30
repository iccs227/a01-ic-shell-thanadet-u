/* ICCS227: Project 1: icsh
 * Name: Thanadet Udomsit
 * StudentID: 6580138
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "header/parser.h"
#include "header/cmd_exec.h"
#include "header/icsh.h"
#include "header/jobs.h"
#include "header/signal_handler.h"
using namespace std;

void runner(string& input, string& last_command);


pid_t foreground_process = -1; // Initialize foreground_process to -1
int exit_status_code = -1;

int main(int argc, char* argv[]){
    string input;
	string last_command;

	// Prevent ^C and ^Z from terminating the shell
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigtstp_handler);

/*
NOTE: should !! return print out the last command and run it? (as according to milestone 1)
	but in milestone 2 the example doesnt print out the last command, it just runs it.
*/
	// script mode
	if (argc > 2) {
		cerr << "ERROR: Too many arguments" << endl;
		exit(1);
	}
	if (argc == 2) {
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
    	check_background_jobs(); // Check for background jobs
    	cout << "icsh$ ";
    	if (!getline(cin, input)) {
    		// Handle EOF (Ctrl+D) (EXTRA FEATURE O_O?)
    		cout << endl;
    		exit(0);
    	}
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
	// exit_status_code = builtin(tokens);
	// if (exit_status_code == -1) {
	// 	exit_status_code = exec_command(tokens);
	// }
	exit_status_code = exec_command(tokens);

}

void set_exit_status(int status) {
	exit_status_code = status;
}
