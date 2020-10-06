#include <iostream>
#include <string>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>

using namespace std;

std::string check_os() {
	#ifdef __linux__
	return "linux";
	#elif __APPLE__ || __MECH__
	return "MAC";
	#endif
}

int check_files(string dir, vector<string> &files) {
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(dir.c_str())) == NULL) {
		cout << "ERROR(" << errno << ") opening " << dir << endl;
		return errno;
	}
	while ((dirp = readdir(dp)) != NULL) {
		files.push_back(string(dirp->d_name));
	}
	closedir(dp);
	return 0;
}

void check_file(string filename) {
	string main_buffer;
	string dir = string(".");
	vector<string> files = vector<string>();
	check_files(dir, files);
	int OT = 0;
	for (unsigned int i=0; i<files.size(); i++) {
		if (filename == files[i]) {
			OT += 1;
		}
	}
	if (OT == 1) {
		string return_data;
		ifstream out_file(filename);
		int line_number = 1;
		while (getline(out_file, return_data)) {
			main_buffer = main_buffer + return_data + "\n";
			cout << "\033[1;3" << line_number%6 << "m" << line_number << ": " << "\033[0m" << return_data << endl;
			line_number += 1;
		}
		out_file.close();
	}
}

void EXIT_FORM() {
	cout << "\033c";
	exit(0);
}

void save_file(string Filename, string input_buffer) {
	std::ofstream out_file (Filename);
	out_file << input_buffer << std::endl;
	out_file.close();
}

/*
void check_file_status(string filename, string input_buffer) {
	if (filename != "") {
		save_file(filename, input_buffer);
	} else {
		cout << "write your file name";
		cin >> filename;
		save_file(filename, input_buffer);
	}
}
*/

void scan_each_line(string input_line, string filename, string buffer) {
	if (input_line == "~@") {
		EXIT_FORM();
	}
	if (input_line == "~!") {
		save_file(filename, buffer);
		EXIT_FORM();
	}
	if (input_line == "~?") {
		cout << buffer;
	}
}
int main(int argc, char** argv) {
	int line_number=1;
	cout << "\033c";
	check_file(argv[1]);
	string All_buffer;
	while (1) {
		string test;
		cout << "\033[1;3" << line_number%6 << "m" << line_number << ": " << "\033[0m";
		getline(cin, test);
		//string Test = line_number+test;
		scan_each_line(test, argv[1], All_buffer);
		if (test[0] != '~') {
			All_buffer += test+"\n";
		}
		line_number += 1;
	}
	return 0;
}
