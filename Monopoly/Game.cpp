#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "Property.h"

using namespace std;

Game::Game() {

	srand((unsigned int) time(NULL));

	// player icon list
	this->playerIcons = {"~", "!", "@", "#", "$", "%", "^", "&", "*", "+"};


	// properties object: name, buy cost, rent cost, isPurchaseable
	// -- top row
	Property p0("GO", "Start of the game", 0, 0);
	Property p1("Farm", "Farm", 60, 40);
	Property p2("R. Inn", "Rue Inn", 40, 10);
	Property p3("Cave", "Cave Party Store", 60, 40);
	Property p4("RockyR", "Rocky R. Supermarket", 200, 0);
	Property p5("Smithy", "Smith Avenue", 100, 80);
	Property p6("LuxTax", "Luxury Tax", 0, 0);
	Property p7("S. Inn", "Shonda Inn", 120, 80);
	Property p8("Arena", "Arena", 250, 150);

	// -- right col
	Property p9("Chance1", "Chance Cards 1", 0, 0);
	Property p10("Torch", "Torch Imporium", 150, 0);
	Property p11("Cart R", "Cart R. Railroad", 200, 0);
	Property p12("In. Tax", "Income Tax", 0, 0);
	Property p13("Cinema", "Cinema", 550, 120);

	// -- bottom row
	Property p14("TwnSqr", "Town Square", 0, 0);
	Property p15("Foody", "Food Mart", 260, 140);
	Property p16("Sephora", "Sephora", 200, 0);
	Property p17("BigE", "BigE", 260, 160);
	Property p18("Luck?", "Luck?", 0, 0);
	Property p19("Mill", "Mill Avenue", 280, 160);
	Property p20("Elec.", "Electric Company", 240, 120);
	Property p21("Oasis", "Oasis Avenue", 280, 160);
	Property p22("JAIL", "Jail", 0, 0);

	// -- left col
	Property p23("Chance2", "Chance Cards 2", 0, 0);
	Property p24("Tavern", "Tavern", 320, 200);
	Property p25("Cart L", "Card L. Railroad", 200, 0);
	Property p26("Granary", "Granary", 350, 220);
	Property p27("Mansion", "Mansion", 400, 250);

	// append ALL properties to board vector
	this->board = {
		p0, p1, p2, p3, p4, p5, p6, p7, p8, p9,
		p10, p11, p12, p13, p14, p15, p16, p17, p18, p19,
		p20, p21, p22, p23, p24, p25, p26, p27
	};

	// append buy-able properties to unowned property vector
	this->unownedProperty = {
		p1, p2, p3, p4, p5, p7, p8,
		p10, p11, p13, p15, p16, p17, p19,
		p20, p21, p24, p25, p26, p27
	};

	// card objects: name, description, jail, deduce money, add money, inventoriable
	// - IDK what to write here... I'm just hoping to get an A for this project to boost my cringing grade. DONT JUDGE ME!
	// - also, dont you dare attempt to make cards that move to different tiles..
	// -- YOU DONT HAVE TIME!!! FINISH THIS PROJECT ASAP!!!
	Card c0{ "DUI", "Caught driving under influence...", true, 500, 0, false};
	Card c1{ "Parking Fine", "You were in a hurry and lost track of your parking meter.", false, 100, 0, false};
	Card c2{ "Promising Chess Master", "You won against Magnus Carlsen, a chess Grand Master!", false, 0, 500, false};
	Card c3{ "Lost BitCoin", "You recover your lost bitcoins.", false, 0, 2300, true};
	Card c4{ "Car Insurance", "You paid your insurance premium.", false, 55, 0, false};
	Card c5{ "Failed Gambler", "Gambled and paid the price.", false, 600, 0, false};
	Card c6{ "Successful Gambler", "Gambled and rewarded with the price.", false, 0, 2390, true};
	Card c7{ "Forgotten Trash", "Last night's party was a blast but the trash were forgotten and your neighbors complained.", false, 40, 0, false};
	Card c8{ "Uncontrolled Whiff","A \"little\" here and there was not enough.\nYou crashed and damages were committed.", true, 9999, 0, false};
	Card c9{ "Volunteered Blood", "You volunteered at a blood drive. There were free cookies!", false, 0, 10, false};
	Card c10{ "\"Accidental\" Donation", "You \"accidentally\" donated 1000 instead of 10 to your favourite streamer.", false, 1000, 0, false};
	Card c11{ "Community Helper", "You helped your neighbor in her groceries.\nShe made you lunch to say thanks!", false, 0, 20, false};
	Card c12{ "Christmas Fund", "Your Christmas fund mature!", false, 0, 200, false};
	Card c13{ "Tax Refund", "There were tax changes due to the pandemic.\nAs a result, the DOT is giving you a refund worth 410.", false, 0, 410, true};
	Card c14{ "Drag Superstar", "You have won in a drag competition.\nYou betta WERQ!", false, 0, 2000, true };
	Card c15{ "Local Hero", "The mayor has summoned you at the Town Square to congratulate you for being the local hero!", false, 0, 500, true };
	Card c16{ "Carboon Footprint Saver", "You are awarded for choosing to deliver your purchases online\non a much later date to save carbon footprint.", false, 0, 30, true };
	Card c17{ "Children's Santa", "You spend the day playing games at a local children's hospital.", false, 0, 100, false };
	Card c18{ "Black Sheep", "You organize a family reuinion but the outcome did not turned out as you expected.", false, 350, 0, false };
	Card c19{ "\"MY DESERT, MY ARRAKIS, MY DUNE\"", "You went to Cinema to watch \"Dune\".", false, 30, 0, false };
	Card c20{ "\"Go back to the void from whence you came!\"", "You went to Cinema to watch \"The Hobbit: The Battle of the Five Armies\" but you hated the film adaptation of the novel.\nYou asked for a refund.", false, 0, 30, true };

	// append ALL card objects to chances list
	this->chancesCards = {
		c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10,
		c11, c12, c13, c14, c15, c16, c17, c18, c19, c20
	};

	// append selected card objects to lucky cards list
	this->luckyCards = {
		c2, c3, c6, c13, c14
	};

	this->randomSayings = {
		"and became suddenly cheerful.",
		"and became grateful for this neighborhood.",
		"and suddenly in the mood for ice cream.",
		"and is happy."
	};
}

