#include "liquid.h"
#include "base/climate.h"
#include "base/commonData.h"
#include "base/commonData.h"
#include "base/settings.h"
Liquid::Liquid()
{
		string output;
		fileAccess hd;
		hd.changeDir(globalSettings->outputDir);

		outputFile.open ("Liquid.xls");
		outputFile<<"TAN"<<'\t'<<"Kn"<<'\t'<<"Kh"<<'\t'<<"NH3aq"<<'\t'<<"NH3g"<<'\t'<<"NH3emis"<<'\t'<<"Mass"<<'\t'<<"TANCon"<<'\n';


		cout<<hd.changeDir(globalSettings->inputDir)<<endl;;
		commonData data;

		data.readFile("Liquid.data");
		data.FindItem("TANmol", &TANmol);
		data.FindItem("pH", &pH);
		data.FindItem("rA", &rA);
		data.FindItem("area", &area);
		data.FindItem("coverlist", &coverlist);
		data.FindItem("cover", &cover);
		TAN =0;
     
		ofstream outputFile;

        Kn=0;
		Kh=0;
		NH3aq=0;
		NH3g=0;
		NH3emis=0;
		rC=0;
		Totalemis=0;
		Mass=0;
		TANCon=0;
		
       /* new Parameter<double>("TANmol", &TANmol, 0.26, this, "mol of TAN - assumed that 1 kg slurry is equal to 1 liter (mol/liter");
        new Parameter<double>("pH", &pH, 7.8, this, "pH in slurry");
        new Parameter<double>("rA", &rA, 20, this, "Description");
        new Parameter<int>("area", &area, 1000, this, "Surface area og slurry tank");
        new Parameter<QString>("coverlist", &coverlist, QString ("((non 0) (crust 100) (plastic 110))"), this, "List of different covers of slurry tank");
        new Parameter<QString> ("cover", &cover, QString ("non"), this, "Default cover");*/
       /* new PullVariable<double>("TAN", &TAN, this, "TAN in slurry (kg)");
        new PullVariable<double>("Kn", &Kn, this, "Ammonium-ammonia equilibrium constant");
        new PullVariable<double>("Kh", &Kh, this, "Henry's law coefficient");
        new PullVariable<double>("NH3aq", &NH3aq, this, "ammonia in solution");
        new PullVariable<double>("NH3g", &NH3g, this, "Gaseous ammonia in equlibrium (mol/L)");
        new PullVariable<double>("NH3emis", &NH3emis, this, "Emission of ammonia pr m2 (kg/m2/day)");
        new PullVariable<double>("Mass", &Mass, this, "Mass of slurry (Tonnes)");
        new PullVariable<double>("TANCon", &TANCon, this, "Concentration of TAN in liquid (Kg/Kg)");
        new PushVariable<double> ("Totalemis", &Totalemis, this, "Total ammonia emission pr day");
        new PushVariable<double> ("TANin", &TANin, this, "TAN from the separtion");
        new PushVariable<double> ("Massin", &Massin, this, "Mass of slurry from the separtion (tonnes)");
		*/
}
Liquid::~Liquid()
{
	outputFile.close();
}
void Liquid::initialize(){
//    weather=seekOne<Model*>("weather");
}

void Liquid::reset() {
    TAN=0;
    Mass=0;

//    update();
//    if (cover == "Non")
//      rC=0 ; /*1*/
//     else if (cover == "Crust")
//       rC=100; /*0.22*/
//    else if (cover== "Plastic")
//       rC=110;/*0.17*/
//    else if (cover=="tent")
//       rC=200; /*0.11*/
//    else if (cover== "concrete")
//        rC=200; /*0.11*/

/*    QMap<QString,double> decoded;
       decoded = decodeList<QString,double>(coverlist);
       if (!decoded.contains(cover)) throw Exception ("cover '" +cover+ "' not valid");
       rC=decoded [cover];
	   */


}

void Liquid::update(double tan,double mass) {
    TAN += tan;
    Mass += mass;
    TANCon = TAN/(Mass * 1000); /*Concentration of TAN in liquid (Kg TAN/Kg Slurry)*/
    double K_temp=theClimate->tmean+ 273.15;/*Temperatur i Kelvin*/

    Kn = pow(10, -0.09018-(2729.92/K_temp)); /*No dimentions*/
    TANmol = TANCon/14; /* mol/L - assumed that 1 kg slurry is equal to 1 liter*/
    Kh = pow(10,-1.69+(1477.7/K_temp)); /*No dimentions*/
    NH3aq = TANmol/((1+(pow(10,-pH)/Kn)));/* mol/L*/
    NH3g = NH3aq/Kh; /*mol/L*/
    NH3emis = (14*NH3g/(rA+rC))*60*60*24; /* Kg NH3-N/m2/day*/
    Totalemis = NH3emis*area;
    TAN-= Totalemis;
	outputFile<<TAN<<'\t';
	outputFile<<Kn<<'\t';
	outputFile<<Kh<<'\t';
	outputFile<<NH3aq<<'\t';
	outputFile<<NH3g<<'\t';
	outputFile<<NH3emis<<'\t';
	outputFile<<Mass<<'\t';
	outputFile<<TANCon<<'\n';



}



