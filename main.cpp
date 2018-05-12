#include <iostream>
#include "cobalt/lexer.hpp"

int main()
{
	co::Lexer lex{
		"a : int = 3 // this shall be ignored\n"
		"/* this is a multiline comment\n"
		"   test */\n"
		"~ // invalid line because of bad token\n"
		"f := (x : int) {return 42 + 3.05 * x}\n"
	};

	co::Token tok;
	while ((tok = lex.next_token()).type != co::TokenType::EndOfFile)
	{
		std::cout << "token: '" << tok.view << "', type = " << int(tok.type) <<
			/*", intval = " << lex.value_int <<
			", floatval = " << lex.value_int <<
			", stringval = " << lex.value_string << */'\n';
	}
}
