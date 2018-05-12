#ifndef AST_EXPR_CALL_HPP
#define AST_EXPR_CALL_HPP

#include "../expr.hpp"
#include <vector>

namespace co::ast
{
struct CallExpr : Expr
{
	string _name;
	vector<ExprNode> _parameters;

public:
	CallExpr(std::string_view name, vector<ExprNode> parameters);
};
}

#endif
