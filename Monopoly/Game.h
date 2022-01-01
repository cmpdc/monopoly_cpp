#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "Card.h"
#include "Player.h"
#include "Property.h"
#include "Utils.h"

class Game {

	private:

		Utils utils;

	public:

		Game();

		// Vectors
		std::vector<Player> playerList;
		std::vector<Player> biddersList;
		std::vector<std::string> playerIcons;
		std::vector<Card> chancesCards;
		std::vector<Card> luckyCards;
		std::vector<std::string> randomSayings;

		std::vector<Property> unownedProperty;
		std::vector<Property> board;
		
		std::vector<Player*> playersToAttack;

		Game& showTitleScreen();
		Game& createPlayerScreen();
		Game& initGame();

		Game& printInnerTileTitle(std::vector<Property>, int, Player);
		Game& printInnerTileIcons(std::vector<Property>, int);

		template <typename T>
		Game& printInnerTileInfos(std::vector<Property>, int, std::string, T);

		Game& printTopRow(std::vector<Property>, Player);
		Game& printMidRow1(std::vector<Property>, int, int, Player);
		Game& printMidRow2(std::vector<Property>, int, int, Player);
		Game& printMidRow3(std::vector<Property>, int, int, Player);
		Game& printBottomRow(std::vector<Property>, Player);
		Game& printBoard(std::vector<Property>, Player);

		int diceRoll();
		Card& cardRandomizer();

		Game& movePlayer(Player&);
		Game& movePlayerManual(Player&, int);
		Game& perTileFunctions(std::vector<Property>&, std::vector<Player>&, Player&);
		Game& travelRailRoad(Player);
		Game& checkPlayers(std::vector<Player>&);
};