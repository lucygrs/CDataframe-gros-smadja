//
// Created by arsma on 3/28/2024.
//

#include "Column.h"
#include <stdio.h>

COLUMN *create_column(char* title){
    COLUMN* column = malloc(1*sizeof(COLUMN));
    if(!column) {
        printf("Couldn't create column!\n");
        return column;
    }

    for(int i = 0; i<NAME_SIZE && title[i]!='\0'; i++){
        column->_name[i] = title[i];
    }
    column->_values = NULL;
    column->_allocated_size = 0;
    column->_used_size = 0;

    return column;
}


void delete_column(COLUMN *col){
    if(!col){
        printf("Invalid pointer!\n");
        return;
    }
    free(col->_values);
    free(col);
}

void print_col(COLUMN* col){
    if(!col){
        printf("Invalid pointer!\n");
        return;
    }
    printf("%s\n", col->_name);
    for(int i = 0; i<col->_used_size; i++){
        printf("[%d] %d\n", i, col->_values[i]);
    }
}

int insert_value(COLUMN* col, int value){
    if(!col){
        printf("Invalid pointer!\n");
        return 0;
    }

    if(col->_used_size < col->_allocated_size){
        col->_values[col->_used_size] = value;
        col->_used_size++;
        return 1;
    } else{
        printf("Not enough space\n");
        int reallocation = reallocate(col);
        if(reallocation) {
            if(insert_value(col, value) == 1)
                return 1;
            else
                return 0;
        }else{
            return 0;
        }
    }
}

int reallocate(COLUMN* col){
    printf("Reallocating... ");
    void * reallocation = realloc((void*)col->_values, (col->_allocated_size + REALOC_SIZE) * sizeof(int));
    if(reallocation) {
        col->_values = reallocation;
        col->_allocated_size+=REALOC_SIZE;
        printf("Reallocation successful\n");
        return 1;
    }
    else {
        printf("Reallocation failed\n");
        return 0;
    }
}

int occurences(COLUMN* col, int x){
    if(!col){
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    for(int i = 0; i<col->_used_size; i++){
        if(x==col->_values[i]) count++;
    }
    return count;
}

int value_at_index(COLUMN* col, int x){
    if(!col){
        printf("Invalid pointer!");
        return 0;
    }
    return col->_values[x];
}

int values_strictly_greater_than(COLUMN* col, int x){
    if(!col){
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    for(int i = 0; i<col->_used_size; i++){
        if(x<col->_values[i]) count++;
    }
    return count;
}

int values_strictly_lower_than(COLUMN* col, int x){
    if(!col){
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    for(int i = 0; i<col->_used_size; i++){
        if(x>col->_values[i]) count++;
    }
    return count;
}

int values_equal_to(COLUMN* col, int x){
    if(!col){
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    for(int i = 0; i<col->_used_size; i++){
        if(x==col->_values[i]) count++;
    }
    return count;
}















