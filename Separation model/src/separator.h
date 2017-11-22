
#ifndef SEPARATION_SEPARATOR
#define SEPARATION_SEPARATOR

#include "liquid.h"
#include "solid.h"

class Separator
{

public: 
	Separator();
	// standard methods
        void initialize();
	void reset();
	void update();

private:
	// parameters
        double slurryTAN, sepindexTAN,sepindexVol, slurryTotal;
        int periode;

        Liquid *theliquid;
        Solid *thesolid;

        int days;
        void load();

        double TANin, Massin;

};


#endif
