//Action.h

#ifndef ACTION_H
#define ACTION_H
#include <string>

using namespace std;

class Action {
	public:
		Action();
		Action(string);
		~Action();
		virtual void executeAction()=0; //pure virtual function execution
		string print_name(int);
		string fillText(int, string);
	private:
		string name;
		string text[3]; //the number of lines in the board for the actions

};

#endif