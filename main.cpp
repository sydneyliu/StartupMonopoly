//main.cpp
#include "Space.h"
#include "Player.h"
#include "Action.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "MoneyAction.h"
#include "CardAction.h"
#include "GotoAction.h"
#include "Bank.h"
using namespace std;


//*****************FUNCTIONS*************************************
int dice(); //random number from 1-6
void printBoard(); //Prints the Board
void printIncompleteRow(int start, int end, bool Bottom); //Prints the sides
void printCompleteRow(int start, int end); // Prints the top and bottom
void pieceSelection(); //does piece selection at the start of the game
void CheckPlayers(); //checks how many players there are
void intro(); //introduction to the game
void SpecificSpaces(); //HardCodes info into the Spaces
void GameRounds(); //Goes through the rounds of the game
void declareWinners(); //checks if any of the players have won. If they have, ends the game.
void DemoDay(); //demo day every 5 turns
void Acquisition(int, int); //if a company has 10x the amount another company does, an acquistion can happen
void setLosers(); //sets players as losers if they lose all of their customers
void organizeLosers(); //organizes the losers so they won't get a turn anymore in the game
void GameProgress(); //gives an update on the progress of the game
void executeAction( Action& a); //execute action
void properties(int, int); //charges and makes the purchases of property

//*****************GLOBAL VARIABLES******************************
const int NumSpaces = 40; //the number of spaces there are on the board
int player_num; //tracks the number of players
Player *players; //later to be dynamically allocated. Tracks number of players
Space *spaces; //later to be dynamically allocated. Tracks the number of spaces
Bank *bank; //creates an instance of the bank
Action *actions[40]; //for actions
char Characters[]= {'A', 'R', 'C', 'J', 'G', 'P', 'B', 'W', 'Z', 'D', 'M', '\0'};
int winnerOVER=0; //if = to 1, the game is over and a winner has been declared!
int rounds = 0; //keeps track of the number of turns that go by.
int LoserSwitch =0; //makes it so the losers are printed only once
int lost[4]; //tracks which have lost and have been posted already so the below parts are not repeatedly outputed every turn.
//**********************************************************************
//********************MAIN**********************************************
int main () {

srand(time(0));
//CHECK THE NUMBER OF PLAYERS

intro();

CheckPlayers(); //gives the number of players playing the game

//DYNAMICALLY ALLOCATE ARRAYS for the number of players and Squares
players = new Player[player_num+1]; //player_num+1 is the Bank
spaces = new Space[NumSpaces]; //in this case there are 40 squares
bank = new Bank[1]; //Declares the bank
SpecificSpaces(); //fills the spaces
//PIECE SELECTION

pieceSelection();

cout << "Are you ready to play the game? Hit any key to START THE GAME!" << endl;
string startgame;
cin.ignore();
getline(cin, startgame);
if (startgame.empty()) {
	startgame ="a";
}
bank[0].money = 1000000000; //starts the bank out with a lot of money

//****************GAME PLAY STARTS******************************
GameRounds();


//DELETE SPACE

delete[] players;
delete[] spaces;
delete[] bank;

	return 0;
}


//*******************FUNCTIONS******************************************
//********************************************************************
void intro() {
	cout << "Do you think you have what it takes to start a company?" << endl;

	cout << "PROVE IT!" << endl;
}

void CheckPlayers() {
	do {
	cout << "How many players? Put 2, 3, or 4: ";
	cin >> player_num;
	if (cin.fail()) { //check if it is an int
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "Not an number, please put a number!" << endl;
		continue;
	}
	if(player_num < 2) { //If the number is too small
		cout << "The number cannot be less than 2. Try again." << endl;
		continue;
	}
	if (player_num > 4) { // if the number is too large
		cout << "The number cannot be greater than 4. Try again." << endl;
		continue;
	}
	cin.ignore(10000000,'\n');
	break;

} while (true);
}


