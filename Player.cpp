#include "Space.h"
#include "Player.h"
#include "Action.h"
#include "MoneyAction.h"
#include "CardAction.h"
#include "GotoAction.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

Player::Player() {
	cash = 150; //amount of money
	customer = 2; //the number of the customer cards that are still available
	playing = 1; //is the player still in the game?
	currentSpace = 0; //Stores the current space the player is on
	companyscore = 5; //the score of the company's progress. The higher the company score, the more likely the players will get money at Demo Days
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

int Player::GameEnd() {
	if(playing==0) {
		return 0;
	} else {
		return 1;
	}

}

int Player::CashChecker() {
	return cash;
}

void Player::Lost() { //sets the player to no longer playing
	playing =0;
}

int Player::checkLost() { //checks if playing = 1 or 0 to see if we should give them a turn
	if (playing==1) {
		return 1;
	} else {
		return 0;
	}

}

int Player::CustomerChecker() { //returns the number of customer cards left

	return customer;
}

int Player::ScoreChecker() {
	return companyscore;
}

void Player::ImproveScore(int improve) {
	companyscore+=improve;
	if (companyscore>=100) { //ensures that 100 is the maximum a company score can be
		companyscore=100;
	}
}

void Player::moneymove(int moneyadd) {
	cash +=moneyadd;
}

void Player::give_money(int amount)
{
	 cash = amount + cash;
}