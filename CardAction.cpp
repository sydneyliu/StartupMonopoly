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

CardAction::CardAction(int spaces)
{
	_amount = spaces;
}

void CardAction::set_amount(int spaces)
{
	_amount = spaces;
}

int CardAction::get_amount()
{
	return _amount;
}

void CardAction::executeAction(Player *q)
{
    cout << "in move action executeAction\n";
}