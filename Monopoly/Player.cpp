#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

#include "Card.h"
#include "Player.h"
#include "Property.h"

using namespace std;

Player::Player(string name){
	this->setPlayerName(name);
}

Player::Player(string name, string marker, int money) {
	this->setPlayerName(name);
	this->setPlayerMarker(marker);
	this->setMoney(money);
	this->setPos(0);

	this->hasTakenFirstMove = false;
	this->hasMovedAfterBuyingProperty = false;
	this->justBoughtProperty = false;
	this->canMove = true;
	this->hasEnded = false;

	this->hasRolledDouble = false;
	this->inJail = false;
	this->rolledDoubleCounter = 0;
	this->luck = 0;
}

string Player::getPlayerName() { return name; }
void Player::setPlayerName(string n) {
	this->name = n;
}

string Player::getPlayerMarker() { return marker; }
void Player::setPlayerMarker(string icon) {
	this->marker = icon;
}

int Player::getMoney() { return money; }
void Player::setMoney(int m = 1500) {
	this->money = m;
}

void Player::addMoney(int money) {
	if (money > 0) this->money += money;

	// limit money for console designing purposes
	// I HATE RELATIVE POSITIONING!!!
	else if (money <= 9999) {
		this->money = 9999;

		// also, implement "wealth tax" when user is in "MA. Tax" tile...
	}

	else cout << "ERROR: Unable to add money.\n";
}

void Player::reduceMoney(int money) {
	if (money >= 0) this->money -= money;

	else if (money <= 0) {
		cout << "ERROR: Bankrupt!";

		// add bankrupt function!
	}

	else cout << "ERROR: Unable to subtract money.\n";

}

void Player::displayPropertiesOwned() {
	cout << "List of all properties owned by " << this->name << " :\n";
	if (this->ownedProperties.size() >= 1) {
		for (Property prop : this->ownedProperties) {
			cout << prop.getPropertyName() << "\n";
		}
	}

	else cout << "None\n";
}

void Player::buyProperty(vector<Property>& unownedPropList, vector<Property>& board) {
	int x = 0;
	int playerPos = this->getPos();
	string propToBuy = board[playerPos].getPropertyName();

	for (Property& prop : unownedPropList) {

		if (board[playerPos].getIsPropertyOwned() == true) {

			cout << "ERROR: " << board[playerPos].getPropertyName()
				<< " is owned by " << board[playerPos].getPropertyOwner() << "!\n";
			break;
		}

		else if ((prop.getPropertyName() == propToBuy) && (prop.getIsPropertyOwned() == false) && (this->getMoney() >= prop.getPropertyCost())) {

			// setters
			board[playerPos].setPropertyOwner(this->getPlayerName());
			board[playerPos].setIsPropertyPurchaseable(true);
			board[playerPos].setPropertyIsOwnedBool(true);

			// subtract money when buying then add property to player
			this->reduceMoney(prop.getPropertyCost());
			this->ownedProperties.push_back(prop);

			unownedPropList.erase(unownedPropList.begin() + x); // remove property from unowned list
			

			// display message
			cout << board[playerPos].getPropertyOwner() << " has purchased \"" << board[playerPos].getPropertyName() << "\" ("
				<< board[playerPos].getPropertyDescription() <<")!\n";

			this->justBoughtProperty = true;

			break;

		}

		// display message when attempting to buy a property and not having enough money
		else if (this->getMoney() < board[playerPos].getPropertyCost()) {
			cout << "ERROR: " << this->getPlayerName()
				<< " has " << this->getMoney()
				<< " but needs " << board[playerPos].getPropertyCost()
				<< " to purchase " << board[playerPos].getPropertyName() << "\n";
			break;
		}

		x++;
	}
}

