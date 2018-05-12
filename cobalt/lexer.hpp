#ifndef LEXER_HPP
#define LEXER_HPP

#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>
#include "token.hpp"

namespace co
{
struct TokenValues
{
	int value_int = 0;
	float value_float = 0.0f;
	std::string value_string;
};

class Lexer
{
	std::string_view _source;
	std::string_view::const_iterator _cursor;
	TokenValues _values;

	static bool is_first_identifier_char(char c);
	static bool is_identifier_char(char c);

	bool eof() const;

	bool match(std::string_view substring) const;
	bool match(char c) const;

	void skip_until(const std::function<bool()>& stop_condition);
	void skip_until(char stop_char);
	void skip_until(std::string_view stop_string);

	void skip_beyond(const std::function<bool()>& stop_condition);
	void skip_beyond(char stop_char);
	void skip_beyond(std::string_view stop_string);

	void skip(size_t count = 1);

	std::optional<Token> try_tokenize(std::string_view name, TokenType type);

	char next_char();

public:
	Lexer(std::string_view source);

	Token next_token();
};
}

#endif // LEXER_HPP
