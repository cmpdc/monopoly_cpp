#include <string>

#include "Player.h"
#include "Property.h"
#include "Game.h"

using namespace std;

Property::Property(string name, string description, int cost = 0, int rent = 0) {
	this->propertyName = name;
	this->propertyDescription = description;
	this->propertyCost = cost;
	this->propertyRent = rent;

	this->isPropertyOwned = false;
	this->hasTurret = false;
}

string Property::getPropertyName() { return this->propertyName; }
void Property::setPropertyName(string name) {
	this->propertyName = name;
}

string Property::getPropertyDescription() { return this->propertyDescription; }
void Property::setPropertyDescription(string description) {
	this->propertyDescription = description;
}

int Property::getPropertyCost() { return this->propertyCost; }
void Property::setPropertyCost(int cost) {
	this->propertyCost = cost;
}

bool Property::getIsPropertyPurchaseable() { return this->isPurchaseable; }
void Property::setIsPropertyPurchaseable(bool isPurchased) {
	this->isPurchaseable = isPurchased;
}

bool Property::getIsPropertyOwned() { return this->isPropertyOwned; }
void Property::setPropertyIsOwnedBool(bool isOwned) {
	this->isPropertyOwned = isOwned;
}

int Property::getPropertyRent() { return this->propertyRent; }
void Property::setPropertyRent(int rent) {
	this->propertyRent = rent;
}

string Property::getPropertyOwner() { return propertyOwner; }

void Property::setPropertyOwner(string name) {
	propertyOwner = name;
}

void Property::mortgageProperty() {
	this->mortageStatus = true;
}

void Property::remvoeMortageProperty() {
	this->mortageStatus = false;
}

void Property::addMarkerToTile(string icon) {
	this->iconOnTile.push_back(icon);
}

void Property::removeMarkerOffTile(string icon) {
	int x = 0;

	for (string playerIcon : this->iconOnTile) {
		if (playerIcon == icon) this->iconOnTile.erase(this->iconOnTile.begin() + x);
		x++;
	}
}

string Property::getMarkerFromTile() {
	string onTileString;
	for (string thing : this->iconOnTile) {
		onTileString += thing;
	}	
	return onTileString;
}

void Property::addUpgrade(string toAdd) {
	upgrades.push_back(toAdd);
}

string Property::getUpgrade() {	return ((this->upgrades.size() < 4) ? to_string(upgrades.size()) : "MAX");
}

string Property::toString(){
	/*
	FORMAT:
		~ Property Info ~
		Name:
		Description:
		(if purchaseable) Owner: NONE or (whoever)
		Has Turret? YES/NO
	*/
	return "\n~ Property Info ~\nName: " + this->getPropertyName() +
		"\nDescription: " + this->getPropertyDescription() + ""+
		((this->isPurchaseable == false) ? "\n" : (
			"\nOwner: " + ((this->propertyOwner == "") ? "NONE" : (this->propertyOwner)) + "\n")) +
		"Has Turret? " + ((this->hasTurret == true) ? "\033[1m\033[34mYES\033[1m\033[37m" : "NO") + "\n";
}