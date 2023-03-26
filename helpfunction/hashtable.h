#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdbool.h>

#define MAX 50

//Create a node structure to use in linked lists.
typedef struct node{
    float amount_repaid;
    char *date;
    struct node *next_node;
}
node;

void test(void);
int tabulate(void);
#endif