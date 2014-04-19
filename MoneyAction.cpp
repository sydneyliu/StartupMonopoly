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

void MoneyAction::pay_money(Player *p, int amount)
{
	p->give_money( amount );
	_money -= amount;
}

void MoneyAction::executeAction(Player *q)
{
	int cashupdate = q->CashChecker();
    if(_money < 0 &&  cashupdate< -1*(_money)) {
    	cout << "You have too little money to lose all of that money. Your balance remains the same." << endl;
    } else {
    	q->moneymove(_money);
    	cout << "Your account balance has been changed by $" << _money << endl;
    }

}