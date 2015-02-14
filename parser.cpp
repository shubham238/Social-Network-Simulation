/*
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include "datastructure.h"
using namespace std;

//Globals
int univindex=0;
int depindex=0;
*/
//Function declarations

/*void linehandler(string s, network* graph);
vector<string> split(string s1, string s2);
void initialise(vector<string>, network* graph);
//vector<string> txt2input(string s);
void parse(string s, network* graph);
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
using namespace std;

vector<string> parser::txt2input(string s)
{
	cout<<"txtinputstart";
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

//call with filename to get stuff done... :)
void parser::parse(string s, network* graph)
{
	cout<<"parserstart";
	vector<string> input = txt2input(s);
	initialise(input,graph);

}



//Needs: a string vector containing each line of input file as seperate string, the network object which will get the data from input.
//Creates all univ, dep etc in the network object from input.
void parser::initialise(vector<string>input, network* graph)
{
	int max = input.size();
	int cur = 0;
	univindex =0;
	while (cur<max)//iterate over input.
	{
		linehandler(input[cur], graph);
		cur++;
	}

}

//split a string s1 by string s2. s2 is not included in any of the pieces.
vector<string> parser::split(string s1, string s2)
{
	vector<string> ans;
	string rem = s1;
	while (!(rem.find(s2)==string::npos))
	{
		int i = rem.find(s2);
		ans.push_back(rem.substr(0, i));
		rem = rem.substr(i+1);
	}
	ans.push_back(rem);
	return ans;
}

//does whatever has to be done for each line of input.
//basically creates an object, sets its properties, and pushes it into the lists of courses, univs, deps etc wherever applies.
void parser::linehandler(string s, network* graph)
{

	vector<string> tokens = split(s," ");
	string instruction = tokens[0];

	if (instruction.compare("UNIVERSITY") == 0)
	{

		university* univ = new university();
		univ->name = tokens[1];
		graph->universitylist.push_back(univ);
		univindex+=1;
		depindex = 0;

	}

	if (instruction.compare("DEPARTMENT") == 0)
	{
		int pkl=0;
		department* dep = new department;
		dep->name = tokens[1];
		dep->faculty_no = atoi(tokens[2].c_str());
		pkl=dep->faculty_no;
		dep->student_no = atoi(tokens[3].c_str());
		pkl=dep->student_no;
		dep->dep_courses = atof(tokens[4].c_str());
		dep->nondep_courses = atof(tokens[5].c_str());
		graph->universitylist[univindex-1]->departments.push_back(dep);
		depindex = depindex + 1;

	}

	if (instruction.compare("COURSE") == 0)
	{
		courses* c = new courses;
		c->name = tokens[1];
		c->frequency_per_year = atof(tokens[3].c_str());
		department* pdep = graph->universitylist[univindex-1]->departments[depindex-1];

		//searching for the dep of the course in courselist.





				c->dep = graph->universitylist[univindex-1]->departments[depindex-1];
				(graph->universitylist[univindex-1]->departments[depindex-1]->courselist).push_back(c);
				(graph->universitylist[univindex-1])->courselist.push_back(c);






	}

	if (instruction.compare("INTEREST") == 0)
	{
		interest* i = new interest;
		i->name = tokens[1];
		graph->interests.push_back(i);
		graph->universitylist[univindex-1]->departments[depindex-1]->poplist[tokens[1]] = atof(tokens[2].c_str());
		graph->universitylist[univindex-1]->departments[depindex-1]->interests.push_back(i);
		for(int p;p<graph->interests.size();p++)
		{
             if(graph->interests[p]->name==i->name)
             {
            	 break;
             }
             else if(p==graph->interests.size()-1)
             {
            	graph->interests.push_back(i);
             }
		}
	}

	if (instruction.compare("HOSTEL") == 0)
	{
		hostel* h = new hostel;
		h->name = tokens[1];
		graph->universitylist[univindex-1]->hostels.push_back(h);

	}

	if (instruction.compare("HOUSELOCALITY") == 0)
	{
		houselocality* h = new houselocality;
		h->name = tokens[1];
		graph->universitylist[univindex-1]->houselocalitylist.push_back(h);

	}

	if (instruction.compare("FRIENDSHIPRATE") == 0)
	{
		graph->universitylist[univindex-1]->FRIENDSHIPRATE = atoi(tokens[1].c_str());

	}

	if (instruction.compare("OPENNESS") == 0)
	{
		graph->universitylist[univindex-1]->OPENNESS = atof(tokens[1].c_str());

	}

	if (instruction.compare("FRIENDLINESS") == 0)
	{
		graph->universitylist[univindex-1]->FRIENDLINESS = atof(tokens[1].c_str());

	}

	if (instruction.compare("RANDOMSEED") == 0)
	{
		graph->RANDOMSEED.push_back(atoi(tokens[1].c_str()));
		graph->RANDOMSEED.push_back(atoi(tokens[2].c_str()));
		graph->RANDOMSEED.push_back(atoi(tokens[3].c_str()));
		int ran4=atoi(tokens[4].c_str());
		graph->RANDOMSEED.push_back(atoi(tokens[4].c_str()));

	}


}


