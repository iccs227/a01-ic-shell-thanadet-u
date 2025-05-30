#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <signal.h>
#include "header/jobs.h"


using namespace std;

vector<Job> job_list;
int next_jobId = 1;

void add_job(pid_t pgid, const vector<string>& command, bool is_background) {
    Job new_job;
    new_job.job_id = next_jobId++;
    new_job.pgid = pgid;
    new_job.command = command;
    new_job.status = RUNNING;
    new_job.is_background = is_background;

    job_list.push_back(new_job);
    cout << "[" << new_job.job_id << "] " << pgid << endl;
}

void remove_job(int job_id) {
    for (auto cur_job = job_list.begin(); cur_job != job_list.end(); ++cur_job) {
        if (cur_job->job_id == job_id) {
            job_list.erase(cur_job);
            return;
        }
    }
}

void update_job_status(pid_t pid, int status) {
    for (auto& job : job_list) {
        if (job.pgid == pid) {
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                cout << "[" << job.job_id << "]+  Done                    ";
                for (auto& cmd : job.command) {
                    cout << cmd << " ";
                }
                cout << endl;
                remove_job(job.job_id);
            } else if (WIFSTOPPED(status)) {
                job.status = STOPPED;
                cout << "[" << job.job_id << "]+  Stopped                 ";
                for (auto& cmd : job.command) {
                    cout << cmd << " ";
                }
                cout << endl;
            }
            return;
        }
    }
}

void list_jobs() {
    for (auto& job : job_list) {
        cout << "[" << job.job_id << "]";
        switch (job.status) {
            case RUNNING: cout << "  Running                 "; break;
            case STOPPED: cout << "  Stopped                 "; break;
            case FINISHED: cout << "  Finished                "; break;
        }
        for (auto& cmd : job.command) {
            cout << cmd << " ";
        }
        if (job.is_background) {
            cout << "&";
        }
        cout << endl;
    }
}

void fg_command(int job_id) {
    for (auto& job : job_list) {
        if (job.job_id == job_id) {
            cout << "[" << job.job_id << "] ";
            for (auto& cmd : job.command) {
                cout << cmd << " ";
            }
            cout << endl;
            // Bring job to foreground
            job.is_background = false;
            job.status = RUNNING;


            //tcsetpgrp(STDIN_FILENO, job.pgid);

            void (*old_sigttou)(int) = signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(STDIN_FILENO, job.pgid);
            signal(SIGTTOU, old_sigttou);

            // Continue the job if stopped
            if (job.status == STOPPED) {
                kill(-job.pgid, SIGCONT);
            }

            int status;
            waitpid(job.pgid, &status, WUNTRACED);

            // Update job status after waiting
            update_job_status(job.pgid, status);

            // Return terminal control to shell
            void (*old_sigttou2)(int) = signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(STDIN_FILENO, getpid());
            signal(SIGTTOU, old_sigttou2);
            return;
        }
    }
    cout << "fg: job not found: " << job_id << endl;
}

void bg_command(int job_id) {
    for (auto& job : job_list) {
        if (job.job_id == job_id && job.status == STOPPED) {
            job.status = RUNNING;
            job.is_background = true;

            // Continue the job in background
            kill(-job.pgid, SIGCONT);

            cout << "[" << job.job_id << "] ";
            for (auto& cmd : job.command) {
                cout << cmd << " ";
            }
            cout << "&" << endl;
            return;
        }
    }
    cout << "bg: no suitable job found for: " << job_id << endl;
}

void check_background_jobs() {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
        update_job_status(pid, status);
    }
}

void mark_job_stopped(int job_id) {
    for (auto& job : job_list) {
        if (job.job_id == job_id) {
            job.status = STOPPED;
            return;
        }
    }
}