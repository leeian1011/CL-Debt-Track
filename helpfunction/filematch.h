#ifndef FILEMATCH_H
#define FILEMATCH_H

#define CSVFILE "file/test.csv"

void file_read(FILE *csv);
char **file_dateparse(char *buffer, FILE *csv, char **date, int file_linesize);
int file_columncount(FILE *csv);
int file_rowcount(FILE *csv);
int regex_match(char **test);
#endif