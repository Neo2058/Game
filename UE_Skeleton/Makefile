CXX=g++
CXXFLAGS=-std=c++23 -O2 -I.

all: GameCoreTest

GameCoreTest: GameCore.o GameCoreTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^

GameCoreCollisionTests: GameCore.o GameCoreCollisionTests.o
	$(CXX) $(CXXFLAGS) -o $@ $^

GameCore.o: GameCore.cpp GameCore.h
	$(CXX) $(CXXFLAGS) -c GameCore.cpp

GameCoreTest.o: GameCoreTest.cpp GameCore.h
	$(CXX) $(CXXFLAGS) -c GameCoreTest.cpp

GameCoreCollisionTests.o: GameCoreCollisionTests.cpp GameCore.h
	$(CXX) $(CXXFLAGS) -c GameCoreCollisionTests.cpp

clean:
	rm -f *.o GameCoreTest
