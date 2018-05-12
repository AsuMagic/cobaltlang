#ifndef LOG_HPP
#define LOG_HPP

#include "lexer.hpp"
#include "utility.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

namespace co
{
struct MessageContext
{
	std::string_view source_line;
	unsigned line, column;
};

MessageContext get_message_context(Token& token, SourceInfo sinfo);

void log_message_header(Token* token, SourceInfo source, std::string_view type);
std::ostream& error(Token* token, SourceInfo source);
std::ostream& warning(Token* token, SourceInfo source);
std::ostream& note(Token* token, SourceInfo source);
}

#endif // LOG_HPP
