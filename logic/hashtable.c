#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "filematch.h"
#include "hashtable.h"

const char *MONTHS[] = {"Jan", "Feb", "Mar",
                      "Apr", "May", "Jun", 
                      "Jul", "Aug", "Sep", 
                      "Oct", "Nov", "Dec"};

node *TABLE[MAX];

void table_initialize(){
    for (int i = 0; i < MAX; i++){
        TABLE[i] = NULL;
    }
}



void table_validate(char *date, char *month, float amount){
    for (int i = 0; i < MAX; i++){
        if(strcmp(month, MONTHS[i]) == 0){
            table_linklist(date, month, amount, i);
            break;
        }
    }
}



void table_linklist(char *date, char *month, float amount, int month_index){
    char datemonth[10] = "";
    strcat(datemonth, date);
    strcat(datemonth, month);
    node *newnode = malloc(sizeof(node));
    newnode->amount_paid = amount;
    strcpy(newnode->date, datemonth);
    newnode->next_node = TABLE[month_index];
    TABLE[month_index] = newnode;
}

void table_matchseek(char *test){
    char *matched_month = regex_validate(test);

    for (int i = 0; i < MAX; i++){
        if (strcmp(matched_month, MONTHS[i]) == 0){
            table_traversal(test, i);
            break;
        }
    }
}

char *table_traversal(char *test, int month_index){
    int trigger = 0;
    
    node *table_seeker = TABLE[month_index];
    while(trigger == 0){
        if (table_seeker == NULL){
            printf("End of entries\n");
            return "failed";
        }

        if (strcmp(table_seeker->date, test) != 0){
            table_seeker = table_seeker->next_node;
            if (table_seeker == NULL){
                printf("End of entries\n");
                return "table_seeker does not exist";
            }
            continue;
        }else if (strcmp(table_seeker->date, test) == 0){
            printf("Repaid on %s: $%.2f\n", table_seeker->date, table_seeker->amount_paid);
            table_seeker = table_seeker->next_node;
            continue;
        }
    }
    return table_seeker->date;
}

float table_sum(){
    float sum = 0.0;
    for(int i = 0; i < MAX; i++){
        int trigger = 0;
        node *table_seeker = TABLE[i];
        if(table_seeker == NULL){
            continue;
        }
            while (trigger == 0){
            sum += table_seeker->amount_paid;
            if (table_seeker->next_node == NULL){
                trigger = 1;
            }
            table_seeker = table_seeker->next_node;
        }
    }
    return sum;
}