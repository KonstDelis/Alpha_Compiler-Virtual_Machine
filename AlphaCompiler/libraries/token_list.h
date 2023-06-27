#include <stdlib.h>
#include <stdio.h>

#ifndef TOKEN_LIST
#define TOKEN_LIST
struct alpha_token_t{
    char* token;
    int line;
    int number;
    char *category;
    char *subcategory;
    char *data_type;
    struct alpha_token_t* next;
};

struct alpha_token_t* insert_token(struct alpha_token_t*head, char* token,int line , int number, char*category, char*subcategory, char* data_type);

void free_token_list(struct alpha_token_t* head);

void token_list_print(struct alpha_token_t* head, FILE* stream);
#endif