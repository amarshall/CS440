CXX=g++
CFLAGS=-Wall -Wextra -Werror -Wformat=2 -Wfloat-equal -Wshadow -Wwrite-strings -Winit-self -pedantic-errors -Wno-long-long # Weffc++ -Winline -Wpadded
.PHONY: clean

RELEASE ?= 0
ifeq ($(RELEASE), 1)
    CFLAGS+=-O2
else
    CFLAGS+=-g -O0
endif

all: part1_test part2_test

part1_test: Part1/test.o
	$(CXX) $(CFLAGS) $^ -o $@

Part1/test.o: Part1/test.cpp Part1/List.hpp
	$(CXX) $(CFLAGS) -c $< -o $@

part2_test: Part2/test.o
	$(CXX) $(CFLAGS) $^ -o $@

Part2/test.o: Part2/test.cpp Part2/Sptr.hpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.dSYM *.plist part1_test part2_test
