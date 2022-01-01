#pragma once
#include <iostream>
#include <string>

class Card {

	private:
		std::string name;
		std::string description;
		bool toJail;
		int giveMoney;
		int getMoney;
		bool inventoriable;

	public:

		Card(std::string, std::string, bool, int, int, bool);
		~Card() = default;

		std::string getName();
		Card& setname(std::string name);

		std::string getDescription();
		Card& setDescription(std::string dec);

		bool getToJail();
		Card& setToJail(bool toJail);

		int getReduceMoney();
		Card& setReduceMoney(int giveMoney);

		int getAddMoney();
		Card& setAddMoney(int getMoney);

		bool isCardInventoriable();

		std::string toString();
	};
