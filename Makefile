CXX=g++
CXXFLAGS=-Wall -g
SRCS = Space.cpp Action.cpp Player.cpp MoneyAction.cpp MoveAction.cpp GotoAction.cpp main.cpp
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

MoveAction.o: MoveAction.h Action.h

MoneyAction.o: MoneyAction.h Action.h Player.h

main.o: Space.h Action.h Player.h GotoAction.h MoveAction.h MoneyAction.h

clean:
	rm -f *.o *~
