
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include "header/cmd_exec.h"
#include "header/builtins.h"
#include "header/icsh.h"
#include "header/signal_handler.h"
#include "header/io_redirect.h"
#include "header/jobs.h"

using namespace std;

int exec_command(vector<string> args) {
	vector<string> new_args;
	string input_file, output_file;
	bool background = false;

	if (args.empty()) {
		return -1; // Return -1 for error
	}

	if (args[0] == "jobs" || args[0] == "fg" || args[0] == "bg" || args[0] == "cd" || args[0] == "exit" || args[0] == "history" || args[0] == "help") {
		return builtin(args);
	}

	if (args.back() == "&") {
		background = true;
		args.pop_back();
	}

	check_redirect(args, new_args, input_file, output_file);


	pid_t pid = fork();
	if (pid < 0) {
		cerr << "ERROR: Fork failed" << endl;
		return -1; // Return -1 for error
	}

	if (pid == 0) {
		// Child process
		setpgid(0, 0);

		setup_redirect(input_file, output_file);

		if (builtin(new_args) != -1) {
			exit(0);
		}

		vector<char*> prog_argv;
		for (size_t i = 0; i < new_args.size(); ++i) {
			prog_argv.push_back(const_cast<char *>(new_args[i].data()));
		}

		prog_argv.push_back(nullptr);

		if (execvp(prog_argv[0], prog_argv.data()) < 0) {
			cerr << "ERROR: Command not found: " << prog_argv[0] << endl;
			exit(127); // Exit with 127 for command not found
		}
	}
	else {
		// Parent process
		setpgid(pid, pid); // Ensures child is in its own group

		if (background) {
			add_job(pid, new_args, true); // Add job to background
			return 0; // Go back to shell without waiting
		}
		foreground_process = pid;

		setup_signal_handler(pid); // Sets terminal control to child

		int status;
		waitpid(pid, &status, WUNTRACED);

		reset_signal_handler(getpid()); // Return terminal control to shell
		foreground_process = -1;

		if (WIFSTOPPED(status)) {
			// If the child process is stopped, update job status
			add_job(pid, new_args, false);
			update_job_status(pid, status);
		}
		if (WIFEXITED(status)) {
			return WEXITSTATUS(status); // Return exit status of child
		}
		if (WIFSIGNALED(status)) {
			return 128 + WTERMSIG(status); // Standard shell signal exit code
		}
	}


	return 0; // Return 0 for success
}