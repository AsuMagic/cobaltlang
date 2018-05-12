#include <iostream>
#include "cobalt/lexer.hpp"
#include "cobalt/log.hpp"

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

	co::Lexer lex{{src, "<commandline>"}};

	std::cout << "=== SOURCE ===\n" << src << "\n=== END SOURCE ===\n\n";

	co::Token tok;
	try
	{
	while ((tok = lex.next_token()).type != co::TokenType::EndOfFile)
	{
		std::cout << "token: '" << tok.view << "', type = " << int(tok.type) <<
			/*", intval = " << lex.value_int <<
			", floatval = " << lex.value_int <<
			", stringval = " << lex.value_string << */'\n';
	}
	}
	catch(...)
	{
		co::error(nullptr, {}) << "compiler crash: uncaught exception.\n";
	}
}
