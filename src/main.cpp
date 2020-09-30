#include <iostream>
#include <string>
#include <fstream>
using namespace std;

std::string check_os() {
	#ifdef __linux__
	return "linux";
	#elif __APPLE__ || __MECH__
	return "MAC";
	#endif
}

void EXIT_FORM() {
	cout << "\033c";
	exit(0);
}

void creat_new_file() {
	string filename="/tmp/MOI_FILES_SAVE/new_file.cpp";
	std::ofstream out_file (filename);
	out_file << "TEST" << std::endl;
	out_file.close();
}

void scan_each_line(string input_line) {
	if (input_line == "~@") {
		EXIT_FORM();
	}
	if (input_line == "~!") {
		creat_new_file();
		EXIT_FORM();
	}
}

int main() {
	int line_number=1;
	cout << "\033c";
	while (1) {
		string test;
		cout << "\033[1;3" << line_number%6 << "m" << line_number << ": " << "\033[0m";
		getline(cin, test);
		scan_each_line(test);
		line_number += 1;
	}
	return 0;
}
