/*
 * datastructure.h
 *
 *  Created on: 12 Oct 2013
 *
 */

#ifndef DATASTRUCTURE_H_
#define DATASTRUCTURE_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <pthread.h>
#include <unistd.h>
using namespace std;

static pthread_mutex_t lock;

//all the classes
class network;
class courses;
class hostel;
class interest;
class students;
class faculty;
class houselocality;
class student;
class university;

//Classes for Part 2

/** The node class for the graph.*/
class people
{
	public:
		///name of person		
		string name;
		///name of university
		string university;
		///This is the entryno/employee code.		
		int id;		
		///temporary  shortest distance from source in graph
		int dkdist;    
		///included in the shortest path between two people or not 		
		bool dkvisited; 
		/// importance is the number of shortest paths on which the node exists
		int importance;//=0;
		///node id is the index of this node in nodelist.
		int nodeid;
		///list of friendships
		vector<people*> friends;
		people()
		{
			importance = 0;
		}
};

/** Each edge represents a friendship.*/
class edge
{
	public:
		/// 1st friend in the friendship edge 
		people* friend1;
		/// 2nd friend in the undirected friendhip edge 
		people* friend2;
};

/** The format for storing data from a graphml file. */
class simplegraph
{
	public:
		string name;
		/// The list of friendships(edges).
		vector<edge*> friendlist; 
		/// The list of people(nodes). 
		vector<people*> nodelist; 
		/// This flag is true if the importance of the nodes has been evaluated.
		bool flag;
		/// This is true if the Floyd-Warshall algo has been run on the graph. 		  
		bool fw;		  
		 /// This pair of matrices is the output from the floyd-warshall algorithm.
		pair<int**,int**> mats;	 
		/// Graph initiation bools 
		simplegraph()             
		{
			flag = false;
			fw = false;
		}
};

class network
{
	public:
		/// list of universities in the network
		vector<university*> universitylist;
		///randomseeds used in the network
		vector<int> RANDOMSEED;           
		 ///list of interests in the network 
		vector<interest*> interests;     
		///constructor 
		network()                          
		{               

		}
};

class department
{	
	public:
		 ///department name
		string name;
		///number of faculty
		int faculty_no; 
		///number of student
		int student_no; 
		///floateds department courses
		float dep_courses; 
		//floated non-department courses
		float nondep_courses; 
		///list of students 
		vector<student*> students; 
		///list of faculty
		vector<faculty*> facultylist;
		///list of courses 
		vector<courses*> courselist; 
		///list of floated courses
		vector<courses*> floatedcourses;
		///list of interests 
		vector<interest*> interests; 
		map<string,float> poplist;
};

class courses
{	
	public:
		///name of course
		string name; 
		///list of students enrolled in this course
		vector<student*> students; 
		///department which floated the course
		department* dep;
		///professor teaching the course 
		faculty* prof; 
		///no of times which is floates
		float frequency_per_year;
};
 
class hostel
{	public:
	///hostel name
	string name; 
	///list of students in the hostel
	vector<student*> students; 
};

class interest
{
	public:
		///interest's name
		string name; 
		///list of students having same interest
		vector<student*> students; 
		///list of faculty having same interest
		vector<faculty*> facultylist; 
		
};

class faculty
{
	public:
		///employee code
		int emp_code;
		///name of faculty 
		string name; 
		///name of university
		university* univty; 
		///name of department
	department* fac_department; 
	///name of course taken by faculty
	courses* fac_course; 
	///houselocality of prof
	houselocality* fac_houselocality;
	///list of interests of prof 
	vector<interest*> fac_interest; 
};

class houselocality
{	public:
		///address of house
		string name; 
		///list of profs living the houselocality
		vector<faculty*> facultylist; 
};

class student
{
	public:
		///entryno
		int entryno; 
		///name of student
		string name; 
		///department of student
	department* st_department; 
	///courses taken by student
	vector<courses*> st_courses; 
	///university of student
	university* st_university; 
	///hostel in which student lives
	hostel* st_hostel; 
	///interests of student
	vector<interest*> st_interest; 
	///friendlist of students
	vector<student*>  sfriends; 
};

class university
{
	public:
		///name of university
		string name; 
		///list of departments
	vector<department*> departments; 
	///list of courses
	vector<courses*> courselist; 
	///list of hostels
	vector<hostel*> hostels; 
	///list of students
	vector<student*> students; 
	///list of faculty
	vector<faculty*> facultylist; 
	///list of houselocalities.
	vector<houselocality*> houselocalitylist; 
	int FRIENDSHIPRATE;
	float OPENNESS;
	float FRIENDLINESS;
};

#endif //DATASTRUCTURE_H_
