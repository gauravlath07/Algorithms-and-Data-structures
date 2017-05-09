#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Trie_node.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
   	// empty constructor
}

Trie::~Trie() {
    if(root_node != nullptr)
    {
        root_node -> clear();
        root_node = nullptr;
    }
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	if (trie_size == 0)
	{
		return true;
	}
	else
		return false;
}

Trie_node *Trie::root() const {
    if(trie_size == 0)
        return nullptr;
    
    
	return root_node;
}

bool Trie::member(std::string const &str ) const {
    int string_length = str.length();
    for(int i=0; i<string_length; i++)
    {
        char c = str[i];
        if(((int)c > 64 && (int)c < 91) || ((int)c > 96 && (int)c < 123))
        {
            
        }
        else
        {
            throw illegal_argument();
        }
    }
    
    if(trie_size == 0)
        return false;
   
    return root_node->member(str,0);
}

bool Trie::insert( std::string const &str ) {
    
    // check for illegal characters
	int string_length = str.length();
	for(int i=0; i<string_length; i++)
	{
		char c = str[i];
		if(((int)c > 64 && (int)c < 91) || ((int)c > 96 && (int)c < 123))
		{
            
		}
        else
        {
            throw illegal_argument();
        }
	}
    
    // instantiate a new node if only the root exists
    if(root_node == nullptr)
    {
        root_node = new Trie_node();
    }
    
    if(member(str) == true)
    {
        return false;
    }
    else
    {
        trie_size++;
        return root_node->insert(str,0);
    }
   
   }

bool Trie::erase( std::string const &str ) {
    int string_length = str.length();
    
    for(int i=0; i<string_length; i++)
    {
        char c = str[i];
        if(((int)c > 64 && (int)c < 91) || ((int)c > 96 && (int)c < 123))
        {
            
        }
        else
        {
            throw illegal_argument();
        }
    }
    
    if (member(str)==true)
    {
        trie_size--;
        root_node->erase(str,0,root_node);
    }
    else
    {
        return false;
    }
    return true;
    
}

void Trie::clear() {
    
    if(root_node != nullptr)
    {
        root_node->clear();
        root_node = nullptr;
        trie_size = 0;
    }
    // You can modify this function however you want:  it will not be tested

}

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
