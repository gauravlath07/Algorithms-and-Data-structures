#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H



#include "ece250.h"
#include "Exception.h"
#include <iostream>

using namespace std;


class Dynamic_deque_as_array
{
	public:
		Dynamic_deque_as_array( int = 10 );
		~Dynamic_deque_as_array();

		int* array;
		int head_index;
		int tail_index;
		int count;
		int array_size;

		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void enqueue_head( const int & );
		void enqueue_tail( const int & );
		int dequeue_head();
		int dequeue_tail();
		void clear();

		int wrap(int index);
		void print_queue();
};		


Dynamic_deque_as_array::Dynamic_deque_as_array( int n) {
	if(n<1)
	{
		//handles the error case. Sets size to 1 if n=0 or less than 1
		array = new int [1];

		array_size = 1;
		head_index = 0;
		tail_index = 0;
		count = 0;

	}
	else
	{
		array = new int [n];

		array_size = n;
		head_index = 0;
		tail_index = 0;
		count=0;
	}
}




Dynamic_deque_as_array::~Dynamic_deque_as_array() {
	//deallocates space after program finishes
	delete[] array;
}





int Dynamic_deque_as_array::size() const {
	//Returns the number of contents in the array currently
	return count;
	
}


int Dynamic_deque_as_array::capacity() const {
	//returns the capacity of elements the array can hold
	return array_size;
	
}


bool Dynamic_deque_as_array::empty() const {
	//tells if the array is empty or not
	if(count == 0)
		return true;
	else
		return false;
}


int Dynamic_deque_as_array::head() const {
	//gives the element on the head currently
	return array[head_index];
}


int Dynamic_deque_as_array::tail() const {
	//gives the element on the tail currently
	return array[tail_index];
}



void Dynamic_deque_as_array::enqueue_head( const int &obj ) {
	/*
	-- Very complicated approach used
	-- Head and tail starts from 0 index. Both the index point to the filled spot
	-- Enqueue head moves leftwards and enqueue tail moves rightwards.
	-- 
	*/

	if(count == 0)
	{
		array[head_index] = obj;
		count++;

	}
	else if(head_index == 0 && count < array_size && count != 0)
	{
		head_index = wrap(0);
		array[head_index] = obj;
		count++;
		
	}
	else if(head_index != 0 && count < array_size)
	{
		head_index--;
		array[head_index] = obj;
		count++;

	}
	// When the array is full, a temp array is created. The all the elements are copied
	// to it in the perfect straight order. Then all the contents are transferred back
	// to a new array of double the size.
	else if(count == array_size)
	{
		int* tempArray = new int[array_size+1];
		count++;
		
		tempArray[0]=obj;
		int check;
		for(int i=1; i < count; i++)
		{
			check++;
			tempArray[i]=dequeue_head();
			count++; 
			//to counter the decrement caused by dequeue head
		}
		
		

		delete[] array;

		array_size = array_size*2;
		array = new int [array_size];
		for(int j=0; j<=count;j++)
		{
			array[j]=tempArray[j];
		}

	
		head_index=0;
		tail_index=count-1;
		
		delete[] tempArray;

	}


	return;
}

int Dynamic_deque_as_array::wrap(int index)
{
	// This is a simple helper method which is called when the tail or head 
	// reaches the end. In that case it wraps around so that the order is maintatined.
	if (index==0)
	{
		return array_size-1;
	}
	else if (index == array_size-1)
	{
		return 0;
	}
	//return index;
}


void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {
	
	if(tail_index == 0 && count == 0)
	{
		array[tail_index] = obj;
		count++;

	}
	else if(tail_index == (array_size-1) && count < array_size)
	{
		
		tail_index = wrap(array_size-1);
		array[tail_index]=obj;
		
		count++;

	}
	else if(tail_index != (array_size-1) && count < array_size)
	{
		tail_index++;
		array[tail_index] = obj;
		count++;

	}
	// When the array is full, a temp array is created. The all the elements are copied
	// to it in the perfect straight order. Then all the contents are transferred back
	// to a new array of double the size.
	else if(count == array_size)
	{
		int* tempArray = new int[array_size+1];

		
		for(int i=0; i<count; i++)
		{
			tempArray[i]=dequeue_head();
			count++; //to counter the deque commands
		}
		
		

		tempArray[array_size]=obj;
		count++;

		
		delete[] array;

		array_size = array_size*2;
		array = new int [array_size];
		
		for(int j=0; j<=count;j++)
		{
			array[j]=tempArray[j];
		}

		delete[] tempArray;

		head_index=0;
		
		tail_index=count-1;
		
	}

	return;
}


int Dynamic_deque_as_array::dequeue_head() {
	int value;
	// A temporary variable value receives the value at the head in O(1)
	// and then it is returned at the end of the method.

	if(count == 0)
	{
		throw underflow();
	}
	else if(head_index != (array_size-1) && count != 0)
	{
		value = array[head_index];
		array[head_index]=NULL;
		
		head_index++;
		
		count--;

		if(count == 0)
		{
			tail_index = 0;
			head_index =0;
		}
		

	}
	else if(head_index == (array_size-1) && count != 0)
	{
		
		value = array[head_index];
		array[head_index]=NULL;

		head_index=wrap(array_size-1);

		count--;

		if(count == 0)
		{
			tail_index = 0;
			head_index = 0;
		}
		

	}

	return value;
	
}

int Dynamic_deque_as_array::dequeue_tail() {
	// A temporary variable value receives the value at the head in O(1)
	// and then it is returned at the end of the method.
	
	int value = 0;

	if(count == 0)
	{
		throw underflow();
	}
	else if(tail_index == 0 && count != 0)
	{
		value = array[tail_index];
		tail_index=wrap(0);
		count--;
		
		if(count == 0)
		{
			tail_index = 0;
			head_index =0;
		}
		
		
	}
	else if(tail_index != 0 && count != 0)
	{
		value = array[tail_index];
		tail_index--;
		count--;

		
		if(count == 0)
		{
			tail_index = 0;
			head_index =0;
		}
		
	}

	return value;
	
}

void Dynamic_deque_as_array::clear() {
	//Count, head index and tail index are restored to its original locations.

	count=0;
	head_index=0;
	tail_index=0;

	return;
}


#endif
