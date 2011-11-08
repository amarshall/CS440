#include <iostream>
#include <sstream>
#include <cmath>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "XmlGenerator.hpp"
using namespace std;

const char* baseaddr = "http://cs.binghamton.edu/";

XmlGenerator::XmlGenerator(string& outfile, int level_in, int num_of_namespace_in_each_level, double rebounded_ratio_in)
{
	srand(time(NULL));
	char random_chr;
	string temp_chrs;
	fout = new fstream(outfile.c_str(), ios::out);
	ratio = rebounded_ratio_in;
	level = level_in;
	num_of_ns = num_of_namespace_in_each_level;
	n_size = level * num_of_ns;
	p_size = (int) (n_size * (1.0-ratio));
	if(n_size == 1)
		p_size = 1;
	if(p_size == 0)
		p_size = n_size;
	gab = n_size - p_size;
	if(level == 1)
		dist = 0;
	else
		dist = ceil( (double) gab / (double)(level-1));  
	if(num_of_ns > p_size)
	{
		cerr<<"the number of namespaces of root bigger than the number of prefixs"<<endl;
		cerr<<"adjust rebound ratio to generate more prefixs at least the same number as prefixs in each element"<<endl;
		exit(1);
	}
	for(int i=0; i<n_size; i++)
	{
		nspaces.push_back(baseaddr + randomizechr(10));
	}
	for(int i=0; i<p_size; i++)
	{
		prefixs.push_back(randomizechr(10));
	}
	int n_start = 0;
	int final_p_size=0;
	root = new Element(fout, dist, &prefixs);
	elements.push_back(root);
	for(; n_start < num_of_ns; n_start++)
	{
		root->ns.push_back( pair< string, string >(prefixs[n_start], nspaces[n_start]) );
		root->prefix_indexs.push_back(n_start);
	}

	Element* element = root;
	for(int i = 1; i<level; i++)
	{
		element->child = new Element(fout, dist, &prefixs);
		element = element->child;
		for(; n_start< num_of_ns*(i+1) ;n_start++)
		{
			element->ns.push_back(pair< string, string>(prefixs[n_start-dist*i], nspaces[n_start]) );
			element->prefix_indexs.push_back(n_start-dist*i);
			final_p_size = n_start-dist*i+1;
		}
		elements.push_back(element);
	}

	Element* textelement = new TextElement(fout, dist, &prefixs);
	elements.push_back(textelement);
	if(final_p_size == 0)
		textelement->prefix_index = -1;
	textelement->text_content = "the number of node : ";
	Element* telement = textelement;
	for(int i = 1; i<final_p_size; i++)
	{
		telement->sibling = new TextElement(fout, dist, &prefixs);
		telement = telement->sibling;
		elements.push_back(telement);
		telement->prefix_index = i;
		telement->text_content = "the number of node : ";
	}
	element->child = textelement;
	rebounded_ratio = (1.0 - (double) final_p_size / n_size);
	cout<<"rebound ratio : "<<rebounded_ratio<<endl;

}

void
Element::rootprintout(int iter, int& numbering)
{		
	int elementnum = numbering;
	ename = XmlGenerator::randomizechr(5)+XmlGenerator::itoa(elementnum);
	(*fout)<<"<"<<ename<<" ";
	int size = ns.size();

	if(size !=0)
	{
		for(int i=0; i<size; i++)
		{
			(*fout)<<"xmlns:"<<ns[i].first<<"="<<"\""<<ns[i].second<<"\""<<" ";
		}
		(*fout)<<">";
	}

	for(int i=0; i<iter; i++)
	{
		numbering++;
		child->printout(i, numbering);
	}
	(*fout)<<"</"<<ename<<">";
}
void
Element::printout(int subtree, int& numbering)
{
	int elementnum = numbering;
	ename = XmlGenerator::randomizechr(5)+XmlGenerator::itoa(elementnum);
	(*fout)<<"<"<<ename<<" ";
	int size = ns.size();
	string newURI, newNS;
	if(subtree > 0)
	{
		for(int i=0; i<dist; i++)
		{
			newURI = baseaddr + XmlGenerator::randomizechr(10);
			ns[i].second = newURI;
		}
		for(int i=dist; i<size; i++)
		{
			newURI = baseaddr + XmlGenerator::randomizechr(10);
			newNS = XmlGenerator::randomizechr(10);
			ns[i].first = newNS;
			ns[i].second= newURI;
			(*prefixs)[prefix_indexs[i]] = newNS;
		}
	}

	if(size !=0)
	{
		for(int i=0; i<size; i++)
		{
			(*fout)<<"xmlns:"<<ns[i].first<<"="<<"\""<<ns[i].second<<"\""<<" ";
		}
		(*fout)<<">";
	}
	numbering++;
	child->printout(subtree, numbering);
	(*fout)<<"</"<<ename<<">";
}

void
TextElement::printout(int subtree,  int& numbering)
{
	int elementnum = numbering;
	ename = XmlGenerator::randomizechr(5)+XmlGenerator::itoa(elementnum);
	if(prefix_index == -1)
		(*fout)<<"<"<<ename<<">";
	else
		(*fout)<<"<"<<(*prefixs)[prefix_index]<<":"<<ename<<">";

	(*fout)<<text_content<<XmlGenerator::itoa(elementnum);

	if(prefix_index == -1)
		(*fout)<<"</"<<ename<<">";
	else
		(*fout)<<"</"<<(*prefixs)[prefix_index]<<":"<<ename<<">";

	if(sibling != NULL)
	{
		numbering++;
		sibling->printout(subtree, numbering);
	}
}

string
XmlGenerator::itoa(int num)
{
	ostringstream stm;
	stm << num;
	return stm.str();
}

string
XmlGenerator::randomizechr(int num)
{
	char random_chr;
	string temp_chrs;
	for(int i=0; i<num; i++)
	{
		while('a' > (random_chr = rand()%('z'+1)));
		temp_chrs.append(1, random_chr);
	}
	return temp_chrs;
}