Game& Game::showTitleScreen() {

	cout << "\n\n\n\n\n"
		<< "\t\t.88b  d88.  .d88b.  d8b   db  .d88b.  d8888b.  .d88b.  db   db    db\n"
		<< "\t\t88'YbdP`88 .8P  Y8. 888o  88 .8P  Y8. 88  `8D .8P  Y8. 88   `8b  d8'\n"
		<< "\t\t88  88  88 88    88 88V8o 88 88    88 88oodD' 88    88 88    `8bd8'\n"
		<< "\t\t88  88  88 88    88 88 V8o88 88    88 88~~~   88    88 88      88\n"
		<< "\t\t88  88  88 `8b  d8' 88  V888 `8b  d8' 88      `8b  d8' 88booo. 88\n"
		<< "\t\tYP  YP  YP  `Y88P'  VP   V8P  `Y88P'  88       `Y88P'  Y88888P YP\n\n\n\n"
		<< "\t\t                              by URI\n\n\n\n\n\n";


	cout << "\t\t\t\t";
	system("pause");
	this->utils.clearScreen();

	return *this;
}

Game& Game::createPlayerScreen() {
	int numOfPlayers;

	cout << "Before starting the game, enter how many players.\n"
		<< "(Mininum of 2, maximum of 6)\n"
		<< ">>> ";

	while (cin >> numOfPlayers || numOfPlayers > 2 || numOfPlayers < 6) {

		cin.clear();
		cin.ignore(256, '\n');

		// validation
		if (numOfPlayers > 6) {
			cout << "\nHmmm? I get that you have many friends\n"
				<< "but this game is designed only to be played with no more than eight players at once.\n"
				<< "Enter a valid number of players!\n"
				<< ">>> ";
		}

		else if (numOfPlayers < 2) {
			cout << "\nError. This game is designed to be played with a minimum of two players.\n"
				<< "Enter a valid number of players!\n"
				<< ">>> ";
		}

		// exit while loop if number of player meets criteria
		else break;
		
		
	}

	// iterate over number of players entered
	for (int i = 0; i < numOfPlayers; i++) {
		string playerName;
		int selectedColorNum{ 0 };
		string playerMarker;

		bool validMarker = false;

		// validate name to be 4 characters length
		while (playerName.length() != 3) {
			cout << "\nEnter Player #" << (i + 1) << "'s name (three characters in length)\n"
				<< ">>> ";
			cin >> playerName;
		}
	 
		// validate marker
		while (!validMarker) {
			cout << "\nAvailable icons: ";
			for (string icon : this->playerIcons)  cout << icon << " ";
			
			cout << "\nSelect a marker for " << utils.str_UpperCase(playerName) << ": ";
			cin >> playerMarker;

			vector<string>::iterator markerSelection = find(this->playerIcons.begin(), this->playerIcons.end(), playerMarker);
			if (markerSelection == this->playerIcons.end()) cout << "Not a valid marker!" << endl;
			else {
				this->playerIcons.erase(markerSelection);
				validMarker = true;
			}

		}

		//adds the created player to the game objects list of players
		playerList.push_back(Player(utils.str_UpperCase(playerName), playerMarker, 1000));

		cout << "\n------\n";
	}


	// player object: name, icon, color, money
	// -- for testing
	//playerList.push_back(Player("URI", "@", 9900));
	//playerList.push_back(Player("REA", "!", 1500));
	//playerList.push_back(Player("SHU", "$", 1500));

	return *this;
}

