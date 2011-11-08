#ifndef CS540_APPLICATION_HPP
#define CS540_APPLICATION_HPP



namespace cs540 {



class Application {
    public:
        virtual ~Application() {}
        virtual void str(const char *) = 0;
        virtual void number(int n) = 0;
};



}



#endif
