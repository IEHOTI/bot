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
	bool Start(); // ���������� ��� ��� �����_����� �������� � �����
	bool checkFind();
	bool checkWait();
	bool checkEnd(); 
	bool Stop();
	bool getAds();
	bool Settings();
	bool getData(); // ���������� ��������� ����� �� ������ 2393812908120 ������� � ����������� � ��� ��� ����(������ ��� � ����������� ����� ��������)
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

