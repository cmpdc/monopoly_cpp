#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

#include "Card.h"
#include "Property.h"

class Player {

	friend class Game;
	friend class Property;

	private:
		std::string name;
		std::string marker;
		int money;

		int position;

		bool hasRolledDouble;
		bool inJail;
		bool hasTakenFirstMove;
		bool hasMovedAfterBuyingProperty;
		bool justBoughtProperty;
		bool canMove;
		bool hasEnded;

		int rolledDoubleCounter;
		int luck;

	public:
		Player(std::string);
		Player(std::string, std::string, int);

		std::vector<Card> cardInventory;
		std::vector<Property> ownedProperties;
		std::vector<Property> mortagedProperties;

		std::string getPlayerName();
		void setPlayerName(std::string);

		std::string getPlayerMarker();
		void setPlayerMarker(std::string);

		void displayPropertiesOwned();

		void buyProperty(std::vector<Property>&, std::vector<Property>&);
		void upgradeProperty(std::vector<Property>&, int);
		void sellProperty(std::vector<Property>&, std::vector<Property>&);

		int getOwnStats(std::vector<Property>&);
		void attackOwnProperty(std::vector<Property>&);

		int getOtherStats(std::vector<Property>&, Player&);
		void attackOtherPlayer(std::vector<Property>&, Player&);

		void buildTurret(std::vector<Property>&, int);

		int getPos();
		void setPos(int);

		int getMoney();
		void setMoney(int);
		void addMoney(int);
		void reduceMoney(int);

		void mortageProperty(Property&);
		void unMortageProp(Property&);
};