#ifndef SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP
#define SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP


#include "Sphere.hpp"
#include "SolarSystemModel.hpp"


class SolarSystemVTKInteractor
{
public:
	SolarSystemVTKInteractor();
	~SolarSystemVTKInteractor();

	void Step();

private:
	SolarSystemModel m_solarSystemModel;
};


#endif //SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP
