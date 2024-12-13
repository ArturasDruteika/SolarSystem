#ifndef STELLARMODEL_STAR_HPP
#define STELLARMODEL_STAR_HPP


#if defined(_WIN32)
    #if defined(STELLARMODEL_EXPORT)
        #define STELLARMODEL_API __declspec(dllexport)
    #else
        #define STELLARMODEL_API __declspec(dllimport)
    #endif /* STELLARMODEL_API */
    #define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
    // GCC
    #define STELLARMODEL_API __attribute__((visibility("default")))
#endif


#include "CosmicBody.hpp"


namespace StellarSystem
{
    class STELLARMODEL_API Star : public CosmicBody
    {
    public:
	    Star(double radius, double mass);
	    ~Star();

    private:
	    void Init();

    };
}


#endif //STELLARMODEL_STAR_HPP
