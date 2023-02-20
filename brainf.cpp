#include "brainf.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cout << "Please input file name" << endl;
		return 1;
	}
	string filename = argv[1];
	compile(filename);

	assemble();

	link();
}
