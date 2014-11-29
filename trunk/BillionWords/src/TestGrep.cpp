//============================================================================
// Name        : TestGrep.cpp
// Author      : mcapolupo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>

using namespace std;


std::string exec(char* cmd) {
	FILE* pipe = popen(cmd, "r");
	if (!pipe)
		return "ERROR";
	char buffer[128];
	std::string result = "";
	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;
}

vector<string> & split(const string &s, char delim,
		vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;

}

vector<string> split(const string &s, char delim) {
	vector<std::string> elems;
	split(s, delim, elems);
	return elems;

}

int main() {

	ofstream myfile("grepscriptprueba2.sh");

	string miPalabra = "the cat";

	string genericSearch = "grep $regularExpression $file";
	myfile.close();

	string result = exec("grep '^the cat' test");
	vector<string> lines = split(result, '\n');


	cout << lines.at(0) << endl;

//	system("./grepscriptprueba2.sh");

	return 0;
}


