#pragma once

#include "Profile.h"
using namespace std;
using namespace cv;
using namespace tesseract;
using namespace std::filesystem;
class bluestacks:
	public uProfile
{
public:
	bluestacks();
	~bluestacks();
	const HWND getmHandle();
	const HWND getgHandle();
	const RECT getmWin();
	const Point getmSize();
	const Point getgSize();

	bool userSavePower(int power);
	bool userSaveID(int number);
	bool userSaveStatus(bool check);

	uProfile getUser();

	bool CheckPremium();
	int Atoi(string str);
private:
	HWND mainWin, gameWin;
	char nameWin[200];
	RECT mWin, gWin;
	Point mSize, gSize;
	uProfile user;
};

