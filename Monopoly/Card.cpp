#include <string>

#include "Card.h"

using namespace std;

Card::Card(string name, string desc, bool toJail, int giveMoney, int getMoney, bool isInventoriable) {
	this->name = name;
	this->description = desc;
	this->toJail = toJail;
	this->giveMoney = giveMoney;
	this->getMoney = getMoney;
	this->inventoriable = isInventoriable;
}

string Card::getName() { return this->name; }
Card& Card::setname(string name) {
	this->name = name;
	return *this;
}

string Card::getDescription() { return this->description; }
Card& Card::setDescription(string dec) {
	this->name = description;
	return *this;
}

bool Card::getToJail() { return this->toJail; }
Card& Card::setToJail(bool toJail) {
	this->toJail = toJail;
	return *this;
}

int Card::getReduceMoney() { return this->giveMoney; }
Card& Card::setReduceMoney(int giveMoney) {
	this->giveMoney = giveMoney;
	return *this;
}

int Card::getAddMoney() { return this->getMoney; }
Card& Card::setAddMoney(int getMoney) {
	this->getMoney = getMoney;
	return *this;
}

bool Card::isCardInventoriable() { return this->inventoriable; }

string Card::toString() {
	return "~ " + this->getName() + " ~\n" + this->getDescription();
}

