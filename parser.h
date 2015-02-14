#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include "datastructure.h"

class parser{
public:
	int univindex;
	int depindex;
	vector<string> split(string s1, string s2);
	void linehandler(string s, network* graph);
	void initialise(vector<string>, network* graph);
	vector<string> txt2input(string s);
	void parse(string s, network* graph);

};



#endif //PARSER_H_


