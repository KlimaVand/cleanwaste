#include "separator.h"
#include "base/commonData.h"
#include "base/settings.h"
using namespace std;




Separator::Separator()
{
		theliquid=new  Liquid();
		thesolid =new Solid();
		fileAccess hd;
		hd.changeDir(globalSettings->inputDir);


		commonData data;
		data.readFile("Separator.data");
		data.FindItem("slurryTotal", &slurryTotal);
		data.FindItem("slurryTAN", &slurryTAN);
		data.FindItem("periode", &periode);
		data.FindItem("sepindexTAN", &sepindexTAN);
		data.FindItem("sepindexVol", &sepindexVol);
		//slurryTotal=0; why read in a value and then set it to zero?



        days=0;


        TANin=0;
		Massin=0;
   /*     new Parameter<double>("slurryTotal", &slurryTotal, 176., this, "Amount of slurry separated (Mg)");
        new Parameter<double>("slurryTAN", &slurryTAN, 3.7, this, "koncentation of TAN in raw slurry (kg/Mg)");
        new Parameter<int>("periode", &periode, 14, this, "interval of separation procedure");
        new Parameter<double>("sepindexTAN", &sepindexTAN, 0.11, this, "separation index TAN (Hjorth et al., 2010)");
        new Parameter<double>("sepindexVol", &sepindexVol, 0.11, this, "separation index TAN (Hjorth et al., 2010)");*/
}
void Separator::initialize(){
//    liquid=seekOneChild<Model*>("liquid");
  //  solid=seekOneChild<Model*>("solid");
}

void Separator::reset() {
    days=0;
    load();

}
void Separator::load (){

	//calculate amount of TAN input in raw slurry
    TANin= slurryTAN * slurryTotal;
   // solid->pushVariable<double> ("TANin", (TANTotal*sepindexTAN));
   // solid->pushVariable<double> ("Massin", (slurryTotal*sepindexVol));
//    liquid->pushVariable<double> ("TANin", (TANTotal*(1-sepindexTAN)));
  //  liquid->pushVariable<double> ("Massin", (slurryTotal*(1-sepindexVol)));
	//calculate amount of TAN etc in the different fractions
	double TANtoSolid = sepindexTAN * TANin;
	double TANtoLiquid=TANin-TANtoSolid;
	double VolumeToSolid=sepindexVol *slurryTotal;
	double VolumeToLiquid = slurryTotal - VolumeToSolid;
    theliquid->update(TANtoLiquid,VolumeToLiquid);
    thesolid->update(TANtoSolid);

}

void Separator::update() {
    //slurryTAN = slurryTotal*3.7;
    days++;
    if (days%periode==0)
        load();

}