void pieceSelection() { //Does piece selection
	cout << "Select your character from the list of startup gurus below:" << endl;
	cout << "Type the letter in parenthesis to select" << endl;
	cout << "Hall of Famers:" << endl;
	cout << "-- Andrew Carnegie (Type A)" << endl;
	cout << "-- John Rockefeller (Type R)" << endl;
	cout << "-- Jim Clark (Type C)" << endl;
	cout << "-- Steve Jobs (Type J)" << endl;

	cout << "Living Legends:" << endl;
	cout << "-- Bill Gates (Type G)" << endl;
	cout << "-- Larry Page (Type P)" << endl;
	cout << "-- Richard Branson (Type B)" << endl;
	cout << "-- Warren Buffet (Type W)" << endl;

	cout << "The Future:" << endl;
	cout << "-- Mark Zuckerberg (Type Z)" << endl;
	cout << "-- Jack Dorsey (Type D)" << endl;
	cout << "-- Elon Musk (Type M)" << endl;
	char choice;
	bool match;
	int j=0; //tracker for if name is in the array of the names that can be selected
	for(int i=0; i<player_num; i++) {
	
		do{
			match=0;
			j=0;
			cout << "Please choose your piece!" << endl;
			cin >> choice;
			if(cin.fail()) {
				cin.clear();
				cin.ignore(100000, '\n');
				cout << "Please enter a char to select your piece." << endl;
				continue;
			}
			for (int i=0; i<11; i++) { //to ensure it is in the list of characters
				if(choice==Characters[i]) {
					j++;
				}
			}
			if(j==0) {
				match=1; //when match is shown, it means it's not on the list or can't be selected
			}
			for (int i=0; i<player_num; i++) {
				if(players[i].name == choice) {
					match=1;
				}
			} 
			if(match==1) {
				cout << "Character you selected is not on the list or has been already selected" << endl;
				continue;
			}
			

			break;
		} while (true);
	
	players[i].nameChange(choice);
}
	cout << "The players you selected are: ";
	for(int i=0; i<player_num; i++) {
		cout << players[i].name << " ,";
	}
	cout << endl;
}

int dice() {
	int randnum; //the random number from 1-6
	randnum = (rand() % 6)+1; //generates a random number 0-5 and adds one to make 1-6
	return randnum;
}


void GameRounds() {
	//Starting positions
	for(int i = 0; i< player_num; i++) {
		spaces[0].pieces[i] = players[i].name;
	}
	int die;
	bool switcher=true; //keeps the loop going
	while(switcher) {
		rounds++; //keeps track of the number of rounds

		for(int i=0; i<player_num; i++) {
			if(players[i].checkLost()==1) {
				cout << players[i].name<< "'s move. Hit enter to roll the die or type Q to quit or R to resign. ";
				string enternow;
				getline(cin, enternow);
				if (enternow=="Q") {
					switcher=false;
					break;
				}
				if (enternow=="R") {
					players[i].Lost();
					cout << players[i].name << " has resigned or lost." << endl;
					int temp1 = players[i].CashChecker(); //keeps track of money that needs to be transfered to the bank
					players[i].moneymove(-temp1);
					bank[0].money+=temp1;
					for (int j=0; j<40; j++) { //removes their property if resign
						if (spaces[j].PrintOwner() == players[i].name) {
							spaces[j].ChangeOwner(' ');
							cout << "Property " << spaces[j].PrintName() << " has been released." << endl; 
						}
					}
				}
				if (enternow.empty()) { //utilizes the empty line to continue
					enternow ="a";
				}
				die=dice(); //random number
				int mover1 = players[i].currentSpace;
				int mover2 =players[i].currentSpace+die;
				if(mover2>=40) { //when the number runs up to 40, it resets back down so it will never run over 40
					mover2-=40;
				}
				players[i].move(spaces[mover1], spaces[mover2], i, die); //adds to currentSpace
				spaces[mover1].pieces[i]=' '; //updates the position in the board
				spaces[mover2].pieces[i]=players[i].name;
				printBoard(); //prints the board
				cout << players[i].name << " rolled a " << die << ". Move " << die << " spaces." << endl;

				//executes the actions that are on the game board
				cout << "You have landed on "<< spaces[mover2].printedName <<"!"<< endl;
				actions[mover2]->executeAction(&players[i]);

				//ends the actions that are execution
				properties(i, mover2);

				if (1 > 2) { //if one company is 10x larger than another company
					int x; //larger company
					int y; //smaller company
					Acquisition(x, y);
				}
				setLosers();
				//organizeLosers();
				declareWinners(); //checks if any of the players have won.
				if (winnerOVER==1) { //if a winner is found
					switcher = false; //breaks out of the loop
				}
			}//end of if statement that chekcs if the player is still in the game

		} //end of for loop
		if ((rounds%5) == 0) { //DEMO DAYS every 5 rounds
			DemoDay();
		}
		declareWinners(); //checks if any of the players have won.
		if (winnerOVER==1) { //if a winner is found
			switcher = false; //breaks out of the loop
		}
		GameProgress();
	} //end of while loop

}

