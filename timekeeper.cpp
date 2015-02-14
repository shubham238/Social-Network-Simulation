#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <queue>
#include <vector>
#include <string.h>
#include <mqueue.h>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include "timekeeper.h"

using namespace std;
#define MSGSZ     128

// class timer
// {
// 	public:
// 		int h;
// 		int m;

// 	timer(int hr, int min){
// 		h = hr;
// 		m = min;
// 	}
// };

// typedef struct msgbuff {
//      long    mtype;
//      char    mtext[MSGSZ];
//   	 } message_buf;


// struct request
// {
// 	string thread;
// 	timer* t;
// 	bool start;
// 	bool pause;
// 	request(string pt, int hr, int min){
// 		*t = timer(hr, min);
// 		start = false;
// 		pause = false;
// 	}
// };

// struct compare
//  {
//    bool operator()( request*& l, request*& r)
//    {
//        timer *t1 = l->t;
//        timer *t2 = r->t;

//        return ((t1->h)*60+t1->m) > ((t2->h)*60+t2->m);
//    }
//  };

//  priority_queue<request,vector<request>,compare> pq;
//  timer* currtime;

 bool run;
 //timer* simtime;
 
 int msqid;
 key_t key;
 message_buf  rbuf;

 vector<string> splitt(string s1, string s2)
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

 void alarmset(string pth, int h, int m)
 {
 	timer *t;
 	*t  = timer(h, m);
 	if(((t->h)*60+t->m) < ((currtime->h)*60+currtime->m))
		cout<<"request invalid"<<endl;
	else
		{
			request *r = new request(pth, h, m);
			pq.push(r);
		}
 }
 
 void pausetimer(request* rq)
 {
 	currtime = rq->t;
 }

 void kill(){
 	exit(0);
 }

void wakeup(){
	request *rt = pq.top();
	string id = rt->thread;
	pausetimer(rt);
	messagesend(id);
}
/*message recieving */
 /************************************************************************/
 /*
 * Declare the message structure.
 */
void messagereceive(){
	if((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }
    /*
     * Receive an answer of message type 1.
     */
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    /*
     * Print the answer.
     */
    //printf("%s\n", rbuf.mtext);
    //char* str;
    //strcpy(str, rbuf.mtext);
    string str;
    str = rbuf.mtext;

    vector<string> spl;
    spl = splitt(str," ");
    string sr1 = spl[0];
    string sr2 = spl[1];
    int h, m;
    if(sr2=="year")
    	{h = (365*24);
    	 m=0;}
    if(sr2=="sem")
    	{h = (365*12);
    	 m=0;}
    if(sr2=="min")
    	{h=0;
    	 m=1;}
    alarmset(sr1, h, m);

    //exit(0);
}

void messagesend(string str)
{
		typedef struct msgbuf {
			long mtype;
			char mtext[MSGSZ];
		} msg_buf;


		int msqid;
		int msgflg = IPC_CREAT | 0666;
		key_t key;
		msg_buf sbuf;
		size_t buf_length;

		/*
		 * Get the message queue id for the
		 * "name" 1234, which was created by
		 * the server.
		 */
		key = 42;

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

		//char* cf= "fac_module";
		 if(str=="fac_module")
		 	//(void) 
		 	strcpy (sbuf.mtext,"fac_module");
		// else if(str=="stud_module")
		// 	sbuf.strg = 
		// 	//(void) strcpy(sbuf.mtext, "stud_module");
		// else if(str=="course_module")
		// 	(void) strcpy(sbuf.mtext, "course_module");
		// else
		// 	(void) strcpy(sbuf.mtext, "friend_module");

		//sbuf.mtext = str;
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
}

void timekeeper(timer* limit){
	int l = ((limit->h)*60+limit->m);
	int ct=0;
	while(l>ct)
	{
		wakeup();
		ct = ((currtime->h)*60+currtime->m);
	}
	kill();
}

//int main(){
//	return 0;
//}
