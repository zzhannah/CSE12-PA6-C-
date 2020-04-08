/******************************************************************************
                                                        Han Zhang
                                                        CSE 12, Winter 2020
                                                        February 10, 2020
                                                        cs12wi20kj
                                Assignment Six
File Name:      Hash.c
Description:    Implement a Symbol Table to allow variable assignment to the 
		calculator. Allow user to insert, write and lookup. 
		Work together with Driver.c.
******************************************************************************/
#include <cstdlib>
#include <string>
#include "Hash.h"
/*=============================================================================
Class HashTable
Description:		Extends from Base
			Allocate a Symbol Table. Allow user to insert, write 
			and lookup. Get the hashCode and equals functions from 
			Driver.c
Data Fields:		counter		- number of HashTables so far
			debug		- allocation of debug state
Functions:	HashTable :: Set_Debug	- turn debug on or off
		HashTable :: HashTable	- allocate and initialize
		HashTable :: ~HashTable	- deallocate the table
		HashTable :: Insert	- allow user to insert element
		HashTable :: Locate	- find spot for elements
		HashTable :: Lookup	- find element in hashtable
		HashTable :: Write	- return readable data to user
=============================================================================*/
using namespace std;
static const char AND[] = " and ";
static const char DEBUG_ALLOCATE[] = " - Allocated]\n";
static const char DEBUG_DEALLOCATE[] = " has been deallocated]\n";
static const char DEBUG_LOCATE[] = " - Locate]\n";
static const char DEBUG_LOOKUP[] = " - Lookup]\n";
static const char BUMP[] = "[Bumping To Next Location...]\n";
static const char COMPARE[] = " - Comparing ";
static const char FOUND_SPOT[] = " - Found Empty Spot]\n";
static const char HASH[] = "[Hash Table ";
static const char HASH_VAL[] = "[Hash value is: ";
static const char INSERT[] = " - Inserting ";
static const char PROCESSING[] = "[Processing ";
static const char TRYING[] = "[Trying index ";
bool HashTable :: debug = true;
int HashTable :: counter = 0;
void HashTable :: Set_Debug (int option)
/***************************************************************************
% Routine Name : HashTable :: Set_Debug (public)
% File :         hash.c
% 
% Description :  This function sets debug mode on or off
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% option             true should set debug mode on, false should set debug
%                    mode off.
***************************************************************************/
{
	/*switch debug on or off*/
	if (debug == false) {
		debug = true;
	} else {
		debug = false;
	}
}
HashTable :: HashTable (int sz) : size (sz),
	table_count(++counter), occupancy (0), table (new Base *[sz]), 
	probeCount (new int[sz])
