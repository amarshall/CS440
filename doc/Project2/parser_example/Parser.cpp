#include "Parser.hpp"
#include <assert.h>
#include <ctype.h>
#include <string>
#include "Input.hpp"
#include "Application.hpp"



namespace cs540 {



Parser::Parser(Application *a) : app(a) {
};

void
Parser::parse(Input *in) {

    enum {
        WHITESPACE = 1,
        STRING,
        NUMBER,
        END
    } state = WHITESPACE;

    std::string str;
    int num;
    while (state != END) {

        char ch = in->get_char();

        switch (state) {
            case WHITESPACE:
                {
                    if (isalpha(ch)) {
                        state = STRING;
                        str = ch;
                    } else if (isdigit(ch)) {
                        state = NUMBER;
                        str = ch;
                        num = ch - '0';
                    } else if (ch == '\0') {
                        state = END;
                    } else if (!isspace(ch)) {
                        assert(false);
                    }
                }
                break;
            case STRING:
                {
                    if (isalnum(ch)) {
                        str += ch;
                    } else if (isspace(ch)) {
                        state = WHITESPACE;
                        app->str(str.c_str());
                    } else if (ch == '\0') {
                        state = END;
                        app->str(str.c_str());
                    } else {
                        assert(false);
                    }
                }
                break;
            case NUMBER:
                {
                    if (isalpha(ch)) {
                        state = STRING;
                        str += ch;
                    } else if (isdigit(ch)) {
                        str += ch;
                        num = 10*num + (ch - '0');
                    } else if (isspace(ch)) {
                        state = WHITESPACE;
                        app->number(num);
                    } else if (ch == '\0') {
                        state = END;
                        app->number(num);
                    } else {
                        assert(false);
                    }
                }
                break;
            default:
                assert(false);
        }
    }
}



} // namespace cs540
