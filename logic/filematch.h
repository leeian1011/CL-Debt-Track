#ifndef FILEMATCH_H
#define FILEMATCH_H
#include <stdbool.h>

#define CSVFILE "file/data.csv"
#define DEBTFILE "file/debt.csv"

//file related functions
char *debtfile_grab();
void file_read(FILE *csv);
void file_skipline(FILE *csv, int linesize);
char **file_dateparse(char *buffer, FILE *csv, char **date, char **amount, int file_linesize);
char **file_amountparse(char *buffer, FILE *csv, char **amount, int file_linesize);
int file_columncount(FILE *csv);
int file_rowcount(FILE *csv);
int file_linesize(FILE *csv);
bool file_insertinput(char *userinput, char* amount);
bool file_removedate(char *userinput);

//regex input&reading functions
int regextable_input(char **date, char **amount);
int regex_checkinput(char *userinput);
char *regex_validate(char *test);

#endif