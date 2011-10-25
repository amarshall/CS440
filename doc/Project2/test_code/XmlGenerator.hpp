#ifndef XML_GENERATOR
#define XML_GENERATOR
#include <vector>
#include <map>
#include <fstream>
using namespace std;
class Element
{
public:
	vector< pair< string, string> > ns;
	vector<string>* prefixs;
	vector<int> prefix_indexs;
	int prefix_index;
	string ename;
	string text_content;
	Element* child;
	Element* sibling;
	fstream* fout;
	int dist;
public:
	
	Element(fstream* fout_in, int dist_in, vector<string>* prefixs_in): prefixs(prefixs_in), fout(fout_in), dist(dist_in)
	{
		child = NULL;
		sibling = NULL;
	};
	~Element(){};
	void randomizeURIandNS();
	void rootprintout(int iter, int& numbering);
	virtual void printout(int subtree, int& numbering);
};

class TextElement : public Element
{
	public:
	TextElement(fstream* fout_in, int dist_in, vector<string>* prefixs_in):Element(fout_in, dist_in, prefixs_in){};
	virtual void printout(int subtree, int& numbering);
};
	
class XmlGenerator
{
public:
	vector<string> nspaces;
	vector<string> prefixs;
	vector<Element*> elements;
	int n_size; //number of namespaces
	int p_size; // number of prefix
	double ratio;
	double rebounded_ratio;
	int level, num_of_ns;
	int gab, dist;
	Element *root;
	fstream* fout;
	
public:
	XmlGenerator(string& outfile, int level_in, int num_of_namespace_in_each_level, double rebounded_ratio_in);
	void generatingXml(int iteration, int &numbering)
	{
		root->rootprintout(iteration, numbering);
		(*fout).close();
		delete fout;
	}

	static string randomizechr(int num);
	~XmlGenerator()
	{
		int size = elements.size();
		for(int i=0; i<size; i++)
		{
			delete elements[i];
		}
	}
	static string itoa(int num);
	

};

#endif
