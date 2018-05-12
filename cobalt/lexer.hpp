#ifndef LEXER_HPP
#define LEXER_HPP

#include <functional>
#include <string>
#include <string_view>
#include <variant>
#include "token.hpp"

namespace co
{
using SourceIt = std::string_view::const_iterator;

struct LexerData
{
	int value_int = 0;
	float value_float = 0.0f;
	std::string value_string;
};

class Lexer
{
	std::string_view _source;
	SourceIt _cursor;
	LexerData _values;

	static bool is_first_identifier_char(char c);
	static bool is_identifier_char(char c);

	bool eof() const;

	bool match(std::string_view substring) const;
	bool match(char c) const;

	void skip_until(const std::function<bool()>& termination_condition);
	void skip_until(char termination_char);
	void skip_until(std::string_view termination_string);

	void skip_beyond(const std::function<bool()>& termination_condition);
	void skip_beyond(char termination_char);
	void skip_beyond(std::string_view termination_string);

	void skip(size_t count = 1);

	char next_char();

public:
	Lexer(std::string_view source);

	Token next_token();
};
}

#endif // LEXER_HPP