#include "bluestacks.h"
bluestacks::bluestacks() {
	mainWin = FindWindowA("Qt5154QWindowIcon", NULL);
	gameWin = FindWindowExA(mainWin, NULL, NULL, "HD-Player");
	GetWindowTextA(mainWin, nameWin, 200);
	mSize = { 1280 + 34,720 + 34 };
	gSize = { 1280,720 };
	MoveWindow(mainWin, 50, 0, mSize.x, mSize.y, true);
	MoveWindow(gameWin, 1, 33, gSize.x, gSize.y, true);
	GetClientRect(mainWin, &mWin);
	GetClientRect(gameWin, &gWin);
}
bluestacks::~bluestacks() {

}
const HWND bluestacks::getmHandle() {
	return mainWin;
}
const HWND bluestacks::getgHandle() {
	return gameWin;
}
const RECT bluestacks::getmWin() {
	return mWin;
}
const Point bluestacks::getmSize() {
	return mSize;
}
const Point bluestacks::getgSize() {
	return gSize;
}
bool bluestacks::CheckPremium() {
	if (user.getPremiumStatus()) return true;
	return false;
}
int bluestacks::Atoi(string str) {
	int num = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] < '0' || str[i] > '9') i++;
		num = num * 10 + (str[i] - '0');
	}
	return num;
}
bool bluestacks::userSavePower(int power) {
	user.takePower(power);
	if (user.getPower() == 0) return false;
	return true;
}
bool bluestacks::userSaveID(int ID) {
	user.takeID(ID);
	if (user.getID() == 0) return false;
	return true;
}
bool bluestacks::userSaveStatus(bool status) {
	user.takePremiumStatus(status);
	if (user.getPremiumStatus() == false) return false;
	return true;
}
uProfile bluestacks::getUser() {
	return user;
}