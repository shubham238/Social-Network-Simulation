#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include "datastructure.h"
#include "question.h"

using namespace std;

pair<int**, int**> modfw(simplegraph* graph)
{
	int v = graph->nodelist.size();
	//int dmat[v][v] = {{-42}};
	//int nmat[v][v] = {{0}};

	int** dmat = new int* [v];
	for(int temp = 0; temp<v; ++temp)
	{
		//int tempr[v] = {{-42}};
		dmat[temp] = new int[v];
		for (int temp2 = 0; temp2<v; temp2++)
		{
			dmat[temp][temp2] = -42;
		}
	}

	int** nmat = new int* [v];
		for(int temp = 0; temp<v; ++temp)
		{
			//int tempr[v] = {{-42}};
			nmat[temp] = new int[v];
			for (int temp2 = 0; temp2<v; temp2++)
			{
				nmat[temp][temp2] = 0;
			}
		}


	for(int n = 0; n<v; n++)
	{
		dmat[n][n] = 0;
	}
	for(int e = 0; e<graph->friendlist.size(); e++)
	{
		dmat[graph->friendlist[e]->friend1->nodeid][graph->friendlist[e]->friend2->nodeid] = 1;
	}

	for(int k=0;k<v;k++)
	{
		for(int j=0;j<v;j++)
		{
			for(int i=0; i<v; i++)
			{
				if(dmat[i][k] + dmat[k][j] < dmat[i][j])
				{
					dmat[i][j] = dmat[i][k] + dmat[k][j];
					nmat[i][j] = k;
				}
			}
		}
	}

	pair<int**, int**> ret;
	ret.first = dmat;
	ret.second = nmat;
	return ret;
}

edge* edgefind(int i, int j, simplegraph* graph)
{
	if(j>i)
	{
		int temp1 = i;
				int temp2 = j;
				j = temp1;
				i = temp2;
	}
	int e = 0;
	int emax = graph->friendlist.size();
	while(e<emax)
	{
		if(graph->friendlist[e]->friend1->nodeid == i && graph->friendlist[e]->friend2->nodeid == j)
		{return graph->friendlist[e];}
		e++;
	}
}

vector<edge*> pathfinder(simplegraph* graph, int i, int j, pair<int**, int**> matrices)
{
	vector<edge*> path;
	if (matrices.first[i][j] == -42)
	{
		return path;
	}
	int itrmdt = matrices.second[i][j];

	if (itrmdt == 0)
	{
		path.push_back(edgefind(i,j, graph));
		return path;
	}
	else
	{
		vector<edge*> patha = pathfinder(graph, i, itrmdt, matrices);
		vector<edge*> pathb = pathfinder(graph, itrmdt, j, matrices);
		for (int ix = 0; i<patha.size(); ix++){path.push_back(patha[ix]);}
		for (int jx = 0; i<pathb.size(); jx++){path.push_back(pathb[jx]);}
		return path;
	}
}


//Answering the questions.

people* id2node (int id, string univ, simplegraph* graph)
{
	int imax = graph->nodelist.size();
	for (int i = 0; i<imax; i++)
	{
		if (graph->nodelist[i]->id == id && graph->nodelist[i]->university == univ)
		{
			return graph->nodelist[i];
		}
	}

	cout<<"id2node couldn't find the person."<<endl;
}

vector<people*> clique(int nodeid, simplegraph* graph)
{
	vector<people*> clq;
	//TODO bern-kerbosch
	return clq;
}

void importance(simplegraph* graph, pair<int**, int**> matrices)
{
	//WARNING : must be run only once, otherwise all imps get 2x, 3x etc
	int v = graph->nodelist.size();
	for(int i = 0; i<v; i++)
	{
		int j = 0;
		while (j<i)
		{
			vector<edge*> path = pathfinder(graph, i, j, matrices);
			path[0]->friend1->importance+=1;
			for (int k = 0; k<path.size(); k++)
			{
				path[k]->friend2->importance+=1;
			}

		}
	}
}

void importancex(simplegraph* graph)
{
	importance(graph, modfw(graph));
}

int q2(people* from, people* to, simplegraph* graph)
{
	vector<people*> path;
//do stuff to have path contain path.
	return path.size();
}


vector<people*> q3(people* from, people* to, simplegraph* graph)
{
	vector<people*> path;
//do stuff to have path contain path.
	return path;
}

//for q4 just call modfw
//for q5 call importance/importancex.

vector<people*> q6(simplegraph* graph, people* guy)
{
	//assuming the importance function has already been run once.
	int imax = guy->friends.size();
	vector<people*> moreimp;
	for (int i = 0; i<imax; i++)
	{
		if (guy->friends[i]->importance>guy->importance)
		{
			moreimp.push_back(guy->friends[i]);
		}
	}
	return moreimp;
}


