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

char Space::PrintOwner() {
	return owner;
}

void Space::ChangeName(string newName) {
	name = newName;
	printedName= name;
}

void Space::AddActions(string Act1, string Act2, string Act3) {
	Actions->fillText(0, Act1);
	Actions->fillText(1, Act2);
	Actions->fillText(2, Act3);

}