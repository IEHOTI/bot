#include "Profile.h"
uProfile::uProfile() {
	uPower = 0;
	uID = 0;
	uPremium = false;
}
uProfile::~uProfile() {

}
int uProfile::getPower() {
	return uPower;
}
int uProfile::getID() {
	return uID;
}
bool uProfile::getPremiumStatus() {
	return uPremium;
}
void uProfile::takePower(int power) {
	uPower = power;
	
}
void uProfile::takeID(int ID) {
	uID = ID;
}
void uProfile::takePremiumStatus(bool status) {
	uPremium = status;
}
uProfile& uProfile::operator= (const uProfile& user) {
	this->uID = user.uID;
	this->uPower = user.uPower;
	this->uPremium = user.uPremium;
	return *this;
}
bool uProfile::Start() {
	bool res = true;
	wstring path = L"C:/Program Files/BlueStacks_nxt/HD-Player.exe";
	// % path % instance % app -> instance pie,android11 etc. need find?
	wstring cmd = (wformat(LR"("%1%" --instance %2% --cmd launchApp --package %3%)") % path % wstring(L"Pie64_1") % "com.my.hc.rpg.kingdom.simulator").str();
	STARTUPINFOW si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	if(!CreateProcessW(NULL, LPWSTR(cmd.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) res = false;
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return res;
}