void declareWinners() { //checks for the winners
	int tracker = 0; //tracks the key numbers to check if the game is over or not.
	int temp =0;
	for(int i=0; i<player_num; i++) {
		tracker += players[i].GameEnd();
	} // end of for loop
	for (int i=0; i<player_num; i++) {
		if(players[i].CashChecker()>=100000) {
			for(int i=0; i<player_num; i++) {
				if(players[i].CashChecker() < 100000) {
					players[i].Lost();
				}
				tracker = 1;
			}
		} 
	}
	if(tracker == 1) {
		cout << "GAME IS OVER!" << endl;
		winnerOVER = 1; //sets the game status to over. Use this to break out of all the loops
		for (int i=0; i<player_num;i++) {
			temp = players[i].GameEnd();
			if(temp==1) {
				cout << "Player " << players[i].name << " has won! CONGRATULATIONS!" << endl;
				break;
			}
		} //for loop to check who the winner is.
	}
} //end of declareWinners

void setLosers() {
	int temp=5; //tracks customers
	int temp2=5; //tracks money
	if(LoserSwitch ==0) {
		for (int i=0; i<4; i++) {
			lost[i]=0;
		} //fill the array with zeros.
		LoserSwitch=1;
	}

	for (int i=0; i<player_num; i++) { //checks the customercards
		if(lost[i]==0) {
			temp = players[i].CustomerChecker();
			if(temp==0) {
				cout <<"Player " << players[i].name << " has lost and owns 0 customers now." << endl;
				players[i].Lost();
				lost[i]=1;
			}
			temp2 = players[i].CashChecker(); //checks if there is any money in that player
			if (temp2<=0) {
				cout <<"Player " << players[i].name << " has lost and owns $0 now." << endl;
				players[i].Lost();
				lost[i]=1;
			}
		}
		
	}
}

/*void organizeLosers() {//check if there are players who have lost. If so, shift the players into the correct positions.
	int num_compare = 0;
	for (int i=0; i<player_num; i++) {
		num_compare+=players[i].checkLost();
	}
	if(num_compare!=player_num) { //this means that one of the players got their playing set to 0. we need to reorganize
		//remove player by placing the loser it at the end of the list


		player_num-=1; // cut short the numbers of players by 1
	}
} */

void DemoDay() {
	int playerscores;
	for (int i=0; i<50; i++) {
		cout << "*";
	}
	cout << endl;
	cout << "****************** DEMO DAY *********************" << endl;
	cout << endl;
	cout << "All the teams have been given a great opportunity to pitch their company very few will walk out with money! \nWill it be you?"<<endl;
	cout << endl;
	for (int i=0; i<player_num; i++) {
		if(players[i].checkLost()==1) {
			cout << "It's " << players[i].name << " turn to demo. Hit ENTER to demo.";
			string enternow;
			getline(cin, enternow);
			if (enternow.empty()) { //utilizes the empty line to continue
				enternow ="a";
			}
			int Demo =rand() % 100 + 1; //selects a random number from 1 to 100.
			playerscores = players[i].ScoreChecker();
			if (playerscores > Demo) {
				cout << "Congrats you won money!" << endl;
				int chance=rand()%100+1;
				if (chance <=25) {
					players[i].moneymove(500);
					players[i].ImproveScore(playerscores/5);
				} else if (chance > 25 && chance <90) {
					players[i].moneymove(250);
					players[i].ImproveScore(playerscores/10);
				} else {
					//give money
					players[i].moneymove(5000);
					players[i].ImproveScore(playerscores/2);
				}

			} else {
				players[i].ImproveScore(2);
				cout << "Sorry, the investors at the Demo Day didn't really like you. Better luck next time!" << endl;
			}
		}

	}

}