/***************************************************************************
% Routine Name : HashTable :: HashTable (public)
% File :         hash.c
% 
% Description :  This function allocates an initializes the memory
%                associated with a hash table.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% size               The number of elements for the table...MUST BE PRIME!!!
***************************************************************************/
{
	/* initialize all table elements */
	for (int i = 0; i < size; i++) {
		table[i] = NULL;
	}
	/*debug msg if debug on*/
	if (debug == true) {
		cerr << HASH << table_count << DEBUG_ALLOCATE;
	}
}	/* end: HashTable */
HashTable :: ~HashTable (void)
/***************************************************************************
% Routine Name : HashTable :: ~HashTable  (public)
% File :         hash.c
% 
% Description :  deallocates memory associated with the Hash Table.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/
{
	/* call function to delete individual elements */
	for (int i = 0; i < size; i++) {
		delete (table[i]);
	}
	/*debug msg if debug on*/
	if (debug == true) {
		cerr << HASH << table_count << DEBUG_DEALLOCATE;
	}
	/* delete table itself and */
	delete[] table;
	delete[] probeCount;
}	/* end: ~HashTable */
bool HashTable :: Insert (Base * element, int initialCount)
/***************************************************************************
% Routine Name : HashTable :: Insert (public)
% File :         hash.c
% 
% Description : This function will insert the element in the hash table.
%		If the element cannot be inserted, false will be returned.
%		If the element can be inserted, the element is inserted
%		and true is returned.  Duplicate insertions will
%		cause the existing element to be deleted, and the duplicate
%		element to take its place.
%
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% element            The element to insert.
% recursiveCall      Whether or not we are entering from recursion
% <return>           true or false indicating success or failure of insertion
***************************************************************************/
{
        bool location;		/*to get truth value from locate*/
	Base * hold;		/*to hold the old number in the table*/
	int holdprobe;		/*to hold probe count of old element*/
		
	/*get initial count and pass to locate*/
	count = initialCount;
	/*debug msg if debug on*/
	if (debug == true) {
		cerr << HASH << table_count << INSERT << (char*)element <<
		       	"]\n";
	}
	/*call locate and save truth value*/
	location = Locate(element);	
	/*if find the element, update*/
	if (location == true) {
		table[index] = element;
	} else {
		/*if full, return false*/
		if (occupancy == size) {
			return false;
		/*if empty spot, fill in element*/
		} else if (table[index] == NULL){
			/*insert element to table*/
			table[index] = element;
			probeCount[index] = count;
			occupancy++;
			/*debug msg if debug on*/
			if (debug == true) {
				cerr << HASH << table_count << FOUND_SPOT;
			}
			
		/*if find a smaller probe num*/
		/*reinsert old element recursively*/
		} else if(count > probeCount[index]) {
			/*insert element to table*/
			/*keep old element's count*/
			hold = table[index];
			holdprobe = probeCount[index];
			table[index] = element;
			probeCount[index] = count;
			/*debug msg if debug on*/
			if (debug == true) {
				cerr << BUMP;
			}
			
			/*insert old element*/
			Insert(hold, ++holdprobe);
			/*increase occupancy*/
			occupancy++;
		}
	}
	return true;
}
bool HashTable :: Locate (Base * element)
/**********************************************************************
% Routine Name : HashTable :: Locate (private)
% File :         HashTable.c
% 
% Description : This function will locate the location in the
%               table for the insert or lookup.
%
% Parameters descriptions :
%  
% name               description
% ------------------ -------------------------------------------------
% element            The element needing a location.
% <return>           true if tem found, or false if not found
**********************************************************************/
{
	int namesum;		/*to track ascii sum of name*/
	int initial;		/*initial value of probecount*/
	int increment;		/*increment of probecount*/
	/*if element is null, return false*/
	if (element == NULL) {
		return false;
	}
	/*calculation of where index should go*/
	namesum = (long)*element;
	initial = namesum % size;
	increment = namesum % (size - 1) + 1;
	/*debug msg if debug on*/
	if (debug == true) {
		cerr << HASH << table_count << DEBUG_LOCATE;
		cerr << PROCESSING << (char*)element << "]\n";
		cerr << HASH_VAL << namesum << "]\n";
	}
	/*make sure only go once for the table*/
	while (count < size) {
		/*go to right index*/
		/*if first time in this loop, init value*/
		if (count == 1) {
			index = initial;
		/*else get the new location by increment*/
		} else {
			index = (index+increment)%size;	
		}
		/*debug msg if debug on*/
		if (debug == true) {
			cerr << TRYING << index << "]\n";
		}
		/*if found has a smaller probe number*/
		if (table[index] == NULL) {
			return false;
	
		} else {
			/*if find element return true*/
			if (*element == *table[index]) {
					
				return true;
			/*if the spot is null*/
			}else {
				/*debug msg if debug on*/
				if (debug == true) {
					cerr << HASH << table_count << COMPARE 
					<< (char*)element << AND 
					<< (char*)table[index] <<
				       	"]\n";
				}
				/*if found smaller probe num than us*/
				if (count > probeCount[index]){
					return false;
				}
			}
		}
		/*increase count, make loop run*/
		count++;
			
	}
		
	return false;
}
Base * HashTable :: Lookup (Base * element)
/***************************************************************************
% Routine Name : HashTable :: Lookup (public)
% File :         hash.c
% 
% Description : This function will lookup the element in the hash table.  If
%               found a pointer to the element is returned.  If the element
%               is not found, NULL will be returned to the user.
%
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% element            The element to insert or to lookup.
% <return>           A pointer to the element if found, else NULL
***************************************************************************/
{
        bool location;	/*to track truth value of locate*/
	/*debug msg if debug on*/
	if (debug == true) {
		cerr << HASH << table_count << DEBUG_LOOKUP;
	}
	/*call location to find element*/
	location = Locate(element);
	/*if found, return element*/
	if (location == true) {
		return table[index];
	}
		
	/*else, return null*/
	return NULL;
}
ostream & HashTable :: Write (ostream & stream)
/***************************************************************************
% Routine Name : HashTable :: Write (public)
% File :         hash.c
% 
% Description : This funtion will output the contents of the hash table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/
{
	stream << "Hash Table " << table_count << ":\n"
	       << "size is " << size << " elements, "
	       << "occupancy is " << occupancy << " elements.\n";
	/* go through all table elements */
	for (int index = 0; index < size; index++)
		if (table[index])
			table[index]->Write(stream << "at index "
			<< index << ": ") << " with probeCount: "
			<< probeCount[index] << "\n";
	return stream;
}	/* end: Write */