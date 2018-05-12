#include "log.hpp"

namespace co
{
MessageContext get_message_context(Token& token, SourceInfo sinfo)
{
	MessageContext ctx{};

	// look up the line and column offsets
	auto i = sinfo.source.begin();
	for (; i != sinfo.source.end() && i != token.view.begin(); ++i)
	{
		if (*i == '\n')
		{
			++ctx.line;
			ctx.column = 0;
		}
		else
		{
			++ctx.column;
		}
	}

	// look up the line source
	ctx.source_line = make_view(sinfo.source.begin(), sinfo.source.end());

	for (auto j = i; j != sinfo.source.begin(); --j)
	{
		// look up the past line ending
		if (*j == '\n')
		{
			ctx.source_line = make_view(j + 1, ctx.source_line.end());
			break;
		}
	}

	for (auto j = i; j != sinfo.source.end(); ++j)
	{
		// look up the next line ending
		if (*j == '\n')
		{
			ctx.source_line = make_view(ctx.source_line.begin(), j);
		}
	}

	return ctx;
}

void log_message_header(Token* token, SourceInfo source, std::string_view type)
{
	std::cout << '\n';

	if (token)
	{
		auto ctx = get_message_context(*token, source);

		std::cout << ctx.source_line << '\n';

		for (unsigned i = 0; i < ctx.column; ++i)
		{
			std::cout << ' ';
		}

		for (unsigned i = 0; i < token->view.size(); ++i)
		{
			std::cout << '^';
		}

		std::cout << '\n' << type << ':' << source.source_fname << ':' << ctx.line << ':' << ctx.column << ": ";
	}
	else
	{
		std::cout << type << ": ";
	}
}

std::ostream& error(Token* token, SourceInfo source)
{
	log_message_header(token, source, "error");
	return std::cout;
}

std::ostream& warning(Token* token, SourceInfo source)
{
	log_message_header(token, source, "warning");
	return std::cout;
}

std::ostream& note(Token* token, SourceInfo source)
{
	log_message_header(token, source, "note");
	return std::cout;
}
}
