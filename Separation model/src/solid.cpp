#include "solid.h"
#include <math.h>
#include "base/commonData.h"
#include "base/settings.h"
#include "base/climate.h"
Solid::Solid()
{

	

	
	string cover="";
  
    Kn=0;
	Kh=0;
	NH3aq=0;
	 NH3g=0;
	NH3emis=0;
	rC=0;
	Totalemis=0;
	TAN=0;
	fileAccess hd;
	hd.changeDir(globalSettings->inputDir);
	commonData data;
	data.readFile("Solid.data");
	data.FindItem("TANmol", &TANmol);
	data.FindItem("pH", &pH);
	data.FindItem("rA", &rA);
	data.FindItem("area", &area);
	data.FindItem("coverlist", &coverlist);

	hd.changeDir(globalSettings->outputDir);

	outputFile.open ("Solid.xls");
	outputFile<<"Kn"<<'\t'<<"Kh"<<'\t'<<"NH3aq"<<'\t'<<"NH3g"<<'\t'<<"NH3emis"<<'\n';
	/*
    new PullVariable<double>("TAN", &TAN, this, "TAN in slurry (kg)");
    new Parameter<double>("TANmol", &TANmol, 0.26, this, "mol of TAN - assumed that 1 kg slurry is equal to 1 liter (mol/liter");
    new Parameter<double>("pH", &pH, 7.8, this, "pH in slurry");
    new Parameter<double>("rA", &rA, 20, this, "Description");
    new Parameter<int>("area", &area, 1000, this, "Surface area of slurry tank");
    new Parameter<QString>("coverlist", &coverlist, QString ("((non 0)(plastic 110))"), this, "List of different covers of slurry tank");
    new Parameter<QString> ("Cover", &cover, QString ("non"), this, "Default cover");
    new PullVariable<double>("Kn", &Kn, this, "Ammonium-ammonia equilibrium constant");
    new PullVariable<double>("Kh", &Kh, this, "Henry's law coefficient");
    new PullVariable<double>("NH3aq", &NH3aq, this, "ammonia in solution");
    new PullVariable<double>("NH3g", &NH3g, this, "Gaseous ammonia in equlibrium (mol/L)");
    new PullVariable<double>("NH3emis", &NH3emis, this, "Emission of ammonia pr m2 (kg/m2/day)");
    new PushVariable<double> ("TANin", &TANin, this, "TAN from the separtion");
    new PushVariable<double> ("Totalemis", &Totalemis, this, "Total ammonia emission pr day");
	*/
}
void Solid::initialize(){
}
Solid::~Solid()
{
	outputFile.close();
}
void Solid::reset() {
    TAN=0;


}

void Solid::update(double TANin) {
    TAN += TANin;

	
    double K_temp=theClimate->tmean+ 273.15;/*Temperatur i Kelvin*/
   double  Kn = pow(10, -0.09018-(2729.92/K_temp)); /*No dimentions*/
    TANmol = TAN/14; /* mol - assumed that 1 kg slurry is equal to 1 liter*/
    Kh = pow(10,-1.69+(1477.7/K_temp)); /*No dimentions*/
    NH3aq = TANmol/((1+(pow(10,-pH)/Kn)));/* mol/L*/
    NH3g = NH3aq/Kh; /*mol*/
    NH3emis = (14*NH3g/(rA+rC))*60*60*24; /* Kg NH3-N/m2/day*/
    Totalemis = NH3emis*area;
    TAN-= NH3emis;
    outputFile<<Kn<<'\t'<<Kh<<'\t'<<NH3aq<<'\t'<<NH3g<<'\t'<<NH3emis<<'\n';
}

