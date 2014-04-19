#include "Space.h"
#include "Player.h"
#include "Action.h"
#include "MoneyAction.h"
#include "CardAction.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

CardAction::CardAction()
{
}

CardAction::CardAction(int decks)
{
	deck_num=decks; //sees which type of deck to use
}

void CardAction::executeAction(Player *q)
{
    cout << "in move action executeAction\n";
}