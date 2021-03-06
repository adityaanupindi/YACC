#ifndef hash_H
#define hash_H


/* Macros and const string variable declarations. */
#define TABLE_SIZE 1000
#define LEXICAL_LEVELS 1024	

#if HASHDEBUG
	#define HASH_DEBUG 1
#else
	#define HASH_DEBUG 0
#endif

/* Global variables. */
struct hashElement {
	char *key;
	struct Symbol *symbol;
	struct hashElement *prev;
	struct hashElement *next;
};

struct hash {
	struct hashElement *elements[TABLE_SIZE];
	int offset[LEXICAL_LEVELS];
	unsigned int (*hashFunction)();
	int lexLevel;

};

/* Non-C99 compliant function prototypes. */

/* Function declarations. */
unsigned int getHashedKeySimple(char *string);
unsigned int getHashedKeyNormal(char *string);
int getSizeOfBucket(struct hash *hash, char *key);
int getHashIndex(struct hash *hash, char *key);
struct hashElement *getHashBucketHead(struct hash *hash, char *key);
int isKeyInBucket(struct hash *hash, char *key);
int isKeysIdentical(struct hashElement *element, char *key);
int isKeyCollison(struct hash *hash, char *key);
void freeHashElement(struct hashElement *element);
void deleteHashBucket(struct hashElement *current);
void destroyHash(struct hash **hashPtr);
int deleteHashElement(struct hash *hash, char *key);
struct hashElement *findHashElementByKey(struct hash *hash, char *key);
// struct hashElement *allocHashElement(char *key, int value);
struct hashElement *allocHashElement(char *key, struct Symbol *symbolPtr);
void appendToHashBucket(struct hashElement *bucketHead, struct hashElement *newElement);
// int createHashElement(struct hash *hash, char *key, int value);
int createHashElement(struct hash *hash, char *key, struct Symbol *symbolPtr);
struct hash *createHash(unsigned int (*hashFunction)(char *));
void dumpHash(struct hash *hash);
void setLexLevel(struct hash *hash, int lexLevel);
int getSymbolLexLevel(struct Symbol *symbol);
int getCurrentLexLevel(struct hash *hash);
int appendToSymbolList(struct hash *hash, struct hashElement *element, struct Symbol *symbol);
struct Symbol *findSymbolByLexLevel(struct hash *hash, char *key, int lexLevel);
struct Symbol *getLocalSymbol(struct hash *hash, char *key);
struct Symbol *getGlobalSymbol(struct hash *hash, char *key);
int getLengthOfSymbolList(struct hashElement *element);
int isOnlySymbolInList(struct hashElement *element, struct Symbol *symbol);
int deleteSymbolAtLexLevel(struct hash *hash, char *key, int lexLevel);
int popLexLevel(struct hash *hash);
int incrementLexLevel(struct hash *hash);
int decrementLexLevel(struct hash *hash);

/* 
 * Functions implementing functionality regarding offset getting and
 * incrementing.
 */

int getOffset(struct hash *hash);
void addToOffset(struct hash *hash, int toAdd);
void incrementOffset(struct hash *hash);
void resetOffset(struct hash *hash);


/* Gets the number of symbols at the current lexical level
 *
 * Parameters: 
 *
 * Return: count of local symbols
*/
int getLocalSymbolCount(struct hash *hash);	


/* Gets the number of symbols that have negative offsets.
 * i.e. parameters to function
 *
 * Parameters: 
 *
 * Return: count of function/procedure parameters
*/
int getLocalParamSymbolCount(struct hash *hash);


#endif
