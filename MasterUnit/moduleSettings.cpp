#include "moduleSettings.h"
#include <string.h>
moduleSettings::moduleSettings(bool con, 
	char* name, 
	char desiredRutine,
	char* activationTime,
	char* rutine1,
	char* rutine2,
	char* rutine3,
	char* rutine4)
{
    isConnected_ = con;
    unitName_ = name;
    desiredRutine_ = desiredRutine;
    
    for (size_t i = 0; i < 6; i++)
        activationTime_[i] = activationTime[i];

    rutine1_ = rutine1;
    rutine2_ = rutine2;
    rutine3_ = rutine3;
    rutine4_ = rutine4;
    
}

moduleSettings::moduleSettings(char adress)
{
    //Constructor with the 4 different units
    switch (adress)
    {
        case '1':
        {
            isConnected_ = true;
            unitName_ = "Kaffemaskine";
            desiredRutine_ = '1';
            strcpy(activationTime_, "00:00");
            activationHour_ = 0;
            activationMinute_ = 0;
            rutine1_ = "Cappucino";
            rutine2_ = "Espresso";
            rutine3_ = "Americano";
            rutine4_ = "Latte";
            adress_ = '1';
            break;
        }
        case '2':
        {
            isConnected_ = false;
            unitName_ = "Lysenhed";
            desiredRutine_ = '1';
            strcpy(activationTime_, "00:00");
            activationHour_ = 0;
            activationMinute_ = 0;
            rutine1_ = "25%";
            rutine2_ = "50%";
            rutine3_ = "75%";
            rutine4_ = "100%";
            adress_ = '2';
            break;
        }
        case '3':
        {
            isConnected_ = true;
            unitName_ = "Gardin";
            desiredRutine_ = '1';
            strcpy(activationTime_, "00:00");
            activationHour_ = 0;
            activationMinute_ = 0;
            rutine1_ = "Lukket";
            rutine2_ = "Lav";
            rutine3_ = "Mellem";
            rutine4_ = "Uafbrudt";
            adress_ = '3';
            break;
        }
        case '4':
        {
            isConnected_ = true;
            unitName_ = "Alarm";
            desiredRutine_ = '1';
            strcpy(activationTime_, "00:00");
            activationHour_ = 0;
            activationMinute_ = 0;
            rutine1_ = "Blid";
            rutine2_ = "Naturlig";
            rutine3_ = "Kraftig";
            rutine4_ = "Ekstrem";
            adress_ = '4';
            break;
        }
        default:
        break;
        
    }
}

moduleSettings::moduleSettings(){

    unitName_ = "name";
    desiredRutine_ = '1';
    strcpy(activationTime_, "00:00");
    rutine1_ = "rutine1";
    rutine2_ = "rutine2";
    rutine3_ = "rutine3";
    rutine4_ = "rutine4";

}
