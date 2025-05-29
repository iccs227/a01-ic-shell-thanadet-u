//
// Created by Thanadet Udomsit on 29/5/25.
//

#ifndef IO_REDIRECT_H
#define IO_REDIRECT_H
#include <vector>
#include <string>
using namespace std;
void check_redirect(const vector<string>& args, vector<string>& new_args, string& input_file, string& output_file);
void setup_redirect(const string& input_file, const string& output_file);
#endif //IO_REDIRECT_H
