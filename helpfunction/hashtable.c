#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"


void file_read(FILE* csv){
    char c;
    int count = 0;
    int rows = file_rowcount(csv);
    int columns = file_columncount(csv);

    while ((c = fgetc(csv)) != EOF){
        count++;
        if(c == '\n'){
            break;
        }
    }

    char *buffer = malloc(count);
    if (buffer == NULL){
        return;
    }
    char **date = malloc(sizeof(char*) * rows);
    if (date == NULL){
        return;
    }

    for(int i = 0; i < rows; i++){
        date[i] = malloc(sizeof(char*) * columns);
        if (date[i] == NULL){
            return;
        }
    }

    int whileloopcount = 0;
    while(fgets(buffer, count, csv) != NULL){
        char *test = strtok(buffer, ",");
        //strtok returns a POINTER to a char * (i.e the address of buffer)
        //whenever buffer gets updated to the next line by fgets, strtok's POINTER return value points to the most up to date buffer token
        //i.e
        //buffer = "hi, hello"
        // strtoken("buffer", ",") returns a ->address of hi
        // if buffer gets set to = "hello, hi"
        // strtoken("buffer", ",") returns a ->addres of hello.
        
        date[whileloopcount] = strdup(test);
        whileloopcount++;
    }

    printf("\n%s\n", date[0]);
    for (int i = 0; i < 4; i++){
        free(date[i]);
    }
    free(buffer);
}



int file_rowcount(FILE *csv){
    int count = 0;
    char c;
    while ((c = fgetc(csv)) != EOF){
        if (c == '\n'){
            count++;
        }
    }
    rewind(csv);
    return count;
}


int file_columncount(FILE *csv){
    int count = 0;
    char c;
    while ((c = fgetc(csv)) != EOF){
        if (c == ','){
            count++;
        }
        else if( c == '\n'){
            rewind(csv);
            return count;
        }
    }
    return count;
}