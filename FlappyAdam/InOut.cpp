#include "InOut.h"


InOut::InOut()
{
	this->settingName = directory + "config.txt";
}
void InOut::setSettingName(string text)
{
	this->settingName = text + "config.txt";
}
bool InOut::loadConfig()
{
	string bin;
	this->read.open(settingName);
	if (!read.is_open())
	{
		cout << "Cannot open " << settingName << endl;
		loadingFailure = 1;
		return false;
	}
	else
	{
		this->read.seekg(28);
		this->read >> bin;
		this->read >> resX;
		this->read >> bin;
		this->read >> resY;
		this->read >> bin;
		this->read >> fullScreen;
		this->read >> bin;
		this->read >> Vsync;
	}
	read.close();
	return true;
}

bool InOut::saveConfig()
{
	write.open(settingName, ios::trunc);
	write.close();
	write.open(settingName, ios::app);
	if (!write.is_open())
	{
		cout << "Cannot save configuration to " << settingName << endl;
		write.close();
		return false;
	}
	else
	{
		write << "example:" << endl
			<< "settingName= value" << endl
			<< "ResolutionWidth= ";
		write << resX << endl;
		write << "ResolutionHeight= ";
		write << resY << endl;
		write << "FullScreen= ";
		write << fullScreen << endl;
		write << "VerticalSync= ";
		write << Vsync;
	}
	write.close();
	return true;
}