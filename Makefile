CXX=g++
CXXFLAGS=-Wall -g
SRCS = Space.cpp Action.cpp Player.cpp MoneyAction.cpp CardAction.cpp GotoAction.cpp Bank.cpp main.cpp
OBJ = $(SRCS:.cpp=.o)

all: main

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

Space.o: Space.h Action.h

Action.o: Action.h

Player.o: Player.h Space.h

GotoAction.o: GotoAction.h Action.h Player.h Space.h

CardAction.o: CardAction.h Action.h

MoneyAction.o: MoneyAction.h Action.h Player.h

Bank.o: Bank.h

main.o: Space.h Action.h Player.h GotoAction.h CardAction.h MoneyAction.h Bank.h

clean:
	rm -f *.o *~
