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
class Lexer
{
	std::string_view _source;
	std::string_view::const_iterator _cursor;

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

	char next_char();

public:
	std::variant<long long, double, std::string> value;

	Lexer(std::string_view source);

	Token next_token();
};
}

#endif // LEXER_HPP
