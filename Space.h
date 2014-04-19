//Space.h
#ifndef SPACE_H
#define SPACE_H
#include "Action.h"
using namespace std;

class Space {
	public:
		Space();
		~Space();
		char pieces[4]; //keeps track of the pieces that are on that square	
		void ChangeOwner(char); //tracks the owner of the space
		string PrintName();
		char PrintOwner();
		void ChangeName(string);
		void AddActions(string, string, string);
		string printedName;
	private:
		string name; //name of the space. 5 chars
		//Action *Actions; //stores the actions that the square does
		char owner; //tracks the owner of the space
};

#endif