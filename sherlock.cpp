/*
 * sherlock.cpp
 * parses a GraphML file and saves data into a network.
 *  Created on: Nov 12, 2013
 *      Author: hooda
 */
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include "datastructure.h"
#include "parser.h"
#include "sherlock.h"
using namespace std;


void sherlock::holmes(string filename, simplegraph* graph)
{
	//calling observe to create a string vector from the file.
	vector<string> input = observe(filename);

	//now process the string vector.
	deduce(input,graph);
}


vector<string> sherlock::observe(string s)
{
//	cout<<"txtinputstart";
	int count = 0;
	vector<string> logs;
	string line;
	ifstream myfile (s.c_str());

	if ( myfile.is_open() )
	{
			while ( ! myfile.eof() )
	        {
				getline (myfile, line);
				logs.push_back(line);
				count++;
	         }

	        myfile.close();
	}

	return logs;
}


void sherlock::deduce(vector<string> input, simplegraph* graph)
{
//	cout<<endl<<"start deduce"<<endl;
	int max = input.size();
		int cur = 0; /** cur is the iterator. */
		while(cur<max)/**iterate over input, for nodes only, because while adding edges its nodes must exist. */
		{
//			cout<<input[cur]<<endl;
			string line = input[cur];
			string inst(line,0,5); /**check whether the description is of a node. */
			if (inst.compare("<node") == 0)
			{
//				cout<<"deduce added a node"<<endl;
				nodehandler(input[cur],input[cur+1],input[cur+2],input[cur+3],graph); /** call nodehandler with all the lines in its description.*/
				cur = cur + 5; /** Increment by 5, since a node description will be of 5 lines.*/
			}
			else
			{
				cur++;
			}
		}
		cur = 0; /** Reset the iterator.*/
		while (cur<max)/** iterate again, this time for edges */
		{
			string line = input[cur];
			string inst(line,0,5);
			if (inst.compare("<edge") == 0)
			{
				edgehandler(line,graph);
				cur++;
			}

			else
			{
				cur++;
			}
		}
}



void sherlock::edgehandler(string s, simplegraph* graph)
{
/**expected edge format:
 * <edge source=" 2" target=" 3"/>
 */
	int node1;
	int node2;

	string t = s.substr(15);
	int tem = t.find(" t");
	string t2 = t.substr(0,tem-1);
	int phew = atoi(t2.c_str());
	node1 = phew;

	int px = t.find("t=");
	string t3 = t.substr(px);
	string t4 = t3.substr(4);
	int py = t4.find("/>");
	string t5 = t4.substr(0,py-1);
	int phew2 = atoi(t5.c_str());
	node2 = phew2;


	edge* e = new edge;
	e->friend1 = graph->nodelist[node1];
	e->friend2 = graph->nodelist[node2];

	e->friend1->friends.push_back(e->friend2); //TODO snake tail chasing?
	e->friend2->friends.push_back(e->friend1);

	graph->friendlist.push_back(e);

}

string sherlock::extract(string s)
{
	string s2 = s.substr(16);
	int pos = s2.find("</");
	string final = s2.substr(0, pos);
	return final;
}

void sherlock::nodehandler(string s1, string s2, string s3, string s4, simplegraph* graph)
{
//	cout<<"tried added a node"<<endl;
/** NOTE: This MUST be the format of the graphml, otherwise won't work properly.
*<node id=" 0" >
*<data key="d0"> Mahima Singh</data>
*<data key="d1"> IITD</data>
*<data key="d2"> 1</data>
*</node>
 */
	string name = extract(s2);
	string univ = extract(s3);
	string id = extract(s4);

	string t = s1.substr(11);
	int tem = t.find(" >");
	string t2 = t.substr(0,tem-1);
	int phew = atoi(t2.c_str());

	people* watson = new people;
	watson->name  = name;
	watson->university = univ;
	watson->id = atoi(id.c_str());
	watson->nodeid = phew;

	graph->nodelist.push_back(watson);
//	cout<<"added a node"<<endl;
}


//int main()
//{
//	sherlock* sh = new sherlock;
//	simplegraph* graph = new simplegraph;
//	string filename = "graph.graphml";
//	sh->holmes(filename, graph);
//
//	cout<<graph->faculty.size()<<endl;
//	cout<<graph->students.size()<<endl;
//	cout<<graph->nodelist.size()<<endl;
//	return 0;
//}
