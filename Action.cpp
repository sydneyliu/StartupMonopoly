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

Action::Action(string name1)
{
	name = name;
}

Action::~Action() {
	
}

string Action::print_name(int number)
{
	return text[number];
}

string Action::fillText(int num, string actions) {

	text[num] = actions;
	return actions;

}


