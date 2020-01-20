#include <iostream>
#include <string>			
#include <vector>
#include <fstream>	
#include <sstream>
#include "Header.h"

using namespace std;


struct vecnode      //my_vector struct 
{
	int label;
	int height;
	int xpos;
	char lr;
	vecnode(int l,int h,int i,char k)		//constructor of the vecnode
	{
		label=l;            //building number according to order
		height=h;          //building height
		xpos=i;             // x-coordinate 
		lr=k;                //wall position


	}
	vecnode()			//default constructor of the vecnode
	{
		label=0;
		height=0;
		xpos=0;
		lr='l';

	}

};



int main()
{
	ifstream input1;

	string fname;

	cout <<"Please, Enter File Name:";           
	cin>>fname;
	input1.open(fname.c_str());            //if corrent filename opening the file
	while(!input1.is_open())
	{
		cout<<"Incorrect Filename!!!"<<endl;
		cin>> fname;
		input1.open(fname.c_str());
	}	

	int buildingcount;
	input1 >> buildingcount;              //first input is about how many buildings we have.

	MpQ maxHeap(buildingcount);	           // we define queue and its capacity whose capacity is equal to building number
	vector<vecnode> my_vector(buildingcount*2);      //its my_vector and i create it capacity*2 because i want to check the wall position (left or right)
	int label=0;
	int hayt=0;
	int xleft;  
	int xright;
	int i=0;
	while(i<buildingcount*2)
	{

		label++;
		input1>> xleft >>hayt >>xright;
		char a='l';
		char b='r';
		vecnode vecnodeleft(label,hayt,xleft,a);         //it holds the leftside of the buildings
		vecnode vecnoderight(label,hayt,xright,b);      //it holds the rightside of the buildings
		my_vector[i]=vecnodeleft;                 //i put the leftside of the current building into myvector
		i++;								     // updating the myvector index	
		my_vector[i]=vecnoderight;				//i put the rightside of the current building into my vector
		i++;                                    //updating myvector index
	}

	bool swapp = true;                          //ordering the vector elements according to min x-position to max x-position
	while(swapp){
		swapp = false;
		for (size_t i = 0; i < my_vector.size()-1; i++) {
			if (my_vector[i].xpos >my_vector[i+1].xpos ){
				vecnode temp=my_vector[i];
				my_vector[i] = my_vector[i+1];
				my_vector[i+1] = temp;
				swapp = true;
			}
		}
	}

	cout<<endl;
	int MaxHeight=0;          //maxheight currently equal to zero
	bool check=true;
	for(unsigned int i=0; i<my_vector.size();i++)
	{
		if(i==my_vector.size()-1)
		{
			cout << my_vector[i].xpos << " " <<  0 << endl;
		}

		if(check && my_vector[i].xpos != 0)		// to begining with the 0,0 position
		{ 
			cout << 0 << " " << 0 << endl;
		}
		check=false;
		if( my_vector[i].lr=='l')              //if wall is left put it into queue with building number and height
		{
			maxHeap.insert(my_vector[i].label,my_vector[i].height);
		}
		else if(my_vector[i].lr=='r')         //if wall is right remove its label
		{
			maxHeap.Remove(my_vector[i].label);
			

		}
		if(i<my_vector.size()-1)
		{
		if(my_vector[i].xpos!=my_vector[i+1].xpos)
		{
		if(MaxHeight!=maxHeap.Getmax())      //if my new heaight is not the max height print the x position and the max height
		{
			cout <<my_vector[i].xpos<< " " << maxHeap.Getmax() << endl;
			MaxHeight=maxHeap.Getmax();
		}
		}
		}
	}

	system("pause");	
	return 0;
	}
