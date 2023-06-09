#include "pcUARTdriver.h"
#include <iostream>
#include <string>
#include <thread>

pcUARTdriver::pcUARTdriver(serialib* serialPtr)
{
	serial_ = serialPtr;

}


void pcUARTdriver::recieveConfig(pcSettings* unitConfig)
{
    const size_t numUnits = 4;
    const char SOM = '@'; // Start-of-message marker
    const char RTS = '&'; // Ready-to-send marker
    const char RTR = '#'; // Ready-to-receive marker

    char marker;          //Marker from aurdunio
    char RTSmarker;

    while (true) {
        serial_->readBytes(&RTSmarker, sizeof(char));
        if (RTSmarker == RTS) {
            //std::cout << "RTS received";
            break; // Found RTS marker, proceed to read size
        }
    } // WAITING FOR ARDUINO TO GO INTO CONFIGURATION MODE

    system("cls");
    std::cout << "Loading..\n";

    serial_->writeBytes(&RTR, sizeof(RTR));

    char sizeArray[8];

    for (size_t j = 0; j < numUnits; j++)
    {
        //system("cls");

        ////Make the "loading" in cout 
        //std::cout << "Loading each unit\n";
        //std::cout << static_cast<char>(205) << std::endl;
        //for (size_t i = 0; i < numUnits; i++)
        //{

        //    if (i < j)
        //        std::cout << static_cast<char>(176) << std::endl;
        //    else
        //        std::cout << std::endl;
        //}
        //std::cout << static_cast<char>(205) << std::endl;


            while (true) {
                serial_->readBytes(&marker, sizeof(char));

                if (marker == SOM) {
                    //std::cout << "SOM received";
                    serial_->readBytes(sizeArray, sizeof(sizeArray));
                    
                    break; // Found SOM marker, proceed to read data
                }
            }
        

        for (size_t i = 0; i < 8; i++) {
            // Create a buffer for receiving the data
            char* dataBuffer = new char[sizeArray[i]];


            // Read the data using the size from sizeArray
            serial_->readBytes(dataBuffer, sizeArray[i]); 

            

            // Process the received data
            if (i == 0) {
                bool isConnected = static_cast<bool>(*dataBuffer);
                unitConfig[j].setStatus(isConnected);
                std::cout << "\nStatus: " << unitConfig[j].getStatus();
                
            }
            else if (i == 1) {
                unitConfig[j].setName(dataBuffer);
                std::cout << "\nName: " << unitConfig[j].getName();
            }
            else if (i == 2) {

                unitConfig[j].setRutine((*dataBuffer));
                std::cout << "\nRutine: " << unitConfig[j].getRutine();
            }
            else if (i == 3) {  
                unitConfig[j].setActivationTime(dataBuffer);
                std::cout << "\nTime: " << unitConfig[j].getActivationTime();
            }
            else if (i == 4) {
                unitConfig[j].setRutine1(dataBuffer);
                std::cout << "\nRutine1: " << unitConfig[j].getRutine1();
            }
            else if (i == 5) {
                unitConfig[j].setRutine2(dataBuffer);
                std::cout << "\nRutine2: " << unitConfig[j].getRutine2();
            }
            else if (i == 6) {
                unitConfig[j].setRutine3(dataBuffer);
                std::cout << "\nRutine3: " << unitConfig[j].getRutine3();
            }
            else if (i == 7) {
                unitConfig[j].setRutine4(dataBuffer);
                std::cout << "\nRutine4: " << unitConfig[j].getRutine4();
            }

            delete[] dataBuffer; // Clean up the buffer
        }
        
    }
}


void pcUARTdriver::sendConfig(pcSettings* unitConfig)
{
    const size_t TIME_SIZE = 6;
    const size_t numUnits = 4;
    const char SOM = '@'; // Start-of-message marker
    const char RTS = '&'; // Ready-to-send marker
    const char RTR = '#'; // Ready-to-recieve marker
    char RTRmarker;

    serial_->writeBytes(&RTS, sizeof(char));

    while (true) {
        serial_->readBytes(&RTRmarker, sizeof(char));
        if (RTRmarker == RTR) {
            //std::cout << "RTR FOUND!";
            break; // Found RTR marker, proceed to read size
        }
    } //WAITING FOR Arduino TO RESPOND WITH Ready-to-recieve



    //Sleep to syncronize Arduinos lower CPU frequency
    std::this_thread::sleep_for(std::chrono::milliseconds(1));


    for (size_t i = 0; i < numUnits; i++)
    {

        // Send SOM marker
        serial_->writeBytes(&SOM, sizeof(char));

        //Create new time string on the heap (POSSIBLY BAD PRACTICE, BUT HAD ISSUES WITHOUT IT...)
        char* activationTime = new char[TIME_SIZE];

        std::string timeString = unitConfig[i].getActivationTime();
        for (size_t v = 0; v < TIME_SIZE; v++)
        {
            activationTime[v] = timeString[v];           //Making time equal the unitConfig[i] activation time
        }


        std::string tempHours = timeString.substr(0, 2);        //Splitting time into hours
        std::string tempMinutes = timeString.substr(3, 2);      //Splitting time into minutes
        const char* hours = tempHours.c_str();                  //Make it a const char* to be sent;
        const char* minutes = tempMinutes.c_str();  

        //Rutine is already a char
        char desiredRutine = unitConfig[i].getRutine();


        //Comments here are for debugging
        //std::cout << "SENDING TIME: " << time << std::endl;
        serial_->writeBytes(activationTime, TIME_SIZE);


        //std::cout << "SENDING hours: " << hours << std::endl;
        serial_->writeBytes(hours, 3);  


        //std::cout << "SENDING MINUTES: " << minutes << std::endl;
        serial_->writeBytes(minutes, 3);


        //std::cout << "SENDING RUTINE: " << rutine << std::endl;
        serial_->writeBytes(&desiredRutine, 1);

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        delete[] activationTime;

    }

}



