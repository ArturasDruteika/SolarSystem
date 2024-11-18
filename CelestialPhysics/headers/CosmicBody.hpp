#ifndef CELESTIALPHYSICS_COSMICBODY_HPP
#define CELESTIALPHYSICS_COSMICBODY_HPP


class CosmicBody
{
public:
	CosmicBody(double radius, double mass);
	~CosmicBody();

	double GetRadius();
	void SetRadius(double radius);
	double GetMass();
	void SetMass(double mass);

private:
	double m_radius;
	double m_mass;
};


#endif //CELESTIALPHYSICS_COSMICBODY_HPP