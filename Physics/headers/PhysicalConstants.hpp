#ifndef PHYSICS_PHYSICALCONSTANTS_HPP
#define PHYSICS_PHYSICALCONSTANTS_HPP


namespace Physics
{
	constexpr double M_PI = 3.141'592'653'589'793'238'46;
	constexpr double EARTH_ROTATIONS_PER_YEAR = 365.256'363'004; // days
	constexpr double GRAVITATIONAL_CONSTANT = 6.67430e-11; // m^3 kg^-1 s^-2
	constexpr double N_ORBIT_PTS = 10'000;
	constexpr int ECCENTRIC_ANOMALY_ITERATIONS = 10'000;
	constexpr double SOLAR_MASS = 1988416e24; // kg
	constexpr double KM = 1000.0; // meters in kilometer
}


#endif //PHYSICS_PHYSICALCONSTANTS_HPP
