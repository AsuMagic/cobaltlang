#include <iostream>
#include "cobalt/lexer.hpp"

int main()
{
	co::Lexer lex{
		"a : int = 3\n"
		"f := (x : int) {return x * x}\n"
	};

	co::Token tok;
	while ((tok = lex.next_token()).type != co::TokenType::EndOfFile)
	{
		std::cout << "token: '" << tok.view << "', type = " << int(tok.type) << '\n';
	}
}
