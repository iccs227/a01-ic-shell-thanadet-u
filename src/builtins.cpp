#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "header/builtins.h"
#include "header/icsh.h"
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

  // cout << "bad command" << endl;	//
  // Not a built-in command return -1
  return -1;
}
