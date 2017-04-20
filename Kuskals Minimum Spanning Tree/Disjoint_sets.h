
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
    
    mutable int nun;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {

    if (n<0) {
        throw illegal_argument();
    }
    
        for(int i=0; i<n;i++)
        {
            nodes[i]=new ll_entry;
            nodes[i]->next=nullptr;
            sets[i]=new set_info;
            
            nodes[i]->content = i;
            nodes[i]->ptr_to_info=sets[i];
            sets[i]->size=1;
            
            sets[i]->head = nodes[i];
            sets[i]->tail = nodes[i];
            
        }
    
    initial_num_sets = n;
    set_counter = n;
    nun = n;

}
   	// initialize the sets



Disjoint_set::~Disjoint_set() {
    
    for(int i=0; i<nun;i++)
    {
        // nodes[i]=new ll_entry;
        delete nodes[i];
        
        
        delete sets[i];
       
        
        //nodes[i]->content = i;
        //nodes[i]->ptr_to_info=sets[i];
        //sets[i]->size=1;
        
        //sets[i]->head = nodes[i];
        //sets[i]->tail = nodes[i];
        
    }
    delete[] nodes;
    delete[] sets;
}
int Disjoint_set::find_set(int item) const{
	// should it be? return nodes[item]->ptr_to_info->head->content
    return nodes[item]->ptr_to_info->head->content;
	
}

int Disjoint_set::num_sets() const {
	return set_counter;
}

void Disjoint_set::union_sets(int node_index1, int node_index2) {
	
	if (node_index1 == node_index2)
		return;
    
    //set_info* si1 = nodes[node_index1]->ptr_to_info;
	//set_info* si2 = nodes[node_index2]->ptr_to_info;

    
    //ni1: the index of the larger set, ni2: the index of the smaller set
	//int ni1 = si1->size >= si2->size ? node_index1 : node_index2;
	//int ni2 = si1->size < si2->size ? node_index1 : node_index2;
    
    // size of the larger set
    //int tmp_size=nodes[ni1]->ptr_to_info->size;
    
    //add size of first one to second
    nodes[node_index1]->ptr_to_info->size=(nodes[node_index1]->ptr_to_info->size)+(nodes[node_index2]->ptr_to_info->size);
    
    //set the next of the end of first set to the start of second set
    nodes[node_index1]->ptr_to_info->tail->next = nodes[node_index2]->ptr_to_info->head;
    
    //backup old tail for while loop
    ll_entry* temp_ptr = nodes[node_index1]->ptr_to_info->head;
    
    //relocate pointer of first's tail to second ones tail
    nodes[node_index1]->ptr_to_info->tail = nodes[node_index2]->ptr_to_info->tail;
    
    //std::cout<<temp_ptr -> content<<std::endl;
	// iterate through the shorter list and modify the pointers
	while (temp_ptr != nullptr) {
       // temp_ptr[nodes]->ptr_to_info=nodes[ni2]->ptr_to_info;
        temp_ptr->ptr_to_info=nodes[node_index1]->ptr_to_info;
        temp_ptr = temp_ptr->next;
	}

	// do we need to modify anything else?
	

	// delete the set_info entry that no longer exists
	
	
	
}


#endif
