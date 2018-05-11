#include "lexer.hpp"

#include <algorithm>
#include <array>

namespace co
{
bool Lexer::is_first_identifier_char(char c)
{
	constexpr std::string_view extra = "+-*/%&|><!^";

	c = tolower(c);
	return isalpha(c)
		|| std::find(extra.begin(), extra.end(), c) != extra.end();
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
	if (size_t(std::distance(_cursor, _source.end())) >= substring.size()
	 && std::equal(_cursor, _cursor + substring.size(), substring.begin(), substring.end()))
	{
		return true;
	}

	return false;
}

bool Lexer::match(char c) const
{
	return c == *_cursor;
}

void Lexer::skip_until(const std::function<bool()>& termination_condition)
{
	// TODO: make this cleaner

	if (eof() || termination_condition())
	{
		return;
	}

	while (++_cursor != _source.end()
		&& !termination_condition());
}

void Lexer::skip_until(char termination_char)
{
	skip_until([&] { return *_cursor == termination_char; });
}

void Lexer::skip_until(std::string_view termination_string)
{
	skip_until([&] { return match(termination_string); });
}

void Lexer::skip_beyond(const std::function<bool()>& termination_condition)
{
	skip_until(termination_condition);
	skip();
}

void Lexer::skip_beyond(char termination_char)
{
	skip_until(termination_char);
	skip();
}

void Lexer::skip_beyond(std::string_view termination_string)
{
	skip_until(termination_string);
	skip(termination_string.size());
}

void Lexer::skip(size_t count)
{
	if (eof())
	{
		return;
	}

	_cursor += count;
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
	token.offset = _cursor;

	auto token_check = [&](std::string_view name, TokenType type) {
		if (match(name))
		{
			token.type = type;
			skip(name.size());
			return true;
		}

		return false;
	};

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

	if (eof())
	{
		return token;
	}

	// check for trivial one-char tokens
	if ((token.type = [&] {
		switch (*_cursor)
		{
		case '\n': return TokenType::EndOfLine;
		case '(':  return TokenType::ParameterListBegin;
		case ')':  return TokenType::ParameterListEnd;
		case '{':  return TokenType::FunctionBodyBegin;
		case '}':  return TokenType::FunctionBodyEnd;
		case '[':  return TokenType::PropertyBodyBegin;
		case ']':  return TokenType::PropertyBodyEnd;
		case '=':  return TokenType::Assign;
		case ':':  return TokenType::TypeConstraintSeparator;
		case ',':  return TokenType::Separator;
		default:   return TokenType::EndOfFile;
		}
	}()) != TokenType::EndOfFile)
	{
		skip();
		return token;
	}

	if (token_check("break",    TokenType::Break)
	 || token_check("continue", TokenType::Continue)
	 || token_check("return",   TokenType::Return))
	{
		return token;
	}

	if (is_first_identifier_char(*_cursor))
	{
		auto begin = _cursor;
		skip_until([&] { return !is_identifier_char(*_cursor); });
		_values.value_string = {begin, _cursor};
		token.type = TokenType::Identifier;
		return token;
	}

	// TODO: handle literals

	return token;
}
}
