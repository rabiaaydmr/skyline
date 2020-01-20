#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Structure//building struct for the heap
{
	int val;			// height 
	int lab;            //building number
	Structure (int v=0, int l=0)		
		: val(v), lab(l)			
	{}
};

class MpQ 
{
public:
	MpQ(int capacity); 
	~MpQ(); 
	int Getmax();
	bool isEmpty();
	void percolatedown( int hole); 
	int Remove(int & lab);
	void insert(int& lab,int& val);
private:
	Structure *heap; 
	int size; //currentsize of heap class
	int *currentindex; //index array

};

MpQ::MpQ(int capacity) 
{
	heap = new  Structure[capacity]; //we create heap
	currentindex= new int[capacity]; //we create index array
	size=0;
}

MpQ::~MpQ()
{
	

}

void MpQ::insert(  int&label,int&value ) //insertþng building to the maxheap
{
	// Percolate up
	// Note that instead of swapping we move the hole up
	int hole = ++size;
	for( ; hole > 1 && value > heap[ hole / 2 ].val; hole /= 2 )
	{
		heap[ hole ]= heap[ hole / 2 ];
		currentindex[heap[ hole ].lab]=hole; //putting the correct number to the index array

	}
	heap[ hole ].lab = label;
	heap[ hole ].val= value;
	currentindex[heap[ hole ].lab]=hole; //putting the correct number to the index array
}

int MpQ :: Getmax()
{
	return heap[1].val;
 
}


bool MpQ :: isEmpty()
{
	if(heap[1].val==0)
	return true; // if the first element is zero than the heap is empty
	else 
	return false;
}


int  MpQ :: Remove(int & label)
{
		if(currentindex[label]==size) //if the currentindex equal to currentsize we delete it
	{
		heap[currentindex[label]].lab=0;
		heap[currentindex[label]].val=0;
		currentindex[label]=0;
		size--;						 //updating currentsize because of deletion 
		return 0;
	}

	heap[currentindex[label]].val = heap[size].val;
	heap[currentindex[label]].lab = heap[size].lab;
	size -= 1;
	percolatedown(currentindex[label]);
	return currentindex[label];

}




void MpQ::percolatedown( int hole )
{
	int child;
	Structure tmp = heap[ hole ]; // we create the structure temp which will percolatedown

	for( ; hole * 2 <= size; hole = child )
	{
		child = hole * 2;
		if( child != size && heap[ child + 1 ].val < heap[ child ].val)
			child++;  
		if( heap[ child ].val < tmp.val )
		{
			heap[ hole ] = heap[ child ]; // swapping which one is percolated and child node
			currentindex[heap[hole].lab]=hole;
		}
		else
			break;
	}
	heap[ hole ] = tmp; 
	currentindex[heap[hole].lab]=hole;
}

