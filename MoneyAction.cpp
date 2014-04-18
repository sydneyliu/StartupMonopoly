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

MoneyAction::MoneyAction()
{
}

MoneyAction::MoneyAction(int money)
{
	_money = money;
}

void MoneyAction::pay_money(Player &p, int amount)
{
	p.give_money( amount );
	_money -= amount;
}

void MoneyAction::executeAction()
{
    
}