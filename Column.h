//
// Created by arsma on 3/28/2024.
//

#ifndef PROJET_CDATAFRAME_COLUMN_H
#define PROJET_CDATAFRAME_COLUMN_H

#include <stdlib.h>

#define REALOC_SIZE 256
#define NAME_SIZE 50


typedef struct {
    char _name[NAME_SIZE];
    int* _values;
    int _allocated_size;
    int _used_size;

}COLUMN;


/**
* Create a column
* @param1 : Column title
* @return : Pointer to created column
*/
COLUMN *create_column(char* title);
/**
* @brief : Free allocated memory
* @param1 : Pointer to a column
*/
void delete_column(COLUMN *col);
/**
* @brief: Print a column content
* @param1: Pointer to a column
*/
void print_col(COLUMN* col);

/**
* @brief : Add a new value to a column
* @param1 : Pointer to a column
* @param2 : The value to be added
* @return : 1 if the value is added 0 otherwise
*/
int insert_value(COLUMN* col, int value);

/**
* @brief : Reallocates while adding a chunk of size REALOC_SIZE
* @param1 : Pointer to a column
* @return : 1 if the reallocation is successful 0 otherwise
*/
int reallocate(COLUMN* col);

/**
* @brief: Count the occurences of x
* @param1: Pointer to a column
* @param2: Integer value to count
* @return: Occurences of x
*/
int occurences(COLUMN* col, int x);

/**
* @brief: Returns the value at index x
* @param1: Pointer to a column
* @param2: Value index
* @return: Value at index x
*/
int value_at_index(COLUMN* col, int x);


//ALL OF THE BELOW ARE FOR INTEGERS COLUMNS ONLY
/**
* @brief: Count the number of values strictly greater than x
* @param1: Pointer to a column
* @param2: Integer value
* @return: Number of values greater than x
*/
int values_strictly_greater_than(COLUMN* col, int x);

/**
* @brief: Count the number of values strictly lower than x
* @param1: Pointer to a column
* @param2: Integer value
* @return: Number of values lower than x
*/
int values_strictly_lower_than(COLUMN* col, int x);

/**
* @brief: Count the number of values equal to x
* @param1: Pointer to a column
* @param2: Integer value
* @return: Number of values equal to x
*/
int values_equal_to(COLUMN* col, int x);

#endif //PROJET_CDATAFRAME_COLUMN_H
