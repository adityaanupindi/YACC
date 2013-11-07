/*
 * Unit tests for the ElementArray adt.
 * Cmput 415 - Team Yet Another Cmput415 Compiler
 */


#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testElementArray.h"

#define INTLOW_VAL 12
#define INTHIGH_VAL 23423



char *
test_newElementArray(){
	
	
	struct ElementArray *ea = newElementArray();
	
	mu_assert("newElementArray(): does not return NULL",ea);
	mu_assert("newElementArray(): ea->len should have len == EA_DEFAULT_SZ",
		  ea->len = EA_DEFAULT_SZ);
	mu_assert("newElementArray(): ea->data pointer is not NULL pointer",
		  ea->data);
	mu_assert("newElementArray(): ea->nElement shoud have zero elements",
		  ea->nElements == 0);
		  
	return NULL;

}

char *
test_growElementArray(){
	
	
	struct ElementArray *ea = newElementArray();
	unsigned int len;
	
	growElementArray(ea);
	

	mu_assert("growElementArray(): The len == 2*(EA_DEFAULT_SZ after we call \
		  2*(DEFAULT_SIZE)", ea->len == 2 * EA_DEFAULT_SZ);
	mu_assert("growElementArray(): should not change nElements \
		  in the array", ea->nElements == 0);
		  
	len = ea->len;
	growElementArray(ea);
	mu_assert("growParamArray(): should double the \
		  prev len", ea->len == 2*len);
	return NULL;
}


char *
test_appendElement(){
	
	double REAL_VAL = 123.321;
	char *constId ="testType";
	char *typeId = "testType";
	
	struct ElementArray *ea = newElementArray();
	Symbol *typeSymbol = setUpTypeSymbol();
	Symbol *constSymbol = setUpConstSymbol();
	
	appendElement(ea,constSymbol);
	
	mu_assert("appendElement(): The nELements should equal to 1 now after adding another \
		  symbol ",ea->nElements == 1);
	
	mu_assert("appendElement(): The id of the first symbol should be \
		  'testConst'",strcmp(((Symbol **)ea->data)[0]->name,constId)==0);
		  
	mu_assert("appendElement(): The kind of the first symbol should be \
		  CONST_KIND",((Symbol **)ea->data)[0]->kind == CONST_KIND);
	
	mu_assert("appendElement(): The value of the first symbol should be \
		  INTLOW_VAL ",((Symbol **)ea->data)[0]->kindPtr.ConstKind->value.Real.value == REAL_VAL);
	
	appendElement(ea,typeSymbol);
	
	mu_assert("appendElement(): The nELements should equal to 2 now after adding another \
		  symbol ",ea->nElements == 2);	
	
	mu_assert("appendElement(): The id of the second symbol should be \
		  'testType'",strcmp(((Symbol **)ea->data)[1]->name,typeId)==0);
	
	mu_assert("appendElement(): The kind of the second symbol should be \
		  TYPE_KIND",(((Symbol **)ea->data)[1]->kind == TYPE_KIND));
	mu_assert("appendElement(): The value of the second symbol should be \
		  INTLOW_VAL ",(((Symbol **)ea->data)[1]->kindPtr.TypeKind->typePtr.Integer->value == INTLOW_VAL));
	return NULL;	
}
char *
test_getElementAt(){
	char constId[20] ="testType";
	char typeId[20] = "testType";
	
	double REAL_VAL = 123.321;
	struct ElementArray *ea = newElementArray();
	
	Symbol *typeSymbol = setUpTypeSymbol();
	Symbol *constSymbol = setUpConstSymbol();
	Symbol *sym;
	
	
	appendElement(ea,constSymbol);
	appendElement(ea,typeSymbol);
	

	sym = (Symbol *)getElementAt(ea,0);
	
	mu_assert("getElementAt(): The name of element at 0 pos is \
	'testConst'",strcmp(sym->name,constId) == 0);
	mu_assert("getElementAt(): The kind of the second symbol should be \
		  CONST_KIND", sym->kind == CONST_KIND);
	mu_assert("getElementAt(): The value of the second symbol should be \
		  INTHIGH_VAL ",sym->kindPtr.ConstKind->value.Real.value == REAL_VAL);
	
	
	sym = (Symbol *)getElementAt(ea,1);
	mu_assert("getElementAt(): The id of the second symbol should be \
		  'testType'",strcmp(sym->name,typeId)==0);
	mu_assert("getElementAt(): The kind of the second symbol should be \
		  TYPE_KIND",sym->kind == TYPE_KIND);
	mu_assert("getElementAt(): The value of the second symbol should be \
		  INTLOW_VAL ",sym->kindPtr.TypeKind->typePtr.Integer->value == INTLOW_VAL);
		
	
	return NULL;
	
}

char *
test_freeElementArray(){
	
	struct ElementArray *ea = newElementArray();
	
	Symbol *typeSymbol = setUpTypeSymbol();
	Symbol *constSymbol = setUpTypeSymbol();
	
	
	appendElement(ea,constSymbol);
	appendElement(ea,typeSymbol);

	freeElementArray(ea,SYMBOL_ELEMENT);
	
	mu_assert("freeElementArray() should free param array pointer witnout \
		  segfaulting", 1);
		  
	return NULL;
}

char *
test_all_ElementArray()
{
	mu_run_test(test_newElementArray);
	mu_run_test(test_growElementArray);
	mu_run_test(test_appendElement);
	mu_run_test(test_getElementAt);
	mu_run_test(test_freeElementArray);
	
	return NULL;
}