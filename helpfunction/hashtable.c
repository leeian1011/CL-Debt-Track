#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

void open_file(){
    FILE *csv = fopen(CSVFILE, "r");
    if (csv == NULL){
        return;
    }
    //initialize a long variable to store bytes in csv file and set the file pointer back to the start
    /*long file_size;
    fseek(csv, 0L, SEEK_END);
    file_size = ftell(csv);
    rewind(csv);*/

    char c;
    int cols = 1;
    while ((c = fgetc(csv)) != EOF){
        if (c == ','){
            cols++; 
        }else if (c == '\n'){
            break;
        }    
    }
    rewind(csv);

    int rows = 1;
    while((c = fgetc(csv)) != EOF){
        if (c == '\n'){
            rows++;
        }
    }
    printf("%dcols and %drows\n", cols, rows);

    //char **file_content = malloc();
    //if(file_content == NULL){
    //    return;
    //}
    
    //char c;
    //int temp_count = 0;
    /*while ((c = (fgetc(csv))) != EOF){
        if (temp_count > file_size + 1){
            break;
        }
        file_content[temp_count] = c;
        temp_count++;
        
    }*/

    //printf("%c\n", file_content);

    //free(file_content);
    fclose(csv);
}