#include "Application.hpp"
#include "Parser.hpp"
#include "Input.hpp"
#include <string>
#include <assert.h>

using namespace std;



class MyInput : public cs540::Input {
    public:
        MyInput(const char *s) : str(s), pos(0) {}
        virtual char get_char();
    private:
        const string str;
        int pos;
};


char
MyInput::get_char() {
    // If at end, return null char.
    if (pos == str.size()) {
        return '\0';
    } else {
        return str.at(pos++);
    }
}

class MyApplication : public cs540::Application {
    public:
        virtual void str(const char *);
        virtual void number(int);
};

void
MyApplication::str(const char *s) {
    printf("Got string: %s\n", s);
}

void
MyApplication::number(int n) {
    printf("Got number: %d\n", n);
}

// Run this with one option, which is the string to parse.
//     ./a.out "a string 1234 1234asdf asdf1234"

int
main(int argc, char *argv[]) {
    assert(argc == 2);
    MyInput in(argv[1]);
    MyApplication app;
    cs540::Parser parser(&app);
    parser.parse(&in);
}
