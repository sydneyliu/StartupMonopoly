#ifndef CARDACTION_H
#define CARDACTION_H

#include <string>

#include "Action.h"

using namespace std;

class CardAction : public Action
{
 public: 
  CardAction();
  CardAction(int spaces);

  void set_amount(int spaces);
  int get_amount();

  void executeAction();


 protected:
  int _amount;

};

#endif