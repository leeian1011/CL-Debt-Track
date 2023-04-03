#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "filematch.h"
//function headers
int addfunct();

int main(){
    FILE *csv = fopen(CSVFILE, "r");
    char *operations[] = {"Add", "Remove", "Remainder", "Find", "Exit"};
    char *query = malloc(10);

    table_initialize();
    file_read(csv);
    fclose(csv);
    do{
        printf("Select an Operation:\n1:Add\n2:Remove\n3:Remainder\n4:Find\n5:Exit\n");
        fgets(query, 10, stdin);
        query[strlen(query) - 1]  = '\0';

        if (strcasecmp(query, operations[0]) == 0 || query[0] == '1'){
            addfunct();
            return 0;
        }
        else if (strcasecmp(query, operations[1]) == 0 || query[0] == '2'){
            //removefunct();
            return 1;
        }
        else if (strcasecmp(query, operations[2]) == 0 || query[0] == '3'){
            //remainderfunct();
            return 2;
        }
        else if (strcasecmp(query, operations[3]) == 0 || query[0] == '4'){
            //findfunct();
            return 3;
        }
        else if(strcasecmp(query, operations[4]) == 0 || query[0] == '5'){
            return 0;
        }
        else{
            printf("%s is not an operation!", query);
        }
    } while (query[0] == '\0');
}

int addfunct(){
    char *date = malloc(sizeof(char*));
    char *amount = malloc(sizeof(char*));
    do{
        printf("Input Date:");
        fgets(date, sizeof(char*), stdin);
        date[strlen(date) - 1] = '\0';  
    }while(date[0] == '\0' || regex_checkinput(date) != 0);
    do{
        printf("Input amount repaid:");
        fgets(amount, sizeof(char*), stdin);
        amount[strlen(amount) - 1] = '\0';
    }while(date[0] == '\0');
    table_insertinput(date, amount);
    return 0;
}
