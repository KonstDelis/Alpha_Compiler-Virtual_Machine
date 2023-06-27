#include "SymTable.h"
#include <string.h>
#include <stdio.h>
#include "utils.h"

extern int error_count;

/* Return a hash code for pcKey. */
static unsigned int SymTable_hash(const char *pcKey){
	size_t ui;
	unsigned int uiHash = 0U;
	for (ui = 0U; pcKey[ui] != '\0'; ui++)
		uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
	return uiHash%INITIAL_SIZE; /*return number between 0 and 509*/
}

/*Insert the library functions into hash table with scope and line equal to 0.*/
static void addLibraryFuncs(SymTable_T oSymTable){
    assert(oSymTable);

    SymTable_insert(oSymTable, "print", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "input", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "objectmemberkeys", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "objecttotalmembers", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "objectcopy", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "totalarguments", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "argument", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "typeof", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "strtonum", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "sqrt", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "cos", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "sin", NULL, LIBFUNC, 0, 0, programvar, 0);

    /*Extra library functions*/
    SymTable_insert(oSymTable, "real2int", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "objectmemberindices", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "objectmemberstrings", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "assert", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "pow", NULL, LIBFUNC, 0, 0, programvar, 0);
    SymTable_insert(oSymTable, "abs", NULL, LIBFUNC, 0, 0, programvar, 0);
}

/*Check if a symbol is library function. TRUE(1) is returned if it is library function else FALSE(0) is returned*/
int symbolIsLIBFUNC(char* name){
    if(strcmp(name, "print")==0 || 
    strcmp(name, "input")==0 || 
    strcmp(name, "objectmemberkeys")==0 || 
    strcmp(name, "objecttotalmembers")==0 ||
    strcmp(name, "objectcopy")==0 || 
    strcmp(name, "totalarguments")==0 || 
    strcmp(name, "argument")==0 || 
    strcmp(name, "typeof")==0 ||
    strcmp(name, "strtonum")==0 ||
    strcmp(name, "sqrt")==0 ||
    strcmp(name, "cos")==0 ||
    strcmp(name, "sin")==0 ||
    /*Extras*/
    strcmp(name, "real2int")==0 ||
    strcmp(name, "objectmemberindices")==0 ||
    strcmp(name, "objectmemberstrings")==0 ||
    strcmp(name, "assert")==0 ||
    strcmp(name, "pow")==0 ||
    strcmp(name, "abs")==0
    )
        return TRUE;
    return FALSE;
}

/*Allocates memory for a new Symbol Table and returns it.
It contains no bindings
*/
SymTable_T SymTable_new(void){
    SymTable_T oSymTable;
    SymbolTableEntry nullnode = NULL;

    int i;
    oSymTable = malloc(sizeof(struct SymTable));
    if (oSymTable == NULL) { /*Check if enough memory was allocated for SymTable*/
        printf("Failed to allocate memory for a new Symbol Table");
        exit(1);
    }
    nullnode = malloc(sizeof(struct SymbolTableEntry));
    if (nullnode == NULL) { /*Check if enough memory was allocated for a Node*/
        printf("Failed to allocate memory for a new Node");
        exit(1);
    }
    /*Initialize nullnode and add it to every array cell*/
    nullnode->s_type = NULLNODE;
   
    for (i = 0; i < INITIAL_SIZE; i++)
        oSymTable->hashTable[i] = nullnode; 
    oSymTable->nodeCount=0;

    oSymTable->scopeListsTable = malloc(sizeof(struct ScopeListReference_t*)*100);
    assert(oSymTable->scopeListsTable);
    oSymTable->max_scopes=99;
    for (i = 0; i < 100; i++)
        oSymTable->scopeListsTable[i] = NULL; 

    addLibraryFuncs(oSymTable);
    return oSymTable;
}
/*First checks if the max_scopes is less than the new reference scope.If so, it reallocates
the memory to be large enough to store references for the new max scope and set all new entries to NULL.Next allocate memory
for the newRef. */
int add_ref_to_scopeList(SymTable_T oSymTable, SymbolTableEntry ref){
    while(oSymTable->max_scopes<ref->scope){
        oSymTable->scopeListsTable = realloc(oSymTable->scopeListsTable, sizeof(struct ScopeListReference*)*((oSymTable->max_scopes+1) * 2));
        assert(oSymTable);
        for(int i = oSymTable->max_scopes+1; i<((oSymTable->max_scopes+1) * 2)-1; i++)
            oSymTable->scopeListsTable[i]=NULL;
        oSymTable->max_scopes = ((oSymTable->max_scopes+1) * 2)-1;
    }
    ScopeListReference newRef = malloc(sizeof(struct ScopeListReference_t));
    newRef->sym_entry_ref = ref;
    newRef->next = oSymTable->scopeListsTable[ref->scope];
    oSymTable->scopeListsTable[ref->scope] = newRef;
    return OK;
}

