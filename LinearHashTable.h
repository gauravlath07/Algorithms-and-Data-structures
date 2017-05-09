#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
	private:
		int count;
		int power;
		int array_size;
        int mod;
		T *array;
		state *occupied;

		double loadfactor;
		int initial_array_size;


	public:
		LinearHashTable( int = 5 );
		~LinearHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void update_power();
		void update_loadfactor();


		void insert( T const & );
		bool remove( T const & );
		void clear();
		void print() const;
};

//constructor
template<typename T >
LinearHashTable<T >::LinearHashTable( int m ):
array_size( 1 << power ){
	// initializes the arrays and variables to
	// be used for the program.

	array_size = pow(2,m);
	mod = pow(2,m);
	initial_array_size = pow(2,m);
	array = new T [array_size];
	occupied = new state [array_size];
	for(int i=0;i<array_size;i++)
	{
		occupied[i] = EMPTY;
	}
	count = 0;
	power = (log(array_size)) / (log(2));
}

//destructor
template<typename T >
LinearHashTable<T >::~LinearHashTable() {
	// deletes both the arrays allocated
	delete[] array;
	delete[] occupied;
}

//helper functions
template<typename T >
void LinearHashTable<T >::update_power() {
	// helper function for updating the power
	// after every change.
    power = (log(array_size)) / (log(2)); 
}

template<typename T >
void LinearHashTable<T >::update_loadfactor() {
	// helper function for updating the 
	// load factor after every change

    double a = (double)count;
    double b = (double)array_size;

    loadfactor = a/b;
}


//Accessors

template<typename T >
int LinearHashTable<T >::size() const {
	return count;
}

template<typename T >
int LinearHashTable<T >::capacity() const {

	return array_size;
}

template<typename T >
bool LinearHashTable<T >::empty() const {
	if(count == 0)
	{
		return true;
	}
	else
		return false;
}

template<typename T >
bool LinearHashTable<T>::member( T const &obj ) const {
	/*
	-- This method uses the hash function to look for the 
	-- element sent in the paramter. The search doesnt stop
	-- until it encounters an empty space.
	*/
	int collission=0;
	int location = ((int)obj+collission) % mod;
	bool exist=false;

	while(occupied[location] != EMPTY) 
	{
		if(array[location] == obj && occupied[location] == OCCUPIED)
		{
			exist = true;
			break;
		}
		else
		{ 
			collission++;
			location = ((int)obj+collission) % mod;
		}
	}
	return exist;
}

template<typename T>
T LinearHashTable<T >::bin( int n ) const {
	return array[n];
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
	return loadfactor;
}

template<typename T >
void LinearHashTable<T >::print() const{
	// helper function for printing out the 
	// hash table
	for(int i=0; i<array_size; i++)
	{
		std::cout << "elementnumber : " << i << std::endl;
		std::cout << "value : " << array[i] << std::endl;
		if (occupied[i] == 0)
		{
			std::cout << "state : empty" << std::endl;
		}
		else if(occupied[i] == 1)
		{
			std::cout << "state : occupied" << std::endl;
		}
		else
		{
			std::cout << "state : deleted" << std::endl;
		}
	}
}

