#include <vector>

namespace AndromedaEngine
{
	//Allows you to search through all iterators, rather than just few of them
	template<typename Init, typename Pr> inline
		std::vector<Init> find_all(Init first, Init last, Pr pred)
	{
		std::vector<Init> result;

		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				result.push_back(first);
			}
		}

		return result;
	}
}