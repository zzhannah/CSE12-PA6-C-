/******************************************************************************
                                                        Han Zhang
                                                        CSE 12, Winter 2020
                                                        February 10, 2020
                                                        cs12wi20kj
                                Assignment Six
File Name:      Driver.c
Description:    Contains the member functions for the UCSDStudent class as part 
		of the Driver.c file used to test symbol table. Work together 
		with Hash.c.
******************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <getopt.h>
#include <iostream>
#include "Base.h"
#include "SymTab.h"
using namespace std;
#ifdef NULL
#undef NULL
#define NULL 0
#endif
/*=============================================================================
Class UCSDStduent
Description:		Extends from Base
			initialize incoming values and provide hashCode and 
			equals function for HashTable
Data Fields:		name		- holds the name inserted from user
			stduentnum	- holds the student num inserted from
					  user
Public Functions:	ostream & Write	- print out strings
			constructor1	- takes incoming value
			constructor2	- initialize values
			destructor	- free the memory
			operator long	- compare the name of the elements
			operator char *	- other classes can get name from here
=============================================================================*/
class UCSDStudent : public Base {
	char * name;
	long studentnum;
public:
	/*constructor1*/
	UCSDStudent (char * nm, long sn) :
		name (strdup (nm)), studentnum (sn) {}
	/*constructor2*/
	UCSDStudent (UCSDStudent & stu) {
		name = strdup (stu.name);
		studentnum = (stu.studentnum);
	}
	/*destructor*/
	~UCSDStudent (void) {
		/*free memory for name*/
		free (name);
	}
	/*overload to return name*/
	operator char * (void) {
		return name;
	}
	/*overload to compare name*/
	operator long (void);
	long operator == (Base & base) {
		return ! strcmp (name, base);
	}
	/*return string to user
	 * */
	ostream & Write (ostream & stream) {
		return stream << "name: " << name
			<< " Studentnum: " << studentnum;
	}
};
/*-----------------------------------------------------------------------------
Function Name:		UCSDStudent :: operator
Description:		takes name from user and converts to ascii sum
Input:			none
Result:			convert succesfully
			retun sum
-----------------------------------------------------------------------------*/
UCSDStudent :: operator long (void) {
	/*get ascii sum of name*/
	long sum = 0;
	/*loop to add ascii num to sum*/
	for (long index = 0; name[index]; index++)
		sum += name[index];
	return sum;
}
int main (int argc, char * const * argv) {
	SymTab ST (5);
	char buffer[128];
	char command;
	long number;
	char option;
	/* initialize debug variable */
	HashTable::Set_Debug(0);
	 /* check command line options for debug display */
	 while ((option = getopt (argc, argv, "x")) != EOF) {
		 switch (option) {
			 case 'x': HashTable::Set_Debug(1);
				 break;
		 	}
	} 
	ST.Write (cout << "Initial Symbol Table:\n");
	while (cin) {
		command = NULL;	// reset command each time in loop
		cout << "Please enter a command:  ((i)nsert, (l)ookup, (w)rite):  ";
		cin >> command;
		switch (command) {
		case 'i':
			cout << "Please enter UCSD student name to insert:  ";
			cin >> buffer;	// formatted input
			cout << "Please enter UCSD student number:  ";
			cin >> number;
			// create student and place in symbol table
			if(!ST.Insert (new UCSDStudent (buffer, number))){
				ST.Write (cout << "\nFinal Symbol Table:\n");
				exit (0);
			}
			break;
		case 'l': {
			Base * found;	// whether found or not
			cout << "Please enter UCSD student name to lookup:  ";
			cin >> buffer;	// formatted input
			UCSDStudent stu (buffer, 0);
			found = ST.Lookup (& stu);
			
			if (found)
				found->Write (cout << "Student found!!!\n") << "\n";
			else
				cout << "Student " << buffer << " not there!\n";
			}
			break;
		case 'w':
			ST.Write (cout << "The Symbol Table contains:\n");
		}
	}
	ST.Write (cout << "\nFinal Symbol Table:\n");
}