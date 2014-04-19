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

  void executeAction(Player *q);


 protected:
  int deck_num; //is it deck number one or two?

};

#endif