//Mutators

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) {
	// If the load factor is greater than 0.75 a new
	// table is initialized and all
	// the previous elements are deleted and rehashed
	// onto the new table. If the load factor is less than that
	// then a new table is added according to the 
	// hash function of linear probing.

	int location = (int)obj % mod;
	int collission=0;
	if(loadfactor > 0.75)
	{	
		T *temp_array = new T[array_size];
		std::copy(array, array+array_size, temp_array);
		state *temp_occupied = new state[array_size];
		std::copy(occupied, occupied+array_size, temp_occupied);

		delete[] array;
		delete[] occupied;

		array_size = array_size*2;
		mod = mod*2;

		array = new T [array_size];
		occupied = new state [array_size];

		for(int i=0;i<array_size;i++)
		{
			occupied[i] = EMPTY;
		}
		count = 0;

		for(int j=0;j<(array_size/2);j++)
		{
			if(temp_occupied[j] == OCCUPIED)
			{
				location = (int)temp_array[j]%mod;
		 		collission=0;
				if(occupied[location] == EMPTY && loadfactor <= 0.75)
					{
						array[location] = temp_array[j];
						occupied[location] = OCCUPIED;
						count++;
						update_power();
						update_loadfactor();
					}
				else
				{
					while(occupied[location] != EMPTY)
					{
						collission++;
						location = ((int)temp_array[j]+collission)%mod;
					}
					array[location] = temp_array[j];
					occupied[location] = OCCUPIED;
					count++;
					update_power();
					update_loadfactor();
				}

			}
			else
			{

			}
		
		}
		delete[] temp_array;
		delete[] temp_occupied;
		update_power();
		update_loadfactor();
		insert(obj);
	}
	else if(occupied[location] != OCCUPIED && loadfactor <= 0.75)
	{
		collission = 0;
		array[location] = obj;
		occupied[location] = OCCUPIED;
		count++;
		update_power();
		update_loadfactor();
	}
	else
	{ 
		while(occupied[location] != EMPTY)
		{
			collission++;
			location = ((int)obj+collission)%mod;
		}
		array[location] = obj;
		occupied[location] = OCCUPIED;
		count++;
		update_power();
		update_loadfactor();
	}
}

template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {
	// If the load factor is less than 0.25 a new
	// hash table of half the size 
	// is initialized and all the previous 
	// elements are deleted and rehashed onto
	// the new table. If the load factor is greater than that
	// then the new object is just added acoording to the 
	// hash function of linear probing.

	int location = (int)obj % mod;
	int collission=0;
	if (member(obj))
	{
		if(loadfactor <= 0.25 && array_size>initial_array_size)
		{	
			T *temp_array = new T[array_size];
			std::copy(array, array+array_size, temp_array);
			state *temp_occupied = new state[array_size];
			std::copy(occupied, occupied+array_size, temp_occupied);

			delete[] array;
			delete[] occupied;

			array_size = array_size/2;
			mod = mod/2;
			array = new T [array_size];
			occupied = new state [array_size];
			for(int i=0;i<array_size;i++)
			{
				occupied[i] = EMPTY;
			}
			count =0;

			for(int j=0;j<(array_size*2);j++)
			{
				if(temp_occupied[j] == OCCUPIED)
				{
					location = (int)temp_array[j]%mod;
			 		collission=0;
					if(occupied[location] == EMPTY && loadfactor <= 0.75)
						{
							array[location] = temp_array[j];
							occupied[location] = OCCUPIED;
							count++;
							update_power();
							update_loadfactor();
						}
					else
					{
						while(occupied[location] != EMPTY)
						{
							collission++;
							location = ((int)temp_array[j]+collission)%mod;
						}
						array[location] = temp_array[j];
						occupied[location] = OCCUPIED;
						count++;
						update_power();
						update_loadfactor();
					}

				}
				else
				{
					continue;
				}
			
			}
			delete[] temp_array;
			delete[] temp_occupied;
			update_power();
			update_loadfactor();
			remove(obj);
			return true;
		}
		else if(array[location] == obj && occupied[location] == OCCUPIED && loadfactor > 0.25)
		{
			occupied[location] = DELETED;
			count--;
			update_power();
			update_loadfactor();
			return true;
		}
		else
		{
			collission = 0;
			
			while(array[((int)obj+collission)%mod] != obj)
			{
				collission++;
				location = ((int)obj+collission)%mod;
			}
			
			occupied[location] = DELETED;
			count--;
			update_power();
			update_loadfactor();
			return true;
		}
	}
	else
	{
		
		return false;
	}
}

template<typename T >
void LinearHashTable<T >::clear() {
	// Sets all the current array value as "EMPTY"
	for(int i=0;i<array_size;i++)
	{
		occupied[i] = EMPTY;
	}
	count = 0;
}


#endif
