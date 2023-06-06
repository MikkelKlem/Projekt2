#include "pcSettings.h"



void pcSettings::setConfig(pcSettings config)
{
	unitName_ = config.unitName_;
	activationTime_ = config.activationTime_;
	isConnected_ = config.isConnected_;
	desiredRutine_ = config.desiredRutine_;
	rutine1_ = config.rutine1_;
	rutine2_ = config.rutine2_;
	rutine3_ = config.rutine3_;
	rutine4_ = config.rutine4_;
}


pcSettings& pcSettings::setActivationTime(std::string time)
{
	activationTime_ = time;
	return *this;
}

pcSettings& pcSettings::setStatus(bool connectionStatus)
{
	isConnected_ = connectionStatus;
	return *this;
}

bool pcSettings::getStatus() const
{
	return isConnected_;
}

std::string pcSettings::getActivationTime() const
{
	return activationTime_;
}

pcSettings& pcSettings::setName(std::string name)
{
	unitName_ = name;
	return *this;
}

std::string pcSettings::getName() const
{
	return unitName_;
}

pcSettings& pcSettings::setRutine(char desiredRutine)
{
	desiredRutine_ = desiredRutine;

	return *this;
}

char pcSettings::getRutine() const
{
	return desiredRutine_;
}

std::string pcSettings::getRutine1() const
{
	return rutine1_;
}

std::string pcSettings::getRutine2() const
{
	return rutine2_;
}

std::string pcSettings::getRutine3() const
{
	return rutine3_;
}

std::string pcSettings::getRutine4() const
{
	return rutine4_;
}

void pcSettings::setRutine1(std::string rutine1)
{
	rutine1_ = rutine1;
}

void pcSettings::setRutine2(std::string rutine2)
{
	rutine2_ = rutine2;
}

void pcSettings::setRutine3(std::string rutine3)
{
	rutine3_ = rutine3;
}

void pcSettings::setRutine4(std::string rutine4)
{
	rutine4_ = rutine4;
}
