/*
 * fw.h
 *
 *  Created on: Nov 17, 2013
 *      Author: hooda
 */

#ifndef FW_H_
#define FW_H_
#include "datastructure.h"


///Implementation of the modified floyd warshall algorithm. Iput a simplegraph object, and returns a pair of int matrices
///the first one is the distance matrix, and the second is the next matrix.
pair<int**, int**> modfw(simplegraph* graph);

///returns an edge connecting ith and jth nodes in the simplegraph, assumes that the two are connected.
edge* edgefind(int i, int j, simplegraph* graph);

///returns the shortest path between two nodes of the graph, uses the matrices from modfw.
vector<edge*> pathfinder(simplegraph* graph, int i, int j, pair<int**, int**> matrices);

/// takes as input the id and university
/// and returns the relevant people object.
people* id2node (int id, string univ, simplegraph* graph);
#endif /* FW_H_ */
