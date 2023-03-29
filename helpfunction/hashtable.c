#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filematch.h"
#include "hashtable.h"

const char *MONTHS[] = {"Jan", "Feb", "Mar",
                      "Apr", "May", "Jun", 
                      "Jul", "Aug", "Sep", 
                      "Oct", "Nov", "Dec"};

node *TABLE[MAX];

void table_initialize(){
    for (int i = 0; i < MAX; i++){
        TABLE[i] = malloc(sizeof(node));
    }
}

void table_validate(char *date, char *month){
    for (int i = 0; i < MAX; i++){
        if(strcmp(month, MONTHS[i]) == 0){
            table_linklist(date, month, i);
            printf("LINK LIST NUMBER :%d", i);
            break;
        }
    }
}

void table_linklist(char *date, char *month, int month_index){
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL){
        return;
    }
    // -> == (*ptr).x where you have to state that the structure is actually a pointer!

    newnode->amount_paid = 100.50;
    strcpy(newnode->date, month);
    newnode->next_node = TABLE[month_index]->next_node;
    TABLE[month_index]->next_node = newnode;

    printf("%s and %s\n", date, TABLE[month_index]->next_node->date);
}
