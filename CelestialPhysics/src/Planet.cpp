#include "Planet.hpp"
#include "ObjectsComponents.hpp"


Planet::Planet()
	: m_planetCount{0}
	, m_planetsMap{}
{
}

Planet::~Planet()
{
}

void Planet::OnNewPlanet(const ObjectAttributes& objectAttributes)
{
	m_planetsMap.insert({m_planetCount, objectAttributes});
	m_planetCount++;
}
