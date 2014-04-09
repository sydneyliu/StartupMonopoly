//main.cpp
#include "Space.h"
#include "Player.h"
#include "Action.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
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

//*****************GLOBAL VARIABLES******************************
const int NumSpaces = 40; //the number of spaces there are on the board
int player_num; //tracks the number of players
Player *players; //later to be dynamically allocated. Tracks number of players
Space *spaces; //later to be dynamically allocated. Tracks the number of spaces
char Characters[]= {'A', 'R', 'C', 'J', 'G', 'P', 'B', 'W', 'Z', 'D', 'M', '\0'};
int winnerOVER=0; //if = to 1, the game is over and a winner has been declared!
int rounds = 0; //keeps track of the number of turns that go by.

//**********************************************************************
//********************MAIN**********************************************
int main () {

srand(time(0));
//CHECK THE NUMBER OF PLAYERS

intro();

CheckPlayers(); //gives the number of players playing the game

//DYNAMICALLY ALLOCATE ARRAYS for the number of players and Squares
players = new Player[player_num];
spaces = new Space[NumSpaces]; //in this case there are 40 squares
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


//****************GAME PLAY STARTS******************************
GameRounds();


//DELETE SPACE

delete[] players;
delete[] spaces;

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
	bool switcher=true;
	while(switcher) {
		rounds++; //keeps track of the number of rounds
		if ((rounds%5) == 0) { //DEMO DAYS every 5 rounds
			DemoDay();
		}
		for(int i=0; i<player_num; i++) {
			cout <<"Player "<< i+1<< "'s move. Hit enter to roll the die or type Q to quit. ";
			string enternow;
			getline(cin, enternow);
			if (enternow=="Q") {
				switcher=false;
				break;
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
			printBoard(); //prints the board
			spaces[mover1].pieces[i]=' '; //updates the position in the board
			spaces[mover2].pieces[i]=players[i].name;
			cout << "Player " << i+1 << " rolled a " << die << ". Move " << die+1 << " spaces." << endl;
			declareWinners(); //checks if any of the players have won.
			if (winnerOVER==1) { //if a winner is found
				switcher = false; //breaks out of the loop
			}
			if (1 > 2) { //if one company is 10x larger than another company
				int x; //larger company
				int y; //smaller company
				Acquisition(x, y);
			}
			setLosers();
			organizeLosers();
		}
	}

}

void declareWinners() { //checks for the winners
	int tracker = 0; //tracks the key numbers to check if the game is over or not.
	int temp =0;
	for(int i=0; i<player_num; i++) {
		tracker += players[i].GameEnd();
	} // end of for loop
	if(tracker == 1) {
		cout << "GAME IS OVER!" << endl;
		winnerOVER = 1; //sets the game status to over. Use this to break out of all the loops
		for (int i=0; i<player_num;i++) {
			temp = players[i].GameEnd();
			if(temp==1) {
				cout << "Player " << players[i].name << " has won! CONGRATULATIONS!" << endl;
			}
		} //for loop to check who the winner is.
	}
} //end of declareWinners

void setLosers() {
		int temp; //tracks customers
		int temp2; //tracks money
	for (int i=0; i<player_num; i++) { //checks the customercards
		temp = players[i].CustomerChecker();
		if(temp==0) {
			cout <<"Player " << players[i].name << " has lost and owns 0 customers now." << endl;
			players[i].Lost();
		}
		temp2 = players[i].CashChecker(); //checks if there is any money in the bank.
		if (temp2<=0) {
			cout <<"Player " << players[i].name << " has lost and owns $0 now." << endl;
			players[i].Lost();	
		}
	}
}

void organizeLosers() {//check if there are players who have lost. If so, shift the players into the correct positions.
	int num_compare = 0;
	for (int i=0; i<player_num; i++) {
		num_compare+=players[i].checkLost();
	}
	if(num_compare!=player_num) { //this means that one of the players got their playing set to 0. we need to reorganize
		//remove player by placing the loser it at the end of the list


		player_num-=1; // cut short the numbers of players by 1
	}
}

void DemoDay() {
	for (int i=0; i<50; i++) {
		cout << "*";
	}
	cout << endl;
	cout << "****************** DEMO DAY *********************" << endl;
	cout << endl;
	cout << "All the teams have been given a great opportunity to pitch their company very few will walk out with money! \nWill it be you?"<<endl;

	cout << endl;

}

void Acquistion(int a, int b) { //input the number position of the first player and the second player. a is the company doing the acquiring, b is acquired.
	cout << players[a].name << " is worth over 10x the amount that " << players[b].name << ". " << players[a].name << " now can acquire the company." << endl;

	//move all the money out of b and into a

	players[b].Lost();
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
			cout << "|" << setw(3) << " " <<setw(5) << spaces[start+i].printedAction1  << setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}

		for (int i =0; i<11; i++) { //Action 2
			cout << "|" << setw(3) << " " << setw(5) << spaces[start+i].printedAction2 << setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}
		for (int i =0; i<11; i++) { //Action 3
			cout << "|" << setw(3) << " " << setw(5)<< spaces[start+i].printedAction3 << setw(2) << " ";
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
			cout << "|" << setw(1) << " " << "Owner: "<< setw(1)<< spaces[start+i].printedOwner << setw(1) << " ";
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
			cout << "|" << setw(3) << " " << setw(5) << spaces[start-i].printedAction1 << setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}

		for (int i =0; i<11; i++) { //Action 2
			cout << "|" << setw(3) << " " << setw(5) << spaces[start-i].printedAction2 << setw(2) << " ";
			if (i==10) {
				cout << "|" << endl;
			}
		}
		for (int i =0; i<11; i++) { //Action 3
			cout << "|" << setw(3) << " " << setw(5) << spaces[start-i].printedAction3 << setw(2) << " ";
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
			cout << "|" << setw(1) << " " << "Owner: "<< setw(1) << spaces[i].printedOwner << setw(1) << " ";
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
	cout << "|" << setw(3) << " " << setw(5) << spaces[start].printedAction1 << setw(2) << " " << "|" << setw(98) << " " << "|" << setw(3) << " " << setw(5) << spaces[end].printedAction1 << setw(2) << " " << "|" << endl;
	cout << "|" << setw(3) << " " << setw(5) << spaces[start].printedAction2 << setw(2) << " " << "|" << setw(98) << " " << "|" << setw(3) << " " << setw(5) << spaces[end].printedAction2 << setw(2) << " " << "|" << endl;
	cout << "|" << setw(3) << " " << setw(5) << spaces[start].printedAction3 << setw(2) << " " << "|" << setw(98) << " " << "|" << setw(3) << " " << setw(5) << spaces[end].printedAction3 << setw(2) << " " << "|" << endl;

	//Sixth Row, a line of ------
	cout << "|" << "----------" << "|" << setw(98) << " " << "|" << "----------" << "|" << endl;

	//Seventh Row, Players on the squre
	cout << "|" << setw(3) << " " <<  spaces[start].pieces[0] << spaces[start].pieces[1] <<spaces[start].pieces[2] <<spaces[start].pieces[3] << setw(3) << " " << "|" << setw(98) << " " << "|" << setw(3) << " " <<  spaces[end].pieces[0] << spaces[end].pieces[1] <<spaces[end].pieces[2] <<spaces[end].pieces[3] << setw(3) << " " << "|" << endl;


	//Eighth row, Line of -----
	cout << "|" << "----------" << "|" << setw(98) << " " << "|" << "----------" << "|" << endl;

	//Ninth Row, Owner
	cout << "|" << setw(1) << " " << "Owner: " <<setw(1) << spaces[start].printedOwner << setw(1) << " " << "|" << setw(98) << " " << "|" << setw(1) << " " << "Owner: " <<setw(1) << spaces[end].printedOwner << setw(1)  << " " << "|" << endl;


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
	
	spaces[0].ChangeName("HOME!");
	spaces[0].ChangeOwner(' ');
	spaces[0].AddActions("+1500","STAY0",".....");


	spaces[1].ChangeName("HOROW");
	spaces[1].ChangeOwner(' ');
	spaces[1].AddActions("+1000","MOVE2",".....");


	spaces[2].ChangeName("BUFFE");
	spaces[2].ChangeOwner(' ');
	spaces[2].AddActions("+5000","MOVE4",".....");


	spaces[3].ChangeName("BAD$$");
	spaces[3].ChangeOwner(' ');
	spaces[3].AddActions("-3000","STAY0",".....");


	spaces[4].ChangeName("RICKR");
	spaces[4].ChangeOwner(' ');
	spaces[4].AddActions("+300.","STAY0","BUY??");


	spaces[5].ChangeName("GATES");
	spaces[5].ChangeOwner(' ');
	spaces[5].AddActions("+7000","MOVE6","CARD.");


	spaces[6].ChangeName("ANGEL");
	spaces[6].ChangeOwner(' ');
	spaces[6].AddActions("+200.","MOVE1",".....");


	spaces[7].ChangeName("SEANP");
	spaces[7].ChangeOwner(' ');
	spaces[7].AddActions("+400.","STAY0","BUY??");


	spaces[8].ChangeName("BOGLE");
	spaces[8].ChangeOwner(' ');
	spaces[8].AddActions("+5000","MOVE3","CARD.");


	spaces[9].ChangeName("LYNCH");
	spaces[9].ChangeOwner(' ');
	spaces[9].AddActions("+4000","STAY0","BUY??");


	spaces[10].ChangeName("GROWT");
	spaces[10].ChangeOwner(' ');
	spaces[10].AddActions("+0000","MOVE5",".....");


	spaces[11].ChangeName("DELAY");
	spaces[11].ChangeOwner(' ');
	spaces[11].AddActions("-4000","BACK3",".....");


	spaces[12].ChangeName("LUCKY");
	spaces[12].ChangeOwner(' ');
	spaces[12].AddActions("+8000","BACK2","CARD.");


	spaces[13].ChangeName("COMPE");
	spaces[13].ChangeOwner(' ');
	spaces[13].AddActions("-8000","MOVE1",".....");


	spaces[14].ChangeName("MENTO");
	spaces[14].ChangeOwner(' ');
	spaces[14].AddActions("+0000","MOVE6","CARD.");


	spaces[15].ChangeName("MISSE");
	spaces[15].ChangeOwner(' ');
	spaces[15].AddActions("-5000","BACK4",".....");


	spaces[16].ChangeName("EMERG");
	spaces[16].ChangeOwner(' ');
	spaces[16].AddActions("-4000","BACK6","CARD.");


	spaces[17].ChangeName("OFFIC");
	spaces[17].ChangeOwner(' ');
	spaces[17].AddActions("+0000","BACK1","CARD.");


	spaces[18].ChangeName("RELOC");
	spaces[18].ChangeOwner(' ');
	spaces[18].AddActions("-700.","BACK5","CARD.");


	spaces[19].ChangeName("LUCKE");
	spaces[19].ChangeOwner(' ');
	spaces[19].AddActions("+8000","MOVE1",".....");


	spaces[20].ChangeName("NEWSP");
	spaces[20].ChangeOwner(' ');
	spaces[20].AddActions("+0000","MOVE3","CARD.");


	spaces[21].ChangeName("DESIG");
	spaces[21].ChangeOwner(' ');
	spaces[21].AddActions("-200.","BACK7",".....");


	spaces[22].ChangeName("SALES");
	spaces[22].ChangeOwner(' ');
	spaces[22].AddActions("-700.","MOVE8","BUY??");


	spaces[23].ChangeName("MARKE");
	spaces[23].ChangeOwner(' ');
	spaces[23].AddActions("+300.","MOVE5",".....");


	spaces[24].ChangeName("LAWYE");
	spaces[24].ChangeOwner(' ');
	spaces[24].AddActions("-100.","BACK3","BUY??");


	spaces[25].ChangeName("PMFIT");
	spaces[25].ChangeOwner(' ');
	spaces[25].AddActions("+5000","MOVE8","CARD.");


	spaces[26].ChangeName("ITERA");
	spaces[26].ChangeOwner(' ');
	spaces[26].AddActions("-400.","MOVE3","CARD.");


	spaces[26].ChangeName("PROGR");
	spaces[26].ChangeOwner(' ');
	spaces[26].AddActions("-400.","MOVE9","BUY??");


	spaces[27].ChangeName("TEAM!");
	spaces[27].ChangeOwner(' ');
	spaces[27].AddActions("+1000","MOVE2","CARD.");


	spaces[28].ChangeName("SMART");
	spaces[28].ChangeOwner(' ');
	spaces[28].AddActions("+3000","MOVE3",".....");


	spaces[29].ChangeName("SOCIL");
	spaces[29].ChangeOwner(' ');
	spaces[29].AddActions("+0000","MOVE3",".....");


	spaces[30].ChangeName("HEALT");
	spaces[30].ChangeOwner(' ');
	spaces[30].AddActions("-4000","BACK9","CARD.");


	spaces[31].ChangeName("FAMIL");
	spaces[31].ChangeOwner(' ');
	spaces[31].AddActions("-2000","BACK3",".....");


	spaces[32].ChangeName("BABY!");
	spaces[32].ChangeOwner(' ');
	spaces[32].AddActions("-4000","BACK8","CARD.");


	spaces[33].ChangeName("SCARD");
	spaces[33].ChangeOwner(' ');
	spaces[33].AddActions("-3000","BACK3",".....");


	spaces[34].ChangeName("FORUN");
	spaces[34].ChangeOwner(' ');
	spaces[34].AddActions("+3000","BACK3",".....");


	spaces[35].ChangeName("TIMES");
	spaces[35].ChangeOwner(' ');
	spaces[35].AddActions("+1500","STAY0",".....");


	spaces[36].ChangeName("LEARN");
	spaces[36].ChangeOwner(' ');
	spaces[36].AddActions("+0000","MOVE3",".....");


	spaces[37].ChangeName("TALTR");
	spaces[37].ChangeOwner(' ');
	spaces[37].AddActions("+9000","MOVE9","BUY??");


	spaces[38].ChangeName("CONFE");
	spaces[38].ChangeOwner(' ');
	spaces[38].AddActions("-400.","MOVE9",".....");


	spaces[39].ChangeName("FLIPR");
	spaces[39].ChangeOwner(' ');
	spaces[39].AddActions("+0000","STAY0","BUY??");
}