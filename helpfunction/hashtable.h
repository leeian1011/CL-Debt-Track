#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAX 10

typedef struct node{
    float amount_paid;
    char *date;
    struct node *next_node;
}
node;

void print(char *x);
#endif