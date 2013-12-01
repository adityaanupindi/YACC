/*
 * Module implementing functions generating asc code for 
 * procedures and functions.
 */
#ifndef EMITPROCS_H
#define EMITPROCS_H

#include <err.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../Error.h"
#include "../Definitions.h"
#include "../Kind.h"
#include "../StmtLL.h"
#include "../SymbolAPI.h"
#include "../Type.h"
#include "../ElementArray.h"
#include "../Hash.h"

#include "EmitUtils.h"

extern int doNotEmit;


/*
 * Emit code to push local procedure/function parameters onto the
 * the stack.
 *
 * Parameters: 	param: parameter symbol
 *				paramNum: the parameter's position number in the 
 *					parameter list.
 * 	
 * Returns: void
 */
void emitProcOrFuncDecl(Symbol *symbol, struct ElementArray *ea);


/*
 * Emit code to end a procedure.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitEndProc();


/*
 * Emit code to end a functions. 
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitEndFunc() ;


/*
 * Emit code to end a procedure/function. Adjusts for any local variables
 * and returns.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitProcOrFuncEndCommon(char *mgs);


/*
 * Creates a label for procedure/function. Label would have form
 * symbolName_currentStackNumber.
 *
 * I fully realize this function was coded as stupid...
 *
 * Parameters: symbol: procedure/function symbol to create label for.
 * 	
 * Returns: generated label
 */
char *createProcOrFunctionLabel(Symbol *symbol);

#endif
