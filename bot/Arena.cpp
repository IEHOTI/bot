#include "Arena.h"

Arena::Arena() {
	localPath = getPath();
	mode = false;
	mult = 1.0;
	power = -1;
}
Arena::~Arena() {

}
bool Arena::Start() {
	localPath = getPath();
	localPath = localPath / "arena\\arena_main";
	/*ClickButton((localPath / "main"), "button_map.png");
	if (!CompareSample((localPath / "map"), "sample.png", "compare.png")) {
		if (!CompareSample((localPath / "map"), "sample_invasion.png", "state_invasion.png")) return false;
	}
	ClickButton((localPath / "map"), "button_arena.png");*/
	if (!CompareSample(localPath, "sample.png", "compare.png")) return false;
	if (mode == false) {
		ClickButton(localPath, "button_food.png");
	}
	else {
		ClickButton(localPath, "button_ticket.png");
	}
	ClickButton(localPath, "button_start.png");
	//pathPages();
	localPath = getPath();
	localPath /= "squad_arena";
	ClickButton(localPath, "button_previous.png");
	ClickButton(localPath, "button_start.png");
	localPath = getPath();
	return true;
}
bool Arena::Settings() {
	int x = 0;
	std::cout << "¬ыберите режим:\n[1]€блоки\n[2]билеты\n";
	cin >> x;
	if (x == 2) mode = true;
	std::cout << "¬ведите множитель разброса силы врагов:\n";
	cin >> mult;
	if (x != 1 || x != 2 ) return false;
	return true;
}
bool Arena::getData() {
	players.clear();
	localPath /= "arena\\arena_battles";
	int flag = 0;
	if(!CompareSample(localPath,"sample.png","compare.png")) return false;
	for (int i = 1; i <= 10; i++) {
		ClickButton(localPath, ("button_" + to_string(i)+".png"));
		Sleep(4000);
		if (!CompareSample(localPath, "battle_sample.png", "battle_compare.png")) {
			flag = 1;
		}
		if (flag == 1) {
			i++;
			ClickButton(localPath,("button_" + to_string(i) + ".png"));
			Sleep(3000);
			if (!CompareSample(localPath, "battle_sample.png", "battle_compare.png")) {
				return false;
			}
			LoadMask((localPath / "battle_my_power.png").generic_string());
			FindObj();
			power = Recognize(CutImg());
			players.push_back(PowerInfo(i-1,PowerInfo::Status::IS_ME,power,(int)(power*mult),0));
			flag = 0;
		}
		LoadMask((localPath / "battle_enemy_power.png").generic_string());
		FindObj();
		power = Recognize(CutImg());
		if (CompareSample(localPath, "battle_sample_available.png", "battle_state_available.png")) players.push_back(PowerInfo(i, PowerInfo::Status::AVAILABLE, power, power, 0));
		else if (CompareSample(localPath, "battle_sample_defeat.png", "battle_state_defeat.png")) players.push_back(PowerInfo(i, PowerInfo::Status::DEFEAT, power, power, 0));
		else if (CompareSample(localPath, "battle_sample_victory.png", "battle_state_victory.png")) players.push_back(PowerInfo(i, PowerInfo::Status::VICTORY, power, power, 0));
		else players.push_back(PowerInfo(i, PowerInfo::Status::UNKNOWN, power, power, 0));
		ClickButton(localPath, "battle_button_close.png");
	}
	localPath = getPath();
	return true;
}
bool Arena::checkFind() {
	while (CompareSample(localPath / "arena\\arena_find", "sample.png", "compare.png")) {
		Sleep(10000);
	}
	return false;
}
bool Arena::checkWait() {
	while (CompareSample(localPath / "arena\\arena_battles", "sample_wait-next.png", "state_wait-next.png")) {
		Sleep(3000);
	}
	return false;
}
bool Arena::checkEnd() {
	while (CompareSample(localPath / "arena\\arena_battles", "sample_wait-end.png", "state_wait-end.png")) {
		Sleep(10000);
	}
	return false;
}
bool Arena::Stop() {
	ClickButton(localPath / "arena\\arena_find", "button_cancel.png");
	localPath /= "arena\\arena_cancel";
	if (!CompareSample(localPath, "sample.png", "compare.png")) return false;
	ClickButton(localPath, "button_yes.png");
	localPath = getPath();
	return true;
}
bool Arena::takeMaxPow() {
	for (const auto& info : players) {
		if (info.status == PowerInfo::Status::IS_ME) {
			power = info.power_max;
			return true;
		}
	}
	return false;
}

