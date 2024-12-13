#include "Star.hpp"
#include <boost/dll/runtime_symbol_info.hpp>

namespace StellarSystem
{
	constexpr int SUN_SCALE_FACTOR = 4;


	Star::Star(double radius, double mass)
		: CosmicBody(radius, mass)
	{
		Init();
	}

	Star::~Star()
	{
	}

	void Star::Init()
	{
	}
}

