//
// Created by Thanadet Udomsit on 26/5/25.
//

#ifndef ICSH_H
#define ICSH_H
#include <vector>
extern pid_t foreground_process;
extern int exit_status_code;
extern std::vector<std::string> command_history;
void set_exit_status(int status);
#endif //ICSH_H
