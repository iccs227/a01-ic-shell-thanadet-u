//
// Created by Thanadet Udomsit on 29/5/25.
//

#include "header/io_redirect.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sys/fcntl.h>
using namespace std;


void check_redirect(const vector<string>& args, vector<string>& new_args, string& input_file, string& output_file) {

	for (size_t i = 0; i < args.size(); ++i) {
		if (args[i] == "<") {
			if (i + 1 < args.size()) {
				input_file = args[i + 1];
				++i;
			} else {
				cerr << "ERROR: No input file specified" << endl;
			}
		} else if (args[i] == ">") {
			if (i + 1 < args.size()) {
				output_file = args[i + 1];
				++i;
			} else {
				cerr << "ERROR: No output file specified" << endl;
			}
		} else {
			new_args.push_back(args[i]);
		}
	}
}

void setup_redirect(const string& input_file, const string& output_file) {
	if (!input_file.empty()) {
		int input_fd = open(input_file.c_str(), O_RDONLY);
		if (input_fd < 0) {
			cerr << "ERROR: Could not open input file: " << input_file << endl;
			exit(-1);
		}
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}

	if (!output_file.empty()) {
		int output_fd = open(output_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd < 0) {
			cerr << "ERROR: Could not open output file: " << output_file << endl;
			exit(-1);
		}
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}

}