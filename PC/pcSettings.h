#pragma once
#include <string>

class pcSettings
{
public:
	pcSettings() {};
	void initSettings();
	void setConfig(pcSettings config);
	pcSettings getConfig(pcSettings) const;
	pcSettings& setActivationTime(std::string time);
	pcSettings & setStatus(bool connectionStatus);
	bool getStatus() const;
	std::string getActivationTime() const;
	pcSettings& setName(std::string name);
	std::string getName() const;
	pcSettings& setRutine(char rutine);
	char getRutine() const;
	std::string getRutine1() const;
	std::string getRutine2() const;
	std::string getRutine3() const;
	std::string getRutine4() const;
	void setRutine1(std::string rutine1);
	void setRutine2(std::string rutine2);
	void setRutine3(std::string rutine3);
	void setRutine4(std::string rutine4);
private:
	bool isConnected_ = true;
	std::string unitName_ = "UNITNAME";
	char desiredRutine_ = '1';
	std::string activationTime_ = "ACTIVATION TIME";
	std::string rutine1_ = "RUTINE 1";
	std::string rutine2_ = "RUTINE 2";
	std::string rutine3_ = "RUTINE 3";
	std::string rutine4_ = "RUTINE 4";
};

