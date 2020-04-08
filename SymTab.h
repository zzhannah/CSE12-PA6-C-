/*=============================================================================
 SymTab.h
 @author Gary Gillespie
 @version 02/10/2020
=============================================================================*/
#ifndef SYMTAB_H
#define SYMTAB_H
#include <iostream>
#include "Base.h"
#include "Hash.h"
using namespace std;
class SymTab : private HashTable {
public:
	using HashTable :: Insert;
	using HashTable :: Lookup;
	using HashTable :: Write;
	SymTab (int sz) : HashTable (sz) {}
};
#endif