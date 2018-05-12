#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <string_view>

namespace co
{
enum class TokenType
{
	EndOfFile,

	Unexpected,

	// typically used to separate statements
	EndOfLine,

	// any variable or type name
	Identifier,

	// literals, e.g. '1' or '23.3' or '"hello"'
	LiteralInt,
	LiteralFloat,
	LiteralString,

	// parenthesis '(' and ')' respectively
	// parameter lists, either in function declarations or function calls
	ParameterListBegin,
	ParameterListEnd,

	// braces '{' and '}' respectively
	// set of statements executed when calling a function
	FunctionBodyBegin,
	FunctionBodyEnd,

	// brackets '[' and ']' respectively
	PropertyBodyBegin,
	PropertyBodyEnd,

	// colon ':' used to separate variables or parameters from constraints,
	// i.e. type constraint, value constraint or custom function constraint
	TypeConstraintSeparator,

	// equal '=' used to assign variables or declare-assign variables
	Assign,

	// flow control instructions
	Break,
	Continue,
	Return,

	// comma ',' used to separate tuples or parameters
	Separator,
};

struct Token
{
	TokenType type;

	// view of the token within the source file
	std::string_view view;
};
}

#endif // TOKENIZE_HPP
