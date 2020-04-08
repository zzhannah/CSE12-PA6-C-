/*=============================================================================
 Stack.c
 @author Gary Gillespie
 @version 02/10/2020
=============================================================================*/
#include <iostream>
#include "Base.h"
#include "Stack.h"
using namespace std;
Base * Stack :: Pop (void) {
	return Remove (END);
}
Base * Stack :: Push (Base * element) {
	return Insert (element, END);
}
Base * Stack :: Top (void) {
	return View (END);
}