#include "separator.h"
#include "base/bstime.h"
#include "base/climate.h"
#include "base/commonData.h"
#include "base/settings.h"
#include "base/controlParameters.h"
#include <string.h>
#include <stdio.h>
bsTime theTime;
message * theMessage;
climate * theClimate;
settings * globalSettings;
controlParameters * theControlParameters;
int main(int argc, char **argv)
{
	theMessage                   = new message;
	char FN1[200],FN2[200];
	string logfile="logfile.txt";
	string warning="warnings.txt";
	theControlParameters = new controlParameters;
	strcpy(FN2,logfile.c_str());
	strcpy(FN1,warning.c_str());
	theMessage->InitMessage(FN1,FN2);
	theClimate                   = new climate(0,0);
	fileAccess hd;


	globalSettings=new settings();
	commonData SystemData;
	SystemData.readFile("system.dat");
	string inputDir;
	SystemData.FindItem("inputDir",&inputDir);

	string outpitDir;
	SystemData.FindItem("outputDir",&outpitDir);
	globalSettings->outputDir=outpitDir;
	globalSettings->inputDir=inputDir;
	int updates;
	SystemData.FindItem("updates",&updates);
	char climatePath[200];
	strcpy(climatePath,inputDir.c_str());

	theClimate->InitClimate(climatePath,"foulum.clm");


	Separator instance;
	for(int i=0;i<updates;i++)
	{
		instance.update();
	}
}
