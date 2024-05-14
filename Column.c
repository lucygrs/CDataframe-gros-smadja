//
// Created by arsma on 3/28/2024.
//

#include "Column.h"
#include <stdio.h>
#include <string.h>

COLUMN *create_column(ENUM_TYPE type, char* title){
    COLUMN* column = malloc(1*sizeof(COLUMN));
    if(!column) {
        printf("Couldn't create column!\n");
        return column;
    }

    for(int i = 0; i<NAME_SIZE && title[i]!='\0'; i++){
        column->_name[i] = title[i];
    }
    switch(type){
        case NULLVAL:
            printf("Invalid column type!\n");
        case UINT:
            column->_values = (unsigned int*)0;
        case INT:
            column->_values = (int*)0;
        case CHAR:
            column->_values = (char*)0;
        case FLOAT:
            column->_values = (float*)0;
        case DOUBLE:
            column->_values = (double*)0;
        case STRING:
            column->_values = (char**)0;
    }
    column->_values = NULL;
    column->_allocated_size = 0;
    column->_used_size = 0;
    column->_column_type = type;

    printf("Allocating... ");
    COL_TYPE * allocation = malloc((REALOC_SIZE) * sizeof(COL_TYPE));
    if(allocation) {
        column->_values = allocation;
        column->_allocated_size+=REALOC_SIZE;
        printf("Allocation successful\n");
    }
    else {
        printf("Allocation failed\n");
    }

    return column;
}

int get_alloc_size(ENUM_TYPE type){
    return sizeof(ENUM_TYPE);
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
    switch(col->_column_type){
        case NULLVAL:
            printf("Invalid column type!");
            return;
        case INT:
            for(int i = 0; i<col->_used_size; i++){
                printf("[%d] %d\n", i, col->_values[i]);
            }
            return;
        case UINT:
            for(int i = 0; i<col->_used_size; i++){
                printf("[%d] %d\n", i, col->_values[i]);
            }
            return;
        case CHAR:
            for(int i = 0; i<col->_used_size; i++){
                printf("[%d] %c\n", i, col->_values[i]);
            }
            return;
        case FLOAT:
            for(int i = 0; i<col->_used_size; i++){
                printf("[%d] %.2f\n", i, col->_values[i]);
            }
            return;
        case DOUBLE:
            for(int i = 0; i<col->_used_size; i++){
                printf("[%d] %.4f\n", i, col->_values[i]);
            }
            return;
        case STRING:
            for(int i = 0; i<col->_used_size; i++){
                printf("[%d] %s\n", i, col->_values[i]);
            }
            return;

    }
}

int insert_value(COLUMN* col, COL_TYPE value){
    if(!col){
        printf("Invalid pointer!\n");
        return 0;
    }

    if(col->_used_size < col->_allocated_size){
        col->_values[col->_used_size] = value;
        col->_used_size++;
        return 1;
    } else {
        printf("Not enough space\n");
        int reallocation = reallocate(col);
        if(reallocation) {
            insert_value(col, value);
        }else{
            return 0;
        }
    }
}

