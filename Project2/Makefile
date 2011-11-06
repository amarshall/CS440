CXX=g++
CFLAGS=-Wall -Wextra -Werror -Wformat=2 -Wfloat-equal -Wshadow -Wwrite-strings -Winit-self -pedantic-errors -Wno-long-long # Weffc++ -Winline -Wpadded
BINARY=parser
SRC_FILES=Element.cpp Node.cpp Parser.cpp String.cpp Text.cpp Visitor.cpp parser_test.cpp
.PHONY: clean

RELEASE ?= 0
ifeq ($(RELEASE), 1)
    CFLAGS+=-O2
else
    CFLAGS+=-g -O0
endif

all: $(BINARY)

generator: XmlGenerator.cpp gen.cpp
	@$(CXX) -O $^ -o $@

$(BINARY): $(SRC_FILES:%.cpp=%.o)
	@$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp %.hpp
	@$(CXX) $(CFLAGS) -c $<

%.o: %.cpp
	@$(CXX) $(CFLAGS) -c $<

clean:
	rm -rf *.o *.dSYM *.plist $(BINARY) generator
