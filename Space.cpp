//Space.cpp
#include "Space.h"
#include "Player.h"
#include "Action.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

Space::Space() {
	owner = ' ';
	for(int i=0; i<4; i++) {
		pieces[i]=' ';
	}
}

Space::~Space() {
	
}

void Space::ChangeOwner(char buyer) { //when somebody takes and owns a space
	owner = buyer;
}

void Space::PrintName() {
	cout << name;
}

void Space::PrintOwner() {
	printedOwner = owner;
}

void Space::ChangeName(string newName) {
	name = newName;
	printedName= name;
}

void Space::AddActions(string Act1, string Act2, string Act3) {
	Actions.text[0]=Act1;
	Actions.text[1]=Act2;
	Actions.text[2]= Act3;
	printedAction1=Act1;
	printedAction2=Act2;
	printedAction3=Act3;
}