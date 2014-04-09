#ifndef PLAYER_H
#define PLAYER_H


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
		char name; //player's piece
		void move(Space, Space, int, int); //the number of spaces a player is moving
		int GameEnd(); //helps check if the game is over by returning the playing bool
		int CashChecker(); //checks if the player has over 1 billion and wins the game
	private:
		int cash; //amount of money left in the bank, in hundred of thousand of dollars
		int customer; //number of customer cards left
		bool playing; //is the player still playing the game?
		int companyscore; //company's score
};

#endif