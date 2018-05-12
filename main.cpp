#include <iostream>
#include "cobalt/parser.hpp"
#include "cobalt/log.hpp"
#include "cobalt/ast/expr/identifier.hpp"

int main()
{
	//std::ios_base::sync_with_stdio(false);

	auto src =
		"s : int = 3 // this shall be ignored\n"
		"a := \"hi\\\", hello\"\n"
		"/* this is a multiline comment\n"
		"   test */\n"
		"~ // invalid line because of bad token\n"
		"f := (x : int) { return 4200000000000000000000000000000000 + 3.05 * x }";

	/*co::SourceInfo info{src, "<commandline>"};

	try
	{
		co::parse_program(info);
	}
	catch(...)
	{
		co::error(nullptr, {}) << "compiler crash: uncaught exception.\n";
	}*/

	std::string in = "";

	for(;;)
	{
		std::cout << "cobalt> ";
		std::getline(std::cin, in);

		if (in == "exit")
		{
			break;
		}

		try
		{
			co::Lexer lex{{in, "<shell>"}};
			lex.token();
			co::ast::parse_identifier_expr(lex);
		}
		catch (std::exception& e)
		{
			co::error(nullptr, {}) << "internal compiler error: " << e.what();
		}

		std::cout << '\n';
	}
}
