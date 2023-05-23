#pragma once
#include "pcSettings.h"

class userIF
{
public:
	userIF();
	char displayMain(); //
	void printMain();

	void displayConfig(pcSettings& config);
	void printConfig(pcSettings& config);

	void displayRutineSaved();
	void printRutineSaved();
	void saveRutine(int rutinenumber);

	void inputTime(pcSettings & tempoary);

	void displaySavedRutines();
	void displayExitRutine();
	void displayExitWithoutSavingRutine();


	void setCopy(pcSettings* currentConfig, pcSettings savedRutines[5][4]);
	

	void setSavedName();
	void getSavedName();

	pcSettings* getConfig();
	pcSettings(*getSavedArray())[4];
	std::string* getSavedArrayNames();


private:
	pcSettings unitConfig_[4];
	pcSettings oldConfig_[4];
	pcSettings savedArray_[5][4];
	std::string savedArrayNames_[5] = { "Smart rutine 1", "Smart rutine 2", "Smart rutine 3", "Smart rutine 4", "Smart rutine 5" };

};





