#pragma once
#include "controller.h"

struct PowerInfo
{
	enum class Status : int
	{
		UNKNOWN,
		IS_ME,
		AVAILABLE,
		VICTORY,
		DEFEAT,
	};
	int pos = -1;
	Status status = Status::UNKNOWN;
	int power = 0;
	int power_max = 0;
	int blacklist_count = 0;
};

class Arena :
	public controller
{
public:
	Arena();
	~Arena();
	bool Start(); // подправить так как сквад_арена перемещу в арена
	bool checkFind();
	bool checkWait();
	bool checkEnd(); 
	bool Stop();
	bool getAds();
	bool Settings();
	bool getData(); // переделать сравнение чтобы не делать 2393812908120 скринов и разобраться с ОКР для цифр(понять код и попробовать буквы вставить)
	bool LoadBL(); // -
	bool SaveEnemyBL(Mat power); // -
	bool ShopFree();
	bool takeMaxPow();

	int getPhase();
	int getAttackPos();

	void tacticFirst();
	void Print();
private:
	int power;
	vector<PowerInfo> players;
	vector<int> blacklist;
	path localPath;
	bool mode; // false = apple true = ticket
	double mult;
};

