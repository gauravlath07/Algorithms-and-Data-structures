# Algorithms and Data Structures

All the projects mentioned below have been created as header files which can be attached to any C++ project and used for effective data management.

## Deque
The goal of this data-structure is to implement a dynamic deque data structure. A deque is a queue that stores elements in an ordered list and allows insertions and deletions at both ends in O(1) time and is able to increase its size if necessary in O(n).
You can read more about it on this wikipedia <a href="https://en.wikipedia.org/wiki/Double-ended_queue">link</a>. 

### Accessors

The header file has 5 accessors:
<ul> 
<li> int head() const – Returns the integer at the head of the data deque in O(1).
<li> int tail() const – Returns the integer at the tail of the data deque in O(1).
<li> int size() const – Returns the number of elements currently stored in the deque in O(1).
<li> bool empty() const – Returns true if deque is empty false otherwise in O(1).
<li> int capacity() const – Returns the capacity of deque in O(1).
</ul>

### Mutators
This class has five mutators:
<ul>
<li> void enqueue head(int const &) – Inserts a new item at the head of the deque in O(1). If the array is full, creates a new array with size 2n (where n is current size of the array) and copy the elements from the current array to the new array in O(n).
<li> void enqueue tail(int const &) – Inserts a new item at the tail of the deque in O(1). If the array is full, create a new array with size 2n (where n is current size of the array) and copy the elements from the current array to the new array in O(n).
<li> int dequeue head() – Removes the element at the head of the deque in O(1). This may throw an underflow exception.
<li> int dequeue tail() – Removes the element at the tail of the deque in O(1). This may throw an underflow exception.
<li> void clear() – Remove all elements from the deque in O(1).
</ul>

## Hash Table

The goal of this project is to design and implement a hash table data structure. A hash table is a data structure where values are mapped to an entry of a table using a hash function. For this project, linear probing is used to resolve collision. The advantage of the hash table data structure is that it can achieve constant expected time for insert and remove operations (O(1)).

### Accessors

This class has seven accessors:
<ul>
<li> int size() const - Return the number of elements currently stored in the hash table. (O(1))
<li> int capacity() const - Return the number of bins in the hash table. (O(1))
<li> bool empty() const - Return true if the hash table is empty, false otherwise. (O(1))
<li> bool member( T const & ) const - Return true if object obj is in the hash table and false otherwise. (O(1))
<li> T bin( int ) const - Return the entry in bin n. The behaviour of this function is undefined if the bin is not filled. It will only be used to test the class with the expected locations. (O(1))
<li> double load_factor() const – Return the load factor of the hash table. (O(1))
<li> void print() const - A function which you can use to print the class in the testing environment. This function will not be tested.
</ul>

### Mutators
This class has three mutators:
<ul>
<li>void insert( T const & ) - If load factor is less than or equal to 0.75, you have to insert the new object into the hash table in the appropriate bin as determined by the hash function and the rules of linear probing (O(1)). Otherwise, double the size of hash table, rehash all elements, and then insert the new element (O(n)).
<li> bool remove( T const & ) - If the load factor is greater than 0.25, you have to remove the object from the hash table if it is in the hash table (returning false if it is not) by setting the corresponding flag of the bin to “DELETED”. (O(1)). Otherwise, if the load factor is less than 0.25 and the current capacity of hash table is not equal to the initial capacity (that was assigned in the constructor), you have to shrink the capacity of the hash table to the half of its current size, rehash the elements, and remove the input from the table (O(𝑛)).
<li> void clear() - Remove all the elements in the hash table. (O(M))
</ul>

You can read more about it on this wikipedia <a href="https://en.wikipedia.org/wiki/Hash_table">link</a>. 

## Trie
In this project I have implemented a trie data structure using recursive programming. A trie is a 26-ary tree where the root node represents an empty string “” and if the kth (k going from 0 to 25) sub-tree is not a null sub-tree, it represents a string that is the concatenation of string represented by the parent and the kth letter of the alphabet (where a is the 0th letter, b is the 1st letter, and so on). Each node may or may not
indicate that it is a terminal entry for a word. While a trie could be used to store hyphenated and capitalized words together with those with apostrophes, we will restrict ourselves to words made up of the twenty-six letters of the English alphabet.

### Accessors
This class has four accessors:
<ul>
<li> bool empty() const - Return true if the trie is empty (the size is 0). (O(1))
<li> int size() const - Returns the number of words in the trie. (O(1))
<li> Trie_node *root() const - Returns a pointer to the root node. (O(1))
<li> bool member( std::String str ) const - Return true if the word represented by the string is in the
Trie and false otherwise. If the string contains any characters other than those of the English
alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw an illegal_argument exception. (O(n))
</ul>

### Mutators
This class has three mutators:
<ul>
<li> bool insert( std::string str) - Insert the word represented by str into the tree. If the string contains
any characters other than those of the English alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw
an illegal_argument exception; otherwise if the string is already in the tree, return false;
otherwise, return true (the insertion was successful). This is done by calling insert on the root, and
if the root node is null, it will be necessary create an instance of the Trie_node class and assign it
to the root first. (O(n))
<li> bool erase( std::string str) - Erase the word represented by str from the tree. If the string contains
any characters other than those of the English alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw
an illegal_argument exception; otherwise if the string is not in the tree, return false; otherwise,
return true (the erase was successful). If the tree is empty, return false, otherwise this function
calls erase on the root. If the word erased is the last one in the tree, delete the root node. (O(n))
<li> void clear() - Delete all the nodes in the tree. Again, if the tree is not empty, it should just call
clear on the root and set the appropriate member variables. (O(N) where N is the number of
words in the tree)
</ul>

You can read more about it on this wikipedia <a href="https://en.wikipedia.org/wiki/Trie">link</a>.

## Kruskals Minimum Spanning Tree

In this project, I implemented the Minimum Spanning Tree (MST) of a weighted undirected graph, using the Kruskal’s algorithm. We consider the nodes in the graph to be numbered from 0 to n – 1. This means a graph with 4 nodes, has nodes named 0, 1, 2 and 3. Each edge has a weight (a positive number and of double type) associated with it.

### Accessors
The class has three accessors:
<ul>
<li> int degree( int n ) const - Returns the degree of the vertex n. Throw an illegal_argument exception if the argument does not correspond to an existing vertex.
<li> int edge_count() const - Returns the number of edges in the graph.
<li> std::pair&lt;double, int&gt; minimum_spanning_tree() const - Uses Kruskal’s algorithm to find the minimum spanning tree. It returns the weight of the minimum spanning tree and the number of edges that were tested for adding into the minimum spanning tree.
</ul>

### Mutators
This class has 3 mutators:
<ul>
<li> bool insert_edge( int i, int j, double w ) - If i equals j and are in the graph, return false. Otherwise,
either add a new edge from vertex i to vertex j or, if the edge already exists, update the weight and
return true. Recall that the graph is undirected. If i or j are outside the range of [0..n-1] or if the
weight w is less than or equal to zero, throw an illegal_argument exception.
<li> bool erase_edge( int i, int j ) - If an edge between nodes i and j exists, remove the edge. In this
case or if i equals j return true. Otherwise, if no edge exists, return false. If i or j are outside the
range of [0..n-1], throw an illegal_argument exception.
<li> void clear_edges() - Removes all the edges from the graph.
</ul>

You can read more about it on this wikipedia <a href="https://en.wikipedia.org/wiki/Kruskal%27s_algorithm">link</a>.
