CXX=g++
CXXFLAGS=-std=c++14 -pedantic -Wall -Wextra -Werror -O3

BIND=epivex
SRC=src/main.cc
OBJ=$(SRC:cc=.o)

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIND)

clean:
	rm -f $(BIND)
check:
	@tests/tests.sh
.phony: all clean 
