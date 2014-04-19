#ifndef CARDACTION_H
#define CARDACTION_H

#include <string>

#include "Action.h"

using namespace std;

class CardAction : public Action
{
 public: 
  CardAction();
  CardAction(int decks);
  void deck1(Player *a);
  void deck2(Player *a);
  void executeAction(Player *q);


 protected:
  int deck_num; //is it deck number one or two?
  int MoneyDeck[50]; //decks of moneyCards

};

#endif