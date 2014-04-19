#include <iostream>
#include <sstream>
#include <string>

#include "Action.h"
#include "MoneyAction.h"
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
    q->currentSpace = _square;
	//spaces[mover1].pieces[i]=' '; //updates the position in the board
	//spaces[mover2].pieces[i]=players[i].name;
}