#README.md

Robin Rowe 2025-04-16

// Stroustrup desk calulator

// includes character-level input (sec6.1.3) and
// command line input (sec6.1.7),
// but no namespaces and
// no exceptions
// pp 107-119, sec 6.1, A Desk Calculator
// uses += rather than push_back() for string
// to work around standard library bug
// uses istrstream from <strstream> rather than istringstream from <sstream>
// to work around standard library bug
// No guarantees offered. Constructive comments to bs@research.att.com

    program:
	END			   // END is end-of-input
	expr_list END

    expr_list:
	expression PRINT	   // PRINT is semicolon
	expression PRINT expr_list

    expression:
	expression + term
	expression - term
	term

    term:
	term / primary
	term * primary
	primary

    primary:
	NUMBER
	NAME
	NAME = expression
	- primary
	( expression )
