//
// Created by arsma on 3/28/2024.
//

#ifndef PROJET_CDATAFRAME_COLUMN_H
#define PROJET_CDATAFRAME_COLUMN_H

#include <stdlib.h>

#define REALOC_SIZE 256
#define NAME_SIZE 50

#define EQUAL 0
#define HIGHER 1
#define LOWER -1

enum enum_type
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING
};
typedef enum enum_type ENUM_TYPE;

enum {NO_INDEX=0, VALID_INDEX=1, INVALID_INDEX=-1};
enum {ASC = 0, DESC = 1};

union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
};
typedef union column_type COL_TYPE ;


typedef struct {
    char _name[NAME_SIZE];
    COL_TYPE* _values;
    int _allocated_size;
    int _used_size;

    ENUM_TYPE _column_type;
    unsigned long long int *_index;
    int _valid_index;
    int _sort_dir;

}COLUMN;

typedef unsigned long long int LONGINT;

COLUMN *create_column(ENUM_TYPE type, char* title);

/**
* @brief: Insert a new value into a column
* @param1: Pointer to the column
* @param2: Pointer to the value to insert
* @return: 1 if the value is correctly inserted 0 otherwise
*/
int insert_value(COLUMN *col, COL_TYPE value);

int get_alloc_size(ENUM_TYPE type);

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
int occurences(COLUMN* col, void* x);

/**
* @brief: Returns the value at index x
* @param1: Pointer to a column
* @param2: Value index
* @return: Value at index x
*/
COL_TYPE value_at_index(COLUMN* col, int x);


//ALL OF THE BELOW ARE FOR INTEGERS COLUMNS ONLY
/**
* @brief: Count the number of values strictly greater than x
* @param1: Pointer to a column
* @param2: Integer value
* @return: Number of values greater than x
*/
int values_strictly_greater_than(COLUMN* col, COL_TYPE x);

/**
* @brief: Count the number of values strictly lower than x
* @param1: Pointer to a column
* @param2: Integer value
* @return: Number of values lower than x
*/
int values_strictly_lower_than(COLUMN* col, COL_TYPE x);

/**
* @brief: Count the number of values equal to x
* @param1: Pointer to a column
* @param2: Integer value
* @return: Number of values equal to x
*/
int values_equal_to(COLUMN* col, COL_TYPE x);

COL_TYPE highest_union(COL_TYPE a, COL_TYPE b, ENUM_TYPE type);

COL_TYPE lowest_union(COL_TYPE a, COL_TYPE b, ENUM_TYPE type);

int equal_union(COL_TYPE a, COL_TYPE b, ENUM_TYPE type);

int equal_by_index(LONGINT a, LONGINT b, COL_TYPE *array, LONGINT *indexes, ENUM_TYPE type);

int left_higher_byindex(LONGINT a, LONGINT b, COL_TYPE *array, LONGINT *indexes, ENUM_TYPE type);

int left_higher_or_eq_byindex(LONGINT a, LONGINT b, COL_TYPE *array, LONGINT *indexes, ENUM_TYPE type);

int left_lower_byindex(LONGINT a, LONGINT b, COL_TYPE *array, LONGINT *indexes, ENUM_TYPE type);

int left_lower_or_eq_byindex(LONGINT a, LONGINT b, COL_TYPE *array, LONGINT *indexes, ENUM_TYPE type);


int sort_column(COLUMN* col);

int insertion_sort(COL_TYPE* array, LONGINT *indexes, int length, int sort_dir, ENUM_TYPE type);

int quick_sort(COL_TYPE *array, LONGINT *indexes, LONGINT length, int sort_dir, ENUM_TYPE type);

int search_value_in_column(COLUMN *col, void *val);

#endif //PROJET_CDATAFRAME_COLUMN_H