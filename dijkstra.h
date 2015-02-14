/*
 * dijkstra.h
 *
 *  Created on: Nov 13, 2013
 *      Author: bhargavvar
 */

#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_



//#include "datastructure.h"
//#include "exporter.h"
#include "sherlock.h"

class dijkstra
{
public:
	vector<people*> path(people* p, people* u);
	void dijkstras(people* source, people* destination,simplegraph* smg);

};



#endif /* DIJKSTRA_H_ */
