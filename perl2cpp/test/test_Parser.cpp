// test_Parser.cpp 
// Created by Robin Rowe 2025-04-16
// MIT Open Source

#include <iostream>
#include "../Parser.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing Parser" << endl;
	Parser parser;
	if(!parser)
	{	cout << "Parser failed on operator!" << endl;
		return 1;
	}
	cout << parser << endl;
	cout << "Parser Passed!" << endl;
	return 0;
}