Game& Game::initGame() {
	int upgradeCost{ 500 };
	int turretCost{ 350 };

	// iterate until the winner is left in the game
	while (this->playerList.size() > 1) {

		// initialize player locations
		for (Player& player : this->playerList) {
			board[player.getPos()].addMarkerToTile(player.getPlayerMarker());
		}

		// add menu to players
		for (Player& player : this->playerList) {
			int playerIndexes = (&player - &*(this->playerList.begin()));
			Player currentPlayer = playerList.at(playerIndexes);

			int choice = 0;
			bool playerEnded = false;

			player.canMove = true;
			player.hasEnded = false;

			vector<string> menu = {
				"Inventory",
				"Property Info",
				"Players Info",
				"Cheat Menu"
			};

			this->checkPlayers(this->playerList);

			// own move
			while (playerEnded != true) {

				utils.pauseScreen();
				utils.clearScreen();
				this->printBoard(this->board, player);

				// append players locations AFTER moving
				// otherwise remove --- removing the element is needed!!
				if (player.canMove == false) {

					// validate -- this is to verify the element only append ONCE
					if (
						find(
							board[player.getPos()].playersInProperty.begin(),
							board[player.getPos()].playersInProperty.end(),
							&player
						) == board[player.getPos()].playersInProperty.end()) {

						board[player.getPos()].playersInProperty.push_back(&player);
					}
				}
				else {
					board[player.getPos()].playersInProperty.erase(
						remove(
							board[player.getPos()].playersInProperty.begin(),
							board[player.getPos()].playersInProperty.end(),
							&player
						),

						board[player.getPos()].playersInProperty.end()
					);

				}

				// append/remove
				// --- verify if element does not already exist beforehand otherwise append

				// toggle move and end turn options
				if ((player.canMove == true) || (player.hasRolledDouble == true)) {
					if (find(menu.begin(), menu.end(), "Move") == menu.end()) {
						menu.insert(menu.begin(), "Move");
					}
					
					menu.erase(remove(menu.begin(), menu.end(), "End Turn"), menu.end());
				}
				else {
					if (find(menu.begin(), menu.end(), "End Turn") == menu.end()) {
						menu.insert(menu.begin(), "End Turn");
					}

					menu.erase(remove(menu.begin(), menu.end(), "Move"), menu.end());
				}

				// toggle railroad option
				if ((player.getPos() == 11) || (player.getPos() == 25)) {

					if (find(menu.begin(), menu.end(), "Travel RailRoad") == menu.end()) {
						menu.push_back("Travel RailRoad");
					}
				}
				else {
					menu.erase(remove(menu.begin(), menu.end(), "Travel RailRoad"), menu.end());
				}

				// toggle auction/buy property options
				// -- delete option if player is not in a purchaseable property
				if ((board[player.getPos()].getPropertyName() == "GO") ||
					(board[player.getPos()].getPropertyName() == "LuxTax") || 
					(board[player.getPos()].getPropertyName() == "Chance") || 
					(board[player.getPos()].getPropertyName() == "In.Tax") || 
					(board[player.getPos()].getPropertyName() == "TwnSqr") || 
					(board[player.getPos()].getPropertyName() == "Luck?") || 
					(board[player.getPos()].getPropertyName() == "JAIL") || 
					(board[player.getPos()].getPropertyName() == "Chest")) {

					// -- delete options if property's owner is not the player
					if (board[player.getPos()].getPropertyOwner() != player.getPlayerName()) {
						//menu.erase(remove(menu.begin(), menu.end(), "Auction Property"), menu.end());
						menu.erase(remove(menu.begin(), menu.end(), "Buy Property"), menu.end());

					}

				}

				// -- add options if player is in purchaseable property 
				else{
					/*if (find(menu.begin(), menu.end(), "Auction Property") == menu.end()) {
						menu.push_back("Auction Property");
					}*/

					if (find(menu.begin(), menu.end(), "Buy Property") == menu.end()) {
						menu.push_back("Buy Property");
					}

					// delete options if player is the property's owner... think about it: you can't rebuy a property!
					// STOP EDITING THIS. YOU ALREADY FIXED THE ISSUE
					// NOTE: I have to edit the condition lol
					// ---- remove option if player do not have enough money to buy property
					if ((board[player.getPos()].getPropertyOwner() == player.getPlayerName()) ||
						(board[player.getPos()].getPropertyCost() >= player.getMoney())) {
						//menu.erase(remove(menu.begin(), menu.end(), "Auction Property"), menu.end());
						menu.erase(remove(menu.begin(), menu.end(), "Buy Property"), menu.end());

					}

				}

				// toggle selling, upgrading property, and building turret options
				// check ownProperty list size
				if (player.ownedProperties.size() != 0) {

					if (find(menu.begin(), menu.end(), "Sell Property") == menu.end()) {
						menu.push_back("Sell Property");
					}

					if ((player.getMoney() >= turretCost) &&
						(board[player.getPos()].getPropertyOwner() == player.getPlayerName())) {

						if (board[player.getPos()].hasTurret == false) {
							if (find(menu.begin(), menu.end(), "Build Turret") == menu.end()) {
								menu.push_back("Build Turret");
							}
							
						}
						else {
							menu.erase(remove(menu.begin(), menu.end(), "Build Turret"), menu.end());
						}
					}

					if ((player.getMoney() >= upgradeCost) &&
						(board[player.getPos()].getPropertyOwner() == player.getPlayerName()) &&
						((board[player.getPos()].upgrades.size() < 4))
						) {
						
						if (find(menu.begin(), menu.end(), "Upgrade Property") == menu.end()) {
							menu.push_back("Upgrade Property");
						}
					}
					else{

						// SO MANY CONDITIONALS!! WHY?? FIX AND SIMPLY THIS!!!
						if (board[player.getPos()].upgrades.size() >= 4) {
							menu.erase(remove(menu.begin(), menu.end(), "Upgrade Property"), menu.end());
						}
					}
				}
				else {
					menu.erase(remove(menu.begin(), menu.end(), "Sell Property"), menu.end());
					menu.erase(remove(menu.begin(), menu.end(), "Upgrade Property"), menu.end());
				}

				// toggle mortgage option
				if (player.mortagedProperties.size() != 0) {
					if (find(menu.begin(), menu.end(), "Pay Mortgage") != menu.end()) {
						menu.push_back("Pay Mortgage");
					}
				}
				else {
					menu.erase(remove(menu.begin(), menu.end(), "Pay Mortgage"), menu.end());
				}

				// toggle attack own property option
				// -- only works AFTER buying a property AND has moved...
				if ((board[player.getPos()].getPropertyOwner() == player.getPlayerName()) && (player.hasMovedAfterBuyingProperty == true)) {
					if (find(menu.begin(), menu.end(), "Attack Own Property") == menu.end()) {
						menu.push_back("Attack Own Property");
					}
				}
				else {
					menu.erase(remove(menu.begin(), menu.end(), "Attack Own Property"), menu.end());
				}

				// toggle attack other player
				if (board[player.getPos()].playersInProperty.size() > 1) {
					if (find(menu.begin(), menu.end(), "Attack Other Players") == menu.end()) {
						menu.push_back("Attack Other Players");
					}
				}
				else {
					menu.erase(remove(menu.begin(), menu.end(), "Attack Players"), menu.end());
				}

				// display menu
				cout << "\n\nMenu selection for " << player.getPlayerName() << ":\n";
				for (int i = 0; i < menu.size(); i++) {
					cout << (i + 1) << ") " << menu.at(i) << "\n";
				}
				cout << ">>> ";
				cin >> choice;

				// if user enters a number
				if (cin.good()) {

					// exception handling because I'm using the index of a vector as a selector of the menu
					try {
						string menuSelector = menu.at(choice - 1);

						if (menuSelector == "Move") {
							utils.clearScreen();
							this->printBoard(this->board, player);

							if ((player.canMove == true) || (player.hasRolledDouble == true)) {

								this->movePlayer(player).perTileFunctions(board, playerList, player);

								player.canMove = false;
							}

							else {
								cout << "\n\nYou already moved your turn!\n";
							}
						}

						else if (menuSelector == "End Turn") {
							utils.clearScreen();
							this->printBoard(this->board, player);

							cout << "\n";

							if (player.canMove == false) {
								cout << "Ending Turn.\n";

								player.hasEnded = true;
								playerEnded = true;

								// switch multiple boolean
								// -- this is an indicator for attacking own property
								if (player.justBoughtProperty == true) {
									player.hasMovedAfterBuyingProperty = true;
								}
								else {
									player.hasMovedAfterBuyingProperty = false;
								}
							}

							else {
								choice = 0;

								cout << "\n" << player.getPlayerName() << " has not moved yet! Must move to end turn.\n";
							}

						}

						else if (menuSelector == "Inventory"){
							if (player.cardInventory.size() == 0) {
								cout << "\nYou have no cards in your inventory...\n\n";
							}

							else {
								cout << "\nInventory:\n\n";
								for (int i = 0; i < player.cardInventory.size(); i++) {
									Card card = player.cardInventory[i];

									cout << "Card #" << (i + 1) << ": "
										<< card.getName() << "\n"
										<< card.getDescription() << "\n\n";
								}

								int cardChoice;
								cout << "-----\n"
									<< "Would you like to use a card?\n"
									<< "1) Yes\n"
									<< "2) No\n"
									<< ">>> ";
								cin >> cardChoice;

								if (cin.good()) {
									if (cardChoice == 1) {

										int cardSelected;
										cout << "\n\nSelect which card: ";
										cin >> cardSelected;

										if (cin.good()) {
											Card selectedCard = player.cardInventory[cardSelected - 1];

											cout << "\n" << selectedCard.toString() << "\n";
											if (selectedCard.getAddMoney() > 0) {
												player.addMoney(selectedCard.getAddMoney());

												cout << "\n" << selectedCard.getAddMoney() << " is added to your money.\n\n\n";
											}
											else {
												player.reduceMoney(selectedCard.getReduceMoney());

												cout << "\n" << selectedCard.getReduceMoney() << " is withdrawn from your money.\n\n\n";
											}
										}

										else if (cin.bad()) {

											cout << "\n\nIncorrect entry. Try again?\n\n";
											cin.clear();
											cin.ignore(256, '\n');
										}
									}

									else if(cardChoice == 2){}

									else {
										cout << "\n\nInvalid entry. Try again?\n\n";
									}
								}

								else if (cin.bad()) {

									cout << "\n\nIncorrect entry. Try again?\n\n";
									cin.clear();
									cin.ignore(256, '\n');
								}
							}
						
						}

						else if (menuSelector == "Property Info") {

							cout << board[player.getPos()].toString();
						}

						else if (menuSelector == "Players Info"){
							for (Player player : this->playerList) {
								cout << "\nName: " << player.getPlayerName() << "\n"
									<< "Icon: " << player.getPlayerMarker() << "\n"
									<< "Money: " << player.getMoney() << "\n"
									<< "Properties: ";

								if (player.ownedProperties.size() != 0) {
									for (auto& prop : player.ownedProperties) {
										cout << prop.getPropertyName();

										if (sizeof(prop) != 0) {
											if (&prop != &player.ownedProperties.back()) {
												cout << ", "; // this is to add comma
											}
										}

										if (sizeof(prop) % 5) cout << "\n"; // add new line
									}
								}

								else cout << "NONE";
								cout << "\n";
							}

							cout << "\n";
						
						}

						else if (menuSelector == "Cheat Menu"){
							utils.clearScreen();
							this->printBoard(this->board, player);

							int subChoice;
							cout << "\nCheat Menu:\n"
								<< "1) Add Money\n"
								<< "2) Move Location\n"
								<< "3) Enable Moving\n"
								<< "4) Enable Attacking Own Property\n"
								<< ">>> ";
							cin >> subChoice;

							// if user enters a valid option
							if (cin.good()) {

								switch (subChoice) {
									// add dirty money
									case 1: {
										int newMoney;

										cout << "\n\nEnter amount: ";
										cin >> newMoney;

										// set max to 9999
										if (newMoney >= 9999) {
											newMoney = 9999;

											cout << "\n\nYou entered too much money.\n"
												<< "Money is capped at 9999!\n\n";
										}

										player.setMoney(newMoney);

										break;
									}

									// jump to new location
									case 2: {
										int newPos;

										cout << "\n\nSelect Location:\n\n";
										for (int index = 0; index < board.size(); index++) {
											cout << "" << (index + 1) << ". "
												<< board[index].getPropertyName()
												<< " (" << board[index].getPropertyDescription() << ")\n";
										}

										cout << ">>> ";
										cin >> newPos;

										cout << "\n";

										this->movePlayerManual(player, newPos - 1).perTileFunctions(board, playerList, player);

										break;
									}

									// player can move
									case 3: {
										player.canMove = true;

										cout << "\nMoving Enabled.\n\n";

										break;
									}

									// player can attack own property
									case 4: {
										if (player.justBoughtProperty == true) {
											player.hasMovedAfterBuyingProperty = true;

											cout << "\nAttacking Own Property Enabled.\n\n";
										}
										else {
											player.hasMovedAfterBuyingProperty = false;
										}

										break;
									}

									default: {
										cout << "\n\nInvalid entry. Try again?\n\n";
										break;
									}

								}
							}

							// otherwise...
							else if (cin.bad()) {

								cout << "\n\nIncorrect entry. Try again?\n\n";
								cin.clear();
								cin.ignore(256, '\n');
							}
						
						}

						else if (menuSelector == "Travel RailRoad") {
							utils.clearScreen();
							this->printBoard(this->board, player);

							if (player.canMove == true) {
								this->printBoard(this->board, player).travelRailRoad(player);

								player.canMove = false;
							}

							else {
								cout << endl;
								cout << "\nYou already moved in this turn!\n";
							}
						}

						/*
						* I cannot make this work
						* And I am running out of time so... i give up
						
						
						else if (menuSelector == "Auction Property") {

							this->biddersList = this->playerList;

							cout << "\n\n------\n"
								<< "Auction for \"" << board[player.getPos()].getPropertyName() << "\" "
								<< "(" << board[player.getPos()].getPropertyDescription() << ").\n\n"
								<< "Highest bidder will win the auction and thus will own the property.\n\n";

							bool failPromptPrinted = false;
							bool hasBidderDeclined = false;
							int propertyValue = board[player.getPos()].getPropertyCost();
							int currentBidValue = propertyValue;


							while (this->biddersList.size() > 1) {

								for (Player bidder : this->biddersList) {
									int bidderIndex = (&bidder - &*(this->biddersList.begin()));

									unsigned int bidValue = 0;
									unsigned int auctionChoice = 0;

									cout << "\n~ Current auction value is at " << currentBidValue << "! ~\n";

									if ((bidder.getMoney() >= currentBidValue)) {
										cout << "\nBidder: " << bidder.getPlayerName() << "\n"
											<< "Select option:\n"
											<< "1) Auction\n"
											<< "2) Decline\n"
											<< ">>> ";
										cin >> auctionChoice;

										if (cin.good()) {

											if (auctionChoice == 1) {

												while (true) {
													cout << "\nEnter bid value: ";
													cin >> bidValue;

													if (cin.good()) {

														if ((bidder.getMoney() >= bidValue) && (bidValue >= currentBidValue)) {
															cout << "\n" << bidder.getPlayerName() << " for " << bidValue << "\n";
															currentBidValue = bidValue;

															break;
														}

														else cout << "\nInvalid amount!\n";

													}

													else if (cin.fail()) {
														cout << "\nInvalid entry. Enter a valid bid value.\n\n";
														cin.clear();
														cin.ignore(256, '\n');
													}
												}
											}

											else if (auctionChoice == 2) {

												cin.clear();

												this->biddersList.erase(this->biddersList.begin() + bidderIndex);
													
											}
										}

										else if (cin.fail()) {
											cout << "\nInvalid option. Enter a valid bid value.\n\n";
											cin.clear();
											cin.ignore(256, '\n');
										}
									}
									else {
										if (failPromptPrinted == false) {
											cout << "\n" << bidder.getPlayerName() << " is unable to participate due to insufficent funds.\n\n";

											failPromptPrinted = true;
										}

										else {
											cout << "\n" << bidder.getPlayerName() << " skipped.\n\n";
										}
									}
								}


							}


							// display auction winner
							// set property data to winner
							for (Player& bidder : this->biddersList) {
								if (this->biddersList.size() == 1) {

									board[player.getPos()].setPropertyCost(currentBidValue);
									board[player.getPos()].setPropertyOwner(bidder.getPlayerName());

									cout << "\n" << bidder.getPlayerName() << " won the auction for "
										<< currentBidValue << "!\n\n";


									break;

								}
							}

							cout << "\n\n";
						}

						*/

						else if (menuSelector == "Buy Property"){

							cout << "\n";
							player.buyProperty(this->unownedProperty, this->board);

						}

						else if (menuSelector == "Sell Property"){
							utils.clearScreen();
							this->printBoard(this->board, player);

							cout << "\n";
							player.sellProperty(this->unownedProperty, this->board);

						}

						else if (menuSelector == "Upgrade Property"){
							utils.clearScreen();
							this->printBoard(this->board, player);

							cout << "\n";
							player.upgradeProperty(board, upgradeCost);

						}

						else if (menuSelector == "Pay Mortgage"){

							int mortgagedIndex;
							cout << "\nMortgaged Properties:\n";
							for (int i = 0; i < player.mortagedProperties.size(); i++) {
								cout << (i + 1) << ") " << player.mortagedProperties[i].getPropertyName() << ": "
									<< player.mortagedProperties[i].getPropertyCost() << "\n";
							}

							cout << "Which property you would like to pay? ";
							cin >> mortgagedIndex;

							if (cin.good()) {
								mortgagedIndex -= 1;
								int x = 0;

								try {
									for (Property prop : player.mortagedProperties) {
										if ((player.mortagedProperties[mortgagedIndex].getPropertyName() == prop.getPropertyName())
											&& (player.getMoney() >= prop.getPropertyCost())) {

											cout << "\nSuccess!\n"
												<< player.mortagedProperties[mortgagedIndex].getPropertyCost() << " has been withdrawn from your account.\n";

											player.unMortageProp(prop);
											board[player.getPos()].mortageStatus = false;

											player.ownedProperties.push_back(prop);
											player.mortagedProperties.erase(player.mortagedProperties.begin() + x);
										}
										x++;
									}
								}

								catch (exception e) {
									cout << "\n\nInvalid entry. Try again?\n\n";
								}
							}

							else if (cin.bad()) {
								cout << "\n\nIncorrect entry. Try again?\n\n";
								cin.clear();
								cin.ignore(256, '\n');
							}
							
						}

						else if (menuSelector == "Attack Own Property") {
							player.attackOwnProperty(board);
						}

						else if (menuSelector == "Attack Other Players") {

							// append all players that is in a property to "playersToAttack" list EXCEPT current player
							for (Player* playerInProperty : board[player.getPos()].playersInProperty) {

								if (playerInProperty != &player) {

									if (find(playersToAttack.begin(), playersToAttack.end(), playerInProperty) == playersToAttack.end()) {
										playersToAttack.push_back(playerInProperty);
									}

								}
							}

							if (this->playersToAttack.size() == 1) {
								// NOTE: you're using "0" as an index because 
								// ----- this is under the condition that players in the list has "one" player.
								// ----- given that, current player was not appended.

								player.attackOtherPlayer(board, *playersToAttack.at(0));
							}

							else {
								int playerToAttackSelected;
								cout << "\n\nSelect a player to attack:\n";
								for (Player* playerToAttack : this->playersToAttack) {
									ptrdiff_t playerToAttackIndex = (playerToAttack - &*playersToAttack[0]);

									cout << (playerToAttackIndex + 1) << ") " << playerToAttack->getPlayerName() << "\n";
								}
								cout << ">>> ";
								cin >> playerToAttackSelected;

								if (cin.good()) {

									try {
										// select player object by using "at()"
										player.attackOtherPlayer(board, *playersToAttack.at(playerToAttackSelected));

									}
									catch (exception e) {
										cout << "\n\nInvalid entry. Try again?\n\n";
									}

								}

								else if (cin.bad()) {
									cout << "\n\nIncorrect entry. Try again?\n\n";
									cin.clear();
									cin.ignore(256, '\n');
								}
							}

						}

						else if (menuSelector == "Build Turret") {
							player.buildTurret(board, turretCost);
						}
					}

					catch (exception e) {
						cout << "\n\nInvalid entry. Try again?\n\n";
					}
				}

				// if user enters a alphabet, symbols, etc...
				else if (cin.fail()) {
					cout << "\n\nIncorrect entry. Try again?\n\n";
					cin.clear();
					cin.ignore(256, '\n');
				}
			}
		}
	}


	// display message until above loop is done
	cout << "Congratulations! " << playerList[0].getPlayerName() << " has won!\n";

	return *this;
}

