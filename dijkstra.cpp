#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include "datastructure.h"
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include "dijkstra.h"
//#include "datastructure.h"
//#include "exporter.h"
//#include "sherlock.h"
using namespace std;

vector<people*> dijkstra::path(people* p, people* u)
{
	vector<people*> traverse;
	people* l = p++;
	while(!(l->name == u->name))
	{
		l = p;
		traverse.push_back(p++);
	}

	return traverse;

	//by using the vector traverse, we can print the people between shortest path and also the length of shortest path.
}

void dijkstra::dijkstras(people* source, people* destination,simplegraph* smg)
{
	//vector<path*> paths;
	simplegraph* net = smg;
	people* dest = destination; //destination
	people* u = source; //source

	for(int i=0; i<net->nodelist.size(); i++)
	{
		people* person = net->nodelist[i];
		person->dkdist = 99999;
		person->dkvisited = false;
		//person->previous = NULL;
	}
	
	queue<people*> q;
	u->dkdist = 0;
	q.push(u);
	
	while(!q.empty())
	{
		people* v = q.front();
		q.pop();
		if(v->name == dest->name)
			{
				path(v, u);
			}
		for(int j=0; j<v->friends.size(); j++)
		{
			people* w = v->friends[j];
			if(w->dkdist = 99999)
			{
				w->dkdist = v->dkdist+1;
				people* wb=w--;
				wb= v;
				//w.path = v;
				q.push(w);
			}
		}
	}	
}
