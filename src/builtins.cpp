#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "header/builtins.h"
#include <unistd.h>
#include "header/icsh.h"
#include "header/jobs.h"
using namespace std;

int builtin(vector<string> args) {

  int argc = args.size();

  if (argc == 0) {
    return 0;
  }
  string command = args[0];

  if (command == "exit") {
    if (argc == 2) {
      try {
        const int exit_value = stol(args[1]) & 0xFF;
        cout << "adios" << endl;
        exit(exit_value);
      } catch (invalid_argument e) {
        exit(-1);
      }
    }
    cout << "ERROR: Invalid exitcode" << endl;
    cout << "bad command" << endl;
    return 0;
  }

  if (command == "echo") {
    if (argc <= 1) {
    }
    if (argc == 2 && args[1] == "$?") {
      cout << exit_status_code << "\n";
    }
    else {
      for (int i = 1; i < argc; i++) {
        cout << args[i] << " ";
      }
      cout << ("\n");
    }
    return 0;
  }

  if (command == "jobs") {
    list_jobs();
    return 0;
  }

  if (command == "fg") {
    if (argc == 2 && args[1][0] == '%') {
      try {
        int job_id = stoi(args[1].substr(1));
        fg_command(job_id);
        return 0;
      } catch (...) {
        cerr << "fg: invalid job id" << endl;
      }
    }
    cerr << "Usage: fg %jobid" << endl;
    return -1;
  }

  if (command == "bg") {
    if (argc == 2 && args[1][0] == '%') {
      try {
        int job_id = stoi(args[1].substr(1));
        bg_command(job_id);
        return 0;
      } catch (...) {
        cerr << "bg: invalid job id" << endl;
      }
    }
    cerr << "Usage: bg %jobid" << endl;
    return -1;
  }

  // Extra feature: cd command
  if (command == "cd") {
    if (argc == 2) {
    // Change to specified directory
    if (chdir(args[1].c_str()) != 0) {
      perror("cd can't change directory");
      return 1;
    }
  } else {
    cerr << "cd <path>" << endl;
    return 1;
  }
    return 0;
  }

  if (command == "history") {
    for (const auto& cmd : command_history) {
      cout << cmd << endl;
    }
  }

  if (command == "help") {
    cout << "Built-in commands:\n"
         << "  cd [dir]    - Change directory\n"
         << "  exit [code] - Exit shell\n"
         << "  echo [text] - Print text\n"
         << "  jobs        - List background jobs\n"
         << "  fg %id      - Bring job to foreground\n"
         << "  bg %id      - Resume job in background\n"
         << "  help        - Show this help\n"
         << "  history     - Show command history\n";
    return 0;
  }

  // Not a built-in command return -1
  return -1;
}