void Acquistion(int a, int b) { //input the number position of the first player and the second player. a is the company doing the acquiring, b is acquired.
	cout << players[a].name << " is worth over 10x the amount that " << players[b].name << ". " << players[a].name << " now can acquire the company." << endl;

	//move all the money out of b and into a

	players[b].Lost();
}

void GameProgress() { //updates the progress of the game and shows the overall scores

	//top bar

	for(int i=0; i<30; i++) {
		cout << "-";
	}
	cout << endl;
	cout << "GAME PROGRESS" << endl;
	for(int i=0; i<30; i++) {
		cout << "-";
	}
	cout << endl;
	cout << "Bank currently has: $" << bank[0].money << endl;
	for (int i = 0; i<player_num; i++) {
		cout << players[i].name << " has $" << players[i].CashChecker();
		if(players[i].checkLost()==0) {
			cout << " (Player has resigned)";
		}
		cout << endl;
	}

}


void executeAction( Action& a)
{
    a.executeAction(&players[1]);
    cout << "Test" << endl;
}

void properties(int playernum, int spacenum) { //deals with the buying and selling of 
	//each property costs a random number between $500 and $1500
	string userResponse;
	int price = rand()%1000 + 500; //prices are randomly generated
	do {
		if (price < players[playernum].CashChecker() && spaces[spacenum].PrintOwner() == ' ') { //if player is not big enough, then skip this part
			cout << "Would you like to purchase this for $" << price << "? Please type Yes or No." << endl;
			cin >> userResponse;
			if(cin.fail()) {
				cin.clear();
				cin.ignore(100000, '\n');
				cout << "Not an number, please put a number!" << endl;
				continue;
			}
			if (userResponse == "Yes" || userResponse=="YES") {
				spaces[spacenum].ChangeOwner(players[playernum].name); //changes the owner of the square
				players[playernum].moneymove(-price);
				bank[0].money +=price;
				cout << "You now own this! Congratulations, you will be paid every time you land on this square!" << endl;
				string enternow1;
				getline(cin, enternow1);
				if (enternow1.empty()) { //utilizes the empty line to continue
					enternow1 ="a";
				}
				break;
			}
			if (userResponse == "No" || userResponse=="NO") {
				string enternow1;
				getline(cin, enternow1);
				if (enternow1.empty()) { //utilizes the empty line to continue
					enternow1 ="a";
				}
				break;
			}
			continue;
		} else if (spaces[spacenum].PrintOwner() == players[playernum].name) {
			int Win = rand() % 2000 + 3000;
			players[playernum].moneymove(Win);
			break;
		} else {
			break;
		}
		
	} while(true);

}

