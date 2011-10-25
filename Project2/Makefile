CC=g++
CFLAGS=-Wall -Wextra -Werror -Wformat=2 -Wfloat-equal -Wshadow -Wwrite-strings -Winit-self -Wmissing-declarations -pedantic-errors # -Winline -Wpadded
BINARY=parsexml
SRC_FILES=Element.cpp Node.cpp Parser.cpp String.cpp Text.cpp Visitor.cpp
.PHONY: clean

RELEASE ?= 0
ifeq ($(RELEASE), 1)
    CFLAGS+=-O2
else
    CFLAGS+=-g
endif

all: $(BINARY)

$(BINARY): $(SRC_FILES:%.c=%.o)
	@$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c %.h
	@$(CC) $(CFLAGS) -c $<

%.o: %.c
	@$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *.dSYM $(BINARY)
