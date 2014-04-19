#ifndef MONEYACTION_H
#define MONEYACTION_H

#include <string>

#include "Action.h"
#include "Player.h"


using namespace std;

class MoneyAction : public Action
{
 public: 
  MoneyAction();
  MoneyAction(int money);

  void pay_money(Player *p, int amount);

  void executeAction(Player *q);

 protected:
  int _money;

};


#endif