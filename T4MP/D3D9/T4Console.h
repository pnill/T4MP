#pragma once
#include <vector>
class ConsoleCommands {
public:
	ConsoleCommands();
	void handle_command(std::string);
	void output(std::wstring result);
	void display(std::string output);
	std::vector<std::string> prevCommands;
	std::vector<std::string> prevOutput;
	BOOL handleInput(WPARAM wp);

	std::string command;
	int caretPos;
	bool handled;
	bool console = false;
	int previous_command_index = 0;
private:
	void writePreviousCommand(std::string msg);
	void writePreviousOutput(std::string msg);
	bool isNum(const char *s);
	bool checked_for_ids = false;
	DWORD sleepTime;
};