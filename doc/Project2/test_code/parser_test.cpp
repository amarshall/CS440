#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>
#include "Parser.hpp"
#include "Element.hpp"
#include "Text.hpp"
#include "Visitor.hpp"
#include <string.h>
#include <errno.h>
#include <sys/time.h>
using namespace xml;
using namespace std;



// Escape strings for clearer printing and debugging.
std::string
escape_string(const std::string &in) {

    std::string s;
    // Escaped string won't be bigger than double the original size.
    s.reserve(2*s.size());

    for (std::string::const_iterator it = in.begin(); it < in.end(); ++it) {
        switch (*it) {
            case '\n':
                s.append("\\n");
                break;
            case '\r':
                s.append("\\r");
                break;
            case '\t':
                s.append("\\t");
                break;
            case '\f':
                s.append("\\f");
                break;
            case '\v':
                s.append("\\v");
                break;
            case '"':
                s.append("\\\"");
                break;
            default:
                s.push_back(*it);
                break;
        }
    }

    return s;
}

class MyVisitor : public xml::Visitor {
    public:
        MyVisitor() : indent(0) {}
        virtual void start_element_visit(const xml::Element &);
        virtual void end_element_visit(const xml::Element &);
        virtual void visit_text(const xml::Text &);
    private:
        size_t indent;
};

void
MyVisitor::start_element_visit(const xml::Element &e) {
    cout << string(indent, ' ') << "Starting visit of element " << e.nmspace() << ":"
         << e.name() << "..." << endl;
    indent += 2;
}

void
MyVisitor::end_element_visit(const xml::Element &e) {
    indent -= 2;
    cout << string(indent, ' ') << "Ending visit of element " << e.nmspace() << ":"
         << e.name() << "." << endl;
}

void
MyVisitor::visit_text(const xml::Text &t) {
    cout << string(indent, ' ') << "Visiting text content \"" << escape_string(t.str()) << "\"." << endl;
}

void
traverse(const Node *n, size_t indent_size) {

    string indent(indent_size, ' ');

    if (Element::is_Element(n)) {

        const Element *e = Element::to_Element(n);
        cout << indent << "Start: " << e->nmspace() << ":" << e->name() << endl;
        for (size_t i = 0; i < e->n_children(); i++) {
            traverse(e->child(i), indent_size + 2);
        }
        cout << indent << "End: " << e->nmspace() << ":" << e->name() << endl;

    } else if (Text::is_Text(n)) {

        const Text *t = Text::to_Text(n);
        cout << indent <<  "Text: \"" << escape_string(t->str()) << "\"" << endl;

    } else {

        assert(false);
    }
}



int
main(int argc, char *argv[]) {

    int ec, opt, en;
    bool correct_mode = true;
    bool performance_mode = false;
    int iteration = 1;
    char* infile = 0;
    if(argc < 3)
    {
        cerr<<"USAGE: ./parser_test -f input_file_name options"<<endl;
        cerr<<"options :"<<endl;
        cerr<<"-c : test correctness"<<endl;
        cerr<<"-p <#> : test performance and the number of times"<<endl;
        cerr<<"if there is no option, the default is test correctness"<<endl;
        return 1;
    }

    while((opt = getopt(argc, argv, "f:cp:")) != -1)
    {
        switch(opt)
        {
            case 'f':
                infile = optarg;
            break;
            case 'c':
                correct_mode = true;
                performance_mode = false;
            break;
            case 'p':
                correct_mode = false;
                performance_mode = true;
                iteration = atoi(optarg);
            break;
            case '?':
                if(optopt == 'p')
                    cerr<<"option : "<<(char)optopt<<" needs a value"<<endl;
                else
                    cerr<<"Unknown option character : "<<(char)optopt<<endl;
                return 1;
            break;
        }
    }

    int fd = open(infile, O_RDONLY);
    if(fd < 0)
    {
        cerr<<"Open file failed : "<<strerror(errno)<<endl;
        return 1;
    }

    struct stat sb;
    ec = fstat(fd, &sb);
    if( ec != 0)
    {
        cerr<<"Get file information failed : "<<strerror(errno)<<endl;
        return 1;
    }

    const char *doc = (const char *) mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(doc == MAP_FAILED)
    {
        cerr<<"mmap document failed : "<<strerror(errno)<<endl;
        return 1;
    }

    Parser parser;
    const Element *r;
    timeval start_tv, stop_tv;
    double dt;
    if(correct_mode == true)
    {
        r = parser.parse(doc, sb.st_size);
        traverse(r, 0);
        MyVisitor v;
        r->accept(&v);
        delete r;
    }
    else
    {
        r = parser.parse(doc, sb.st_size); // warm up
        delete r;
        ec = gettimeofday(&start_tv, 0);
        if(ec != 0)
        {
                cerr<<"gettimeofday failed : "<<strerror(errno)<<endl;
                return 1;
        }
        for(int i=0; i<iteration; i++)
        {
                r = parser.parse(doc, sb.st_size);
                delete r;
        }
        ec = gettimeofday(&stop_tv, 0);
        if(ec != 0)
        {
                cerr<<"gettimeofday failed : "<<strerror(errno)<<endl;
                return 1;
        }
        dt = (stop_tv.tv_sec + stop_tv.tv_usec/1000000.0)
                - (start_tv.tv_sec + start_tv.tv_usec/1000000.0);
        long long total_bytes = ((long long) iteration)*sb.st_size;
        printf("Elapsed time: %.6f,  Rate (MB/s): %f\n", dt, (total_bytes/(1024*1024))/dt);
    }

    return 0;
}
