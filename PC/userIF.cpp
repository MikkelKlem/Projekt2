#include "userIF.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <istream>
#include <Windows.h>

using namespace std;


userIF::userIF()
{
	//Start up rutine
	cout << "Program starting... \n\n";
	system("Color 70");							//White background, black text
	getSavedName();								//Getting savedArrayNames from txt file
}

char userIF::displayMain()
{
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));			//Clear the input buffer
	char choice = '0';													//The user choice in the main menu
	while (choice != 'q' && choice != 'g')
	{
		printMain();
		choice = _getch();
		switch (choice)
		{
		case '1':														//Unit 1
		{
			if (unitConfig_[0].getStatus() == false)
			{
				MessageBox(0, L"Enhed ikke tisluttet", L"UI error", MB_OK);
				break;
			}
			else
			{
				displayConfig(unitConfig_[0]);
				break;
			}
		}
		case '2':														//Unit 2
		{
			if (unitConfig_[1].getStatus() == false)
			{
				MessageBox(0, L"Enhed ikke tisluttet", L"UI error", MB_OK);
				break;
			}
			else
			{
				displayConfig(unitConfig_[1]);
				break;
			}
		}
		case '3':														//Unit 3
		{
			if (unitConfig_[2].getStatus() == false)
			{
				MessageBox(0, L"Enhed ikke tisluttet", L"UI error", MB_OK);
				break;
			}
			else
			{
				displayConfig(unitConfig_[2]);
				break;
			}
		}
		case '4':														//Unit 4
		{
			if (unitConfig_[3].getStatus() == false)
			{
				MessageBox(0, L"Enhed ikke tisluttet", L"UI error", MB_OK);
				break;
			}
			else
			{
				displayConfig(unitConfig_[3]);
				break;
			}
		}
		case '5':														//Save rutine
		{
			displayRutineSaved();
			break;
		}
		case '6':														//Load saved rutines
		{
			displaySavedRutines();
			break;
		}
		case 'g':														//Exit and save
		{	
			displayExitRutine();
			break;
		}
		case 'q':														//Exit without saving
		{
			displayExitWithoutSavingRutine();
			break;
		}
		default:														//Play "alert windows" sound
		{	
			cout << "\a";
			break;
		}
		}
	}
	return choice;
}

void userIF::printMain()
{
	system("cls");
	cout << "			SMART RUTINE - main menu\n\n\n";
	cout << "V\x91lg enhed at konfigurere\n\n";
	for (size_t i = 0; i < 4; i++)
	{
		if (unitConfig_[i].getStatus() == true)
			cout << endl << i+1 << " -	" << unitConfig_[i].getName();
		else
			cout << endl << i+1 << " -	ENHED IKKE TILSLUTTET";
	}
	cout << "\n\n\n\n";
	cout << "5 - Gem nuv\x91rende rutine" << "          6 - Indlæs gemte rutiner \n\n";
	cout << "\n\n";
	cout << "'g' for at gemme og afslutte konfiguringen" << "                  "
		 << "'q' for at afslutte uden at gemme";
}

void userIF::displayConfig(pcSettings& config)
{
	char choice = '0';
	pcSettings temp = config;
	string time;
	this->printConfig(config);
	
	
	do
	{
		choice = _getch();
		switch (choice)
		{
		case '1':										//Change time
		{
			inputTime(temp);
				break;
		}
		case '2':										//Setrutine to rutine 1
		{
			temp.setRutine('1');
			this->printConfig(temp);
			break;
		}
		case '3':										//Setrutine to rutine 2
		{
			temp.setRutine('2');						
			this->printConfig(temp);
			break;
		}
		case '4':										//Setrutine to rutine 3
		{
			temp.setRutine('3');
			this->printConfig(temp);
			break;
		}
		case '5':										//Setrutine to rutine 4
		{
			temp.setRutine('4');
			this->printConfig(temp);
			break;
		}
		case 'q':										//Quit without saving
		{
			system("cls");
			cout << "\n\n\n\nDu har afsluttet uden at gemme! ";
			Sleep(2000);
			system("cls");
			break;
		}
		case 'g':										//Quit and save
		{
			system("cls");
			cout << "\n\n\n\nDu har afsluttet og gemt! ";
			config = temp;
			Sleep(2000);
			system("cls");
			break;
		}
		default:										//Playing default windows "alert"
		{
			cout << "\a";
			this->printConfig(temp);
			break;
		}
		} // END OF SWITCH

	} while (choice != 'q' && choice != 'g');

}

