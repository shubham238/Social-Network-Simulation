#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "string.h"
#include "datastructure.h"
#include "generateFaculty.h"
//#include "generator.cpp"
using namespace std;
#define MSGSZ     128

string gen_name(){
	
	int length = rand()%6+3; //random strings of size 3 to 8
	string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string ret = "";
	for(int i=0; i<length; i++)
	{
		ret += str[rand() % str.length()];
	}
	return ret;
}


void *generate_faculty(void *graph){
	
	int employeecode = 1;
	pthread_mutex_lock(&lock);
	network *net = (network *)graph;
	srand(net->RANDOMSEED[0]);
	int pku=net->universitylist.size();
	for(int i=0; i<net->universitylist.size(); i++)
	{

		university *univ = net->universitylist[i];
		//univ = new university;
		cout<<"faculty"<<endl;
		cout<<univ->name<<endl;
         int pkd=univ->departments.size();
		for(int j=0; j<univ->departments.size(); j++)
			{

				department *dept = univ->departments[j];
				cout<<dept->name<<endl;
                int pkf=dept->faculty_no;
				for(int k=0; k<dept->faculty_no;k++)
				{

					faculty *prf = new faculty;
					prf->univty=univ;
					//cout<<prf->univty->name<<endl;
					prf->emp_code = employeecode;
					string str;
					while(true)
					{
					stringstream ss;
					ss << employeecode;
					str = ss.str();
					break;
					}

					//cout<<prf->emp_code<<endl;
					employeecode++;
					string str2 = univ->name; //"IITD_";
					string str1 = str2.append("fac");
					prf->name = str1.append(str);
					cout<<prf->name<<endl;
					prf->fac_department = dept;//allocating department to prof
					(dept->facultylist).push_back(prf);//adding prof to department
					(univ->facultylist).push_back(prf);
					//cout<<prf->fac_department->name<<endl;
					houselocality *hl = univ->houselocalitylist[rand()%univ->houselocalitylist.size()]; 
					prf->fac_houselocality = hl;//allocating house to prof
					(hl->facultylist).push_back(prf);//adding prof to houselocality list
					//cout<<prf->fac_houselocality->name<<endl;
					//cout<<"interests"<<endl;
					int pki=dept->interests.size();
					for(int s=0; s<dept->interests.size(); s++)
					{
						interest* inr = dept->interests[s];
						vector<interest*> intr=net->interests;
						int n = rand()%100;
						interest* intrs;
						for(int in=0;in<intr.size();in++)
						{
							if((inr->name==intr[in]->name))
						    {
								intrs=intr[in];
								break;
							}
						}
						if(n<(int)(100*dept->poplist[inr->name]))
							{(prf->fac_interest).push_back(intrs);//allocating prof a interest
							(inr->facultylist).push_back(prf);//adding prof to interestlist
							(intrs->facultylist).push_back(prf);
							//cout<<inr->name<<endl;;
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

	(void) strcpy(sbuf.mtext, "fac_module year");

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





