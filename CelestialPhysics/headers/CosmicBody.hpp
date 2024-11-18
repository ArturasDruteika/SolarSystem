#ifndef CELESTIALPHYSICS_COSMICBODY_HPP
#define CELESTIALPHYSICS_COSMICBODY_HPP


class CosmicBody
{
public:
	CosmicBody(double radius, double mass);
	~CosmicBody();

	double GetRadius() const;
	double GetMass() const;

private:
	double m_radius;
	double m_mass;
};


#endif //CELESTIALPHYSICS_COSMICBODY_HPP