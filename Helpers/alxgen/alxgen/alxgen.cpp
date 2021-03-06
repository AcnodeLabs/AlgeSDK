// alxgen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

//format alxgen tag width height
vector<string> lines, outp;

void prepare() {
	lines.push_back("//786//");
	lines.push_back("obj[%dx%dx2]{");
	lines.push_back("v[ -%d.000000, -%d.00000, 0.000000]");
	lines.push_back("n[ 0.000000, 0.000000, 1.000000]");
	lines.push_back("t[ 0.000000, 1.000000]");
	lines.push_back("v[ %d.000000, -%d.00000, 0.000000]");
	lines.push_back("n[ 0.000000, 0.000000, 1.000000]");
	lines.push_back("t[ 1.000000, 1.000000]");
	lines.push_back("v[ %d.000000, %d.00000, 0.000000]");
	lines.push_back("n[ 0.000000, 0.000000, 1.000000]");
	lines.push_back("t[ 1.000000, 0.000000]");
	lines.push_back("v[ -%d.000000, -%d.00000, 0.000000]");
	lines.push_back("n[ 0.000000, 0.000000, 1.000000]");
	lines.push_back("t[ 0.000000, 1.000000]");
	lines.push_back("v[ %d.000000, %d.00000, 0.000000]");
	lines.push_back("n[ 0.000000, 0.000000, 1.000000]");
	lines.push_back("t[ 1.000000, 0.000000]");
	lines.push_back("v[ -%d.000000, %d.00000, 0.000000]");
	lines.push_back("n[ 0.000000, 0.000000, 1.000000]");
	lines.push_back("t[ 0.000000, 0.000000]");
	lines.push_back("}");
	lines.push_back("vertex_count[6]");
	lines.push_back("//Good Luck from alxgen !!");
}

int main(int argc, char** argv)
{
	if (argc != 4) {
		std::cout << "format: alxgen name width height\n";
		return 0;
	} else {
		prepare();
		int width = atoi(argv[2]);
		int height = atoi(argv[3]);

		char line[256];
		for (auto a : lines) {
			sprintf_s(line, 256, a.c_str(), width / 2, height/ 2);
			outp.push_back(string(line) + "\n");
		}
		FILE* f;
		fopen_s(&f, (string(argv[1]) + ".alx").c_str(), "w+");
		if (f) {
			for (auto a : outp) {
				fputs(a.c_str(),f);
			}
			fclose(f);
		}
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
