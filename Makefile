CXX=g++
CXXFLAGS=-Wall -g
SRCS = Space.cpp Action.cpp Player.cpp main.cpp
OBJ = $(SRCS:.cpp=.o)

all: main

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

Space.o: Space.h Action.h

Action.o: Action.h

Player.o: Player.h

main.o: Space.h Action.h Player.h

clean:
	rm -f *.o *~