void userIF::printConfig(pcSettings& config)
{
	//Printing to console
	system("cls");				
	cout << "Du konfigurer nu enhed: " << config.getName() << endl << endl;
	cout << "Parametre der kan \x91ndres:" << endl << endl;


	cout << "1 -	\x92ndre tidspunkt : Nuv\x91rende aktiveringstidspunkt:  " << config.getActivationTime() << endl 
		 <<	"        Hvis tiden s\x91ttes til 00:00 er enheden deaktiveret" << endl << endl;

	cout << "Rutine der udf\x9Bres\n";
	cout << "2 -	" << config.getRutine1() << endl;
	cout << "3 -	" << config.getRutine2() << endl;
	cout << "4 -	" << config.getRutine3() << endl;
	cout << "5 -	" << config.getRutine4() << endl << endl;

	cout << "'q' - Afslut uden at gemme " << "     'g' - Aflsut og gem";
	cout << "\n\nNuv\x91rende rutine valgt: ";

	switch (config.getRutine())				//Checking the active rutine
	{
		case '1':
		{
			cout << config.getRutine1();
			break;
		}
		case '2':
		{
			cout << config.getRutine2();
			break;
		}
		case '3':
		{
			cout << config.getRutine3();
			break;
		}
		case '4':
		{
			cout << config.getRutine4();
			break;
		}

	}


}

void userIF::displayRutineSaved()
{
	char choice = '0';
	while (choice != 'q')
	{ 

		this->printRutineSaved();
		choice = _getch();

		switch (choice)
		{
		case '1':
		{
			saveRutine(0);
			break;
			
		}
		case '2':
		{
			saveRutine(1);
			break;
		}
		case '3':
		{
			saveRutine(2);
			break;
		}
		case '4':
		{
			saveRutine(3);
			break;

		}
		case '5':
		{
			saveRutine(4);
			break;
		}
		case 'q':
			break;
		default:
		{
			MessageBox(0, L"Forkert knap trykket", L"Error", MB_OK);
			this->printRutineSaved();
			break;
		}
		} //END OF SWITCH
		

	}
}

void userIF::printRutineSaved()
{
	system("cls");
	cout << "Gem nuv\x91rende rutine:\n\n";
	cout << "Der kan gemmmes op til 5 unikker rutiner, tryk 'q' for at afslutte\n\n";
	cout << "\nRutine 1 - " << savedArrayNames_[0];
	cout << "\nRutine 2 - " << savedArrayNames_[1];
	cout << "\nRutine 3 - " << savedArrayNames_[2];
	cout << "\nRutine 4 - " << savedArrayNames_[3];
	cout << "\nRutine 5 - " << savedArrayNames_[4];

}

void userIF::saveRutine(int rutinenumber)
{
	
	//Checking if the name has been changed from the default... Not a perfect solution, but it works...
	if (savedArrayNames_[rutinenumber].substr(0, savedArrayNames_[rutinenumber].find(" ")) == "Smart")
	{
		while (true)
		{
			cout << "\n\nAngiv navn til rutine " << rutinenumber+1 << " (max 10 karakterer, 1 ord): ";
			std::string tempName; //Creating a tempoary name
			cin >> tempName;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n'); //Clearing the buffer up until '\n'
			
			if (tempName.length() <= 10 && 0 < tempName.length())		//Checking if name is within boundary
			{
				savedArrayNames_[rutinenumber] = tempName;				//Overwriting name and unitConfig
				for (size_t i = 0; i < 4; i++)
				{
					savedArray_[rutinenumber][i] = unitConfig_[i];
				}
				break;
			}
			else
			{
				MessageBox(0, L"Forkert input", L"Status", MB_OK);
			}
		}

	}
	else
	{
		//Overwriting rutine...
		cout << "\n\nDu er ved at overskrive rutine "<< rutinenumber+1 << " " << savedArrayNames_[rutinenumber] 
			 << "\nTryk 'j' for at gemme || Tryk 's' for at \x91ndre navn || Tryk alt andet for at annulere";
		char choice = _getch();
		if (choice == 's')
		{
			while (true)
			{
				cout << "\n\nAngiv navn til rutine 1 (max 10 karakterer, 1 ord): ";
				std::string tempName;
				cin >> tempName;
				if (tempName.length() <= 10 && 0 < tempName.length())	//Checking bounadary
				{
					savedArrayNames_[rutinenumber] = tempName;			//Changing name
					for (size_t i = 0; i < 4; i++)
					{
						savedArray_[rutinenumber][i] = unitConfig_[i];	//Overwriting rutine
					}
					break;
				}
				else
				{
					MessageBox(0, L"Forkert input", L"Status", MB_OK);
				}
			}
		}
		else if (choice == 'j')
		{
			for (size_t i = 0; i < 4; i++)
			{
				savedArray_[rutinenumber][i] = unitConfig_[i];			//Overwrite rutine, without changing name
			}
		}
	}
}

void userIF::inputTime(pcSettings& temp)
{
	string time;
	while (true)
	{
		cout << "\n\nIndtast nyt tidspunkt:  ";
		cin >> time;

		if (isdigit(time[0]) != 0 && isdigit(time[1]) != 0 && isdigit(time[3]) != 0
			&& isdigit(time[4]) != 0 && time[2] == ':' && time.length() == 5)		//Checking if format is correct
		{
			if (stoi(time) >= 0 && 23 >= stoi(time) &&								//Checking if hours is in range
				stoi(time.substr(3, 2)) >= 0 && 59 >= stoi(time.substr(3, 2)))		//Checking if minute is in range
			{
				temp.setActivationTime(time);
				this->printConfig(temp);
				break;
			}
			else
			{
				MessageBox(0, L"Forkert tid indtastet - prøv igen", L"Ny aktiveringstid", MB_OK);
				this->printConfig(temp);
			}
		}
		else
		{
			MessageBox(0, L"Forkert tid indtastet - prøv igen", L"Ny aktiveringstid", MB_OK);
			this->printConfig(temp);
		}

	}
}

