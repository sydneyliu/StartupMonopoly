//Action.cpp
#include "Space.h"
#include "Player.h"
#include "Action.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

Action::Action()
{
}

Action::Action(string name)
{
	_name = name;
}

Action::~Action() {
	
}

string Action::print_name()
{
	return _name;
}


