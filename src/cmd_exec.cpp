
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;
int exec_command(vector<string> args) {

	if (args.empty()) {
		cerr << "ERROR: No command provided" << endl;
		return -1; // Return -1 for error
	}

	pid_t pid = fork();
	if (pid < 0) {
		cerr << "ERROR: Fork failed" << endl;
		return -1; // Return -1 for error
	}

	if (pid == 0) {
		// Child process
		vector<char*> prog_argv;
		for (size_t i = 0; i < args.size(); ++i) {
			prog_argv.push_back(const_cast<char *>(args[i].data()));
		}

		prog_argv.push_back(nullptr);

		if (execvp(prog_argv[0], prog_argv.data()) < 0) {
			cerr << "ERROR: Command execution failed" << endl;
			exit(1); // Exit child process with error code
		}
	}
	else {
		// Parent process
		int status;
		waitpid(pid, &status, 0); // Wait for child process to finish
		if (WIFEXITED(status)) {
			return WEXITSTATUS(status); // Return exit status of child
		}
	}

	return 0; // Return 0 for success
}