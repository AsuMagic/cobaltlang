#ifndef AST_EXPR_IDENTIFIER_HPP
#define AST_EXPR_IDENTIFIER_HPP

#include "../expr.hpp"

namespace co::ast
{
ExprNode parse_identifier_expr(Lexer& lexer);
}

#endif
