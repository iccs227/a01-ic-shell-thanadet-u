//
// Created by Thanadet Udomsit on 26/5/25.
//

#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

void sigint_handler(int signum);
void sigtstp_handler(int signum);
void setup_signal_handler(pid_t pid);
void reset_signal_handler(pid_t pid);

#endif //SIGNAL_HANDLER_H