void Player::upgradeProperty(vector<Property>& board, int upgradeCost) {
	int playerPos = this->getPos();
	int rentUpgradeCost = { 150 };
	int currentRentCost = board[playerPos].getPropertyRent();

	for (Property& prop : this->ownedProperties) {
		if ((board[playerPos].getPropertyName() == prop.getPropertyName()) &&
			(board[playerPos].upgrades.size() < 4) &&
			(this->getMoney() >= upgradeCost)) {

			board[playerPos].addUpgrade("H");
			board[playerPos].setPropertyRent(currentRentCost + rentUpgradeCost);

			prop.setPropertyRent(currentRentCost + rentUpgradeCost);

			cout << "\n" << prop.getPropertyName() << " (" << prop.getPropertyDescription() << ") is upgraded.\n"
				<< "Rent cost is now " << prop.getPropertyRent() << ".\n"
				<< upgradeCost << " is withdrawn from your account.\n\n";

			this->reduceMoney(upgradeCost); // subtract upgrade price
		}

		else {

			if (this->getMoney() <= upgradeCost) {
				cout << "\nERROR: Not enough money to pay for the upgrade (" << upgradeCost << ") cost.\n\n";
			}
		}
	}
}

void Player::sellProperty(vector<Property>& unownedProperty, vector<Property>& board) {

	cout << "\n\nProperties:\n";
	for (auto& prop : this->ownedProperties) {
		int index = (&prop-&*(this->ownedProperties.begin()));

		cout << (index + 1) << ") " << prop.getPropertyName() << "\n";
	}

	// asks the user what property to sell
	int propertyIndex;
	cout << "\nWhich property would you like to sell?\n"
		<< ">>> ";
	cin >> propertyIndex;

	// validate then return money using property's cost + upgrades
	// then remove property from its appropriate lists
	if (cin.good()) {
		propertyIndex -= 1;

		try {
			
			int x = 0;
			for (Property prop : this->ownedProperties) {
				if (prop.getPropertyName() == this->ownedProperties.at(propertyIndex).getPropertyName()) {
					this->ownedProperties.erase(this->ownedProperties.begin() + x);
					this->addMoney(prop.getPropertyCost() + prop.getPropertyRent());

					unownedProperty.push_back(prop);

					cout << "Success!\n"
						<< this->name << " has sold " << prop.getPropertyName() << "\n";

					board[this->getPos()].setPropertyOwner("");
					board[this->getPos()].setPropertyIsOwnedBool(false);
				}

				x++;
			}
		}

		catch (exception e) {
			cout << "\n\nInvalid entry.\n";
		}
	}

	// if user enters a alphabet, symbols, etc...
	else if (cin.fail()) {
		cout << "\n\nIncorrect entry. Try again?\n\n";
		cin.clear();
		cin.ignore(256, '\n');
	}
}

int Player::getOwnStats(vector<Property>& board) {
	int playerPos = this->getPos();

	cout << "\n~ " << this->getPlayerName() << "'s Stats: ~\n"
		<< "Properties Owned: " << this->ownedProperties.size() << "\n"
		<< "Current Property's Upgrades (" << board[playerPos].getPropertyName() << "): " << board[playerPos].upgrades.size() << "\n";

	// Calculate total houses owned
	int totalHousesCounter{ 0 };
	int totalOfMaxUpgrades{ 0 };
	for (int property = 0; property < board.size(); property++) {

		if (board[property].getPropertyOwner() == this->getPlayerName()) {
			totalHousesCounter += board[property].upgrades.size();

			if (board[property].upgrades.size() == 4) {
				totalOfMaxUpgrades++;
			}
		}
	}

	cout << "Total of Owned House Upgrades: " << totalHousesCounter << "\n"
		<< "Total of Maxed House Upgrades: " << totalOfMaxUpgrades << "\n"
		<< "-------\n\n";

	// tally all player stats (including luck, which should be hidden from player's view) then return its value
	return (this->ownedProperties.size()) + (totalHousesCounter) + (totalOfMaxUpgrades) + (this->luck);
}

