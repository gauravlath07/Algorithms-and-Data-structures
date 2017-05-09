#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;

	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *&);
		int location_index(std::string const &str, int index) const;
		void clear();

		friend class Trie;
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {

	// empty constructor
}

Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;             //already implemented from before
	} else {
		return children[n];
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {
	
    // uses a helper function to get the letter index of the string passed as parameter
    int loc = location_index(str,depth);
    // variable to find out we have reached the last letter and we need to stop traversing
    int string_length = str.length();
    int depth_counter = depth;
    
    if(children == nullptr || children[loc] == nullptr)
    {
        return false;
    }

    else
    {
        depth_counter++;
        if ((is_terminal == true && depth == (string_length-1)))
        {
            return true;
        }
        else if ((is_terminal == false && depth == (string_length-1)))
        {
            return false;
        }
        return children[loc]->member(str,depth_counter);
    }
    
    
    return true;
}

bool Trie_node::insert(std::string const &str, int depth ) {
	
    // takes each character and checks if its index has a nullplr.
    // If it has a nullptr than a new trie_node is instantiated else we call
    // recursion insert on the child of the existing node.
    int string_length = str.length();
    int recursion_counter = str.length();
    int loc = location_index(str,depth);
    int depth_counter = depth;
    
	if(children == nullptr)
	{
        children = new Trie_node*[CHARACTERS];
        for (int i = 0; i < CHARACTERS; i++)
        {
            children[i] = nullptr;
        }
    }
    
    if (children[loc] == nullptr) {
        
        children[loc] = new Trie_node();
        depth_counter++;
        
        if (depth_counter==(string_length))
        {
            is_terminal=true;
            return true;
        }
        children[loc]->insert(str,depth_counter);
    }
    else if(children[loc] != nullptr)
    {
        depth_counter++;
        if(depth_counter == (string_length))
        {
            is_terminal = true;
            return true;
        }
        children[loc]->insert(str,depth_counter);
    }
    
	return true;
}

bool Trie_node::erase(std::string const &str, int depth, Trie_node *&ptr_to_this) {
    // traverses to the end of the string and sets is_terminal to false so that the
    // member method cannot locate it
    int depth_counter=depth;
    int loc = location_index(str,depth);
    int string_length = str.length();
    //int isterminal_counter=is_terminal_counter;
    
    
    if(depth_counter == (string_length-1) && is_terminal==true && children[loc] != nullptr)
    {
        is_terminal=false;
        return true;
    }
    else if(depth_counter == (string_length-1) && is_terminal==true)
    {
        //delete [] children;
        is_terminal=false;
        return true;
    }
    else
    {
        depth_counter++;
        
        
        children[loc]->erase(str,depth_counter,children[loc]);
        
    }
    return true;
}

void Trie_node::clear()
{
    // clears the entire array including the rootnode
    if(children != nullptr)
    {
        for (int i = 0; i<CHARACTERS; i++)
        {
            if(children[i] != nullptr)
            {
                
                children[i]->clear();
                
                children[i] = nullptr;
                
            }
        }
    
            delete [] children;
        
    }
    
    delete this;

}


int Trie_node::location_index(std::string const &str, int index) const
{
    return tolower(str[index]) - 'a';
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
