#ifndef CS540_PARSER_HPP
#define CS540_PARSER_HPP



namespace cs540 {



// Forward declarations.
class Input;
class Application;



class Parser {
    public:
        Parser(Application *);
        ~Parser() {}
        void parse(Input *);
    private:
        Application *const app;
};



}



#endif
