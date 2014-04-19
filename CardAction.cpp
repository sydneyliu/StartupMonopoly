#include "Space.h"
#include "Player.h"
#include "Action.h"
#include "MoneyAction.h"
#include "CardAction.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

CardAction::CardAction()
{
}

CardAction::CardAction(int decks)
{
	deck_num=decks; //sees which type of deck to use
	for(int i=0; i<50; i++) {
		MoneyDeck[i]=i*100;
	}
}

void CardAction::deck1(Player *a) { //Deals with Cash. Generates a random card between 1-50.
	srand(time(0));
	cout << "You can now draw from the money deck! Please hit enter to draw.";
	string enternow;
	getline(cin, enternow);
	if (enternow.empty()) { //utilizes the empty line to continue
		enternow ="a";
	}
	int shuffle = rand() % 50;
	a->moneymove(MoneyDeck[shuffle]);
	cout << "You drew a card that delivers: $"<< MoneyDeck[shuffle] << endl;
	cout << "Congratulations! Enjoy the gift from given by the TalentTrail team from the MoneyCard!" << endl;
}

void CardAction::deck2(Player *a) { //Deals with customercards. Remove somebody's customer card. Who's customer card?
	srand(time(0));
	cout << "You can now draw from the Customer Deck! Please hit enter to draw." << endl;
	string enternow;
	getline(cin, enternow);
	if (enternow.empty()) { //utilizes the empty line to continue
		enternow ="a";
	}
	int CustomDeck = rand() %10;

	if(CustomDeck == 0) {
		cout << "Whoa! You have found the rare card! You may now select anybody's customer card and take it!" << endl;
	} else if (CustomDeck <8) {
		cout << "You now have one more customer card" << endl;
		a->AddCustomer();
		cout << "You have " << a->CustomerChecker() << " Customer cards" << endl;
	} else {
		cout << "This is what your card says:" << endl;
		cout << "'Have a nice day!'" << endl;
		cout << "Looks like you don't get anything from this card." << endl;
	}
}

void CardAction::executeAction(Player *q)
{
    if(deck_num ==1 ) { //deck num is 1
    	deck1(q);
    } else { //deck num is 2
    	deck2(q);
    }
}