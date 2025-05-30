//
// Created by Thanadet Udomsit on 30/5/25.
//

#ifndef JOBS_H
#define JOBS_H
#include <vector>
#include <string>
enum JobStatus {
	RUNNING,
	STOPPED,
	FINISHED
};

struct Job {
	int job_id;
	pid_t pgid;
	std::vector<std::string> command;
	JobStatus status;
	bool is_background;
};

extern std::vector<Job> job_list;
extern int next_jobId;

void add_job(pid_t pgid, const std::vector<std::string>& command, bool is_background);
void remove_job(int job_id);
void update_job_status(pid_t pid, int status);
void list_jobs();
void fg_command(int job_id);
void bg_command(int job_id);
void check_background_jobs();
void mark_job_stopped(int job_id);

#endif //JOBS_H
