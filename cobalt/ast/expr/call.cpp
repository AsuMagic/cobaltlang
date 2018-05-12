#include "call.hpp"

namespace co::ast
{
CallExpr::CallExpr(std::string_view name, vector<ExprNode> parameters) :
	_name{name},
	_parameters{std::move(parameters)}
{}
}
