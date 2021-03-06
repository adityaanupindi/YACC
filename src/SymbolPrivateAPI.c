#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ElementArray.h"
#include "Error.h"
#include "ErrorLL.h"
#include "Type.h"
#include "Hash.h"
#include "PreDef.h"
#include "SymbolAll.h"



/* Set the name of the passed symbol
 *
 * Parameters:
 * 		s: symbol to be named
 *		id: name of symbole
 *
 * Return: void
 */
void setSymbolName(Symbol *s, char *id) {
	size_t len;
	
	if (id == NULL) {
		s->name = NULL;
		return;
	}
	
	len = strlen(id) + 1;
	s->name = calloc(1, sizeof(char)*len);
	if (!s->name) {
		err(1, "Failed to allocate memory for symbol name!");
		exit(EXIT_FAILURE);
	}
	
	strncpy(s->name, id, len - 1);
}


/* Creates a new symbol. Auto-determines all substructures
 * based on the parameter kind.
 *
 * Does not insert into the symbol table, use createAndInsertSymbol for that.
 *
 * Parameters:
 * 		table: the symbol table from which to get lexical level
 *              id: name of symbol
 *		kind: kind of symbol. Comes from kind_t enum
 *		typeOriginator: flag for if type originator 
 *
 * Return: Newly created symbol.
 */
Symbol *createSymbol(
    struct hash *table, char *id, kind_t kind, int typeOriginator)
{
	Symbol *symbol = allocateSymbol();

	if (symbol == NULL) {
		err(1, "Could not create new symbol.");
		exit(EXIT_FAILURE);			
	}

	// set symbol independent values
	setSymbolName(symbol, id);
	

	symbol->kind = kind;
	allocateKindPtr(symbol);

	symbol->lvl = getCurrentLexLevel(table);
	symbol->typeOriginator = typeOriginator;
	symbol->isRecordHead = 0;
	symbol->next = NULL;

	return symbol;
}


/* Allocates memeory for a struct symbol and only a struct symbol.
 *
 * Parameters:
 *
 * Return: Pointer to newly allocated memory chunk
 */
Symbol *allocateSymbol() {
	Symbol *symbol = NULL;

	symbol = calloc(1, sizeof(Symbol));
	if ( symbol == NULL ) {
		err(1, "Could not alloc memory for symbol.");
		exit(EXIT_FAILURE);		
	}

	return symbol;
}


/*
 * Sets the size (i.e., the number of ASC memory units occupied by) the given
 * symbol.  In appropriate cases, it calculates the size of the given symbol
 * and then correctly sets the value.
 * Parameters:
 *		s: the symbol whose size is to be set
 */
void setSymbolSize(Symbol *s)
{
	if (!s) return;
	if (!getTypeSym(s)) return;
	switch (s->kind) {
	case CONST_KIND:
		if (getType(s) == SCALAR_T) s->size = 1;
		else s->size = getTypeSym(s)->size;
		break;
	case PARAM_KIND:
		/* fall through */
	case VAR_KIND:
		if (getType(s) == SCALAR_T) s->size = 1;
		else s->size = getTypeSym(s)->size;
		break;
	case PROC_KIND:
		/* fall through */
	case FUNC_KIND:
		/* Procs and Func symbols have no size */
		s->size = -1;
		break;
	case TYPE_KIND:
	{
		/* We do not set the size for record types as at this point
		 * we have lost the information we need to do so correctly */
		if (getType(s) != RECORD_T) s->size = calculateSymbolSize(s);
		break;
	}
	default:
		/* NOT REACHED */
		break;  
	}
}

