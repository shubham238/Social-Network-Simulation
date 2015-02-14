/*
 * sherlock.h
 *
 *  Created on: Nov 12, 2013
 *      Author: hooda
 */

#ifndef SHERLOCK_H_
#define SHERLOCK_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include "datastructure.h"


class sherlock
{
	public:

		/**This is the main export function.
		 * It reads the contents of the "filename" file,
		 * and writes it to the graph object given.
		*/
		void holmes(string filename, simplegraph* graph);

		/**
		 * Returns a string array created from given file.
		 * Each string consists of one line of the file.
		 * */
		vector<string> observe(string s);

		/** Processes each line from the string vector
		 * and adds the data to the simplegraph object.
		 * iterates twice over the file, first builds all nodes and then all the edges.
		 */
		void deduce(vector<string>, simplegraph* graph);

		/**Stores the data of the edge contained in the string into the graph. */
		void edgehandler(string s, simplegraph* graph);

		/**Stores the data of a node contained in the graph.*/
		void nodehandler(string s1, string s2, string s3, string s4, simplegraph* graph);

		/**extracts the nodeid from a string of type "<node id=" 3" >" */
		string extract(string s);
};


#endif /* SHERLOCK_H_ */
