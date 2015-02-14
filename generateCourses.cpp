/*
 * generateCourses.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: bhargavvar
 */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "string.h"
#include "datastructure.h"
#include "parser.h"
//#include "generator.cpp"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define MSGSZ  128
void *generate_courses(void *graph){

	pthread_mutex_lock(&lock);
	network *net = (network *) graph;
    int pkiu=net->universitylist.size();
	for(int i=0; i<net->universitylist.size(); i++)
	{

	//	cout<<"\n \n \nCOURSE START"<<endl;
		university *univ = net->universitylist[i];
		//univ = new university;
	//	cout<<univ->name<<endl;
		int pkid=univ->departments.size();
		for(int j=0; j<univ->departments.size(); j++)
			{

				department *dept = univ->departments[j];
				//cout<<dept->name<<endl;
				//cout<<"run";
				srand(net->RANDOMSEED[2]);
				int pkl=dept->courselist.size();
				for(int k=0;k<dept->courselist.size();k++)

				{


					float p=200.0/(dept->courselist[k]->frequency_per_year);
					//cout<<p<<endl;
					cout<<"fs "<<dept->facultylist.size()<<endl;
					int pp=rand()%dept->facultylist.size();
					int pi=((rand()))%(int)p;
					//cout<<"print"<<endl;
					//cout<<pi<<endl;

					if(pi<100)
					{
						//course k floated
						(dept->floatedcourses).push_back(dept->courselist[k]);
                        //cout<<"puff\n";
						dept->courselist[k]->prof=dept->facultylist[pp];
						((dept->facultylist[pp])->fac_course)=dept->courselist[k];
						//cout<<"print"<<endl;
						//cout<<dept->courselist[k]->name<<dept->facultylist[pp]->name<<endl;;


					}
				}


			}
	}

		for(int i=0; i<net->universitylist.size(); i++)
			{

			//	cout<<"\n \n \nCOURSE START"<<endl;
				university *univ = net->universitylist[i];

				//univ = new university;
        int pkd=univ->departments.size();
		for(int j=0; j<univ->departments.size(); j++)
					{

						department *dept = univ->departments[j];
						srand(net->RANDOMSEED[2]);
						int depcourses=dept->dep_courses;
						int nondepcourses=dept->nondep_courses;
					/*	for(int yp=0;yp<univ->departments.size();yp++)
						{
							cout<<" dep  "<<univ->departments[yp]->name<<endl;
							for(int yl=0;yl<univ->departments[yp]->floatedcourses.size();yl++)
							{
								cout<<univ->departments[yp]->floatedcourses[yl]->name<<endl;
							}
						}
*/
                        int pks=dept->students.size();
                        srand(net->RANDOMSEED[2]);
						for(int k=0;k<dept->students.size();k++)
						{
						//	cout<<"diff stud"<<k<<endl;
                          //  cout<<"student is"<<dept->students[k]->name<<k+1<<endl;
							int dc=0;;



                        int pkl=dept->dep_courses;
						for(int l=0;l<dept->dep_courses;l++)
						{

							//<<dept->dep_courses<<endl;
							//cout<<dept->dep_courses-l<<"pur  "<<endl;
							if((dept->dep_courses-l)>=1.0)
							{
								//cout<<"chill hai!"<<endl;
								if(dept->students[k]->st_courses.size()==0)
								{
									(dept->students[k]->st_courses).push_back(dept->floatedcourses[dc]);
									(dept->floatedcourses[dc]->students).push_back(dept->students[k]);

								}
								else
								{
                                for(int cc=0;cc<dept->students[k]->st_courses.size();cc++)
                                {
                                		dc=(dc+(rand()))%(dept->floatedcourses.size());
                                		if(dept->students[k]->st_courses[cc]->name==dept->floatedcourses[dc]->name)
                                		{
                                			dc=(dc+(rand())%(dept->floatedcourses.size()));
                                		}
                                		else
                                		{

                                			    	(dept->students[k]->st_courses).push_back(dept->floatedcourses[dc]);
                                					(dept->floatedcourses[dc]->students).push_back(dept->students[k]);

                                                    break;

                                		}

                                }
								}


							}

						/*if(dept->dep_courses-l>=(rand()%100)/100.0){
							dc=((rand())%pc.size());
							courses cour=pc[dc];
							pc.erase(pc.begin()+dc);
							(dept->students[k]->st_courses).push_back(&cour);
							cout <<"course name"<<cour.name;
							for(int m=0;m<dept->floatedcourses.size();m++){
							if(cour.name==(dept->floatedcourses[m])->name){
								(dept->floatedcourses[m]->students).push_back(dept->students[k]);
								cout<<"float value  float  "<< l<<"  student names"<<dept->students[k]->name;
								break;

						}
					}

					}
					}*/
						//cout<<"print"<<endl;
					}

					//cout<<"comeon";
					int dc1=0;int dc2;
					vector<courses> pc1;
					//cout<<"printed"<<univ->departments.size();
					for(int m=0;m<univ->departments.size();m++)
					{
						if(m==j)
						{
							continue;
						}
						else
						{
							dc1+=(univ->departments[m]->floatedcourses).size();
						}
					}




					for(int l=0;l<dept->nondep_courses;l++)
					{
						dc2=((rand())%dc1);
						if(dc2==dc1)
						{
							dc2=((rand())%dc1);
						}
						if(dept->nondep_courses-l>=1 || dept->nondep_courses-l>=(rand()%100)/100.0){
						for(int m=0;m<univ->departments.size();m++)
						{
							int cc1=0;
							if(m==j)
							{
								continue;
							}

							else
							{
								int pkcd=(univ->departments[m]->floatedcourses).size();
								cc1+=(univ->departments[m]->floatedcourses).size();
								if(cc1>dc2)
								{
									cc1-=(univ->departments[m]->floatedcourses).size();
									int dc7=dc2-cc1;
									(dept->students[k]->st_courses).push_back(univ->departments[m]->floatedcourses[dc7]);
									univ->departments[m]->floatedcourses[dc7]->students.push_back(dept->students[k]);
									break;
								}
							}
						}



					}
					}

					int csum=0;

					for(int m=0;m<univ->departments.size();m++)
					{
						if(m==j)
						{
							continue;
						}
						else
						{
							csum+=(univ->departments[m]->courselist).size();



						}

					}


					/*	for(int yp=0;yp<dept->students[k]->st_courses.size();yp++)
						{
cout<<"courses"<<dept->students[k]->st_courses[yp]->name<<endl;

						}
						cout<<k<<"  "<<j<<  "  "<<i<<endl;*/

						}


			}

		{

		}
		for(int yp=0;yp<univ->students.size();yp++)
				{
			cout<<"student"<<yp<<"  "<<univ->students[yp]->st_courses.size()<<endl;
			for(int yl=0;yl<univ->students[yp]->st_courses.size();yl++)
			{
		cout<<"courses"<<univ->students[yp]->st_courses[yl]->name<<endl;

				}
				}
				cout<<i<<"  "<<  "  "<<endl;

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

		(void) strcpy(sbuf.mtext, "course_module year");

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




