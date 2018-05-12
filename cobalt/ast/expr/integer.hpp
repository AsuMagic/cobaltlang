#ifndef AST_EXPR_INTEGER_HPP
#define AST_EXPR_INTEGER_HPP

#include "../expr.hpp"

namespace co::ast
{
struct IntegerExpr : Expr
{
	IntegerValue _value;

public:
	IntegerExpr(IntegerValue value);
};

ExprNode parse_number_expr(Lexer& lexer);
}

#endif