int reallocate(COLUMN* col){
    printf("Reallocating.... ");
    void * reallocation = malloc((col->_allocated_size+REALOC_SIZE)*sizeof(COL_TYPE));
    if(reallocation) {
        memcpy(reallocation, col->_values, (col->_allocated_size) * get_alloc_size(col->_column_type));
        free(col->_values);
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

int occurences(COLUMN* col, void* x){
    if(!col){
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    switch(col->_column_type){
        case NULLVAL:
            printf("Invalid type!");
            return 0;
        case INT:
            for(int i = 0; i<col->_used_size; i++){
                if(*((int*)x) == *(int*)(&col->_values[i])){
                    count++;
                }
            }
            return count;
        case FLOAT:
            for(int i = 0; i<col->_used_size; i++){
                if(*((float *)x) == *(float *)(&col->_values[i])){
                    count++;
                }
            }
            return count;
        case UINT:
            for(int i = 0; i<col->_used_size; i++){
                if(*((unsigned int*)x) == *(unsigned int*)(&col->_values[i])){
                    count++;
                }
            }
            return count;
        case CHAR:
            for(int i = 0; i<col->_used_size; i++){
                if(*((char*)x) == *(char*)(&col->_values[i])){
                    count++;
                }
            }
            return count;
        case DOUBLE:
            for(int i = 0; i<col->_used_size; i++){
                if(*((double*)x) == *(double*)(&col->_values[i])){
                    count++;
                }
            }
            return count;
        case STRING:
            for(int i = 0; i<col->_used_size; i++){
                if(strcmp(*(char**)(&col->_values[i]), x) == 0){
                    count++;
                }
            }
            return count;
    }
    return count;
}

COL_TYPE value_at_index(COLUMN* col, int x){
    if(!col){
        printf("Invalid pointer!");
        return (COL_TYPE)0;
    }
    return col->_values[x];
}

int values_strictly_greater_than(COLUMN* col, COL_TYPE x){
    if(!col){
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    switch(col->_column_type){
        case NULLVAL:
            printf("Invalid column type!\n");
            return count;
        case UINT:
            for(int i = 0; i<col->_used_size; i++){
                if(*(unsigned int*)(&x)<*(unsigned int*)(&(col->_values[i]))) count++;
            }
            return count;
        case INT:
            for(int i = 0; i<col->_used_size; i++){
                if(*(int*)(&x)<*(int*)(&(col->_values[i]))) count++;
            }
            return count;
        case CHAR:
            for(int i = 0; i<col->_used_size; i++){
                if(*(char*)(&x)<*(char*)(&(col->_values[i]))) count++;
            }
            return count;
        case FLOAT:
            for(int i = 0; i<col->_used_size; i++){
                if(*(float*)(&x)<*(float*)(&(col->_values[i]))) count++;
            }
            return count;
        case DOUBLE:
            for(int i = 0; i<col->_used_size; i++){
                if(*(double*)(&x)<*(double*)(&(col->_values[i]))) count++;
            }
            return count;
        case STRING:
            for(int i = 0; i<col->_used_size; i++){
                if(strcmp((&x), &(col->_values[i])) < 0) count++;
            }
            return count;
    }
}

int values_strictly_lower_than(COLUMN* col, COL_TYPE x){
    if(!col){
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    switch(col->_column_type){
        case NULLVAL:
            printf("Invalid column type!\n");
            return count;
        case UINT:
            for(int i = 0; i<col->_used_size; i++){
                if(*(unsigned int*)(&x)>*(unsigned int*)(&(col->_values[i]))) count++;
            }
            return count;
        case INT:
            for(int i = 0; i<col->_used_size; i++){
                if(*(int*)(&x)>*(int*)(&(col->_values[i]))) count++;
            }
            return count;
        case CHAR:
            for(int i = 0; i<col->_used_size; i++){
                if(*(char*)(&x)>*(char*)(&(col->_values[i]))) count++;
            }
            return count;
        case FLOAT:
            for(int i = 0; i<col->_used_size; i++){
                if(*(float*)(&x)>*(float*)(&(col->_values[i]))) count++;
            }
            return count;
        case DOUBLE:
            for(int i = 0; i<col->_used_size; i++){
                if(*(double*)(&x)>*(double*)(&(col->_values[i]))) count++;
            }
            return count;
        case STRING:
            for(int i = 0; i<col->_used_size; i++){
                if(strcmp((&x), &(col->_values[i])) > 0) count++;
            }
            return count;
    }
}

int values_equal_to(COLUMN* col, COL_TYPE x){
    if(!col){
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    switch(col->_column_type){
        case NULLVAL:
            printf("Invalid column type!\n");
            return count;
        case UINT:
            for(int i = 0; i<col->_used_size; i++){
                if(*(unsigned int*)(&x)==*(unsigned int*)(&(col->_values[i]))) count++;
            }
            return count;
        case INT:
            for(int i = 0; i<col->_used_size; i++){
                if(*(int*)(&x)==*(int*)(&(col->_values[i]))) count++;
            }
            return count;
        case CHAR:
            for(int i = 0; i<col->_used_size; i++){
                if(*(char*)(&x)==*(char*)(&(col->_values[i]))) count++;
            }
            return count;
        case FLOAT:
            for(int i = 0; i<col->_used_size; i++){
                if(*(float*)(&x)==*(float*)(&(col->_values[i]))) count++;
            }
            return count;
        case DOUBLE:
            for(int i = 0; i<col->_used_size; i++){
                if(*(double*)(&x)==*(double*)(&(col->_values[i]))) count++;
            }
            return count;
        case STRING:
            for(int i = 0; i<col->_used_size; i++){
                if(strcmp((&x), &(col->_values[i])) == 0) count++;
            }
            return count;
    }
}















