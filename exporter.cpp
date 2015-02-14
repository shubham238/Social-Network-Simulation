/*
 * exporter.cpp
 * Exports a graph into a graphml file.
 *  Created on: Nov 13, 2013
 *      Author: hooda
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include "datastructure.h"
#include "exporter.h"

//
//int main()
//{
//
//	ofstream myfile;
//		myfile.open ("example.txt");
//		myfile << "Writing this to a file.\n";
//		myfile.close();
//	return 0;
//}

void exporter::write (network* graph)
{
		cout<<"exporting"<<endl;
		vector<int> nodelist;
	vector<pair<int,int> > edgelist;
	ofstream myfile;
	myfile.open ("network.graphml");
	cout<<"exporting"<<endl;

	int univ_count = graph->universitylist.size();
	int i=0;

	// add nodes to the graph.
	while(i<univ_count)
	{
		int j = 0;
		int jmax = graph->universitylist[i]->students.size();
		while(j<jmax)
		{
			vector<string> node_data = nodexs(graph->universitylist[i]->students[j], nodelist.size());
			nodelist.push_back(graph->universitylist[i]->students[j]->entryno);
			for(int d = 0; d<node_data.size(); d++){myfile<<node_data[d]<<endl;}
			j++;
		}
		int k=0;
		int kmax = graph->universitylist[i]->facultylist.size();
		while (k<kmax)
		{
			vector<string> node_data = nodexf(graph->universitylist[i]->facultylist[k], nodelist.size());
			nodelist.push_back(graph->universitylist[i]->facultylist[k]->emp_code);
			for(int f = 0; f<node_data.size(); f++){myfile<<node_data[f]<<endl;}
			k++;
		}
		i++;
	}

	//add edges to the graph
		i=0;
		while(i<univ_count)
		{
			int j = 0;
			int jmax = graph->universitylist[i]->students.size();
			while(j<jmax)
			{
				int x = 0;
				int x_max = graph->universitylist[i]->students[j]->sfriends.size();
				while(x<x_max)
				{
					int n1 = lookup(graph->universitylist[i]->students[j]->entryno, nodelist);
					int n2 = lookup(graph->universitylist[i]->students[j]->sfriends[x]->entryno, nodelist);
					string edge = edgex(n1, n2, edgelist);
					if (edge != "xxx")
					{
						myfile<<edge<<endl;
					}
				}
				j++;
			}
//			int k=0;
//			int kmax = graph->universitylist[i]->facultylist.size();
//			while (k<kmax)
//			{
//				int y = 0;
//				int y_max = graph->universitylist[i]->facultylist[k]->friends.size();
//				while(y<y_max)
//				{
//					int n1 = lookup(graph->universitylist[i]->facultylist[k]->emp_code, nodelist);
//					int n2 = lookup(graph->universitylist[i]->facultylist[k]->friends[y]->emp_code, nodelist);
//					string edge = edgex(n1, n2, edgelist);
//					if (edge != "xxx")
//					{
//						myfile<<edge;
//					}
//				}
//				k++;
//			}
			i++;
		}
	myfile.close();
}

string exporter::edgex(int n1, int n2, vector<pair<int, int> > edgelist)
{
	pair<int,int> friends;
	if (n1>n2)
	{
		int temp1 = n1;
		int temp2 = n2;
		n2 = temp1;
		n1 = temp2;
	}

	friends.first = n1;
	friends.second = n2;

	bool exist = false;
	int i=0;
	int imax = edgelist.size();
	while(i<imax)
	{
		if (edgelist[i]==friends)
		{
			exist = true;
			i = imax;
		}
		i++;
	}
	if (!exist)
	{
		//<edge source=" 3" target=" 211"/>

		string s1 = "<edge source=\" ";
		string s2 = to_string(n1);
		string s3 = "\" target=\" ";
		string s4 = to_string(n2);
		string s5 = "\"/>";
		string sf = s1+s2+s3+s4+s5;
		edgelist.push_back(friends);
		return sf;
	}
	return "xxx";
}

vector<string> exporter::nodexs(student* stud, int i)
{
//	<node id=" 0" >
//	<data key="d0"> Mahima Singh</data>
//	<data key="d1"> IITD</data>
//	<data key="d2"> CSE</data>
//	<data key="d3"> F9</data>
//	<data key="d4"> Faculty</data>
//	<data key="d5"> 1</data>
//	</node>

	vector<string> data;
	string s1 = "<node id=\" ";
	string s2 = to_string(i);
	string s3 = "\" >";
	data.push_back(s1+s2+s3);

	s1 = "<data key=\"d0\"> ";
	s2 = stud->name;
	s3 = "</data>";
	data.push_back(s1+s2+s3);

	s1 = "<data key=\"d1\"> ";
	s2 = stud->st_university->name;
	data.push_back(s1+s2+s3);

//	s1 = "<data key=\"d2\"> ";
//	s2 = stud->st_department->name;
//	data.push_back(s1+s2+s3);
//
//	s1 = "<data key=\"d3\"> ";
//	s2 = stud->st_hostel->name;
//	data.push_back(s1+s2+s3);
//
//	s1 = "<data key=\"d4\"> ";
//	s2 = "Student";
//	data.push_back(s1+s2+s3);

	s1 = "<data key=\"d2\"> ";
	s2 = to_string(stud->entryno);
	data.push_back(s1+s2+s3);

	return data;
}

vector<string> exporter::nodexf(faculty* fac, int i)
{
	vector<string> data;
	string s1 = "<node id=\" ";
	string s2 = to_string(i);
	string s3 = "\" >";
	data.push_back(s1+s2+s3);

	s1 = "<data key=\"d0\"> ";
	s2 = fac->name;
	s3 = "</data>";
	data.push_back(s1+s2+s3);

	s1 = "<data key=\"d1\"> ";
	s2 = fac->univty->name;
	data.push_back(s1+s2+s3);

//	s1 = "<data key=\"d2\"> ";
//	s2 = fac->fac_department->name;
//	data.push_back(s1+s2+s3);
//
//	s1 = "<data key=\"d3\"> ";
//	s2 = fac->fac_houselocality->name;
//	data.push_back(s1+s2+s3);
//
//	s1 = "<data key=\"d4\"> ";
//	s2 = "Faculty";
//	data.push_back(s1+s2+s3);

	s1 = "<data key=\"d2\"> ";
	s2 = to_string(fac->emp_code);
	data.push_back(s1+s2+s3);

	return data;
}

int exporter::lookup(int id, vector<int> nodelist)
{
	int ans;
	int i = 0;
	int imax = nodelist.size();
	while(i<imax)
	{
		if (nodelist[i] == id)
		{
			ans = i;
			i = imax;
		}
		i++;
	}
	return ans;
}

string exporter::to_string(int number){
    string number_string = "";
    char ones_char;
    int ones = 0;
    while(true){
        ones = number % 10;
        switch(ones){
            case 0: ones_char = '0'; break;
            case 1: ones_char = '1'; break;
            case 2: ones_char = '2'; break;
            case 3: ones_char = '3'; break;
            case 4: ones_char = '4'; break;
            case 5: ones_char = '5'; break;
            case 6: ones_char = '6'; break;
            case 7: ones_char = '7'; break;
            case 8: ones_char = '8'; break;
            case 9: ones_char = '9'; break;
        }
        number -= ones;
        number_string = ones_char + number_string;
        if(number == 0){
            break;
        }
        number = number/10;
    }
    return number_string;
}
