/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		mutable int num_edges;
    
		
        bool **check;
        double **graph_matrix;
		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();
        std::pair<int,int> find_lowest() const;
    
        double total_weight=0.0;
	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {
    
    //std::cout<< n << endl;
    num_nodes=n;
    if (n<0)
    {
        throw illegal_argument();
    }
    
    
    graph_matrix = new double*[num_nodes]; // dynamic array (size 10) of pointers to int
    for (int i = 0; i < num_nodes; i++) {
        graph_matrix[i] = new double[num_nodes];
        }
    for (int i = 0; i < num_nodes; i++) {   // for each row
        for (int j = 0; j < num_nodes; j++) { // for each column
            graph_matrix[i][j] = INF;
        }
    }
    
    check = new bool*[num_nodes]; // dynamic array (size 10) of pointers to int
    for (int i = 0; i < num_nodes; i++) {
        check[i] = new bool[num_nodes];
    }
    for (int i = 0; i < num_nodes; i++) {   // for each row
        for (int j = 0; j < num_nodes; j++) { // for each column
            check[i][j] = false;
        }
    }

    
    num_nodes=n;
    num_edges=0;
}

Weighted_graph::~Weighted_graph() {
    for (int i = 0; i < num_nodes; i++) {
        delete [] graph_matrix[i];
    }
    delete [] graph_matrix;
    
    for (int i = 0; i < num_nodes; i++) {
        delete [] check[i];
    }
    delete [] check;

}

int Weighted_graph::degree(int u) const {
    int degree=0;
    
    if(u > (num_nodes-1))
        throw illegal_argument();
    if(u<0)
        throw illegal_argument();
    
    for (int i=0; i<num_nodes; i++) {
        
        if(graph_matrix[u][i] != INF)
            degree++;
    }
    
	return degree;

}

int Weighted_graph::edge_count() const {
    int edge_count=0;
    
    for(int i=0;i<num_nodes;i++)
    {
        for(int j=0; j<num_nodes;j++)
        {
            
            if(graph_matrix[i][j] != INF)
            {
                edge_count++;
            }
        }
    }
    num_edges=edge_count/2;
    
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
    
   
    if(i<0 || j<0 || i>(num_nodes-1) || j>(num_nodes-1))
    {
        throw illegal_argument();
    }

    if(i == j)
    {
        return true;
    }
    if (graph_matrix[i][j]==INF) {
        return false;
    }
           if(graph_matrix[i][j]==0)
    {
        return false;
    }
    
    graph_matrix[i][j]=INF;
    graph_matrix[j][i]=INF;
    edge_count();
    
   
    
    
    return true;
    
}

void Weighted_graph::clear_edges() {

    for(int i=0;i<num_nodes;i++)
    {
        for(int j=0; j<num_nodes;j++)
        {
            graph_matrix[i][j]=INF;
        }
    }
    edge_count();
    
    return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    
    if(i>(num_nodes-1) || j>(num_nodes-1) || d<=0)
    {
        throw illegal_argument();
    }
    if(i<0 || j<0)
    {
        throw illegal_argument();
    }
    if(i == j)
    {
        return false;
    }
    graph_matrix[i][j]=d;
    graph_matrix[j][i]=d;
    edge_count();
    
	return true;
}

std::pair<int,int> Weighted_graph::find_lowest() const{
    
    double lowest_key = std::numeric_limits<int>::max();
    int lowest_row_index=0;
    int lowest_column_index=0;
    
    
    for (int i = 0; i < num_nodes; i++) {   // for each row
        for (int j = 0; j < num_nodes; j++) { // for each column
            if(graph_matrix[i][j] < lowest_key && check[i][j]==false && graph_matrix[i][j] != 0)
            {
                lowest_row_index=i;
                lowest_column_index=j;
                lowest_key = graph_matrix[i][j];
            }
        }
    }
    
    check[lowest_row_index][lowest_column_index]=true;
    check[lowest_column_index][lowest_row_index]=true;
    
    return std::make_pair(lowest_row_index,lowest_column_index);
    
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    
    int edges_tested=0;
    std::pair<int , int> data_set;
    double total_weight = 0.0;
    int successful_edges=0;

    Disjoint_set *obj = new Disjoint_set(num_nodes);
    
    for (int i = 0; i < num_edges; i++) {   // for each row
        
        data_set = Weighted_graph::find_lowest();
        edges_tested++;
        
        if(obj->find_set(data_set.first) != obj->find_set(data_set.second))
        {
            obj->union_sets(data_set.first, data_set.second);
            total_weight = total_weight+graph_matrix[data_set.first][data_set.second];
            successful_edges++;
        }
        if(successful_edges == num_nodes-1)
        {
            break;
        }
        
    }
    
    for (int i = 0; i < num_nodes; i++) {   // for each row
        for (int j = 0; j < num_nodes; j++) { // for each column
            check[i][j] = false;
        }
    }
    
    delete obj;
	return std::pair<double, int>( total_weight, edges_tested );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	

	return out;
}


#endif
