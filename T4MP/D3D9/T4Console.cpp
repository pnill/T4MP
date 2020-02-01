#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <algorithm> 
#include <windows.h>
#include "T4Console.h"
#include "../Engine.h"

#include <time.h>

extern HWND CurWindow;
extern std::set<DWORD> wep_pointers;

ConsoleCommands::ConsoleCommands() {
	command = "";
	caretPos = 0;
}

void ConsoleCommands::writePreviousOutput(std::string msg) {
	std::vector<std::string>::iterator it;
	it = prevOutput.begin();
	prevOutput.insert(it, msg);

	if (prevOutput.size() > 18) {
		prevOutput.pop_back();
	}

}

void ConsoleCommands::writePreviousCommand(std::string msg) {
	std::vector<std::string>::iterator it;
	it = prevCommands.begin();
	prevCommands.insert(it, msg);

	if (prevCommands.size() > 18) {
		prevCommands.pop_back();
	}
}

time_t start = time(0);
BOOL ConsoleCommands::handleInput(WPARAM wp) {

	if (CurWindow != GetForegroundWindow())
	{
		return false;
	}

	//double seconds_since_start = difftime(time(0), start);
	if (wp == VK_OEM_3) {
		//if (seconds_since_start > 0.1) {
			console = !console;

			if (console == false)
			{
				DWORD dwBack;

				VirtualProtect((PVOID)0x004D0466, 1, PAGE_EXECUTE_READWRITE, &dwBack);
				*(BYTE*)(0x004D0466) = 0x74; // enable game input
			}
		//	start = time(0);
		//}
		return false;
	}
	switch (wp) {
	case '\b':   // backspace
	{
		if (console) {
			if (caretPos > 0)
			{
				command.erase(caretPos - 1, 1);
				caretPos -= 1;
			}
			return true;
		}
	}
	break;

	case '\r':    // return/enter
	{
		if (console) {
			this->writePreviousCommand(command);

	
			handle_command(command);

			command = "";
			caretPos = 0;
			return true;
		}
	}
	break;

	default:
		if (console) {

			if (wp == VK_UP)
			{
				command = "";
				caretPos = 0;
				if (prevCommands.size() > 0  && previous_command_index <= prevCommands.size()-1)
				{
					command = prevCommands[previous_command_index];
					caretPos = command.length();
					previous_command_index++;
				}
				return true;
			}

			if (wp == VK_DOWN)
			{
				command = "";
				caretPos = 0;

				if (prevCommands.size() > 0 && previous_command_index > 0)
				{
					previous_command_index--;
					command = prevCommands[previous_command_index];
					caretPos = command.length();
				}
				return true;
			}

			if (wp == VK_END)
			{
				caretPos = command.length();
				return true;
			}

			if (wp == VK_HOME)
			{
				caretPos = 0;
				return true;
			}

			if (wp == VK_LEFT)
			{
				if(caretPos)
					caretPos--;

				return true;
			}

			if (wp == VK_RIGHT)
			{
				if (caretPos != command.length())
					caretPos++;

				return true;
			}


			if (((wp >= 0x30 && wp <= 0x5A) || wp == 0x20 || wp == VK_OEM_MINUS || wp == VK_OEM_COMMA || wp == VK_OEM_PERIOD || wp == VK_OEM_MINUS || wp == VK_OEM_PLUS ||
				wp == VK_OEM_1 || wp == VK_OEM_2 || wp == VK_OEM_3 || wp == VK_OEM_4 || wp == VK_OEM_5 || wp == VK_OEM_6 || wp == VK_OEM_7)) {
				
				
				
				switch (wp)
				{
					case VK_OEM_COMMA:
						wp = ',';
					break;
					
					case VK_OEM_PERIOD:
						wp = '.';
					break;

					case VK_OEM_MINUS:
						wp = '-';
					break;

					case VK_OEM_1:
						wp = ';';
					break;

					case VK_OEM_2:
						wp = '/';
					break;

					case VK_OEM_4:
						wp = '[';
					break;

					case VK_OEM_5:
						wp = '\\';
					break;

					case VK_OEM_6:
						wp = ']';
					break;

					case VK_OEM_7:
						wp = '\'';
					break;

					case VK_OEM_PLUS:
						wp = '=';
					break;
				}
			

				
				if (GetAsyncKeyState(0x10) & 0x8000 || GetAsyncKeyState(0xA0) & 0x8000 || GetAsyncKeyState(0xA1) & 0x8000) {
		
					switch (wp)
					{
						case '1':
							wp = '!';
						break;
						
						case '-':
							wp = '_';
						break;

						case '2':
							wp = '@';
						break;
						
						case '3':
							wp = '#';
						break;

						case '4':
							wp = '$';
						break;

						case '5':
							wp = '%';
						break;

						case '6':
							wp = '^';
						break;

						case '7':
							wp = '&';
						break;

						case '8':
							wp = '*';
						break;

						case '9':
							wp = '(';
						break;

						case '0':
							wp = ')';
						break;

						case '=':
							wp = '+';
						break;

						case '[':
							wp = '{';
						break;

						case ']':
							wp = '}';
						break;

						case '\'':
							wp = '"';
						break;

						case ';':
							wp = ':';
						break;

						case ',':
							wp = '<';
						break;

						case '.':
							wp = '>';
						break;

						case '/':
							wp = '?';
						break;

						case '\\':
							wp = '|';
						break;

					

						default:
							wp = toupper(wp);
						break;
					}

				}
				else {
					wp = tolower(wp);
				}
				command.insert(caretPos, 1, (char)wp);
				caretPos += 1;
				return true;
			}
		}
		break;
	}
	return false;
}


