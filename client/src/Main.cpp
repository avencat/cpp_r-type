#include "Core.hpp"

int main(int ac, char **av)
{
	Core core;

	static_cast<void>(av);
	if (!core.run(ac > 1 ? true : false))
		return (-1);
	return 0;
}
