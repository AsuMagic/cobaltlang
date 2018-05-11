#include <iostream>
#include "cobalt/lexer.hpp"

int main()
{
	co::Lexer lex{
		"f := (x : int){return x * x}"
	};

	co::Token tok;
	while ((tok = lex.next_token()).type != co::TokenType::EndOfFile)
	{
		std::cout << "rest: '" << &(*tok.offset) << "', type = " << int(tok.type) << '\n';
	}
}
