#ifndef ACTION_STRUCT_STAT_H
#define ACTION_STRUCT_STAT_H

/*
 * Encountered 'continue' statement. Verify we're in a while loop and then
 * continue to next iteration.
 */
void continueLoop(void);


/*
 * Encountered 'exit' statement. Verify we're in a while loop and then
 * exit innermost loop.
 */
void exitLoop(void);


/*
 * End of while loop.
 */
void endWhileLoop(void);

/*
 * Confirm that exp is of boolean type.
 */
void ifPart(ProxySymbol *expr);

#endif
