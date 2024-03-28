//
// Created by arsma on 3/28/2024.
//

#include "Column.h"
#include <stdio.h>

COLUMN *create_column(char* title){
    COLUMN* column = malloc(1*sizeof(COLUMN));
    if(!column)
        printf("Couldn't create column");

    for(int i = 0; i<NAME_SIZE && title[i]!='\0'; i++){
        column->_name[i] = title[i];
    }
    column->_values = NULL;
    column->_allocated_size = 0;
    column->_used_size = 0;

    return column;
}


void delete_column(COLUMN *col){
    free(col->_values);
    free(col);
}

void print_col(COLUMN* col){
    for(int i = 0; i<col->_used_size; i++){
        printf("[%d] %d", i, col->_values[i]);
    }
}
