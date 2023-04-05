#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "hashtable.h"
#include "filematch.h"


//function headers
void selector(int operator);
int addfunct();
int findfunct();
bool amount_check(char *amount);
bool removefunct();


int main(){
    FILE *csv = fopen(CSVFILE, "r");
    if (csv == NULL){
        return 1;
    }
    char *operations[] = {"Add",
                          "Remove",
                          "Find",
                          "Update",
                          "Exit"};
    const int operation_count = 5;

    char *query = malloc(10);
    
    float debt = atof(debtfile_grab());
    table_initialize();
    file_read(csv);
    fclose(csv);
    do{
        printf("DEBT: $%.2f\n", debt);
        printf("REPAID: $%.2f\n", table_sum());
        if (debt <= table_sum()){
            printf("You've cleared off your debts!");
        }else{
        printf("REMAINDER: %.2f\n", debt - table_sum());
        }
        printf("Select an Operation:\n1:Add entry\n2:Remove entry\n3:Find entries\n4:Update debt\n5:Exit\n");
        fgets(query, 10, stdin);
        query[strlen(query) - 1]  = '\0';
        int checkformatch = 0;
        for(int i = 1; i < operation_count; i++){
            char placeholder = i + '0';
            if(strcasecmp(query, operations[i - 1]) == 0 || query[0] == placeholder){
                selector(i);
                break;
            } 
            checkformatch++;
        }
        if (checkformatch == operation_count){
            printf("%s is not a valid operation!\n", query);
            main();
        }
        } while (query[0] == '\0');
    free(query);
}


void selector(int operator){
    switch (operator){
        case 1:
            addfunct();
            break;
        case 2: 
            removefunct();
            break;
        case 3: 
            findfunct();
            break;
        case 4:
            break;
            
        default:
            break;
    }
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
    }while(date[0] == '\0' || !amount_check(amount));
    if(file_insertinput(date, amount)){
        printf("Succesfully Added!");
    }
    return 0;
}


int findfunct(){
    char *input = malloc(sizeof(char*));
    do{
        printf("Input date:");
        fgets(input, sizeof(char*), stdin);
        input[strlen(input) - 1] = '\0';
    }while(input[0] == '\0' || regex_checkinput(input) != 0);
    
    table_matchseek(input);
    return 0;
}


bool removefunct(){
    char *input = malloc(sizeof(char*));
    do{
        printf("Input date to remove:");
        fgets(input, sizeof(char*), stdin);
        input[strlen(input) - 1] = '\0';
    }while(input[0] == '\0' || regex_checkinput(input) != 0);

    file_removedate(input);
    free(input);
    return true;
}


bool amount_check(char *amount){
    int count = strlen(amount);

    for (int i = 0; i < count; i++){
        if(!isdigit(*amount)){
            return false;
        }
    }
    return true;
}