void Player::attackOwnProperty(vector<Property>& board) {
	srand((unsigned int) time(NULL));
	int playerPos = this->getPos();
	int turretValue{ 0 };

	if (board[playerPos].hasTurret == true) {
		turretValue = 20;
	}

	cout << "\n";
	if ((this->hasMovedAfterBuyingProperty == false) && (this->ownedProperties.size() == 0)) {
		cout << "\nERROR: GAME IS NOT WORKING AS INTENDED!\n\n";
	}

	else {
		int playerStats = this->getOwnStats(board);
		int innerChoice;

		cout << "\nWould you like to continue?\n"
			<< "1) Yes\n"
			<< "2) No\n"
			<< ">>> ";
		cin >> innerChoice;

		if (cin.good()) {

			// Attack
			if (innerChoice == 1) {

				// "player stats" + "turret value" vs. "random value from 1 to player stats"

				if ((playerStats + turretValue) >= ((rand() % playerStats) + 1)) {
					int prize = (board[playerPos].getPropertyCost()) * 2;

					cout << "\nYou won!\n"
						<< prize << " is added to your account.\n\n";

					this->addMoney(prize);
				}

				else {

					cout << "\nYou lost.\n"
						<< "Better luck next time...\n\n";
				}
			}
		}

		else if (cin.fail()) {
			cout << "\n\nIncorrect entry.\n\n";
			cin.clear();
			cin.ignore(256, '\n');
		}
	}
}

// also similar to "attackOwnProperty"
void Player::attackOtherPlayer(vector<Property>& board, Player& otherPlayer) {
	srand((unsigned int) time(NULL));
	int ownPosition = this->getPos();
	int otherPlayerPosition = otherPlayer.getPos();
	int turretValue{ 0 };

	if (board[otherPlayerPosition].hasTurret == true) {
		turretValue = 20;
	}

	cout << "\n";

	int ownStats = this->getOwnStats(board);
	int otherPlayerStats = otherPlayer.getOwnStats(board);
	int innerChoice;

	cout << "\nWould you like to continue?\n"
		<< "1) Yes\n"
		<< "2) No\n"
		<< ">>> ";
	cin >> innerChoice;

	if (cin.good()) {

		// Attack
		if (innerChoice == 1) {
			int prize = round(otherPlayer.getMoney() * 0.20);

			// own stats vs. other player's stats
			// validate results then display different outputs

			if ((ownStats == 0) && (otherPlayerStats == 0)) {

				cout << "\nError: Battle cannot be initiated when both players have nothing to offer...\n\n";
			}			

			else if ((ownStats + turretValue) >= (otherPlayerStats + turretValue)) {

				this->addMoney(prize);
				otherPlayer.reduceMoney(prize);

				cout << "\nYou won against " << otherPlayer.getPlayerName() << "!\n"
					<< prize << " is added to your account.\n"
					<< prize << " is also removed from " << otherPlayer.getPlayerName() << "'s account after losing!\n\n";
			}

			else {

				cout << "\nYou lost against " << otherPlayer.getPlayerName() << "!\n"
					<< prize << " is withdrawn from your account.\n\n";

				this->reduceMoney(prize);
			}
		}
	}

	else if (cin.fail()) {
		cout << "\n\nIncorrect entry.\n\n";
		cin.clear();
		cin.ignore(256, '\n');
	}
}

void Player::buildTurret(vector<Property>& board, int turretCost) {
	int playerPos = this->getPos();
	int innerChoice;

	cout << "\n\nTurret Cost: " << turretCost << "\n\n"
		<< "Would you like to continue building a turret on \"" << board[playerPos].getPropertyName() <<  "\"?\n"
		<< "1) Yes\n"
		<< "2) No\n"
		<< ">>> ";
	cin >> innerChoice;

	if (cin.good()) {

		// Attack
		if (innerChoice == 1) {

			if (this->getMoney() >= turretCost) {

				// subtract money when building turret
				this->reduceMoney(turretCost);
				board[playerPos].hasTurret = true;

				// display message
				cout << "\n\nA turret has been added to \"" << board[playerPos].getPropertyName() << "\".\n"
					<< turretCost << " was withdrawn from your account!\n\n";

			}
		}
	}

	else if (cin.fail()) {
		cout << "\n\nIncorrect entry.\n\n";
		cin.clear();
		cin.ignore(256, '\n');
	}
}

int Player::getPos() { return this->position; }

void Player::setPos(int x) {
	this->position = x;
}

void Player::mortageProperty(Property& prop) {
	prop.mortgageProperty();
	this->addMoney(prop.getPropertyCost());
}

void Player::unMortageProp(Property& prop) {
	prop.remvoeMortageProperty();
	this->reduceMoney(prop.getPropertyCost());
}