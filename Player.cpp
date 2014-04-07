#include "Space.h"
#include "Player.h"
#include "Action.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

Player::Player() {
	cash = 15;
	customer = 2;
	playing = 1;
	currentSpace = 0;
}


Player::~Player() {

}

void Player::nameChange(char newName) {
	name = newName;
}

void Player::move(Space j,Space k, int playerSpace, int steps) {
	if (currentSpace+steps>=40) {
		currentSpace-=40;
	}
	currentSpace += steps;
	j.pieces[playerSpace]=' ';
	k.pieces[playerSpace]=name;
} 