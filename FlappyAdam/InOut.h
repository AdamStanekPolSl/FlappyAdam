#pragma once
#include <fstream>
#include <iostream>


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
	bool loadConfig();
	bool saveConfig();
	void setSettingName(string text);
private:
	string settingName;
	ofstream write;
	ifstream read;
};

