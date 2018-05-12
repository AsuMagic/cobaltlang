#include "integer.hpp"

namespace co::ast
{
ExprNode parse_number_expr(Lexer& lexer)
{
	ExprNode ret{new IntegerExpr(std::get<IntegerValue>(lexer.value))};
	lexer.token();
	return ret;
}

IntegerExpr::IntegerExpr(IntegerValue value) :
	_value{value}
{}

}