Game& Game::printInnerTileTitle(vector<Property> board, int index, Player player) {

	// differentiate a property with/without turret!
	if (board[index].hasTurret == false) {
		cout << " " << board[index].getPropertyName();
	}
	else {
		cout << "\033[1m\033[34m" << " " << board[index].getPropertyName() << "\033[1m\033[37m";
	}

	// relative positioning for property names
	for (int i = 2; i <= 8; i++) {
		if (board[index].getPropertyName().length() == i) cout << setw(8 - i);
	}

	cout << left << " "
		<< ((board[index].getPropertyOwner() == "") ? "    " : board[index].getPropertyOwner() + " ")
		<< "|" << internal;

	return *this;
}

Game& Game::printInnerTileIcons(vector<Property> board, int index) {

	// Re-attempt adding colors for each player's icon <<<< IMPORTANT
	cout << " " << board[index].getMarkerFromTile();

	// relative positioning for property names
	for (int i = 0; i < 8; i++) {
		if (board[index].getMarkerFromTile().length() == i) cout << setw(12 - i) << " ";
	}

	cout << "|";

	return *this;
}

// Using template as a way of passing lambda as an argument
// P.S. My hatred with C++ is off the roof...
template <typename T>
Game& Game::printInnerTileInfos(vector<Property> board, int index, string text, T boardFunc) {

	if (board[index].getPropertyCost() != 0) {
		cout << text << setw(9) << boardFunc << setw(2) << "|";
	}

	else cout << setw(14) << "|";

	return *this;
}