/*Deallocates all the memory that oSymTable has allocated.
If oSymTable is NULL the function returns without doing anything
*/
void SymTable_free(SymTable_T oSymTable){
    SymbolTableEntry current, next;
    int i=0;
    if(oSymTable==NULL) return;

    for(i=0; i<INITIAL_SIZE; i++){
        current = oSymTable->hashTable[i];
        while(current->next!=NULL){ /*Until we reach the nullnode*/
            free(current->name);
            next=current->next;
            free(current);
            current=next;
        }
    }

    for(i=0; i<oSymTable->max_scopes; i++){
        if(oSymTable->scopeListsTable[i]==NULL) continue;
        ScopeListReference curr = oSymTable->scopeListsTable[i], tmp;
        while(curr!=NULL){
            tmp = curr;
            curr=curr->next;
            free(tmp);
        }
    }
    free(oSymTable->scopeListsTable);
    free(current);
    free(oSymTable);
}

/* If no such binding exists then it is added to the symbol table using name as the key
and pcValue as the value and TRUE(1) is returned
If the binding already exists then the symbol table remains unchanged and FLASE(0) is returned
Checked runtime error if name or oSymTable are NULL
*/
SymbolTableEntry SymTable_insert(SymTable_T oSymTable, const char *name, const void *pvValue, enum SymbolType s_type, unsigned int lineno, unsigned int scope, enum scopespace_t space, unsigned int offset){
    SymbolTableEntry newNode, nextNode;
    assert(oSymTable);

    newNode = malloc(sizeof(struct SymbolTableEntry)); 
    if (newNode == NULL) { /*Check if memory for new Node was allocated*/
        fprintf(stderr,"Failed to allocate memory for a new Node");
        exit(1);
    }

    newNode->name = malloc(sizeof(char)*(strlen(name)+1));
    if (newNode->name == NULL) { /*Check if memory for new key in the new node was allocated*/
        fprintf(stderr,"Failed to allocate memory for a key in the new Node");
        exit(1);
    }
    newNode->active = TRUE;
    newNode->line = lineno;
    newNode->scope = scope;
    newNode->s_type = s_type;
    newNode->offset=offset;
    newNode->space = space;
    if(s_type==LIBFUNC)
        newNode->type = libraryfunc_s;
    else if(s_type == USERFUNC)
        newNode->type = programfunc_s;
    else
        newNode->type = var_s;
    strcpy(newNode->name, name);

    nextNode = oSymTable->hashTable[SymTable_hash(name)];
    newNode->next = nextNode;

    oSymTable->hashTable[SymTable_hash(name)]=newNode;

    oSymTable->nodeCount++;
    add_ref_to_scopeList(oSymTable, newNode);
    return newNode;
}

/*Change the activity (make it equal to FALSE(0)) of symbols with a specific scope*/
void hide_scope(SymTable_T oSymTable, unsigned int scope){
    assert(oSymTable);
    if(scope>=oSymTable->max_scopes)
    return;

    ScopeListReference current = oSymTable->scopeListsTable[scope];
    while(current != NULL){
        current->sym_entry_ref->active = FALSE;
        current = current->next;
    }
}

/* Checks if the binding exists in the Symbol Table in a specific scope
TRUE(1) is returned if it exists
else FALSE(0) is returned
Checked runtime error if oSymTable or name are NULL
*/
int SymEntry_exists(SymTable_T oSymTable, const char *name,unsigned int scope){
    SymbolTableEntry current;
    assert(oSymTable);
    current = oSymTable->hashTable[SymTable_hash(name)];
    while(current!=NULL){
        if (current->name != NULL && strcmp(current->name, name) == 0 && scope==current->scope)
            return TRUE;
        if(current->next==NULL) break; /*Reached the nullnode*/
        current = current->next;
    }
    return FALSE;
}

/*Check if a symbol is defined. TRUE(1) is returned if it exists else FALSE(0) is returned*/
int symbolIsDefined(SymTable_T oSymTable, char* name){
    SymbolTableEntry current;
    assert(oSymTable);

    current = oSymTable->hashTable[SymTable_hash(name)];
    while(current!=NULL){
        if (current->name != NULL && strcmp(current->name, name) == 0 && current->active)
            return TRUE;
        if(current->next==NULL) break; /*Reached the nullnode*/
            current = current->next;
    }
    return FALSE;
}

