#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "filematch.h"
#include "hashtable.h"

int date_array = 0;
// initialized date_array to keep track of number of strings in **date

void file_read(FILE* csv){
    char c;
    int file_linesize = 0;
    int rows = file_rowcount(csv);
    int columns = file_columncount(csv);

    // This grabs the size in bytes of the first line of the csv file AND sets the reader pointer to the second line.
    while ((c = fgetc(csv)) != EOF){
        file_linesize++;
        if(c == '\n'){
            break;
        }
    }
    char *buffer = malloc(file_linesize);
    if (buffer == NULL){
        return;
    }
    char **date = malloc(sizeof(char*) * rows);
    if (date == NULL){
        return;
    }

    char **amount = malloc(sizeof(char*) * rows);
    if (amount == NULL){
        return;
    }

    for (int i = 0; i < rows; i++){
        date[i] = malloc(sizeof(char*) * columns);
        amount[i] = malloc(sizeof(char*) * columns);
    }

    

    
    file_dateparse(buffer, csv, date, amount, file_linesize);
    regextable_input(date, amount);

}



char **file_dateparse(char *buffer, FILE *csv, char **date, char **amount, int file_linesize){
    while(fgets(buffer, file_linesize, csv) != NULL){
        char *token_date = strtok(buffer, ",");
        char *token_amount = strtok(NULL, ",");
        printf("amount: %s\n", token_amount);
        // strtok returns a POINTER to a char * (i.e the address of buffer)
        // whenever buffer gets updated to the next line by fgets, strtok's POINTER return value points to the most up to date buffer token
        // i.e
        // buffer = "hi, hello"
        // strtoken("buffer", ",") returns a ->address of hi
        // if buffer gets set to = "hello, hi"
        // strtoken("buffer", ",") returns a ->addres of hello.
        // strtoken(NULL, ",") to extract the next token after the delimiter.
        date[date_array] = strdup(token_date);
        amount[date_array] = strdup(token_amount);
        printf("date %s\n", date[date_array]);
        date_array++;
    }
    return date;
}


int regextable_input(char **date, char **amount){
    regex_t regex;
    regmatch_t regex_match[3];
    // regmatch is used to extract out SUBEXPRESSIONS grouped i.e (...) in pattern
    printf("DATE ARRAY: %d\n", date_array);
    char *regex_pattern = "([[:digit:]]+)-(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Oct|Sep|Nov|Dec)";
    // surround [[:digit:]] in SUBEXPRESSIONS in order to be able to extract date and Mth
    // regex_match is an object which gives you access to .rm_so and .rm_eo
    // so and eo are basically the byte offset of the start of the string matched and the end of the string matched respectively.
    // essentially, the pointer positions (start/end) of the match within the inputted string.

    int regex_checker = regcomp(&regex, regex_pattern, REG_EXTENDED);
    // regex_checker returns 0 if regex engine compiles and returns an error code if it doesnt

    for (int i = 0; i < date_array; i++){
        regex_checker = regexec(&regex, date[i], 3, regex_match, REG_EXTENDED);
        if (regex_checker == 0){
            printf("matches\n");
        }

        float amountf = atof(amount[i]);
        // initialize matches and match_length only after regexec has been executed, if not there are no matches to reference!
        int match_monthstart = regex_match[2].rm_so;
        int match_monthend = regex_match[2].rm_eo;
        // regex_match has an array of 2 because there are only two subexpressions to be matched. ([2] contains the 2nd match (mth))
        size_t match_monthlength = match_monthend - match_monthstart;

        char *match_month = malloc(match_monthlength + 1);
        strncpy(match_month, date[i] + match_monthstart, match_monthlength);
        // test + match_m... = char *(pointer) + int = pointer arithmetic, it sets the pointer position to the first character of the match.
        match_month[match_monthlength] = '\0';
        // extracts the month subexpression (Jan|Feb|Mar...|Dec)

        int match_datestart = regex_match[1].rm_so;
        int match_dateend = regex_match[1].rm_eo;
        size_t match_datelength = match_dateend - match_datestart;

        char *match_date = malloc(match_datelength);
        strncpy(match_date, date[i] + match_datestart, match_datelength);
        match_date[match_datelength] = '\0';
        
        table_validate(match_date, match_month, amountf);
    }
    return regex_checker;
}

 char *regex_validate(char *test){
    regex_t regex;
    regmatch_t match[3];

    char *regex_pattern = "([[:digit:]])*(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Oct|Sep|Nov|Dec)";
    int regex_engine = regcomp(&regex, regex_pattern, REG_EXTENDED);

    regex_engine = regexec(&regex, test, 3, match, REG_EXTENDED);
    if (regex_engine == 0){
        printf("regex_engine: match found\n");
    }else{
        printf("regex_engine: no match");
        return "fail";
    }
    

    int matchstart = match[2].rm_so;
    int matchend = match[2].rm_eo;
    size_t match_length = matchend - matchstart;
    char *matched = malloc(match_length);
    strncpy(matched, test + matchstart, match_length);
    matched[match_length] = '\0';
    printf("matched string: %s\n", matched);

    return matched;
 }   

int regex_inputcheck(char userinput[10]){
    regex_t regex;
    
    int value;
    char *pattern = "(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Oct|Sep|Nov|Dec)";

    value = regcomp(&regex, pattern, REG_EXTENDED);

    value = regexec(&regex, userinput, 0, NULL, REG_EXTENDED);
    
    return value;
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