Game& Game::printTopRow(vector<Property> board, Player player) {

	// border
	cout << "\n\t|";
	for (int i = 0; i < 9; i++) {
		cout << "-------------|";
	}

	// property info
	cout << "\n\t|";
	for (int x = 0; x < 9; x++) {
		this->printInnerTileTitle(board, x, player);
	}

	// right side of the board
	cout << setw(25)
		<< "~ Current Player ~"
		<< "\n" << internal;

	cout << "\t|";

	// player icons
	for (int x = 0; x < 9; x++) {
		this->printInnerTileIcons(board, x);
	}

	// player name on the right side
	cout << setw(15) << "Name: " << setw(8) << player.getPlayerName();

	cout << "\n\t|";
	for (int x = 0; x < 9; x++) {

		// cost
		this->printInnerTileInfos(board, x, " C:", board[x].getPropertyCost());
	}

	// player icon on the right side
	cout << setw(14) << "Icon:" << setw(9) << player.getPlayerMarker();

	cout << "\n\t|";
	for (int x = 0; x < 9; x++) {

		// rent
		this->printInnerTileInfos(board, x, " R:", board[x].getPropertyRent());
	}

	// location
	cout << setw(15) << "Loc:  " << setw(8) << board[player.getPos()].getPropertyName();

	cout << "\n\t|";
	for (int x = 0; x < 9; x++) {

		// upgrade
		this->printInnerTileInfos(board, x, " U:", board[x].getUpgrade());
	}

	// player money on the right side
	cout << setw(15) << "Money:" << setw(8) << player.getMoney();


	// border
	cout << "\n\t|";
	for (int i = 0; i < 9; i++) {
		cout << "-------------|";
	}

	return *this;
}

