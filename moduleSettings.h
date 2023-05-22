#pragma once
#include <string.h>
class moduleSettings
{
public:
	moduleSettings(
		bool con, 
	char* name, 
	char desiredRutine_,
	char* activationTime_,
	char* rutine1_,
	char* rutine2_,
	char* rutine3_,
	char* rutine4_
	);
	moduleSettings();

	moduleSettings(char adress);
	
	bool isConnected_;
	char* unitName_;
	char desiredRutine_;
	char activationTime_[6];
	int activationHour_;
	int activationMinute_;
	char* rutine1_;
	char* rutine2_;
	char* rutine3_;
	char* rutine4_;



	
	char adress_;
};

