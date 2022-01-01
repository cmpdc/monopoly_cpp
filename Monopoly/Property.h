#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

class Property {

	friend class Player;
	friend class Game;

	private:
		std::string propertyName;
		std::string propertyDescription;
		std::string propertyOwner;

		int propertyCost;
		int propertyRent;

		bool isPurchaseable;
		bool isPropertyOwned;
		bool hasTurret;

	public:
		Property(std::string, std::string, int, int);

		bool mortageStatus = false;

		std::vector<std::string> iconOnTile;
		std::vector<std::string> upgrades;

		std::vector<Player*> playersInProperty;

		std::string getPropertyName();
		void setPropertyName(std::string);

		std::string getPropertyDescription();
		void setPropertyDescription(std::string);

		int getPropertyCost();
		void setPropertyCost(int);

		bool getIsPropertyPurchaseable();
		void setIsPropertyPurchaseable(bool);

		bool getIsPropertyOwned();
		void setPropertyIsOwnedBool(bool);

		int getPropertyRent();
		void setPropertyRent(int);

		std::string getPropertyOwner();
		void setPropertyOwner(std::string);

		void mortgageProperty();
		void remvoeMortageProperty();

		void addMarkerToTile(std::string);
		void removeMarkerOffTile(std::string);
		std::string getMarkerFromTile();

		void addUpgrade(std::string);

		std::string getUpgrade();

		std::string toString();
};
