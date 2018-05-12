#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string_view>

namespace co
{
    template<class RAIt>
    std::string_view make_view(RAIt a, RAIt b)
	{
		return {a, size_t(std::distance(a, b))};
	}
}

#endif // UTILITY_HPP
