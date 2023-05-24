#pragma once
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


	bool getIsConnected() const;
	void setIsConnected(bool connectionStatus);
	char* getUnitName() const; 
	char* getDesiredRutine();
	void setDesiredRutine(char rutine);
	const char* getActivationTime() const;
	int getActivationHour() const;
	void setActivationHour(int hour);
	int getActivationMinute();
	void setActivationMinute(int minute);
	char* getRutine1() const;
	char* getRutine2() const;
	char* getRutine3() const;
	char* getRutine4() const;
	char activationTime_[6];

private:	
	bool isConnected_;
	char* unitName_;
	char desiredRutine_;
	int activationHour_;
	int activationMinute_;
	char* rutine1_;
	char* rutine2_;
	char* rutine3_;
	char* rutine4_;



	
	char adress_;
};

