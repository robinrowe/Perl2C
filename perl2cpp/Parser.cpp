// Parser.cpp
// Created by Robin Rowe 2025-04-16
// MIT Open Source

#include "Parser.h"
using namespace std;

ostream& Parser::Print(ostream& os) const
{	// to-do
	return os << "Parser";
} 

istream& Parser::Input(std::istream& is) 
{	// to-do
	return is;
}

double Parser::error(const char* s)
{   no_of_errors++;
    cerr << "error: " << s << '\n';
    return 1;
}

Parser::Token_value Parser::get_token()
{	char ch;
	do {	// skip whitespace except '\en'
		if(!input->get(ch)) return curr_tok = END;
	} while (ch!='\n' && isspace(ch));
	switch (ch) {
	case ';':
	case '\n':
		return curr_tok=PRINT;
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '=':
		return curr_tok=Token_value(ch);
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '.':
		input->putback(ch);
		*input >> number_value;
		return curr_tok=NUMBER;
	default:			// NAME, NAME=, or error
		if (isalpha(ch)) {
			string_value = ch;
			while (input->get(ch) && isalnum(ch))
				string_value += ch;	// string_value.push_back(ch);
							// to work around library bug
			input->putback(ch);
			return curr_tok=NAME;
		}
		error("bad token");
		return curr_tok=PRINT;
	}
}

double Parser::prim(bool get)		// handle primaries
{	if (get) get_token();
	switch (curr_tok) {
	case NUMBER:		// floating-point constant
	{	double v = number_value;
		get_token();
		return v;
	}
	case NAME:
	{	double& v = table[string_value];
		if (get_token() == ASSIGN) v = expr(true);
		return v;
	}
	case MINUS:		// unary minus
		return -prim(true);
	case LP:
	{	double e = expr(true);
		if (curr_tok != RP) return error(") expected");
		get_token();		// eat ')'
		return e;
	}
	default:
		return error("primary expected");
	}
}

double Parser::term(bool get)		// multiply and divide
{	double left = prim(get);
	for (;;)
		switch (curr_tok) {
		case MUL:
			left *= prim(true);
			break;
		case DIV:
			if (double d = prim(true)) {
				left /= d;
				break;
			}
			return error("divide by 0");
		default:
			return left;
		}
}

double Parser::expr(bool get)		// add and subtract
{	double left = term(get);
	for (;;)				// ``forever''
		switch (curr_tok) {
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
}

int Parser::Run()
{	while(*input) {
		get_token();
		if (curr_tok == END) break;
		if (curr_tok == PRINT) continue;
		cout << expr(false) << '\n';
	}
	return no_of_errors;
}
