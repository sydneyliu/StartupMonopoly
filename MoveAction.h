#ifndef MOVEACTION_H
#define MOVEACTION_H

#include <string>

#include "Action.h"

using namespace std;

class MoveAction : public Action
{
 public: 
  MoveAction();
  MoveAction(int spaces);

  void set_amount(int spaces);
  int get_amount();

  void executeAction();


 protected:
  int _amount;

};

#endif