void printCompleteRow(int start, int end) {
		//the TOP BAR
	if (start < end) {//if true, then the counter increases, if false, it decreases
		for (int i=0; i<12*10+1; i++) {
			cout << "-";
		}
		cout << endl;

	//First ROW: Name
		for (int i =0; i<11; i++) {
			cout << "|" << setw(3) << " " << setw(5) << spaces[start+i].printedName << setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}

	//Second ROW: a line of -----
		for (int i =0; i<11; i++) {
			cout << "|" << "----------";
			if (i==10) {
				cout << "|" << endl;
			}
		}
	//THIRD ROW through FIFTH ROW, ACTIONS
		for (int i =0; i<11; i++) { //Action 1
			cout << "|" << setw(3) << " " <<setw(5) << actions[start+i]->print_name(0) << setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}

		for (int i =0; i<11; i++) { //Action 2
			cout << "|" << setw(3) << " " << setw(5) << actions[start+i]->print_name(1) << setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}
		for (int i =0; i<11; i++) { //Action 3
			cout << "|" << setw(3) << " " << setw(5)<< actions[start+i]->print_name(2)<< setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}
	//Sixth Row, a line of ------
		for (int i =0; i<11; i++) {
			cout << "|" << "----------";
			if (i==10) {
				cout << "|" << endl;
			}
		}

	//Seventh Row, Players on the squre
		for (int i =0; i<11; i++) { //Action 3
			cout << "|" << setw(3) << " " << spaces[start+i].pieces[0] << spaces[start+i].pieces[1] <<spaces[start+i].pieces[2] <<spaces[start+i].pieces[3] << setw(3) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}

	//Eighth row, Line of -----

		for (int i =0; i<11; i++) {
			cout << "|" << "----------";
			if (i==10) {
				cout << "|" << endl;
			}
		}

	//Ninth Row, Owner
		for (int i =0; i<11; i++) { //Action 3
			cout << "|" << setw(1) << " " << "Owner: "<< setw(1)<< spaces[start+i].PrintOwner()<< setw(1) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}

	//Bottom bar
		for (int i=0; i<12*10+1; i++) {
			cout << "-";
		}
		cout << endl;

	} else { //end of if start loop
		for (int i=0; i<12*10+1; i++) {
			cout << "-";
		}
		cout << endl;

	//First ROW: Name
		for (int i =0; i<11; i++) {
			cout << "|" << setw(3) << " " << setw(5) << spaces[start-i].printedName << setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}

	//Second ROW: a line of -----
		for (int i =0; i<11; i++) {
			cout << "|" << "----------";
			if (i==10) {
				cout << "|" << endl;
			}
		}
	//THIRD ROW through FIFTH ROW, ACTIONS
		for (int i =0; i<11; i++) { //Action 1
			cout << "|" << setw(3) << " " << setw(5) << actions[start-i]->print_name(0) << setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}

		for (int i =0; i<11; i++) { //Action 2
			cout << "|" << setw(3) << " " << setw(5) << actions[start-i]->print_name(1) << setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}
		for (int i =0; i<11; i++) { //Action 3
			cout << "|" << setw(3) << " " << setw(5) << actions[start-i]->print_name(2)<< setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}
	//Sixth Row, a line of ------
		for (int i =0; i<11; i++) {
			cout << "|" << "----------";
			if (i==10) {
				cout << "|" << endl;
			}
		}

	//Seventh Row, Players on the squre
		for (int i =0; i<11; i++) { //Action 3
			cout << "|" << setw(3) << " " <<  spaces[start-i].pieces[0] << spaces[start-i].pieces[1] <<spaces[start-i].pieces[2] <<spaces[start-i].pieces[3] << setw(3) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}

	//Eighth row, Line of -----

		for (int i =0; i<11; i++) {
			cout << "|" << "----------";
			if (i==10) {
				cout << "|" << endl;
			}
		}

	//Ninth Row, Owner
		for (int i =0; i<11; i++) { //Action 3
			cout << "|" << setw(1) << " " << "Owner: "<< setw(1) << spaces[10-i].PrintOwner() << setw(1) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}

	//Bottom bar
		for (int i=0; i<12*10+1; i++) {
			cout << "-";
		}
		cout << endl;
	} //end of else loop
} // end of PrintCompleteRow
	

void printIncompleteRow(int start, int end, bool Bottom) { //Bottom hecks if you print the bottom line of the board


	//First ROW: Name
	cout << "|" << setw(3) << " " << setw(5) << spaces[start].printedName << setw(2) << " " << "|" << setw(98) << " " << "|" << setw(3) << " " << setw(5) << spaces[end].printedName << setw(2) << " " << "|" << endl;


	//Second ROW: a line of -----

	cout << "|" << "----------" << "|" << setw(98) << " " << "|" << "----------" << "|" << endl;

	//THIRD ROW through FIFTH ROW, ACTIONS
	cout << "|" << setw(3) << " " << setw(5) << actions[start] ->print_name(0) << setw(2) << " " << "|" << setw(98) << " " << "|" << setw(3) << " " << setw(5) << actions[end]->print_name(0) << setw(2) << " " << "|" << endl;
	cout << "|" << setw(3) << " " << setw(5) << actions[start] ->print_name(1)<< setw(2) << " " << "|" << setw(98) << " " << "|" << setw(3) << " " << setw(5) << actions[end]->print_name(1) << setw(2) << " " << "|" << endl;
	cout << "|" << setw(3) << " " << setw(5) << actions[start] ->print_name(2) << setw(2) << " " << "|" << setw(98) << " " << "|" << setw(3) << " " << setw(5) << actions[end]->print_name(2) << setw(2) << " " << "|" << endl;

	//Sixth Row, a line of ------
	cout << "|" << "----------" << "|" << setw(98) << " " << "|" << "----------" << "|" << endl;

	//Seventh Row, Players on the squre
	cout << "|" << setw(3) << " " <<  spaces[start].pieces[0] << spaces[start].pieces[1] <<spaces[start].pieces[2] <<spaces[start].pieces[3] << setw(3) << " " << "|" << setw(98) << " " << "|" << setw(3) << " " <<  spaces[end].pieces[0] << spaces[end].pieces[1] <<spaces[end].pieces[2] <<spaces[end].pieces[3] << setw(3) << " " << "|" << endl;


	//Eighth row, Line of -----
	cout << "|" << "----------" << "|" << setw(98) << " " << "|" << "----------" << "|" << endl;

	//Ninth Row, Owner
	cout << "|" << setw(1) << " " << "Owner: " <<setw(1) << spaces[start].PrintOwner() << setw(1) << " " << "|" << setw(98) << " " << "|" << setw(1) << " " << "Owner: " <<setw(1) << spaces[end].PrintOwner() << setw(1)  << " " << "|" << endl;


	//Bottom bar
	if (Bottom == true) {
		cout << "------------" << setw(98) << " "<< "------------"  << endl;
	}
} //end of PrintIncompleteRow

