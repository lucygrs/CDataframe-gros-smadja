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
printf("Hello");
#endif //PROJET_CDATAFRAME_COLUMN_H
