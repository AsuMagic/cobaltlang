#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include "ast/expr.hpp"
#include "lexer.hpp"
#include "log.hpp"

namespace co
{
std::unique_ptr<ast::Expr> parse_program(SourceInfo info)
{
	Lexer lexer{info};

	auto token = lexer.token();

	switch (token.type)
	{
	default:
		error(&token, info) << "Unexpected token\n";
	}

	return {};
}
}

#endif // PARSER_HPP
