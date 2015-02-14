/*
 * generatefriends.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: cs1120254
 */




/*
 * generateFriends.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: bhargavvar
 */
#include <array>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "string.h"
#include "datastructure.h"
using namespace std;

bool friendship(student* a,student* b )
{
	bool p=false;
	int pkaf=a->sfriends.size();
	string pl=b->name;
	string pla=a->name;
	for(int i=0;i<a->sfriends.size();i++)
	{
		if(b->name==(a->sfriends[i])->name)
		{
			p=true;
		}

	}
	return p;
}



void *generatefriends(void *graph){


	network *net = (network *) graph;

	srand(net->RANDOMSEED[2]);
	int no_1people=0;
	bool stud=false;
	float out_prob=0;

    int pk1u=net->universitylist.size();
	for(int i=0; i<net->universitylist.size(); i++)
	{

		university *univ = net->universitylist[i];
		//univ = new university;
		no_1people+=univ->students.size();
	//	no_people+=univ->facultylist.size();
	}
	int first=(rand())%(no_1people);
//	no_people=0;
	student *stud1;
	student *stud2;
//	faculty* fac2=NULL;
//	faculty* fac1=NULL;

    int pkfu=net->universitylist.size();
	for(int i=0; i<net->universitylist.size(); i++)
    {
		university *univ = net->universitylist[i];
		int no_2ppl=0;
		int jlp=net->universitylist.size();
		for(int jl=0;jl<net->universitylist.size();jl++)
		{
	        no_2ppl+=net->universitylist[jl]->students.size();

			if(no_2ppl>first)
			{
				no_2ppl-=univ->students.size();
				stud1=net->universitylist[jl]->students[first-no_2ppl];
			}

		}



			stud=true;
			out_prob=univ->OPENNESS;
			float out=(rand()%100)/100.0;
			if(out_prob<out){
				if(0==rand()%4){
					department* depart=stud1->st_department;
					int f2d;
					for(int fd=0;fd<depart->students.size();fd++)
					{

						int f2d=rand()%(depart->students.size());

						if(depart->students[f2d]->name==stud1->name || friendship(stud1,depart->students[f2d]))
						{
							f2d=(f2d+5)%depart->students.size();
						}
						else
						{
							break;

						}



						}
					stud2=depart->students[f2d];
					(stud1->sfriends).push_back(stud2);
					(stud2->sfriends).push_back(stud1);
					cout<<"rand1";

					}


				else if(1==rand()%4){
					hostel* host=stud1->st_hostel;
					int f2h;
					for(int fh=0;fh<host->students.size();fh++){

						f2h=rand()%host->students.size();
						while(host->students[f2h]->name==stud1->name || friendship(stud1,host->students[f2h])){
							f2h=(f2h+5)%host->students.size();
							stud2=host->students[f2h];
						}
						}
					(stud1->sfriends).push_back(stud2);
					(stud2->sfriends).push_back(stud1);
					cout<<"rand2";




					}
				else if(2==rand()%4){
					vector<courses*> courses=stud1->st_courses;
					int fpc=0;
					for(int fc=0;fc<courses.size();fc++){
                        fpc+=courses[fc]->students.size();
                        fpc+=1;

					}
					fpc=rand()%fpc;
					int fpsc=0;
					for(int fc=0;fc<courses.size();fc++){
						fpsc+=courses[fc]->students.size();
						if(fpsc>fpc){
							fpsc-=courses[fc]->students.size();
							stud2=courses[fc]->students[fpc-fpsc];
							while(stud1->name==stud2->name || friendship(stud1,stud2)){
								fpc=fpsc+(fpc-fpsc+5)%courses[fc]->students.size();
								stud2=courses[fc]->students[fpc-fpsc];
							}
							break;
						}

					}
					(stud1->sfriends).push_back(stud2);
					(stud2->sfriends).push_back(stud1);
					cout<<"rand3";


				}
				else if(3==rand()%4){
					vector<interest*> interests=stud1->st_interest;
					int fpi=0;
					for(int fi=0;fi<interests.size();fi++){
                        fpi+=interests[fi]->students.size();
                        fpi+=1;

					}
					fpi=rand()%fpi;
					int fpsi=0;
					for(int fi=0;fi<interests.size();fi++){
						fpsi+=interests[fi]->students.size();
						if(fpsi>fpi){
							fpsi-=interests[fi]->students.size();
							stud2=interests[fi]->students[fpi-fpsi];
							while(stud1->name==stud2->name || friendship(stud1,stud2)){
								fpi=fpsi+(fpi-fpsi+5)%interests[fi]->students.size();
								stud2=interests[fi]->students[fpi-fpsi];
							}
							break;
						}


						}
					(stud1->sfriends).push_back(stud2);
					(stud2->sfriends).push_back(stud1);
					cout<<"rand4";

					}







			}

			else{
				int sp2=rand()%(univ->students.size());

					stud2=univ->students[sp2];
                   cout<<"names   "<<univ->students[12]->name<<stud1->name<<endl;
					while(true){

						if((stud2->st_department)->name==(stud1->st_department)->name  ||(stud2->st_hostel)->name==(stud1->st_hostel)->name ||friendship(stud1,stud2)){
						sp2=(sp2+5)%univ->students.size();
						stud2=univ->students[sp2];

						}
						else{
							bool feas=false;

							for(int g=0;g<stud1->st_courses.size();g++){
								for(int g2=0;g2<stud2->st_courses.size();g2++){
									if(stud1->st_courses[g]->name==stud2->st_courses[g2]->name){
										bool feas=true;
                                        break;
									}

								}
								if(feas){

									break;}
							}
							int  pkcs=stud1->st_courses.size();
							 int pkcs2=stud2->st_courses.size();
							for(int g=0;g<stud1->st_interest.size();g++){
								for(int g2=0;g2<stud2->st_interest.size();g2++){
									if(stud1->st_interest[g]->name==stud2->st_interest[g2]->name){
										bool feas=true;
										break;
									}

								}
								if(feas){

									break;}
							}
							if(feas){
								sp2=(sp2+5)%univ->students.size();
								stud2=univ->students[sp2];

							}
							else{break;}
						}


					}
					(stud1->sfriends).push_back(stud2);
					(stud2->sfriends).push_back(stud1);
				}





			}

	return NULL;
}



















