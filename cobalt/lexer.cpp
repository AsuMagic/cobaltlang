#include "lexer.hpp"

#include <algorithm>
#include <array>
#include "utility.hpp"
#include "log.hpp"

namespace co
{
constexpr std::array<std::pair<char, TokenType>, 10> char_tokens {{
	{'\n', TokenType::EndOfLine},
	{'(', TokenType::ParameterListBegin},
	{')', TokenType::ParameterListEnd},
	{'{', TokenType::FunctionBodyBegin},
	{'}', TokenType::FunctionBodyEnd},
	{'[', TokenType::PropertyBodyBegin},
	{']', TokenType::PropertyBodyEnd},
	{'=', TokenType::Equal},
	{':', TokenType::TypeConstraintSeparator},
	{',', TokenType::Separator},
}};

constexpr std::array<std::pair<std::string_view, TokenType>, 3> identifier_tokens {{
	{"return", TokenType::Return},
	{"break", TokenType::Break},
	{"continue", TokenType::Continue}
}};

constexpr std::array<std::pair<std::string_view, char>, 5> string_escapes {{
	{R"(\n)", '\r'},
	{R"(\n)", '\n'},
	{R"(\t)", '\t'},
	{R"(\\)", '\\'},
	{R"(\")",  '"'}
}};

bool Lexer::is_first_identifier_char(char c)
{
	return isalpha(c);
}

bool Lexer::is_identifier_char(char c)
{
	return is_first_identifier_char(c)
		|| isdigit(c);
}

bool Lexer::eof() const
{
	return _cursor == _source.end();
}

bool Lexer::match(std::string_view substring) const
{
	return size_t(std::distance(_cursor, _source.end())) >= substring.size()
		&& substring == std::string_view{_cursor, substring.size()};
}

bool Lexer::match(char c) const
{
	return *_cursor == c;
}

void Lexer::skip_until(const std::function<bool()>& stop_condition)
{
	while (!eof() && !stop_condition())
	{
		++_cursor;
	}
}

void Lexer::skip_until(char stop_char)
{
	skip_until([&] { return *_cursor == stop_char; });
}

void Lexer::skip_until(std::string_view stop_string)
{
	skip_until([&] { return match(stop_string); });
}

void Lexer::skip_beyond(const std::function<bool()>& stop_condition)
{
	skip_until(stop_condition);
	skip();
}

void Lexer::skip_beyond(char stop_char)
{
	skip_until(stop_char);
	skip();
}

void Lexer::skip_beyond(std::string_view stop_string)
{
	skip_until(stop_string);
	skip(stop_string.size());
}

void Lexer::skip(size_t count)
{
	if (!eof())
	{
		_cursor += count;
	}
}

char Lexer::next_char()
{
	return *(++_cursor);
}

Token Lexer::next_token()
{
	skip_until([&]{ return !isspace(*_cursor); });

	if (match("//"))
	{
		skip_until('\n');
	}
	else if (match("/*"))
	{
		skip_beyond("*/");
	}

	if (eof())
	{
		return {TokenType::EndOfFile, {_cursor, 1}};
	}

	auto token_begin = _cursor;

	for (auto& t : char_tokens)
	{
		if (match(t.first))
		{
			return Token{t.second, {_cursor++, 1}};
		}
	}

	if (is_first_identifier_char(*_cursor))
	{
		skip_until([&] { return !is_identifier_char(*_cursor); });

		std::string_view view = make_view(token_begin, _cursor);

		for (auto& t : identifier_tokens)
		{
			if (view == t.first)
			{
				return {t.second, view};
			}
		}

		value = std::string{view};
		return {TokenType::Identifier, view};
	}

	if (isdigit(*_cursor)) // numeric literal
	{
		skip_until([&] { return !isdigit(*_cursor); });

		if (match('.')) // floating point
		{
			skip(); // skip digit separator '.'
			skip_until([&] { return !isdigit(*_cursor); });

			Token token{TokenType::LiteralFloat, make_view(token_begin, _cursor)};

			value = std::stod(std::string{token_begin, _cursor});
			return token;
		}
		else
		{
			Token token{TokenType::LiteralInt, make_view(token_begin, _cursor)};

			try
			{
				value = std::stoll(std::string{token_begin, _cursor});
			}
			catch (std::out_of_range& e)
			{
				warning(&token, _source_info) <<
					"Integer out of range, assuming zero.\n";
				value = IntegerValue(0);
			}

			return token;
		}
	}

	if (match('"'))
	{
		std::string str;

		skip();
		while (!eof())
		{
			bool has_escaped = false;
			for (auto& p : string_escapes)
			{
				if (match(p.first))
				{
					str += p.second;
					skip(p.first.size());
					has_escaped = true;
				}
			}

			if (has_escaped)
			{
				continue;
			}

			if (match('"'))
			{
				skip();
				break;
			}
			else
			{
				str += *_cursor;
				skip();
			}
		}

		value = str;

		return {TokenType::LiteralString, make_view(token_begin, _cursor)};
	}

	return {TokenType::Unexpected, {_cursor++, 1}};
}

Lexer::Lexer(SourceInfo source) :
	_source_info{source},
	_source{source.source},
	_cursor{_source.begin()}
{}

Token& Lexer::token()
{
	return (last_token = next_token());
}
}
