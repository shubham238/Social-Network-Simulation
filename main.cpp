#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "datastructure.h"
#include "generateFaculty.h"
#include "parser.h"
#include "generateStudent.h"
#include "generateCourses.h"
#include "generatefriends.h"
#include "timekeeper.h"
#include "exporter.h"
#include <pthread.h>
#include <unistd.h>
#include <random>
#include <array>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;
#define MSGSZ     128

bool running = true;

network* graph = new network; //= new network;

pthread_t fac_module;
pthread_t stud_module;
pthread_t course_module;
pthread_t frnd_module;


// typedef struct msgbuf {
// 				 long    mtype;
// 				 char    mtext[MSGSZ];
// 				 } message_buf;

// int msqid;
// int msgflg = IPC_CREAT | 0666;
// key_t key;
// message_buf sbuf;
// size_t buf_length;

vector<string> split(string s1, string s2)
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

// void messagerecieve(){
// 	key = 42;

// 	if((msqid = msgget(key, 0666)) < 0) {
// 		perror("msgget");
// 		exit(1);
// 	}

// 	if (msgrcv(msqid, &sbuf, MSGSZ, 1, 0) < 0) {
// 		perror("msgrcv");
// 		exit(1);
// 	}

// 	char* str;
// 	strcpy(str, sbuf.mtext);
// 	vector<string> spl;
// 	spl = split(str," ");
// 	string sr1 = spl[0];
// 	if(sr1 == "fac_module")
// 		{pthread_create(&fac_module, NULL, generate_faculty, graph);
// 		pthread_join(fac_module, NULL);}
// 	if(sr1 == "stud_module")
// 		{pthread_create(&fac_module, NULL, generate_faculty, graph);
// 		pthread_join(fac_module, NULL);}
// 	if(sr1=="course_module")
// 		{pthread_create(&fac_module, NULL, generate_faculty, graph);
// 		pthread_join(fac_module, NULL);}
// 	if(sr1=="friend_module")
// 		{pthread_create(&fac_module, NULL, generate_faculty, graph);
// 		pthread_join(fac_module, NULL);}
// }

int main()
	{
		cout<<"mainstart"<<endl;
		cout<<"parsingstart"<<endl;
		parser *pars = new parser; // = new parser;
		pars->parse("SocialNetworkEnv.inp",graph);

		const int nrolls=10000;  // number of experiments
  		const int nstars=100;    // maximum number of stars to distribute
  		const int nintervals=10; // number of intervals

		default_random_engine generator;
		exponential_distribution<double> distribution(3.5);

		int p[nintervals]={};

		for (int i=0; i<nrolls; ++i) 
		{
			double number = distribution(generator);
		    if (number<1.0) ++p[int(nintervals*number)];
		}

		cout << "exponential_distribution (3.5):" << std::endl;
		cout << std::fixed; std::cout.precision(1);

		for (int i=0; i<nintervals; ++i) {
		    cout << float(i)/nintervals << "-" << float(i+1)/nintervals << ": ";
		    cout << string(p[i]*nstars/nrolls,'*') <<endl;
		  }

		pthread_mutex_init(&lock, NULL);

		cout<<"pthread start"<<endl;
		pthread_create(&fac_module, NULL, generate_faculty, graph);
		pthread_join(fac_module, NULL);
		pthread_create(&stud_module, NULL, generate_student, graph);
		pthread_join(stud_module, NULL);
		pthread_create(&course_module, NULL, generate_courses, graph);
		pthread_join(course_module, NULL);
		//pthread_create(&frnd_module, NULL, generatefriends, graph);
		//pthread_join(frnd_module, NULL);
		
		//		while(running)
//		{
//			messagerecieve();
//
//		}
		pthread_mutex_destroy(&lock);
		cout<<"exx"<<endl;
		
		exporter *ex = new exporter;
		ex->write(graph);
		cout<<"exiting";
	return 0;
	}

