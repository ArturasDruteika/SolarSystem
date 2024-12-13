#ifndef STELLARMODEL_OBJECTSCOMPONENTS_HPP
#define STELLARMODEL_OBJECTSCOMPONENTS_HPP


namespace StellarSystem
{
    typedef struct
    {
        double radius; // km
        double mass; // kg
        double semiMajorAxis; // km
        double semiMinorAxis; // km
        double rotationalPeriod; // days
        double inclination; // radians (for orbit calculation) / degrees (for rendering)
        double tilt; // degrees
    } PlanetAttributes;
}


#endif // STELLARMODEL_OBJECTSCOMPONENTS_HPP
