// calc.cpp 
// Created by Robin Rowe 2025-04-16
// MIT Open Source

#include "Parser.h"
using namespace std;

void Usage()
{	cout << "Usage: calc " << endl;
}

enum
{	ok,
	invalid_args,
	file_not_found
};

int main(int argc,char* argv[])
{	cout << "calc starting..." << endl;
	Parser parser;
	switch (argc) 
	{	case 1:					// read from standard input
			parser.ReadStdInput();
			break;
		case 2: 				// read argument string
			if(!parser.Open(argv[1]))
			{	cout << "file not found: " << argv[1] << endl;
				return file_not_found;
			}
			break;
		default:
		{	Usage();
			parser.error("too many arguments");
			return invalid_args;
	}	}
	parser.Set("pi",3.1415926535897932385);	
	parser.Set("e",2.7182818284590452354);
	int no_of_errors = parser.Run();
	if(no_of_errors)
	{	cout<< "calc errors: " << no_of_errors << endl;
	}
	else
	{	cout << "calc done!" << endl;
	}
	return ok;
}

