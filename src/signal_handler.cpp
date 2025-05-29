//
// Created by Thanadet Udomsit on 26/5/25.
//

#include <signal.h>
#include <unistd.h>

#include "header/icsh.h"

void sigint_handler(int /* signum */) {
	// Handle SIGINT signal (Ctrl+C)
	if (foreground_process > 0) {
		kill(-foreground_process, SIGINT);
	}
}

void sigtstp_handler(int /* signum */) {
	// Handle SIGTSTP signal (Ctrl+Z)
	if (foreground_process > 0) {
		kill(-foreground_process, SIGTSTP);
	}
}

void setup_signal_handler(pid_t pid) {
	signal(SIGTTOU, SIG_IGN);	// Ignore SIGTTOU to stop shell from getting suspended when child process tries to access terminal
	tcsetpgrp(STDIN_FILENO, pid);
}

void reset_signal_handler(pid_t pid) {
	tcsetpgrp(STDIN_FILENO, pid);
	signal(SIGTTOU, SIG_DFL); // Reset SIGTTOU to default behavior
}

