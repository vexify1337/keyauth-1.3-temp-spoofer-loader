
#include "string"
#include "iostream"
#include "Windows.h"
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int choice;


struct CoreP {
public:

	void CMsg(std::string tt, bool endl, WORD col) {
		if (endl) {
			SetConsoleTextAttribute(hConsole, col);
			std::cout << tt << std::endl;
		}
		else {
			SetConsoleTextAttribute(hConsole, col);
			std::cout << tt;
		}

	}
	void ClearC() {
		system("cls");
	}
	void CWait(WORD ms) {
		Sleep(ms);
	}
	void CExit() {
		exit(0);
	}
	void Branding() {
		SetConsoleTitle(L"Beat Spoofer -> source code: https://discord.gg/shellcode, made with 💝 By UE5");
		CMsg("  _                _                            __           \n"
			" | |__   ___  __ _| |_   ___ _ __   ___   ___  / _| ___ _ __ \n"
			" | '_ \\ / _ \\/ _` | __| / __| '_ \\ / _ \\ / _ \\| |_ / _ \\ '__|\n"
			" | |_) |  __/ (_| | |_  \\__ \\ |_) | (_) | (_) |  _|  __/ |   \n"
			" |_.__/ \\___|\\__,_|\\__| |___/ .__/ \\___/ \\___/|_|  \\___|_|   \n"
			"                         |_|                                 \n", true, 2);
	}
}; CoreP* Console = new CoreP();