void printBoard() {
	printCompleteRow(20, 30);
	for (int i=0; i<8; i++) {
		printIncompleteRow(19-i, 31+i, true);
	}
		printIncompleteRow(11, 39, false);
	printCompleteRow(10,0);

}

void SpecificSpaces() { //hardcodes specific info into the spaces

	actions[0]=new GotoAction(0); //just set it to go to Home
	spaces[0].ChangeName("HOME!");
	actions[0]->fillText(0, "     ");
	actions[0]->fillText(1, "     ");
	actions[0]->fillText(2, "     ");
	
	actions[1]= new MoneyAction(500);
	spaces[1].ChangeName("HOROW");
	actions[1]->fillText(0, "Add  ");
	actions[1]->fillText(1, "$500 ");
	actions[1]->fillText(2, "to u!");

	actions[2]= new CardAction();
	spaces[2].ChangeName("BUFFE");
	actions[2]->fillText(0, "DRAW ");
	actions[2]->fillText(1, "a    ");
	actions[2]->fillText(2, "CARD!");


	actions[3]= new GotoAction(11);
	spaces[3].ChangeName("BAD$$");
	spaces[3].ChangeOwner(' ');
	actions[3]->fillText(0, "GO TO");
	actions[3]->fillText(1, "DELAY");
	actions[3]->fillText(2, "     ");


	actions[4]= new MoneyAction(1000);
	spaces[4].ChangeName("RICKR");
	spaces[4].ChangeOwner(' ');
	actions[4]->fillText(0, "Add  ");
	actions[4]->fillText(1, "$1000");
	actions[4]->fillText(2, "to u!");


	actions[5]= new MoneyAction(600);
	spaces[5].ChangeName("GATES");
	spaces[5].ChangeOwner(' ');
	actions[5]->fillText(0, "Add  ");
	actions[5]->fillText(1, "$600 ");
	actions[5]->fillText(2, "to u!");


	actions[6]= new CardAction();
	spaces[6].ChangeName("ANGEL");
	spaces[6].ChangeOwner(' ');
	actions[6]->fillText(0, "DRAW ");
	actions[6]->fillText(1, "a    ");
	actions[6]->fillText(2, "CARD!");


	actions[7]= new MoneyAction(200);
	spaces[7].ChangeName("SEANP");
	spaces[7].ChangeOwner(' ');
	actions[7]->fillText(0, "Add  ");
	actions[7]->fillText(1, "$200 ");
	actions[7]->fillText(2, "to u!");



	actions[8]= new MoneyAction(600);
	spaces[8].ChangeName("BOGLE");
	spaces[8].ChangeOwner(' ');
	actions[8]->fillText(0, "Add  ");
	actions[8]->fillText(1, "$600 ");
	actions[8]->fillText(2, "to u!");


	actions[9]= new CardAction();
	spaces[9].ChangeName("LYNCH");
	spaces[9].ChangeOwner(' ');
	actions[9]->fillText(0, "DRAW ");
	actions[9]->fillText(1, "a    ");
	actions[9]->fillText(2, "CARD!");



	actions[10] = new GotoAction(10); //set it to Growt
	spaces[10].ChangeName("GROWT");
	spaces[10].ChangeOwner(' ');
	actions[10]->fillText(0, "     ");
	actions[10]->fillText(1, "     ");
	actions[10]->fillText(2, "     ");



	actions[11]= new MoneyAction(-200);	
	spaces[11].ChangeName("DELAY");
	spaces[11].ChangeOwner(' ');
	actions[11]->fillText(0, "LOSE ");
	actions[11]->fillText(1, "$200 ");
	actions[11]->fillText(2, "     ");


	actions[12]= new CardAction();
	spaces[12].ChangeName("LUCKY");
	spaces[12].ChangeOwner(' ');
	actions[12]->fillText(0, "DRAW ");
	actions[12]->fillText(1, "a    ");
	actions[12]->fillText(2, "CARD!");


	actions[13]= new MoneyAction(-800);
	spaces[13].ChangeName("COMPE");
	spaces[13].ChangeOwner(' ');
	actions[13]->fillText(0, "LOSE ");
	actions[13]->fillText(1, "$800 ");
	actions[13]->fillText(2, "     ");


	actions[14] = new GotoAction(14);
	spaces[14].ChangeName("MENTO");
	spaces[14].ChangeOwner(' ');
	actions[14]->fillText(0, "     ");
	actions[14]->fillText(1, "     ");
	actions[14]->fillText(2, "     ");


	actions[15]= new MoneyAction(-200);
	spaces[15].ChangeName("MISSE");
	spaces[15].ChangeOwner(' ');
	actions[15]->fillText(0, "LOSE ");
	actions[15]->fillText(1, "$200 ");
	actions[15]->fillText(2, "     ");


	actions[16]= new MoneyAction(-400);
	spaces[16].ChangeName("EMERG");
	spaces[16].ChangeOwner(' ');
	actions[16]->fillText(0, "LOSE ");
	actions[16]->fillText(1, "$400 ");
	actions[16]->fillText(2, "     ");


	actions[17]= new CardAction();
	spaces[17].ChangeName("OFFIC");
	spaces[17].ChangeOwner(' ');
	actions[17]->fillText(0, "DRAW ");
	actions[17]->fillText(1, "a    ");
	actions[17]->fillText(2, "CARD!");


	actions[18]= new GotoAction();	
	spaces[18].ChangeName("RELOC");
	spaces[18].ChangeOwner(' ');
	actions[3]->fillText(0, "GO TO");
	actions[3]->fillText(1, "ANGEL");
	actions[3]->fillText(2, "     ");



	actions[19]= new CardAction();
	spaces[19].ChangeName("LUCKE");
	spaces[19].ChangeOwner(' ');
	actions[19]->fillText(0, "DRAW ");
	actions[19]->fillText(1, "a    ");
	actions[19]->fillText(2, "CARD!");



	actions[20]= new CardAction();
	spaces[20].ChangeName("NEWSP");
	spaces[20].ChangeOwner(' ');
	actions[20]->fillText(0, "DRAW ");
	actions[20]->fillText(1, "a    ");
	actions[20]->fillText(2, "CARD!");


	actions[21]= new MoneyAction(-200);
	spaces[21].ChangeName("DESIG");
	spaces[21].ChangeOwner(' ');
	actions[21]->fillText(0, "LOSE ");
	actions[21]->fillText(1, "$200 ");
	actions[21]->fillText(2, "     ");


	actions[22]= new MoneyAction(500);
	spaces[22].ChangeName("SALES");
	spaces[22].ChangeOwner(' ');
	actions[22]->fillText(0, "Add  ");
	actions[22]->fillText(1, "$500 ");
	actions[22]->fillText(2, "to u!");


	actions[23]= new MoneyAction(1000);
	spaces[23].ChangeName("MARKE");
	spaces[23].ChangeOwner(' ');
	actions[23]->fillText(0, "Add  ");
	actions[23]->fillText(1, "$1000");
	actions[23]->fillText(2, "to u!");


	actions[24]= new MoneyAction(-2000);
	spaces[24].ChangeName("LAWYE");
	spaces[24].ChangeOwner(' ');
	actions[24]->fillText(0, "LOSE ");
	actions[24]->fillText(1, "$2000");
	actions[24]->fillText(2, "     ");

	actions[25]= new MoneyAction(500);
	spaces[25].ChangeName("PMFIT");
	spaces[25].ChangeOwner(' ');
	actions[25]->fillText(0, "Add  ");
	actions[25]->fillText(1, "$500 ");
	actions[25]->fillText(2, "to u!");


	actions[26]= new CardAction();
	spaces[26].ChangeName("ITERA");
	spaces[26].ChangeOwner(' ');
	actions[26]->fillText(0, "DRAW ");
	actions[26]->fillText(1, "a    ");
	actions[26]->fillText(2, "CARD!");


	actions[27]= new MoneyAction(200);
	spaces[27].ChangeName("TEAM!");
	spaces[27].ChangeOwner(' ');
	actions[27]->fillText(0, "Add  ");
	actions[27]->fillText(1, "$200 ");
	actions[27]->fillText(2, "to u!");


	actions[28]= new MoneyAction(300);
	spaces[28].ChangeName("SMART");
	spaces[28].ChangeOwner(' ');
	actions[28]->fillText(0, "Add  ");
	actions[28]->fillText(1, "$300 ");
	actions[28]->fillText(2, "to u!");



	actions[29]=new GotoAction(29); //goto the SOCIL
	spaces[29].ChangeName("SOCIL");
	spaces[29].ChangeOwner(' ');
	actions[29]->fillText(0, "     ");
	actions[29]->fillText(1, "     ");
	actions[29]->fillText(2, "     ");

	actions[30]= new MoneyAction(-500);
	spaces[30].ChangeName("HEALT");
	spaces[30].ChangeOwner(' ');
	actions[30]->fillText(0, "LOSE ");
	actions[30]->fillText(1, "$500 ");
	actions[30]->fillText(2, "     ");


	actions[31]= new MoneyAction(-200);
	spaces[31].ChangeName("FAMIL");
	spaces[31].ChangeOwner(' ');
	actions[31]->fillText(0, "LOSE ");
	actions[31]->fillText(1, "$200 ");
	actions[31]->fillText(2, "     ");


	actions[32]= new MoneyAction(-400);
	spaces[32].ChangeName("BABY!");
	spaces[32].ChangeOwner(' ');
	actions[32]->fillText(0, "LOSE ");
	actions[32]->fillText(1, "$400 ");
	actions[32]->fillText(2, "     ");


	actions[33]= new MoneyAction(-300);
	spaces[33].ChangeName("SCARD");
	spaces[33].ChangeOwner(' ');
	actions[33]->fillText(0, "LOSE ");
	actions[33]->fillText(1, "$300 ");
	actions[33]->fillText(2, "     ");


	actions[34]= new MoneyAction(100);
	spaces[34].ChangeName("FORUN");
	spaces[34].ChangeOwner(' ');
	actions[34]->fillText(0, "Add  ");
	actions[34]->fillText(1, "$100 ");
	actions[34]->fillText(2, "to u!");


	actions[35]= new MoneyAction(100);
	spaces[35].ChangeName("TIMES");
	spaces[35].ChangeOwner(' ');
	actions[35]->fillText(0, "Add  ");
	actions[35]->fillText(1, "$100 ");
	actions[35]->fillText(2, "to u!");


	actions[36]= new MoneyAction(200);
	spaces[36].ChangeName("LEARN");
	spaces[36].ChangeOwner(' ');
	actions[36]->fillText(0, "Add  ");
	actions[36]->fillText(1, "$200 ");
	actions[36]->fillText(2, "to u!");



	actions[37]= new MoneyAction(500);
	spaces[37].ChangeName("TALTR");
	spaces[37].ChangeOwner(' ');
	actions[37]->fillText(0, "Add  ");
	actions[37]->fillText(1, "$500 ");
	actions[37]->fillText(2, "to u!");


	actions[38]= new MoneyAction(-400);
	spaces[38].ChangeName("CONFE");
	spaces[38].ChangeOwner(' ');
	actions[38]->fillText(0, "LOSE ");
	actions[38]->fillText(1, "$400 ");
	actions[38]->fillText(2, "     ");


	actions[39]= new GotoAction(37);
	spaces[39].ChangeName("FLIPR");
	spaces[39].ChangeOwner(' ');
	actions[39]->fillText(0, "GO TO");
	actions[39]->fillText(1, "TALTR");
	actions[39]->fillText(2, "     ");

}