Game& Game::printMidRow1(vector<Property> board, int boardIndexLeft, int boardIndexRight, Player player) {

	// property info - left
	cout << "\n\t|";
	this->printInnerTileTitle(board, boardIndexLeft, player);

	// property info - right
	cout << setw(98) << "|";
	this->printInnerTileTitle(board, boardIndexRight, player);

	// players icons
	cout << "\n\t|";

	// players icons - left
	this->printInnerTileIcons(board, boardIndexLeft);

	cout << setw(98) << "|";

	// players icons - right
	this->printInnerTileIcons(board, boardIndexRight);

	// display owned properties to the right of map - header
	cout <<  setw(26) << "~ Owned Properties ~";

	// cost
	cout << "\n\t|";

	// cost - left
	this->printInnerTileInfos(board, boardIndexLeft, " C:", board[boardIndexLeft].getPropertyCost());

	// cost - right
	cout << setw(98) << "|";
	this->printInnerTileInfos(board, boardIndexRight, " C:", board[boardIndexRight].getPropertyCost());

	// display owned properties to the right of map - content
	cout << setw(14);
	for (auto& prop : player.ownedProperties) {
		cout << prop.getPropertyName();

		// add comma if element is not last
		if ((sizeof(prop) != 0) && (&prop != &player.ownedProperties.back())) cout << ", ";
		else cout << " ";
	}

	// rent
	cout << "\n\t|";

	// rent - left
	this->printInnerTileInfos(board, boardIndexLeft, " R:", board[boardIndexLeft].getPropertyRent());

	// rent - right
	cout << setw(98) << "|";
	this->printInnerTileInfos(board, boardIndexRight, " R:", board[boardIndexRight].getPropertyRent());

	// upgrade
	cout << "\n\t|";

	// upgrade - left
	this->printInnerTileInfos(board, boardIndexLeft, " U:", board[boardIndexLeft].getUpgrade());

	// upgrade - right
	//cout << setw(98) << "|";

	cout << "               "
	<< ".88b  d88.  .d88b.  d8b   db  .d88b.  d8888b.  .d88b.  db   db    db"
	<< "              "
	<< "|" << internal;

	this->printInnerTileInfos(board, boardIndexRight, " U:", board[boardIndexRight].getUpgrade());

	// border
	cout << "\n\t|-------------|"
		//<< setw(112)
		<< "               "
		<< "88'YbdP`88 .8P  Y8. 888o  88 .8P  Y8. 88  `8D .8P  Y8. 88   `8b  d8'"
		<< "              "
		<< "|-------------|";


	return *this;
}

Game& Game::printMidRow2(vector<Property> board, int boardIndexLeft, int boardIndexRight, Player player) {


	// property info - left
	cout << "\n\t|";
	this->printInnerTileTitle(board, boardIndexLeft, player);

	cout << "               "
		<< "88  88  88 88    88 88V8o 88 88    88 88oodD' 88    88 88    `8bd8'"
		<< "               ";

	// property info - right
	cout << "|";
	this->printInnerTileTitle(board, boardIndexRight, player);


	// players icons
	cout << "\n\t|";

	// players icons - left
	this->printInnerTileIcons(board, boardIndexLeft);

	cout << "               "
		<< "88  88  88 88    88 88 V8o88 88    88 88~~~   88    88 88      88"
		<< "                 "
		<< "|";

	// players icons - right
	this->printInnerTileIcons(board, boardIndexRight);

	// display owned properties to the right of map - header
	cout << setw(28) << "~ Mortaged Properties ~";

	// cost
	cout << "\n\t|";

	// cost - left
	this->printInnerTileInfos(board, boardIndexLeft, " C:", board[boardIndexLeft].getPropertyCost());

	// cost - right
	cout
		//<< setw(98)
		<< "               "
		<< "88  88  88 `8b  d8' 88  V888 `8b  d8' 88      `8b  d8' 88booo. 88"
		<< "                 "
		<< "|";
	this->printInnerTileInfos(board, boardIndexRight, " C:", board[boardIndexRight].getPropertyCost());

	// display owned properties to the right of map - content
	cout << setw(30);
	for (auto& prop : player.mortagedProperties) {
		cout << prop.getPropertyName();

		// add comma if element is not last
		if ((sizeof(prop) != 0) && (&prop != &player.mortagedProperties.back())) cout << ", ";
		else cout << " ";
	}

	// rent
	cout << "\n\t|";

	// rent - left
	this->printInnerTileInfos(board, boardIndexLeft, " R:", board[boardIndexLeft].getPropertyRent());

	// rent - right
	cout
		//<< setw(98)
		<< "               "
		<< "YP  YP  YP  `Y88P'  VP   V8P  `Y88P'  88       `Y88P'  Y88888P YP"
		<< "                 "
		<< "|";
	this->printInnerTileInfos(board, boardIndexRight, " R:", board[boardIndexRight].getPropertyRent());

	// upgrade
	cout << "\n\t|";

	// upgrade - left
	this->printInnerTileInfos(board, boardIndexLeft, " U:", board[boardIndexLeft].getUpgrade());

	// upgrade - right
	cout << setw(98) << "|";
	this->printInnerTileInfos(board, boardIndexRight, " U:", board[boardIndexRight].getUpgrade());

	return *this;
}

Game& Game::printMidRow3(vector<Property> board, int boardIndexLeft, int boardIndexRight, Player player) {

	cout << "\n\t|-------------|" << setw(113) << "|-------------|\n";

	// property info - left
	cout << "\t|";
	this->printInnerTileTitle(board, boardIndexLeft, player);

	// property info - right
	cout << setw(98) << "|";
	this->printInnerTileTitle(board, boardIndexRight, player);

	// players icons
	cout << "\n\t|";

	// players icons - left
	this->printInnerTileIcons(board, boardIndexLeft);

	cout << setw(98) << "|";

	// players icons - right
	this->printInnerTileIcons(board, boardIndexRight);

	// cost
	cout << "\n\t|";

	// cost - left
	this->printInnerTileInfos(board, boardIndexLeft, " C:", board[boardIndexLeft].getPropertyCost());

	// cost - right
	cout << setw(98) << "|";
	this->printInnerTileInfos(board, boardIndexRight, " C:", board[boardIndexRight].getPropertyCost());

	// rent
	cout << "\n\t|";

	// rent - left
	this->printInnerTileInfos(board, boardIndexLeft, " R:", board[boardIndexLeft].getPropertyRent());

	// rent - right
	cout << setw(98) << "|";
	this->printInnerTileInfos(board, boardIndexRight, " R:", board[boardIndexRight].getPropertyRent());

	// upgrade
	cout << "\n\t|";

	// upgrade - left
	this->printInnerTileInfos(board, boardIndexLeft, " U:", board[boardIndexLeft].getUpgrade());

	// upgrade - right
	cout << setw(98) << "|";
	this->printInnerTileInfos(board, boardIndexRight, " U:", board[boardIndexRight].getUpgrade());

	return *this;
}

