#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdbool.h>

#define MAX 12


typedef struct node{
    float amount_paid;
    char date[sizeof(char*)];
    struct node *next_node;
}
node;

void table_initialize();
void table_validate(char *date, char *month, float amount);
void table_linklist(char *date, char*month, float amount, int month_index);
void table_matchseek(char *userinput);
char *table_traversal(char *userinput, int month_index);
float table_sum();
#endif