void userIF::displaySavedRutines()
{
	


	system("cls");
	cout << "Indl\x91s gemt rutine\n\n";
	cout << "Tryk tilf\x91ldig knap for at annulere\n\n";
	cout << "\nRutine 1 - " << savedArrayNames_[0];
	cout << "\nRutine 2 - " << savedArrayNames_[1];
	cout << "\nRutine 3 - " << savedArrayNames_[2];
	cout << "\nRutine 4 - " << savedArrayNames_[3];
	cout << "\nRutine 5 - " << savedArrayNames_[4];

	char choice;

	choice = _getch();
	
	int NMB = choice - '0';
	if (NMB >= 1 && 5 >= NMB)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (unitConfig_[i].getStatus() == true)
				unitConfig_[i] = savedArray_[NMB - 1][i];

		}
;		wstring temp = wstring(savedArrayNames_[NMB-1].begin(), savedArrayNames_[NMB-1].end());
		LPCWSTR wideString = temp.c_str();
		MessageBox(0, wideString, L"Rutine indlæst", MB_OK);
	}

}

void userIF::displayExitRutine()	
{
	system("cls");
	cout << "Du har aflsuttet programmet med f\x9Blgende rutine";

	
	for (size_t i = 0; i < 4; i++)
	{
		if (unitConfig_[i].getStatus() == true)
		{
			cout << "\n\nEnhed: " << unitConfig_[i].getName();
			cout << "\nAktiveringstid: " << unitConfig_[i].getActivationTime();
			cout << "\nRutine: ";
				
			switch (unitConfig_[i].getRutine())				//Checking the active rutine
			{
			case '1':
			{
				cout << unitConfig_[i].getRutine1();
				break;
			}
			case '2':
			{
				cout << unitConfig_[i].getRutine2();
				break;
			}
			case '3':
			{
				cout << unitConfig_[i].getRutine3();
				break;
			}
			case '4':
			{
				cout << unitConfig_[i].getRutine4();
				break;
			}
			}
		}
	}
	setSavedName();
	//Sleep(5000);

}

void userIF::displayExitWithoutSavingRutine()
{
	system("cls");
	cout << "Du har aflsuttet programmet uden at gemme, dette er den nuv\x91rende rutine";


	for (size_t i = 0; i < 4; i++)
	{
		if (oldConfig_[i].getStatus() == true)
		{
			cout << "\n\nEnhed: " << oldConfig_[i].getName();
			cout << "\nAktiveringstid: " << oldConfig_[i].getActivationTime();
			cout << "\nRutine: ";
			switch (oldConfig_[i].getRutine())				//Checking the old active rutine
			{
			case '1':
			{
				cout << oldConfig_[i].getRutine1();
				break;
			}
			case '2':
			{
				cout << oldConfig_[i].getRutine2();
				break;
			}
			case '3':
			{
				cout << oldConfig_[i].getRutine3();
				break;
			}
			case '4':
			{
				cout << oldConfig_[i].getRutine4();
				break;
			}
			}
		}
	}
	

}

void userIF::setCopy(pcSettings* currentConfig, pcSettings savedRutines[5][4])
{
	//Setting a copy in the UI class of the PC. 
	for (size_t i = 0; i < 4; i++)	
	{
		unitConfig_[i].setConfig(currentConfig[i]);
		oldConfig_[i].setConfig(currentConfig[i]);
	}

	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 4; j++)
		{
			savedArray_[i][j].setConfig(savedRutines[i][j]);
		}
		
	
}

void userIF::setSavedName()
{
	ofstream savedNames;

	string names;

	//CLEAR THE TXT FILE

	savedNames.open("SavedNames.txt", ios::out | ios::trunc);
	savedNames.close();

	savedNames.open("SavedNames.txt", ios::out);
	if (!savedNames)
	{
		cout << "Error happened with file ...\n";
	}

	//Fill the txt file with the new saved names, these are stored locally on the PC

	for (size_t i = 0; i < 5; i++)
		savedNames << savedArrayNames_[i] << endl;

	savedNames.close();
}

void userIF::getSavedName()
{

	ifstream savedNames;
	string names;

	//Open SavedNames file with all the names for the saved rutines
	savedNames.open("SavedNames.txt", ios::in);



	//If no file is detected create new one, and set the default name (Smart rutine X)
	if (!savedNames) {
		cout << "creating file... \n";
		ofstream{ "SavedNames.txt" };
		setSavedName();
	}


	//Get each name from the txt file
	else
	{
		for (size_t i = 0; i < 5; i++) {
			(getline(savedNames, names));
			savedArrayNames_[i] = names;
		}
		
	}
	savedNames.close();
}

pcSettings* userIF::getConfig()
{
	return unitConfig_;
}

pcSettings(*userIF::getSavedArray())[4]
{
	return savedArray_;
}

std::string* userIF::getSavedArrayNames()
{
	return savedArrayNames_;
}














