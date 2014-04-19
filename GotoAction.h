#ifndef GOTOACTION_H
#define GOTOACTION_H

#include <string>

#include "Action.h"
#include "Player.h"

using namespace std;

class GotoAction : public Action
{
 public: 
  GotoAction();
  GotoAction(int square);
  void executeAction(Player *q);

 protected:
  int _square;

};

#endif
