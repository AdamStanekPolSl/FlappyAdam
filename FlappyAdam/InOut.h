#pragma once
#include <fstream>
#include <iostream>
//loading and saving config object

using namespace std;

extern unsigned int resX;
extern unsigned int resY;
extern bool Vsync, fullScreen, loadingFailure;
extern string directory;


class InOut
{
public:
	InOut();
	~InOut() = default;
	bool loadConfig();//load config
	bool saveConfig();//save config
	void setSettingName(string text);//creates string with path
private:
	string settingName;
	ofstream write;
	ifstream read;
};

