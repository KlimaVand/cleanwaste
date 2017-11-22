#ifndef __LIQUID
#define __LIQUID

#include "base/base.h"
#include "base/message.h"
#include "base/common.h"
#include <sys/stat.h>
#include "tools/fileAccess.h"
#include <iostream>
#include <fstream>

class Liquid
{
public: 
	Liquid();
	~Liquid();
	// standard methods
        void initialize();
        void reset();
	void update(double tan,double mass);

private:
	// parameters
        double TAN, pH, rA,TANmol;
        string cover, coverlist;

        int area;
		ofstream outputFile;

	// pull variables
        double Kn, Kh, NH3aq, NH3g, NH3emis, rC, Totalemis, Mass, TANCon;

};

#endif
