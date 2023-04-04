#ifndef FILEMATCH_H
#define FILEMATCH_H
#include <stdbool.h>

#define CSVFILE "file/data.csv"

void file_read(FILE *csv);
char **file_dateparse(char *buffer, FILE *csv, char **date, char **amount, int file_linesize);
char **file_amountparse(char *buffer, FILE *csv, char **amount, int file_linesize);
int file_columncount(FILE *csv);
int file_rowcount(FILE *csv);
int regextable_input(char **date, char **amount);
int regex_checkinput(char *userinput);
char *regex_validate(char *test);
bool file_insertinput(char *userinput, char* amount);

#endif