#include "stdlib.h"
#include "assert.h"
#ifndef SYM_TABLE_H
#define SYM_TABLE_H

#define FALSE 0
#define TRUE 1
#define OK 2
#define HASH_MULTIPLIER 65599
#define INITIAL_SIZE 1024


#define ALL_TYPES NULL
#define GLOBAL_SCOPE 0

#define SAME_FUNCNAME_SCOPE_ERR 500
#define LIBFUNC_NAME_ERR 501
#define SAME_SCOPE_FUNC_VAR 502
#define DOUBLE_FORMAL_ERR 503
#define CALL_UNDEFINED_FUNC 504
#define UNDEFINED_SYMBOL_ERR 505

enum SymbolType{GLOBAL,LOCAL,FORMAL,USERFUNC,LIBFUNC,NULLNODE};

enum symbol_t {var_s, programfunc_s, libraryfunc_s};

enum scopespace_t {programvar, functionlocal, formalarg};

/*The table will be a list of these nodes*/
typedef struct SymbolTableEntry{
    int active;
    enum scopespace_t space;
    enum symbol_t type;
    enum SymbolType s_type;
    char*name;
    unsigned int scope;
    unsigned int offset;
    unsigned int line;
    unsigned int totalScopeOffset;
    unsigned int iaddress;
    struct SymbolTableEntry *next;
} *SymbolTableEntry;

typedef struct ScopeListReference_t{
    struct SymbolTableEntry* sym_entry_ref;
    struct ScopeListReference_t* next;
} *ScopeListReference;

/*Symbol Table struct*/
typedef struct SymTable{
    unsigned int nodeCount;
    SymbolTableEntry hashTable[INITIAL_SIZE];
    struct ScopeListReference_t** scopeListsTable;
    unsigned int max_scopes;
} *SymTable_T;

/*Allocates memory for a new Symbol Table and returns it.
It contains no bindings
*/
SymTable_T SymTable_new(void);

/*Deallocates all the memory that oSymTable has allocated.
If oSymTable is NULL the function returns without doing anything
*/
void SymTable_free(SymTable_T oSymTable);

/*Returns the length(number of bindings) of the SymbolTable.
*/
unsigned int SymTable_getLength(SymTable_T oSymTable);

/* If no such binding exists then it is added to the symbol table using name as the key
and pcValue as the value and TRUE(1) is returned
If the binding already exists then the symbol table remains unchanged and FLASE(0) is returned
Checked runtime error if name or oSymTable are NULL
*/
SymbolTableEntry SymTable_insert(SymTable_T oSymTable, const char *name, const void *pvValue,enum SymbolType s_type, unsigned int lineno, unsigned int scope, enum scopespace_t space, unsigned int offset);

/*Check if a symbol is defined. TRUE(1) is returned if it exists else FALSE(0) is returned*/
int symbolIsDefined(SymTable_T oSymTable, char* name);

/*Change the activity (make it equal to FALSE(0)) of symbols with a specific scope*/
void hide_scope(SymTable_T oSymTable, unsigned int scope);

/* Checks if the binding exists in the Symbol Table
TRUE(1) is returned if it exists
else FALSE(0) is returned
Checked runtime error if oSymTable or name are NULL
*/
int SymEntry_exists(SymTable_T oSymTable, const char *name,unsigned int scope);

/*Check a symbol using name as a key return OK if symbol is not defined and is called else return different types of error 
based on current situation.*/
int checkSymbolName(SymTable_T oSymTable, char* name, unsigned int scope, enum SymbolType* type, int is_call);

/*Looking into hashtable for a symbol with a specific name and scope.
If the symbol exists then return the symbol else return NULL.*/
SymbolTableEntry SymTable_lookup(SymTable_T oSymTable, const char *name, unsigned int scope, enum SymbolType* type);

/* lookup in hash table for a symbol using name as a key and scope equal to all scopes except global and current.
If the symbol exists then return the symbol else return NULL*/
SymbolTableEntry SymTable_lookupall(SymTable_T oSymTable, const char *name,unsigned int scope, unsigned int outer_scope, unsigned int lineno);

/*print the scope lists*/
void print_scope_lists(SymTable_T oSymTable);
#endif