void ConsoleCommands::output(std::wstring result) {
		std::string str(result.begin(), result.end());
		writePreviousCommand(str);
}

void ConsoleCommands::display(std::string output)
{
	writePreviousCommand(output);
}

bool ConsoleCommands::isNum(const char *s) {
	int i = 0;
	while (s[i]) {
		//if there is a letter in a string then string is not a number
		if (isalpha(s[i])) {
			return false;
		}
		i++;
	}
	return true;
}

void ConsoleCommands::handle_command(std::string command) {

	if (command == "pointers")
	{
		void * ptr1 = 0;
		void*  ptr2 = 0;
		void*  ptr3 = 0;
		void*  ptr4 = 0;
		void*  ptr5 = 0;
		void*  ptr6 = 0;
		void*  ptr7 = 0;
		void*  ptr8 = 0;

		T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
		if (TurokEngine->pT4Game)
			if (TurokEngine->pT4Game->pEngineObjects)
			{
				ptr1 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0];
				if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor)
				{
					ptr2 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor;
					ptr3 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor->pDMPlayer;
					ptr4 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor->pDMPlayer->pHealth;
					ptr5 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pPlayer;
					ptr6 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor->pDMPlayer->pBlendedCamera;
					ptr7 = &TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor->pDMPlayer->pBlendedCamera->enabled;

					if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[1])
						ptr8 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[1]->pActor->pDMPlayer;
				}
			}

		this->writePreviousOutput("local ptrs:");

		std::stringstream otptr1;
		otptr1 << "pBlendedCamera: " << std::hex << ptr1;

		std::stringstream otptr2;
		otptr2 << "pActor: " << std::hex << ptr2;

		std::stringstream otptr3;
		otptr3 << "pDMPlayer: " << std::hex << ptr3;

		std::stringstream otptr4;
		otptr4 << "pHealth: " << std::hex << ptr4;

		std::stringstream otptr5;
		otptr5 << "pPlayer: " << std::hex << ptr5;

		std::stringstream otptr6;
		otptr6 << "dmPlayer(BlendedCamera): " << std::hex << ptr6;

		std::stringstream otptr7;
		otptr7 << "BlendedCamera enable ptr: " << std::hex << ptr7;

		std::stringstream otptr8;
		otptr8 << "pDMPlayer[1]: " << std::hex << ptr8;


		this->writePreviousOutput(otptr1.str());
		this->writePreviousOutput(otptr2.str());
		this->writePreviousOutput(otptr3.str());
		this->writePreviousOutput(otptr4.str());
		this->writePreviousOutput(otptr5.str());
		this->writePreviousOutput(otptr6.str());
		this->writePreviousOutput(otptr7.str());
		this->writePreviousOutput(otptr8.str());

	}

	if (command == "spawn")
	{
		TurokEngine tengine;
		tengine.SpawnPlayer();
	}

	if (command == "attack")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(1);

		p->fire_weapon(0, 0);
		p->fire_release(0);
	}



	if (command == "hold_attack")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(1);
		p->fire_weapon(0, 0);
		p->fire_held(1.0f, 0);
	}

	if (command == "release_attack")
	{
		TurokEngine tengine;
		DMPlayer* p = tengine.GetDMPlayer(1);
		p->fire_release(1.0f);
	}

	if (command == "walk")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(1);
		p->Walk_backward = 1.0f;
		p->bThirdPerson = false;
	}

	if (command == "jump")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(1);
		p->jump(0, 15.0f);
	}

	if (command == "switch_weapon")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(1);
		p->pWeaponWheel->bHas_SpikeGrenade = 1;
		p->pWeaponWheel->bHas_SpikeGrenade2 = 1;
		p->pWeaponWheel->SpikeGrenade_Ammo = 50;
		p->pWeaponWheel->SpikeGrenade_Ammo2 = 50;
		p->pWeaponWheel->SpikeGrenade_Ammo3 = 50;
		
		
		SwitchWeapon(&p->pWeapon, p->pWeaponWheel->SpikeGrenadeID);

	}

	if (command == "modify_my_weapon")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(0);
		p->modify_weapon(0, 0);
		p->modify_weapon2(0, 0);
	}

	if (command == "disable_my_camera")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(0);
		p->pBlendedCamera->enabled = false;
	}

	if (command == "enable_my_camera")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(0);
		p->pBlendedCamera->enabled = true;
	}

	if (command == "disable_camera")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(1);

		p->pBlendedCamera->enabled = false;
	}

	if (command == "enable_camera")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(1);
		p->pBlendedCamera->enabled = true;
	}

	if (command == "modify_weapon")
	{
		TurokEngine tengine;
		DMPlayer *p = tengine.GetDMPlayer(1);
		//p->modify_weapon(0, 0);
		WeaponModify(p);
	}


}