#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"
#include "filematch.h"
//function headers

int main(){
    FILE *csv = fopen(CSVFILE, "r");
    table_initialize();
    file_read(csv);
}