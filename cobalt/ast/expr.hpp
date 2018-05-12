#ifndef AST_EXPR_HPP
#define AST_EXPR_HPP

#include <memory>
#include <string>
#include <vector>
#include "../lexer.hpp"

namespace co::ast
{
struct Expr
{
	virtual ~Expr() = default;
};

using std::string;
using std::vector;
using ExprNode = std::unique_ptr<Expr>;
}

#endif // EXPR_HPP
