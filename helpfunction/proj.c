#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "filematch.h"
//function headers

int main(){
    table_initialize();
    FILE *csv = fopen(CSVFILE, "r");
    file_read(csv);
    fclose(csv);
    printf("hi");
    table_sum();
}