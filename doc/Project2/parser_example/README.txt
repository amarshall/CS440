This does a simple parse and callback.

It parses strings consisting of sequences of digits and
characters, separated by white space.  If the sequence consists
only of digits, then it is treated as a number.

Compile with:

    g++ main.cpp Parser.cpp

Run with:

    ./a.out "test_string"

For example, running with:

    ./a.out "a 123 213df df1234    fooey"

prints out:

    Got string: a
    Got number: 123
    Got string: 213df
    Got string: df1234
    Got string: fooey
