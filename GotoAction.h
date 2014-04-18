#ifndef GOTOACTION_H
#define GOTOACTION_H

#include <string>

#include "action.h"
#include "player.h"

using namespace std;

class GotoAction : public Action
{
 public: 
  GotoAction();
  GotoAction(int square);
  void executeAction();

 protected:
  int _square;

};

#endif
