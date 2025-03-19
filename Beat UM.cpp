#include "SpooferUM/driver.h"
#include "Dependencies/core.h"
#include "Authentication/auth.hpp"
#include "Authentication/Obfuscation/oxorany_include.h"
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)BeatEncrypt(__DATE__);
const std::string compilation_time = (std::string)BeatEncrypt(__TIME__);
void sessionStatus();

using namespace KeyAuth;
std::string name = BeatEncrypt("app namea"); // App name
std::string ownerid = BeatEncrypt("owner id"); // Account ID
std::string version = BeatEncrypt("1.0"); // Application version. Used for automatic downloads see video here https://www.youtube.com/watch?v=kW195PLCBKs
std::string url = BeatEncrypt("https://keyauth.win/api/1.3/"); // change if using KeyAuth custom domains feature
std::string path = BeatEncrypt(""); // (OPTIONAL) see tutorial here https://www.youtube.com/watch?v=I9rxt821gMk&t=1s


api BeatAuth(name, ownerid, version, url, path);

// taking our struct from SpooferUM/driver.h we will now make a proper loader.
int spoofer;
std::string tkn;
int main() {
	BeatAuth.init(); 
	Console->Branding();
	Console->CMsg(BeatEncrypt("[!] Please Enter A Valid Token -> "), false, 3);
	std::cin >> tkn;
	BeatAuth.license(tkn);



	if (!BeatAuth.response.success)
	{
		Console->ClearC();
		Console->CMsg(BeatEncrypt("[-] Invalid Token ;(."), true, 4);
		Console->CWait(3500);
		Console->CExit();

	}
	else {


		Console->ClearC();
		Console->Branding();
		Console->CMsg(BeatEncrypt("[!] Please Select A Valid Option "), true, 5);
		Console->CMsg(BeatEncrypt("[+] (1) Virtualise Computer "), true, 1);
		Console->CMsg(BeatEncrypt("[+] (2) Clean Computer "), true, 1);
		Console->CMsg(BeatEncrypt("[BEAT-INPUTMANAGER] Your Option: "), false, 2);
		std::cin >> spoofer;

		switch (spoofer) {
		case 1:
			BeatUM->spoof();
			Console->CMsg(BeatEncrypt("[+] Sucesssfully Virtualised Your Machine, You May Now Open Up Your Game! "), true, 2);
			Console->CWait(2400);
			Console->CExit();
			break;
		  // add your own case statement for case 2: what would be for cleaning!
		}
	}
}
