.PHONY: all
all: parser_test gen

.PHONY: gen
gen:
	g++ -O -Wall -Wno-unused -o gen XmlGenerator.cpp gen.cpp

.PHONY: parser_test
parser_test:
	g++ -g -Wall -Wno-unused -o parser_test parser_test.cpp Element.cpp Parser.cpp String.cpp Text.cpp

clean:
	rm -rf gen parser_test *.o