/*Check a symbol using name as a key return OK if symbol is not defined and is called else return different types of error 
based on current situation.*/
int checkSymbolName(SymTable_T oSymTable, char* name, unsigned int scope, enum SymbolType* type, int is_call){
    SymbolTableEntry rt;
    assert(oSymTable);
    assert(type!=ALL_TYPES);
    if(!is_call && symbolIsLIBFUNC(name)) return LIBFUNC_NAME_ERR;

    if(!symbolIsDefined(oSymTable, name) && is_call)
        return OK;

    enum SymbolType stype;
    if(*type==LOCAL || *type==FORMAL){
        stype=USERFUNC;
        rt = SymTable_lookup(oSymTable, name, scope, &stype);
        if(rt!=NULL) return SAME_SCOPE_FUNC_VAR;
    }
    if(*type==FORMAL){
        stype=FORMAL;
        rt = SymTable_lookup(oSymTable, name, scope, &stype);
        if(rt!=NULL) return DOUBLE_FORMAL_ERR;
    }
    if(!is_call && *type==USERFUNC){
        stype=LOCAL;
        rt = SymTable_lookup(oSymTable, name, scope, &stype);
        if(rt!=NULL) return SAME_SCOPE_FUNC_VAR;

        stype=GLOBAL;
        rt = SymTable_lookup(oSymTable, name, scope, &stype);
        if(rt!=NULL) return SAME_SCOPE_FUNC_VAR;

        stype=FORMAL;
        rt = SymTable_lookup(oSymTable, name, scope, &stype);
        if(rt!=NULL) return SAME_SCOPE_FUNC_VAR;

        stype=USERFUNC;
        rt = SymTable_lookup(oSymTable, name, scope, &stype);
        if(rt!=NULL) return SAME_FUNCNAME_SCOPE_ERR;
    }

    return OK;
}

/*Looking into hashtable for a symbol with a specific name and scope.
If the symbol exists then return the symbol else return NULL.*/
SymbolTableEntry SymTable_lookup(SymTable_T oSymTable, const char *name, unsigned int scope, enum SymbolType* type){
    SymbolTableEntry current;
    assert(oSymTable);

    current = oSymTable->hashTable[SymTable_hash(name)];
    while(current!=NULL){
        if (current->name != NULL && strcmp(current->name, name) == 0 && scope==current->scope && current->active==TRUE)
            if((type==ALL_TYPES)||(*type==current->s_type))
                return current;
        if(current->next==NULL) break; /*Reached the nullnode*/
            current = current->next;
    }
    return NULL;
}

/* lookup in hash table for a symbol using name as a key and scope equal to all scopes except global and current.
If the symbol exists then return the symbol else return NULL.*/
SymbolTableEntry SymTable_lookupall(SymTable_T oSymTable, const char *name, unsigned int scope, unsigned int outer_scope, unsigned int lineno){
    SymbolTableEntry rt;
    assert(oSymTable);
    if(scope==0) return NULL;
    scope--;
    while(scope > 0){
        rt = SymTable_lookup(oSymTable,name,scope,ALL_TYPES);
        if(rt != NULL && (rt->s_type==USERFUNC || rt->scope>outer_scope)){
            return rt;
        }
        if(rt != NULL && rt->scope<=outer_scope){
            red();
            error_count++;
            fprintf(stderr, "Error: line %d: variable '%s' is not accessible\n", lineno, name);
            reset();
            return rt;
        }
        scope--;
    }
    return NULL;
}

/*print a specific scope of the hash table.*/
static void print_scope(ScopeListReference current){
    if(current!=NULL) print_scope(current->next);
    if(current==NULL) return;
    printf("\"%s\" ",current->sym_entry_ref->name);
    switch (current->sym_entry_ref->s_type)
    {
    case GLOBAL:
        printf("[global variable]");
        break;
    case LOCAL:
        printf("[local variable]");
        break;
    case FORMAL:
        printf("[formal argument]");
        break;
    case USERFUNC:
        printf("[user function]");
        break;
    case LIBFUNC:
        printf("[library function]");
        break;
    
    default:
        fprintf(stderr, "Error: unexpected error line %d\n", __LINE__);
        break;
    }
    printf(" (line %d) (scope %d)  || offset %d\n",current->sym_entry_ref->line, current->sym_entry_ref->scope, current->sym_entry_ref->offset);
    current = current->next;
}

/*print all scope lists*/
void print_scope_lists(SymTable_T oSymTable){
    printf("\n");
    for(int i = 0; i<oSymTable->max_scopes; i++){
        if(oSymTable->scopeListsTable[i]==NULL) continue;
        ScopeListReference current = oSymTable->scopeListsTable[i];
        printf("-----------     Scope #%d     -----------\n",i);
        print_scope(oSymTable->scopeListsTable[i]);
        printf("\n");
    }

}
