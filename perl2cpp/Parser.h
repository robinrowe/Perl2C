// Parser.h 
// Created by Robin Rowe 2025-04-16
// MIT Open Source

#ifndef Parser_h
#define Parser_h

#include <iostream>
#include <string>
#include <cctype>
#include<map>
//#include<sstream>	// string streams
#include<strstream>	// C-style string streams

class Parser
{	Parser(const Parser&) = delete;
	void operator=(const Parser&) = delete;
	std::istream* input;	// pointer to input stream
	int no_of_errors;	// note: default initialized to 0
	enum Token_value {
		NAME,		NUMBER,		END,
		PLUS='+',	MINUS='-',	MUL='*',	DIV='/',
		PRINT=';',	ASSIGN='=',	LP='(',		RP=')'
	};
	Token_value curr_tok = PRINT;
	double number_value;
	std::string string_value;
	std::map<std::string,double> table;
	Token_value get_token();
	double prim(bool get);
	double term(bool get);
	double expr(bool get);
public:
	~Parser()
	{	if (input != &std::cin)
		{	delete input;
			input = 0;
	}	}
	Parser()
	{}
	bool operator!() const
	{	// to-do
		return true;
	}
	void ReadStdInput()
	{	input = &std::cin;
	}
	bool Open(const char* filename)
	{	//		input = new istringstream(argv[1]);
		input = new std::istrstream(filename);
		return input->good();
	}
	void Set(const char* name,double value)
	{	table[name] = value;
	}
	int Run();
	double error(const char* s);
	std::ostream& Print(std::ostream& os) const;
	std::istream& Input(std::istream& is);
};

inline
std::ostream& operator<<(std::ostream& os,const Parser& parser)
{	return parser.Print(os);
}

inline
std::istream& operator>>(std::istream& is,Parser& parser)
{	return parser.Input(is);
}

#endif