Game& Game::printBottomRow(vector<Property> board, Player player) {

	// border
	cout << "\n\t|";
	for (int i = 0; i < 9; i++) {
		cout << "-------------|";
	}

	// property info
	cout << "\n\t|";
	for (int x = 22; x > 13; x--) {
		this->printInnerTileTitle(board, x, player);
	}

	// player icons
	cout << "\n\t|";
	for (int x = 22; x > 13; x--) {
		this->printInnerTileIcons(board, x);
	}


	cout << "\n\t|";
	for (int x = 22; x > 13; x--) {

		// cost
		this->printInnerTileInfos(board, x, " C:", board[x].getPropertyCost());
	}

	cout << "\n\t|";
	for (int x = 22; x > 13; x--) {

		// rent
		this->printInnerTileInfos(board, x, " R:", board[x].getPropertyRent());
	}

	cout << "\n\t|";

	for (int x = 22; x > 13; x--) {

		// upgrade
		this->printInnerTileInfos(board, x, " U:", board[x].getUpgrade());
	}

	cout << "\n\t|";
	for (int i = 0; i < 9; i++) {
		cout << "-------------|";
	}

	cout << "\n";


	return *this;
}

Game& Game::printBoard(vector<Property> board, Player player) {
	this->printTopRow(board, player)
		.printMidRow1(board, 27, 9, player)
		.printMidRow2(board, 26, 10, player)
		.printMidRow3(board, 25, 11, player)
		.printMidRow3(board, 24, 12, player)
		.printMidRow3(board, 23, 13, player)
		.printBottomRow(board, player);

	return *this;
}

// random number between 1-5
int Game::diceRoll() {return rand() % 5 + 1;}

Card& Game::cardRandomizer() {
	srand((unsigned int) time(NULL));

	// randomly select a card from cards list - no erasing whatsoever
	// so players can get duplicates...
	return this->chancesCards[rand() % this->chancesCards.size()];
}

Game& Game::movePlayer(Player &player) {
	srand((unsigned int) time(NULL));

	int oldPos = player.getPos();

	int diceResult_1 = this->diceRoll();
	int diceResult_2 = this->diceRoll();

	// set "hasRolledDouble" to true if both dice gets the same result
	// then increment counter
	// otherwise reset
	if (diceResult_1 == diceResult_2) {
		player.hasRolledDouble = true;
		player.rolledDoubleCounter++;
	}

	else {
		player.hasRolledDouble = false;
		player.rolledDoubleCounter = 0;
	}

	int diceTotal = diceResult_1 + diceResult_2;
	int newPos = oldPos + diceTotal;

	if (newPos <= 25) newPos = newPos;

	else if (newPos > 25) {
		newPos -= 26;
		player.addMoney(200);
	}

	else cout << "ERROR!\n";

	// display result
	cout << "\n\nMove Results:\n\n";
	cout << "Dice 1: " << diceResult_1 << "\n";
	cout << "Dice 2: " << diceResult_2 << "\n";
	cout << "Dice Total: " << diceTotal << "\n\n";

	if (player.rolledDoubleCounter < 3) {
		if (diceResult_1 == diceResult_2) cout << "Nice, you rolled a double!\n\n";
	}

	else {
		cout << "Huh?? You rolled a double three times in a row?!\n"
			<< "Super unlikely! LIES! Go to jail.\n\n";

		player.inJail = true;
	}

	// move player to jail
	if (player.inJail == true) {
		newPos = 22;
		player.canMove = false;
	}

	// set player position in the board
	player.setPos(newPos);

	// move player icons
	board[oldPos].removeMarkerOffTile(player.getPlayerMarker());
	board[newPos].addMarkerToTile(player.getPlayerMarker());

	cout << player.getPlayerName()
		<< " has moved from \"" << board[oldPos].getPropertyName()
		<< "\" (" << board[oldPos].getPropertyDescription()
		<< ") to \"" << board[newPos].getPropertyName() << "\" ("
		<< board[newPos].getPropertyDescription() << ").\n\n";

	return *this;
}

Game& Game::movePlayerManual(Player &player, int newPos) {
	int oldPos = player.getPos();

	player.setPos(newPos);

	board[oldPos].removeMarkerOffTile(player.getPlayerMarker());
	board[newPos].addMarkerToTile(player.getPlayerMarker());

	cout << player.getPlayerName() << " has moved from \""
		<< board[oldPos].getPropertyName() << "\" (" << board[oldPos].getPropertyDescription() << ") to \""
		<< board[newPos].getPropertyName() <<  "\" (" << board[newPos].getPropertyDescription() << ")\n";

	return *this;
}

// program different actions per tile
Game& Game::perTileFunctions(vector<Property> &board, vector<Player> &playerList, Player &player) {
	srand((unsigned int) time(NULL));
	string playerPosition = board[player.getPos()].getPropertyName();

	cout << "-----\n";

	if ((playerPosition == "GO") && (player.hasTakenFirstMove == true)) {

		// adds money when player lands on "GO" tile AFTER moving
		player.addMoney(200);

		// display message
		cout << "\n" << player.getPlayerName() << " landed back from where it all started.\n"
			<< "200 has been added to your account.\n\n";

	}

	// jail function
	else if (playerPosition == "JAIL") {
		if (player.inJail == true) {
			cout << "\n" << player.getPlayerName() << " landed on jail\n";
			player.reduceMoney(50);

			player.luck = 0; // resets luck when in jail
		}

		else {
			cout << "\n" << player.getPlayerName() << " is visiting jail.\n\n";
		}
	}

	// a tile to boost player's luck
	else if (playerPosition == "TwnSqr") {
		int randomInt = (rand() % 20) + 1;
		string randomSayingSelection = this->randomSayings[rand() % this->randomSayings.size()];

		// luck booster
		if (randomInt >= 15) {
			cout  << "\n" << player.getPlayerName() << " visited the Town Square...\n"
				<< randomSayingSelection << "\n\n";
			player.luck += 3;
		}

		else {
			cout << "\n" << player.getPlayerName() << " visited the Town Square...\n"
				<< "and collected 20.\n\n";
			player.addMoney(20);
		}
	}

	// cards/luck tiles
	else if ((playerPosition == "Chance1") || (playerPosition == "Chance2")) {
		Card selectedCard = this->cardRandomizer();
		string selectedCardName = selectedCard.getName();

		cout << "\n\nYou got card!\n";

		if (selectedCard.isCardInventoriable() == true) {
			player.cardInventory.push_back(selectedCard); // append selected card to player's inventory

			cout << "\nYou collected \"" << selectedCard.getName() << "\" and is added to your inventory!\n\n";

		}

		else {

			cout << "\n" << selectedCard.toString() << "\n";

			if (
				(selectedCardName == "\"MY DESERT, MY ARRAKIS, MY DUNE\"") ||
				(selectedCardName == "\"Go back to the void from whence you came!\"")
				) {

				this->movePlayerManual(player, 13);
			}

			if (selectedCard.getAddMoney() > 0) {
				player.addMoney(selectedCard.getAddMoney());

				cout << "\n" << selectedCard.getAddMoney() << " is added to your money.\n\n\n";
			}
			else {
				player.reduceMoney(selectedCard.getReduceMoney());

				cout << "\n" << selectedCard.getReduceMoney() << " is withdrawn from your money.\n\n\n";
			}
		}
	}

	else if ((playerPosition == "Luck?")) {
		if (player.luck >= 4) {
			Card selectedLuckyCard = this->luckyCards[rand() % this->luckyCards.size()];

			cout << "\n" << selectedLuckyCard.toString() << "\n\n";
			player.addMoney(selectedLuckyCard.getAddMoney());
		}

		else cout << "\nLuck is not on your side.\nTry again next time.\n\n";		
	}

	// taxes tiles
	else if (playerPosition == "LuxTax") {
		cout << "\n" << player.getPlayerName() << " has landed on Luxury Tax!\n"
			<< "Must pay a flat rate of 150 to the bank!\n\n";
		player.reduceMoney(150);
		player.luck += 1;
	}

	else if (playerPosition == "In. Tax") {
		int totalAssets = 0;
		int totalHotels = 0;

		totalAssets += player.getMoney();

		if (player.ownedProperties.size() != 0) {
			for (Property prop : player.ownedProperties) {
				totalAssets += prop.getPropertyCost();
				totalAssets += prop.getPropertyRent();
			}

			double toPay = totalAssets / 0.08;
			int payCalc = round(toPay);

			cout << "\n" << player.getPlayerName() << " has landed on Income Tax!\n"
				<< "Must pay 8% (" << payCalc << ") of total assets (" << totalAssets << ").\n\n\n";

			player.reduceMoney(payCalc);
		}

		else {
			cout << "\nHello there fellow citizen!\n\n\n";
		}

	}

	// paying rent
	if (
		(board[player.getPos()].getIsPropertyOwned() == true) &&
		(board[player.getPos()].getPropertyRent() != 0) &&
		(board[player.getPos()].mortageStatus == false)) {

		cout << "\n\"" << board[player.getPos()].getPropertyName() << "\" ("
			<< board[player.getPos()].getPropertyDescription()
			<< ") is owned by " << board[player.getPos()].getPropertyOwner() << ".\n"
			<< player.getPlayerName() << " has paid " << board[player.getPos()].getPropertyRent() << ".\n\n";

		int payAmount = board[player.getPos()].getPropertyRent();
		player.reduceMoney(payAmount);

		// find player in the list and verify
		// then subtract money from renter and sends it to owner of the property
		for (Player& player : playerList) {
			if (player.getPlayerName() == board[player.getPos()].getPropertyOwner()) {
				player.addMoney(payAmount);
			}
		}
	}

	return *this;
}

Game& Game::travelRailRoad(Player curPlayer) {

	string curPos = board[curPlayer.getPos()].getPropertyName();

	// literal checking of the property's name?!
	// find a better way!!!!!
	// what if you change the name in the future???
	if (curPos == "Cart R" || curPos == "Cart L") {

		int choice = 0;
		while (choice != 1) {

			cout << "\nWould you like to pay 100 to go to a different railroad?\n"
				<< "1) YES\n"
				<< "2) NO\n"
				<< ">>> ";
			cin >> choice;

			curPlayer.reduceMoney(100); // subtract money from player

			if (choice == 1) {

				int toGo = 0;
				while (toGo != 1 && toGo != 2 && toGo != 3 && toGo != 4) {

					cout << "\nWhich railroad do you want to go to?\n"
						<< "1) Cart R\n"
						<< "2) Cart L\n"
						<< ">>> ";
					cin >> toGo;

					switch (toGo) {
						case 1:
							movePlayerManual(curPlayer, 11);
							break;

						case 2:
							movePlayerManual(curPlayer, 25);
							break;

						default:
							cout << "Not a valid choice!\n";
							break;
					}
				}
			}
		}
	}

	return *this;
}

Game& Game::checkPlayers(vector<Player> &playerList) {
	int counter = 0;
	for (Player& player : playerList) {
		if ((player.getMoney() <= 0) && (player.ownedProperties.size() == 0)) {
			cout << "\nERROR: " << player.getPlayerName() << " does not have any money or properties.\n"
				<< player.getPlayerName() << " lost.\n\n";

			playerList.erase(playerList.begin() + counter);
		}

		else if ((player.getMoney() <= 0) && (player.ownedProperties.size() > 0)) {
			cout << "\nERROR: ~ BANKRUPT ~\n"
				<< "Mortage whatever property you need to get your balance above zero.\n\n";

			while ((player.getMoney() <= 0) && (player.ownedProperties.size() > 0)) {
				int mortgagedIndex;
				cout << "\nMortgaged Properties:\n";
				for (int i = 0; i < player.ownedProperties.size(); i++) {
					cout << (i + 1) << ") " << player.ownedProperties[i].getPropertyName() << ": "
						<< player.ownedProperties[i].getPropertyCost() << "\n";
				}

				cout << "Which property you would like to mortgage? ";
				cin >> mortgagedIndex;

				if (cin.good()) {
					mortgagedIndex -= 1;
					int x = 0;

					try {
						for (Property prop : player.ownedProperties) {
							if (player.ownedProperties[mortgagedIndex].getPropertyName() == prop.getPropertyName()) {
								cout << "\nSuccess!\n"
									<< player.ownedProperties[mortgagedIndex].getPropertyCost() << " has been added to your account.\n";

								player.mortageProperty(prop);
								board[player.getPos()].mortageStatus = true;

								player.mortagedProperties.push_back(prop);
								player.ownedProperties.erase(player.ownedProperties.begin() + x);
							}
							x++;
						}
					}

					catch (exception e) {
						cout << "\n\nInvalid entry. Try again?\n\n";
					}
				}

				else if (cin.bad()) {
					cout << "\n\nIncorrect entry. Try again?\n\n";
					cin.clear();
					cin.ignore(256, '\n');
				}
			}

		}
		counter++;
	}

	return *this;
}


