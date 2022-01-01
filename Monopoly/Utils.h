#pragma once
#include <string>
#include <vector>

class Utils {

	friend class Game;

private:

public:

	std::string str_UpperCase(std::string);

	void pauseScreen();

	void changeWindowSize(int, int);

	void clearScreen();
};






