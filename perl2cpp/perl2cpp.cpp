// perl2cpp.cpp 
// Created by Robin Rowe 2025-04-16
// MIT Open Source

#include <iostream>
using namespace std;

void Usage()
{	cout << "Usage: perl2cpp " << endl;
}

enum
{	ok,
	invalid_args

};

int main(int argc,char* argv[])
{	cout << "perl2cpp starting..." << endl;
	if(argc < 1)
	{	Usage();
		return invalid_args;
	}

	cout << "perl2cpp done!" << endl;
	return ok;
}
