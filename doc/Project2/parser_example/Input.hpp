#ifndef CS540_INPUT_HPP
#define CS540_INPUT_HPP



namespace cs540 {



class Input {
    public:
        virtual ~Input() {}
        virtual char get_char() = 0;
};



}



#endif
