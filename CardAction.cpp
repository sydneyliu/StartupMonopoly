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
}

void CardAction::deck1(Player *a) { //Deals with Cash. Generates a random card between 1-50.
	srand(time(0));
}

void CardAction::deck2(Player *a) { //Deals with customercards. Remove somebody's customer card. Who's customer card?
	srand(time(0));
}

void CardAction::executeAction(Player *q)
{
    if(deck_num ==1 ) { //deck num is 1

    } else { //deck num is 2

    }
}