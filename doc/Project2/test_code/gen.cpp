#include <iostream>
#include <cstdlib>
#include "XmlGenerator.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 6)
	{
		cerr<<"USAGE:./gen (output file name) (#level) (#namespaces of each level) (#approximate rebound ratio) (#subtree)"<<endl;
		cerr<<"EX) ./gen text.xml 4 6 0.25 100000"<<endl;
		return 1;
	}
	string outfile(argv[1]);
	if(outfile.empty())
	{
		cerr<<"missing output file name"<<endl;
		return 1;
	}
	int level = atoi(argv[2]);
	if(level < 1)
	{
		cerr<<"the number of level should be bigger than 1 (root level)"<<endl;
		return 1;
	}
	int number_of_namespace_on_each_level = atoi(argv[3]);
	double ratio = atof(argv[4]);
	if(ratio < 0 || ratio > 1)
	{
		cerr<<"rebound ratio should be bigger than 0.0 and less than 1.0"<<endl;
		return 1;
	}
	int iteration = atoi(argv[5]);
	if(iteration < 1)
	{
		cerr<<"the number of subtree should be bigger than 1"<<endl;
		return 1;
	}
	XmlGenerator gen(outfile, level, number_of_namespace_on_each_level, ratio);
	//XmlGenerator gen(outfile, 4, 6, 0.25);
	int number_for_naming = 0;
	//gen.root->printout(500, number_for_naming);
	gen.generatingXml(iteration, number_for_naming);
	cout<<"the number of elements : "<<number_for_naming<<endl;
	return 0;
}

