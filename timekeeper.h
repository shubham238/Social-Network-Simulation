#ifndef _TIMEKEEPER_H_
#define _TIMEKEEPER_H_
#include <iostream>
#include <queue>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include "datastructure.h"
using namespace std;
#define MSGSZ     128

class timer
{
	public:
		int h;
		int m;

	timer(int hr, int min){
		h = hr;
		m = min;
	}
};

class request
{
	public:	

		string thread;
		timer* t;
		bool start;
		bool pause;

		request(string pt, int hr, int min){
		//	th = pt;
			thread  = pt;
			*t = timer(hr, min);
			start = false;
			pause = false;
		}
};

struct compare
 {
   bool operator()( request*& l, request*& r)
   {
       timer *t1 = l->t;
       timer *t2 = r->t;

       return ((t1->h)*60+t1->m) > ((t2->h)*60+t2->m);
   }
 };

 priority_queue<request*,vector<request*>,compare> pq;
 timer* currtime;

vector<string> split(string s1, string s2);

void alarmset(string pth, int h, int m);

void pausetimer(request rq);

void kill();

void wakeup();

void messagereceive();

void messagesend(string str);

void timekeeper(timer* limit);

#endif
