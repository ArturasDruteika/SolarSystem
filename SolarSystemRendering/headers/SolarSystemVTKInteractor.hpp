#ifndef SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP
#define SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP


#include "Planet.hpp"
#include "Star.hpp"


class SolarSystemVTKRenderer
{
public:
	SolarSystemVTKRenderer();
	~SolarSystemVTKRenderer();

private:
	std::map<int, Star> m_starsMap;
	std::map<int, Planet> m_planetsMap;
};


#endif //SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP
