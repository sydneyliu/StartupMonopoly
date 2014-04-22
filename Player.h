
#ifndef PLAYER_H
class Space;
#define PLAYER_H

#include "Space.h"
#include "Action.h"
using namespace std;

class Player {
	public:
		Player();
		~Player();
		int currentSpace; //tracks the current location
		void nameChange(char);
		void moneymove(int); //increases or decreases a player's cash
		void customermove(int); //increase of decreases a player's customer card
		void Lost();//makes the player lose. Changes playing to 0
		int checkLost(); //checks if the player is still playing before giving them a turn.
		char name; //player's piece
		void move(Space, Space, int, int); //the number of spaces a player is moving
		int GameEnd(); //helps check if the game is over by returning the playing bool
		int CashChecker(); //returns the amount of cash
		int CustomerChecker(); //checks the number of customers left
		int ScoreChecker(); //returns the company score
		void ImproveScore(int); //Improve the score of the company
		void give_money(int); //give up money
		void AddCustomer(); //adds customer cards
		void ChangeCustomerCards(bool);
		bool ReturnCustomerCard();
		void RemoveCustomer();
	private:
		int cash; //amount of money left in the bank, in hundred of thousand of dollars
		int customer; //number of customer cards left
		bool playing; //is the player still playing the game?
		int companyscore; //company's score
		bool customerCard; //special customer card
};

#endif