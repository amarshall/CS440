CC=g++
CFLAGS=-g -Wall -Wextra -Werror -Wformat=2 -Wfloat-equal -Wshadow -Wwrite-strings -Winit-self -pedantic-errors -Wno-long-long # -Winline -Wpadded
BINARY=parser
SRC_FILES=Element.cpp Node.cpp Parser.cpp String.cpp Text.cpp Visitor.cpp parser_test.cpp
.PHONY: clean

RELEASE ?= 0
ifeq ($(RELEASE), 1)
    CFLAGS+=-O2
else
    CFLAGS+=-g
endif

all: $(BINARY)

generator: XmlGenerator.cpp gen.cpp
	$(CC) -O $^ -o $@

$(BINARY): $(SRC_FILES:%.cpp=%.o)
	@$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp %.hpp
	@$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *.dSYM *.plist $(BINARY) generator
