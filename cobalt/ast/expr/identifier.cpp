#include "call.hpp"
#include "identifier.hpp"
#include "../../log.hpp"

namespace co::ast
{
ExprNode parse_identifier_expr(Lexer& lexer)
{
	string name = std::get<StringValue>(lexer.value);
	auto token = lexer.token();

	if (token.type == TokenType::ParenLeft) // function call
	{
		vector<ExprNode> parameters;

		for (;;)
		{
			token = lexer.token();

			/*if (auto expr = parse_expression())
			{
				parameters.push_back(expr);
			}*/

			if (token.type == TokenType::ParenRight)
			{
				break;
			}

			if (token.type != TokenType::Separator)
			{
				error(&token, lexer.source_info) <<
					"unexpected token in function call\n";

				if (token.type == TokenType::Colon)
				{
					note(nullptr, lexer.source_info) <<
						"constraints only apply to declarations\n";
				}

				return {};
			}
		}

		return ExprNode{new CallExpr{name, std::move(parameters)}};
	}

	lexer.token();

	return {};
}
}
