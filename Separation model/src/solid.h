#ifndef SEPARATION_SOLID
#define SEPARATION_SOLID
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Solid
{
public: 
	Solid();
	~Solid();
	// standard methods
        void initialize();
        void reset();
	void update(double TANin);

private:
	// parameters
        double TAN;
		double pH;
		double rA;
		ofstream outputFile;
		double TANmol;
       
		

        int area;
		string coverlist;
		 string cover;
        // pull variables
        double Kn, Kh, NH3aq, NH3g, NH3emis, rC, Totalemis;
        //UniSim::Model *weather;


};
#endif
