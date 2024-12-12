#include "CosmicBody.hpp"


CosmicBody::CosmicBody(double radius, double mass)
	: m_radius{radius}
	, m_mass{mass}
{
}

CosmicBody::~CosmicBody()
{
}

double CosmicBody::GetRadius() const
{
	return m_radius;
}

double CosmicBody::GetMass() const
{
	return m_mass;
}