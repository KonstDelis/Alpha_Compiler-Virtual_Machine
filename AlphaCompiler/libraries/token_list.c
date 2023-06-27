#include "token_list.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

struct alpha_token_t* insert_token(struct alpha_token_t*head, char* token,int line , int number, char*category, char*subcategory, char* data_type){
    struct alpha_token_t*tmp=head;
    struct alpha_token_t* newNode=(struct alpha_token_t*)malloc(sizeof(struct alpha_token_t));
    if(newNode==NULL) {
        red();fprintf(stderr, "Error: cannot allocate memory for string value\n");reset();exit(2);
    }
    char* d_category = strdup(category);
    char* d_token = strdup(token);
    char* d_subcategory = strdup(subcategory);
    char* d_data_type = strdup(data_type);
    if(d_category==NULL || d_subcategory==NULL || d_data_type==NULL || d_data_type==NULL){
        free(newNode);
        red();fprintf(stderr, "Error: cannot allocate memory for string value\n");reset();
        exit(2);
    }
    newNode->token = d_token;
    newNode->line=line;
    newNode->number=number;
    newNode->category=d_category;
    newNode->subcategory=d_subcategory;
    newNode->data_type=d_data_type;
    newNode->next=NULL;
    if(head==NULL){
        return newNode;
    }
    while(tmp->next!=NULL){
      tmp=tmp->next;
    }
    tmp->next=newNode; 
    return head;
}

void free_token_list(struct alpha_token_t*head){
    struct alpha_token_t*tmp;
    while(head->next!=NULL){
        free(head->data_type);
        free(head->subcategory);
        free(head->category);
        free(head->token);
        tmp = head;
        head= head->next;
        free(tmp);
    }
}

void token_list_print(struct alpha_token_t* head, FILE* stream){
    fprintf(stream,"-----Lexical Analysis-----\n");
    while(head!=NULL){
        fprintf(stream,"%d: #%d \"%s\" %s %s <-- %s\n", head->line,head->number,head->token,head->category,head->subcategory, head->data_type);
        head=head->next;
    }
}
