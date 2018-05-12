#include "lexer.hpp"

#include <algorithm>
#include <array>

namespace co
{
constexpr std::array<std::pair<std::string_view, TokenType>, 13> basic_tokens {{
	{"\n", TokenType::EndOfLine},
	{"(", TokenType::ParameterListBegin},
	{")", TokenType::ParameterListEnd},
	{"{", TokenType::FunctionBodyBegin},
	{"}", TokenType::FunctionBodyEnd},
	{"[", TokenType::PropertyBodyBegin},
	{"]", TokenType::PropertyBodyEnd},
	{"=", TokenType::Equal},
	{":", TokenType::TypeConstraintSeparator},
	{",", TokenType::Separator},
	{"break", TokenType::Break},
	{"continue", TokenType::Continue},
	{"return", TokenType::Return}
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

bool Lexer::try_token(Token& token, std::string_view name, TokenType type)
{
	if (match(name))
	{
		token.type = type;
		token.view = {_cursor, name.size()};
		skip(name.size());
		return true;
	}

	return false;
}

char Lexer::next_char()
{
	return *(++_cursor);
}

Lexer::Lexer(std::string_view source) :
	_source{source},
	_cursor{source.begin()}
{}

Token Lexer::next_token()
{
	Token token{};

	// first, skip whitespaces and comments as they are not actual tokens and
	// only behave as separation
	skip_until([&]{ return !isspace(*_cursor); });

	if (match("//"))
	{
		skip_until('\n');
	}
	else if (match("/*"))
	{
		skip_beyond("*/");
	}

	// default to a one character token
	token.view = {_cursor, 1};

	if (eof())
	{
		return token;
	}

	for (auto& t : basic_tokens)
	{
		if (try_token(token, t.first, t.second))
		{
			return token;
		}
	}

	if (is_first_identifier_char(*_cursor))
	{
		auto begin = _cursor;
		skip_until([&] { return !is_identifier_char(*_cursor); });
		_values.value_string = {begin, _cursor};
		token.view = {begin, size_t(std::distance(begin, _cursor))};
		token.type = TokenType::Identifier;
		return token;
	}

	// TODO: handle literals

	token.type = TokenType::Unexpected;
	skip();
	return token;
}
}
