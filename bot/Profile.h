#pragma once
#include <baseapi.h> // tesseract
#include <allheaders.h> // leptonica 
#include <opencv.hpp> // opencv 
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <iconv.h>
#include <boost/format.hpp>
using namespace boost;
using namespace std;
using namespace cv;
using namespace tesseract;
//struct arena {
//	bool battle = false;
//	bool blacklist = false;
//	bool victory = false;
//	int power = 0;
//	int place = 0;
//
//	arena& operator=(arena& X) {
//		battle = X.battle;
//		blacklist = X.blacklist;
//		power = X.power;
//		place = X.place;
//	}
//	friend ostream& operator <<(ostream& x, arena& A) {
//		if (A.place < 0) { x << "my place:" << A.place*(-1) << " power: " << A.power << endl; }
//		else { x << "enemy`s place: " << A.place << " power: " << A.power << " battle: "; if (A.battle && A.victory) x << "Win" << endl; else if (A.battle && !A.victory)x << "Defeat" << endl; else x << "Didn`t fight" << endl; }
//		return x;
//	}
//};

class uProfile
{
public:
	uProfile();
	~uProfile();
	int getPower();
	int getID();

	bool getPremiumStatus();
	static bool Start();
	bool Init();

	void takePower(int power);
	void takeID(int ID);
	void takePremiumStatus(bool status);
	uProfile& operator= (const uProfile& user);
private:
	int uPower, uID;
	bool uPremium;
};