int Arena::getPhase() {
	int unavailable_count = 0;
	for (const auto& info : players)
		unavailable_count += (info.status != PowerInfo::Status::AVAILABLE);
	if (unavailable_count > 0 && unavailable_count <= 5) // € + 5 врагов
		return unavailable_count /*- 1*/;
	return -1;
}
int Arena::getAttackPos() {
	for (int i = 9; i >= 0; i--) {
		if (players[i].status == PowerInfo::Status::AVAILABLE) {
			return (players[i].pos - 1);//return i;
		}
	}
	return -1;
}

void Arena::tacticFirst() {
	Sleep(5000); // от надписей
	takeMaxPow();
	int phase;
	do {
		int i = 0;
		int x = 0;
		bool res = false;
		getData();
		phase = getPhase();
		//std::cout << "Phase " << phase << "   " << endl;
		//Print();
		if (players.size() != 10) {
			goto breakAll;
		}
		i = getAttackPos();
		if (i == -1) goto breakAll;
		//std::cout << "Click button_1" << endl;
		ClickButton(localPath / "arena\\arena_battles", ("button_" + to_string(i + 1) + ".png"));
		if (!CompareSample(localPath / "arena\\arena_battles", "battle_sample.png", "battle_compare.png")) {
			//TODO WARNING
			goto breakAll;
		}
		if (/*getPremiumStatus()*/true) {
			//std::cout << "Click button_2" << endl;
			ClickButton(localPath / "arena\\arena_battles", "battle_button_qstart.png");
			do {
				if (!CompareSample(localPath / "battle\\quick", "sample.png", "compare.png")) {
					if (CompareSample(localPath / "battle\\quick", "sample_event.png", "compare.png")) {
						res = true;
						//std::cout << "Click button_3" << endl;
						ClickEsc();
					}
					Sleep(2000);
				}
				else res = true;
				x++;
				if (x == 10) {
					goto breakAll;
				}
			} while (!res);
			/*if (phase == 5) {
				if (CompareSample(localPath / "battle\\quick", "sample_victory.png", "state_victory.png")) players[i].status = PowerInfo::Status::VICTORY;
				else players[i].status = PowerInfo::Status::DEFEAT;
			}*/
			//std::cout << "Click button_4" << endl;
			ClickEsc();
		}
		else {
			//без према
		}
		if (phase < 5) {
			while (checkWait());
			Sleep(5000);
		}
		else {
			while (checkEnd());
			if (CompareSample(localPath / "arena\\arena_battles", "sample_ended.png", "state_ended.png")) {
				getData();
				ClickButton(localPath / "arena\\arena_battles", "button_close.png");
				phase = -1;
			}
		}
	} while (phase != -1);
	std::cout << "________Result________" << endl;
	Print();
	pathPages();
	localPath = getPath();
breakAll: ;
}
void Arena::Print() {
	for (const auto& info : players)
	{
		stringstream ss;
		ss << setiosflags(ios::fixed) << setw(4) << left
			<< info.pos;
		if (info.status == PowerInfo::Status::AVAILABLE)
			ss << "Available ";
		else if (info.status == PowerInfo::Status::DEFEAT)
			ss << "Defeat    ";
		else if (info.status == PowerInfo::Status::IS_ME)
			ss << "Me        ";
		else if (info.status == PowerInfo::Status::VICTORY)
			ss << "Victory   ";
		else
			ss << "Unknown   ";
		ss << setiosflags(ios::fixed) << setw(12) << left
			<< info.power;
		ss << setiosflags(ios::fixed) << setw(12) << left
			<< info.power_max;
		ss << setiosflags(ios::fixed) << setw(12) << left
			<< info.blacklist_count;
		std::cout << ss.str() << endl;
	}
}