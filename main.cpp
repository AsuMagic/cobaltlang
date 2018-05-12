#include <iostream>
#include "cobalt/lexer.hpp"

int main()
{
	auto src =
		"s : int = 3 // this shall be ignored\n"
		"a := \"hi\\\"\"\n"
		"/* this is a multiline comment\n"
		"   test */\n"
		"~ // invalid line because of bad token\n"
		"f := (x : int) {return 42 + 3.05 * x}";

	co::Lexer lex{src};

	std::cout << "=== SOURCE ===\n" << src << "\n=== END SOURCE ===\n\n";

	co::Token tok;
	while ((tok = lex.next_token()).type != co::TokenType::EndOfFile)
	{
		std::cout << "token: '" << tok.view << "', type = " << int(tok.type) <<
			/*", intval = " << lex.value_int <<
			", floatval = " << lex.value_int <<
			", stringval = " << lex.value_string << */'\n';
	}
}
