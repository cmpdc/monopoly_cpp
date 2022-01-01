#include "Game.h"
#include "Player.h"
#include "Property.h"
#include "Utils.h"

using namespace std;

int main() {
	Utils utils; // initialize utility functions
	Game monopoly; // initialize monopoly game

	// --- TITLE SCREEN
	// adjusts the window size for "title screen"
	utils.changeWindowSize(800, 500);
	monopoly.showTitleScreen().createPlayerScreen();

	// --- GAMEPLAY
	// adjusts the window size for the game itself then initialize game
	utils.changeWindowSize(1600, 780);
	monopoly.initGame();
	utils.pauseScreen();
}