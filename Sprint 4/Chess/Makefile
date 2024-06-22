CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJS = main.o Board.o Pawn.o Rook.o Bishop.o Knight.o King.o Queen.o

all: chess

chess: $(OBJS)
	$(CXX) $(CXXFLAGS) -o chess $(OBJS)

main.o: main.cpp Board.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Board.o: Board.cpp Board.h Piece.h Pawn.h Rook.h Bishop.h Knight.h King.h Queen.h
	$(CXX) $(CXXFLAGS) -c Board.cpp

Pawn.o: Pawn.cpp Pawn.h Piece.h
	$(CXX) $(CXXFLAGS) -c Pawn.cpp

Rook.o: Rook.cpp Rook.h Piece.h
	$(CXX) $(CXXFLAGS) -c Rook.cpp

Bishop.o: Bishop.cpp Bishop.h Piece.h
	$(CXX) $(CXXFLAGS) -c Bishop.cpp

Knight.o: Knight.cpp Knight.h Piece.h
	$(CXX) $(CXXFLAGS) -c Knight.cpp

King.o: King.cpp King.h Piece.h
	$(CXX) $(CXXFLAGS) -c King.cpp

Queen.o: Queen.cpp Queen.h Piece.h
	$(CXX) $(CXXFLAGS) -c Queen.cpp

clean:
	rm -f *.o chess
