#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

void C() {
	string dir = string(".");
	vector<string> files = vector<string>();
	getdir(dir, files);
	for (unsigned int i = 0; i<files.size(); i++) {
		cout << files[i] << endl;
	}
}

int main()
{
	string input;
	getline(cin, input);
	if (input == "~T") {
		C();

	}
}
