//player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {
 private:
  	QString playerName;
  	int cash; //amount of money left in the bank, in hundred of thousand of dollars
	int customer; //number of customer cards left
	bool playing; //is the player still playing the game?
	int companyscore; //company's score
	bool customerCard; //special customer card
 public:
  	Player(QString n);
  	void setName( QString n );
  	QString getName();
 	Player();
	~Player();
	int currentSpace; //tracks the current location
	void nameChange(QString);
	void moneymove(int); //increases or decreases a player's cash
	void customermove(int); //increase of decreases a player's customer card
	void Lost();//makes the player lose. Changes playing to 0
	int checkLost(); //checks if the player is still playing before giving them a turn.
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
	void SetCustomer(int);
	int turn;
};

#endif
