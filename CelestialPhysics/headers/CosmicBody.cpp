#include "CosmicBody.hpp"


CosmicBody::CosmicBody(double radius, double mass)
	: m_radius{radius}
	, m_mass{mass}
{
}

CosmicBody::~CosmicBody()
{
}

double CosmicBody::GetRadius()
{
	return m_radius;
}

void CosmicBody::SetRadius(double radius)
{
	m_radius = radius;
}

double CosmicBody::GetMass()
{
	return m_mass;
}

void CosmicBody::SetMass(double mass)
{
	m_mass = mass;
}
