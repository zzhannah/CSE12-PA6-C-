/*=============================================================================
 Stack.h
 @author Gary Gillespie
 @version 02/10/2020
=============================================================================*/
#ifndef STACK_H
#define STACK_H
#include <iostream>
#include "List.h"
using namespace std;
class Stack : private List {
public:
	using List :: IsEmpty;
	using List :: NumElements;
	using List :: Write;
	Base * Pop (void);
	Base * Push (Base *);
	Base * Top (void);
};
#endif