#pragma once
#include <io.h>
#include <time.h>
#include <direct.h>    
#include <iostream>
#include "ATM_Matrix.h"
using namespace std;
class ATM_SaveLoadFile
{
	string _uidStr = "000000000";

	string _saveIndex = "";
	char _lastSaveTimeChars[60] = {'\0'};
	string _uidFilePath = "";
	string logFilePath = "";

	const string _uid_ = "UID-";
public:
	ATM_Matrix _stateFST = ATM_Matrix(1, 65);
	ATM_Matrix _stateYST = ATM_Matrix(1, 131);
	ATM_Matrix _stateLST = ATM_Matrix(1, 95);
	ATM_Matrix _stateFHYS = ATM_Matrix(1, 80);
	ATM_Matrix _stateLST2 = ATM_Matrix(1, 50);
	/********/
	ATM_Matrix _stateFlag;
	int _uid = 0;

	ATM_SaveLoadFile();
	~ATM_SaveLoadFile();
	void setIndex(string index);
	void setUID(int uid);
	void save();
	void load();

	bool tryLoad();

	void logError(string mes);
	void logExeRun();
	void logExeExit();
	void logUIDEvent(int newUID);
	void logAvatarEvent(double x, double y, double a);
	void logStarEvent(int starClass, int starId, int starState);
	void logStarEvent(int starClass, int starId, int x, int y);
	//ATM_Matrix* StateClass(int klass);

private:

	void loadVersion(FILE * fpSave);
	
	void getUIDStr();
	void getFilePath();
	string getSystemTime();

	void saveMatrix(FILE * fpSave,ATM_Matrix &mat);
	void loadMatrix(FILE * fpLoad, ATM_Matrix &mat);
	bool loadMatrix2(FILE * fpLoad,ATM_Matrix &mat);

};

