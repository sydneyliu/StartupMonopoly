#include <iostream>
#include <sstream>
#include <string>

#include "Action.h"
#include "Moneyaction.h"
#include "Player.h"
#include "GotoAction.h"

using namespace std;


GotoAction::GotoAction(){
	
}

GotoAction::GotoAction(int square)
{
	_square = square;
}

void GotoAction::executeAction(Player *q)
{
    cout << "in GotoAction executeAction\n";
}