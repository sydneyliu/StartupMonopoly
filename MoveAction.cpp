#include "Space.h"
#include "Player.h"
#include "Action.h"
#include "MoneyAction.h"
#include "MoveAction.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

MoveAction::MoveAction()
{
}

MoveAction::MoveAction(int spaces)
{
	_amount = spaces;
}

void MoveAction::set_amount(int spaces)
{
	_amount = spaces;
}

int MoveAction::get_amount()
{
	return _amount;
}

void MoveAction::executeAction()
{
    cout << "in move action executeAction\n";
}