#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "string.h"
#include <sstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "datastructure.h"
#include "generateStudent.h"
//#include "generator.cpp"
using namespace std;
#define MSGSZ     128

string gen_name1(){
	
	int length = rand()%6+3; //random strings of size 3 to 8
	string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string ret = "";
	for(int i=0; i<length; i++)
	{
		ret += str[rand() % str.length()];
	}
	return ret;
}

void *generate_student(void* graph){
	
	cout<<"chill"<<endl;
	pthread_mutex_lock(&lock);
	int entrynum = 1000;
	cout<<entrynum<<endl;
	cout<<"graph before"<<endl;
	network *net = (network *)graph;
	cout<<"graph after"<<endl;
	srand(net->RANDOMSEED[1]);
	int pkl=net->universitylist.size();
	cout<<"universitylist size"<<pkl<<endl;
	for(int i=0; i<net->universitylist.size(); i++)
	{
		university *univ;
		univ=net->universitylist[i];
		cout<<univ->name;
		//univ = new university;
		cout<<univ->name<<endl;
		pkl=univ->departments.size();
		for(int j=0; j<univ->departments.size(); j++)
			{
				department *dept = univ->departments[j];
				cout<<dept->name<<endl;
				pkl=dept->student_no;
				cout<<pkl<<endl;
				for(int k=0; k<dept->student_no;k++)
				{
					student *stud = new student;
					stud->entryno = entrynum;
					cout<<stud->entryno<<endl;


					string str;
					while(true)
					{
					stringstream ss;
					ss << entrynum;
					str = ss.str();
					break;
					}

					entrynum++;
					string str2 = univ->name; //"IITD_";
					string str1 = str2.append("_");
					stud->name = str1.append(str);
					cout<<stud->name<<endl;
					stud->st_department = dept;//allocating department to student
					stud->st_university = univ;
					(dept->students).push_back(stud);//adding student to department
					(univ->students).push_back(stud);
					//cout<<stud->st_department->name<<endl;
					hostel *hl = univ->hostels[rand()%univ->houselocalitylist.size()]; 
					stud->st_hostel = hl;//allocating hostel to student
					(hl->students).push_back(stud);//adding student to hostel list
					//cout<<stud->st_hostel->name<<endl;
                    pkl=dept->interests.size();
					for(int s=0; s<dept->interests.size(); s++)
					{
						interest* inr = dept->interests[s];
						vector<interest*> intr=net->interests;
						interest* intrs;
						for(int in=0;in<intr.size();in++)
						{
							if((inr->name==intr[in]->name))
							{
								intrs=intr[in];
								break;
							}
						}
						int n = rand()%100;
						if(n<(int)(100*dept->poplist[inr->name]))
							{
							(stud->st_interest).push_back(intrs);//allocating student a interest
							(inr->students).push_back(stud);//adding student to interestlist
							(intrs->students).push_back(stud);
							//cout<<inr->name<<endl;
							}

					}
				}

			}
	}

	/*message passing */
		/******************************************************/

		/*
		 * Declare the message structure.
		 */

		typedef struct msgbuf {
				 long    mtype;
				 char    mtext[MSGSZ];
				 } message_buf;

		int msqid;
		int msgflg = IPC_CREAT | 0666;
		key_t key;
		message_buf sbuf;
		size_t buf_length;

		/*
		 * Get the message queue id for the
		 * "name" 1234, which was created by
		 * the server.
		 */
		key = 345;

		(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,\
		%#o)\n",
		key, msgflg);

		if ((msqid = msgget(key, msgflg )) < 0) {
				perror("msgget");
				exit(1);
			}
		else
			 cout<<"msgget: msgget succeeded: msqid ="<< msqid<<endl;

			/*
			 * We'll send message type 1
			 */

		sbuf.mtype = 1;

		(void) strcpy(sbuf.mtext, "stud_module year");

		buf_length = strlen(sbuf.mtext) + 1 ;

		/*
		 * Send a message.
		 */
		if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
		   printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
		   perror("msgsnd");
		   exit(1);
		}

	   else
		  printf("Message: \"%s\" Sent\n", sbuf.mtext);

		//exit(0);

	pthread_mutex_unlock(&lock);
	return NULL;


}




