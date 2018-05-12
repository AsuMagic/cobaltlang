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
struct SourceInfo
{
	std::string_view source, source_fname;
};

using IntegerValue = long long;
using FloatValue = double;
using StringValue = std::string;

class Lexer
{
	std::string_view _source; // points to _source_info.source for convenience

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
	Token next_token();

public:
	SourceInfo source_info;
	std::variant<IntegerValue, FloatValue, StringValue> value;
	Token last_token;

	Lexer(SourceInfo source);

	Token& token();
};
}

#endif // LEXER_HPP
