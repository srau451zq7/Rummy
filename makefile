CXX := g++
GTEST := -lgtest -lgtest_main -lgmock -pthread
STD :=
SRC_TESTS :=./test/*.cpp
SRC_DIRS :=./src/*.cpp
INCLUDE:=-I ./include
MAIN := main.cpp

tests:
	$(CXX) $(INCLUDE) -o tests.out $(SRC_TESTS) $(SRC_DIRS) $(STD) $(GTEST)

rummy:
	$(CXX) $(INCLUDE) -o rummy.out $(MAIN) $(SRC_DIRS) $(STD)



clean:
	rm -f *.c *.o *.out