//
// Created by arsma on 3/28/2024.
//

#ifndef PROJET_DATAFRAME_DATAFRAME_H
#define PROJET_DATAFRAME_DATAFRAME_H

#include "Column.h"

#define COL_REALLOC_SIZE 256

typedef struct {
    COLUMN ** _cols;
    int _ncols;
    int _used_cols
} DATAFRAME;

DATAFRAME* create_dataframe(){
    return malloc(1*sizeof(DATAFRAME));
}

void fill_dataframe(DATAFRAME* dataframe);//until _used_cols

void fill_column_at_index(DATAFRAME* dataframe, int index);

COLUMN* get_column_at_index(DATAFRAME* dataframe, int index);

void print_dataframe(DATAFRAME* dataframe);

void print_dataframe_cols(DATAFRAME* dataframe, int index_limit);

void print_dataframe_rows(DATAFRAME* dataframe, int index_limit);

int add_column(DATAFRAME* dataframe);

int add_row(DATAFRAME* dataframe);

int delete_row_at_index(DATAFRAME* dataframe, int index);

int delete_column_at_index(DATAFRAME* dataframe, int index);

void rename_column_at_index(DATAFRAME* dataframe, int index, char* new_name);

int does_value_exist(DATAFRAME* dataframe, int value);

void overwrite_value(DATAFRAME* dataframe, int col, int row);

void print_columns_names(DATAFRAME* dataframe);

int get_number_of_used_rows(DATAFRAME* dataframe);

int get_number_of_columns(DATAFRAME* dataframe);

int get_number_of_cells_equal_to(DATAFRAME* dataframe, int value);

int get_number_of_cells_greater_than(DATAFRAME* dataframe, int value);

int get_number_of_cells_lower_than(DATAFRAME* dataframe, int value);

void sort_column_at_index(DATAFRAME* dataframe, int index);

int average_value(DATAFRAME* dataframe);

int average_value_of_column(DATAFRAME* dataframe, int index);

int delete_dataframe(DATAFRAME* dataframe);


#endif //PROJET_DATAFRAME_DATAFRAME_H
