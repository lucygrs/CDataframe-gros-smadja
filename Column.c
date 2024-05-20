//
// Created by arsma on 3/28/2024.
//

#include "Column.h"
#include <stdio.h>
#include <string.h>

COLUMN *create_column(ENUM_TYPE type, char *title) {
    COLUMN *column = malloc(1 * sizeof(COLUMN));
    if (!column) {
        printf("Couldn't create column!\n");
        return column;
    }

    for (int i = 0; i < NAME_SIZE && title[i] != '\0'; i++) {
        column->_name[i] = title[i];
    }
    switch (type) {
        case NULLVAL:
            printf("Invalid column type!\n");
        case UINT:
            column->_values = (unsigned int *) 0;
        case INT:
            column->_values = (int *) 0;
        case CHAR:
            column->_values = (char *) 0;
        case FLOAT:
            column->_values = (float *) 0;
        case DOUBLE:
            column->_values = (double *) 0;
        case STRING:
            column->_values = (char **) 0;
    }
    column->_values = NULL;
    column->_allocated_size = 0;
    column->_used_size = 0;
    column->_column_type = type;

    printf("Allocating... ");
    COL_TYPE *allocation = malloc((REALOC_SIZE) * sizeof(COL_TYPE));
    column->_index = malloc(REALOC_SIZE * sizeof(unsigned long long int));
    if (allocation) {
        column->_values = allocation;
        column->_allocated_size += REALOC_SIZE;
        printf("Allocation successful\n");
    } else {
        printf("Allocation failed\n");
    }

    return column;
}

int get_alloc_size(ENUM_TYPE type) {
    return sizeof(ENUM_TYPE);
}


void delete_column(COLUMN *col) {
    if (!col) {
        printf("Invalid pointer!\n");
        return;
    }
    free(col->_values);
    free(col);
}

void print_col(COLUMN *col) {
    if (!col) {
        printf("Invalid pointer!\n");
        return;
    }
    printf("%s\n", col->_name);
    switch (col->_column_type) {
        case NULLVAL:
            printf("Invalid column type!");
            return;
        case INT:
            for (int i = 0; i < col->_used_size; i++) {
                printf("[%d] %d\n", i, col->_values[col->_index[i]]);
            }
            return;
        case UINT:
            for (int i = 0; i < col->_used_size; i++) {
                printf("[%d] %d\n", i, col->_values[col->_index[i]]);
            }
            return;
        case CHAR:
            for (int i = 0; i < col->_used_size; i++) {
                printf("[%d] %c\n", i, col->_values[col->_index[i]]);
            }
            return;
        case FLOAT:
            for (int i = 0; i < col->_used_size; i++) {
                printf("[%d] %.2f\n", i, col->_values[col->_index[i]]);
            }
            return;
        case DOUBLE:
            for (int i = 0; i < col->_used_size; i++) {
                printf("[%d] %.4f\n", i, col->_values[col->_index[i]]);
            }
            return;
        case STRING:
            for (int i = 0; i < col->_used_size; i++) {
                printf("[%d] %s\n", i, col->_values[col->_index[i]]);
            }
            return;

    }
}

int insert_value(COLUMN *col, COL_TYPE value) {
    if (!col) {
        printf("Invalid pointer!\n");
        return 0;
    }

    if (col->_used_size < col->_allocated_size) {
        col->_values[col->_used_size] = value;
        col->_index[col->_used_size] = col->_used_size;
        col->_used_size++;
        if (col->_valid_index == VALID_INDEX) {
            col->_valid_index = INVALID_INDEX;
        }
        if (col->_valid_index == INVALID_INDEX) {
            col->_valid_index = NO_INDEX;
        }
        return 1;
    } else {
        printf("Not enough space\n");
        int reallocation = reallocate(col);
        if (reallocation) {
            insert_value(col, value);
        } else {
            return 0;
        }
    }
}

int reallocate(COLUMN *col) {
    printf("Reallocating.... ");
    void *reallocation = realloc(col->_values, (col->_allocated_size + REALOC_SIZE) * sizeof(COL_TYPE));
    unsigned long long int *index = realloc(col->_index,
                                            (col->_allocated_size + REALOC_SIZE) * sizeof(unsigned long long int));
    if (reallocation && index) {
        col->_values = reallocation;
        col->_index = index;
        col->_allocated_size += REALOC_SIZE;
        printf("Reallocation successful\n");
        return 1;
    } else {
        printf("Reallocation failed\n");
        return 0;
    }
}

int occurences(COLUMN *col, void *x) {
    if (!col) {
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    switch (col->_column_type) {
        case NULLVAL:
            printf("Invalid type!");
            return 0;
        case INT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*((int *) x) == *(int *) (&col->_values[i])) {
                    count++;
                }
            }
            return count;
        case FLOAT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*((float *) x) == *(float *) (&col->_values[i])) {
                    count++;
                }
            }
            return count;
        case UINT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*((unsigned int *) x) == *(unsigned int *) (&col->_values[i])) {
                    count++;
                }
            }
            return count;
        case CHAR:
            for (int i = 0; i < col->_used_size; i++) {
                if (*((char *) x) == *(char *) (&col->_values[i])) {
                    count++;
                }
            }
            return count;
        case DOUBLE:
            for (int i = 0; i < col->_used_size; i++) {
                if (*((double *) x) == *(double *) (&col->_values[i])) {
                    count++;
                }
            }
            return count;
        case STRING:
            for (int i = 0; i < col->_used_size; i++) {
                if (strcmp(*(char **) (&col->_values[i]), x) == 0) {
                    count++;
                }
            }
            return count;
    }
    return count;
}

COL_TYPE value_at_index(COLUMN *col, int x) {
    if (!col) {
        printf("Invalid pointer!");
        return (COL_TYPE) 0;
    }
    return col->_values[x];
}

int values_strictly_greater_than(COLUMN *col, COL_TYPE x) {
    if (!col) {
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    switch (col->_column_type) {
        case NULLVAL:
            printf("Invalid column type!\n");
            return count;
        case UINT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(unsigned int *) (&x) < *(unsigned int *) (&(col->_values[i]))) count++;
            }
            return count;
        case INT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(int *) (&x) < *(int *) (&(col->_values[i]))) count++;
            }
            return count;
        case CHAR:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(char *) (&x) < *(char *) (&(col->_values[i]))) count++;
            }
            return count;
        case FLOAT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(float *) (&x) < *(float *) (&(col->_values[i]))) count++;
            }
            return count;
        case DOUBLE:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(double *) (&x) < *(double *) (&(col->_values[i]))) count++;
            }
            return count;
        case STRING:
            for (int i = 0; i < col->_used_size; i++) {
                if (strcmp((&x), &(col->_values[i])) < 0) count++;
            }
            return count;
    }
}

int values_strictly_lower_than(COLUMN *col, COL_TYPE x) {
    if (!col) {
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    switch (col->_column_type) {
        case NULLVAL:
            printf("Invalid column type!\n");
            return count;
        case UINT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(unsigned int *) (&x) > *(unsigned int *) (&(col->_values[i]))) count++;
            }
            return count;
        case INT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(int *) (&x) > *(int *) (&(col->_values[i]))) count++;
            }
            return count;
        case CHAR:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(char *) (&x) > *(char *) (&(col->_values[i]))) count++;
            }
            return count;
        case FLOAT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(float *) (&x) > *(float *) (&(col->_values[i]))) count++;
            }
            return count;
        case DOUBLE:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(double *) (&x) > *(double *) (&(col->_values[i]))) count++;
            }
            return count;
        case STRING:
            for (int i = 0; i < col->_used_size; i++) {
                if (strcmp((&x), &(col->_values[i])) > 0) count++;
            }
            return count;
    }
}

int values_equal_to(COLUMN *col, COL_TYPE x) {
    if (!col) {
        printf("Invalid pointer!");
        return 0;
    }
    int count = 0;
    switch (col->_column_type) {
        case NULLVAL:
            printf("Invalid column type!\n");
            return count;
        case UINT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(unsigned int *) (&x) == *(unsigned int *) (&(col->_values[i]))) count++;
            }
            return count;
        case INT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(int *) (&x) == *(int *) (&(col->_values[i]))) count++;
            }
            return count;
        case CHAR:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(char *) (&x) == *(char *) (&(col->_values[i]))) count++;
            }
            return count;
        case FLOAT:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(float *) (&x) == *(float *) (&(col->_values[i]))) count++;
            }
            return count;
        case DOUBLE:
            for (int i = 0; i < col->_used_size; i++) {
                if (*(double *) (&x) == *(double *) (&(col->_values[i]))) count++;
            }
            return count;
        case STRING:
            for (int i = 0; i < col->_used_size; i++) {
                if (strcmp((&x), &(col->_values[i])) == 0) count++;
            }
            return count;
    }
}

COL_TYPE highest_union(COL_TYPE a, COL_TYPE b, ENUM_TYPE type) {
    switch (type) {
        case NULLVAL:
            printf("Invalid type!\n");
            return (COL_TYPE) 0;
        case UINT:
            if (*(unsigned int *) &a > *(unsigned int *) &b)
                return a;
            else if (*(unsigned int *) &a <= *(unsigned int *) &b)
                return b;
        case INT:
            if (*(int *) &a > *(int *) &b)
                return a;
            else if (*(int *) &a <= *(int *) &b)
                return b;

        case CHAR:
            if (*(char *) &a > *(char *) &b)
                return a;
            else if (*(char *) &a <= *(char *) &b)
                return b;

        case FLOAT:
            if (*(float *) &a > *(float *) &b)
                return a;
            else if (*(float *) &a <= *(float *) &b)
                return b;

        case DOUBLE:
            if (*(double *) &a > *(double *) &b)
                return a;
            else if (*(double *) &a <= *(double *) &b)
                return b;

        case STRING: {
            int res = strcmp(*(char **) &a, *(char **) &b);
            if (res > 0) {
                return a;
            } else if (res <= 0) {
                return b;
            }
        }
    }
}

COL_TYPE lowest_union(COL_TYPE a, COL_TYPE b, ENUM_TYPE type) {
    switch (type) {
        case NULLVAL:
            printf("Invalid type!\n");
            return (COL_TYPE) 0;
        case UINT:
            if (*(unsigned int *) &a < *(unsigned int *) &b)
                return a;
            else if (*(unsigned int *) &a >= *(unsigned int *) &b)
                return b;
        case INT:
            if (*(int *) &a < *(int *) &b)
                return a;
            else if (*(int *) &a >= *(int *) &b)
                return b;

        case CHAR:
            if (*(char *) &a < *(char *) &b)
                return a;
            else if (*(char *) &a >= *(char *) &b)
                return b;

        case FLOAT:
            if (*(float *) &a < *(float *) &b)
                return a;
            else if (*(float *) &a >= *(float *) &b)
                return b;

        case DOUBLE:
            if (*(double *) &a < *(double *) &b)
                return a;
            else if (*(double *) &a >= *(double *) &b)
                return b;

        case STRING: {
            int res = strcmp(*(char **) &a, *(char **) &b);
            if (res < 0) {
                return a;
            } else if (res >= 0) {
                return b;
            }
        }
    }
}

int equal_union(COL_TYPE a, COL_TYPE b, ENUM_TYPE type) {
    switch (type) {
        case NULLVAL:
            printf("Invalid type!\n");
            return 0;
        case UINT:
            if (*(unsigned int *) &a == *(unsigned int *) &b)
                return 1;
            else return 0;
        case INT:
            if (*(int *) &a == *(int *) &b)
                return 1;
            else return 0;

        case CHAR:
            if (*(char *) &a == *(char *) &b)
                return 1;
            else return 0;

        case FLOAT:
            if (*(float *) &a == *(float *) &b)
                return 1;
            else return 0;

        case DOUBLE:
            if (*(double *) &a == *(double *) &b)
                return 1;
            else return 0;

        case STRING: {
            int res = strcmp(*(char **) &a, *(char **) &b);
            if (res == 0)
                return 1;
            else return 0;
        }
    }
}

int sort_column(COLUMN *col) {
    if (col->_valid_index == NO_INDEX) {
        quick_sort(col->_values, col->_index, col->_used_size, col->_sort_dir, col->_column_type);
    } else {
        insertion_sort(col->_values, col->_index, col->_used_size, col->_sort_dir, col->_column_type);
    }
    col->_valid_index = VALID_INDEX;
}

int insertion_sort(COL_TYPE *array, LONGINT *indexes, int length, int sort_dir, ENUM_TYPE type) {
    if (sort_dir == ASC) {
        int found_place = 0;
        if (equal_union(highest_union(array[indexes[length - 2]], array[indexes[length - 1]], type),
                        array[indexes[length - 1]], type)) {
            return 1;
        } else if (equal_union(lowest_union(array[indexes[0]], array[indexes[length - 1]], type),
                               array[indexes[length - 1]], type)) {
            LONGINT temp = indexes[0];
            indexes[0] = indexes[length - 1];
            for (int i = 1; i < length; i++) {
                LONGINT temp2 = indexes[i];
                indexes[i] = temp;
                temp = temp2;

            }
        } else {
            for (int i = 1; i < length - 2; i++) {
                if (equal_union(highest_union(array[indexes[i]], array[indexes[length - 1]], type),
                                array[indexes[length - 1]], type) &&
                    equal_union(lowest_union(array[indexes[i + 1]], array[indexes[length - 1]], type),
                                array[indexes[length - 1]], type)) {
                    LONGINT temp = indexes[i + 1];
                    indexes[i + 1] = indexes[length - 1];
                    for (int j = i + 2; j < length; j++) {
                        LONGINT temp2 = indexes[j];
                        indexes[j] = temp;
                        temp = temp2;
                    }
                }
            }
        }
    } else {
        int found_place = 0;
        if (left_lower_byindex(length-1, length-1, array, indexes, type)) {
            return 1;
        }else if(left_higher_byindex(length-1, 0, array, indexes, type)){
            LONGINT temp = indexes[0];
            indexes[0] = indexes[length - 1];
            for (int i = 1; i < length; i++) {
                LONGINT temp2 = indexes[i];
                indexes[i] = temp;
                temp = temp2;

            }
        } else {
            for (int i = 1; i < length - 2; i++) {
                if(left_lower_byindex(length-1, i, array, indexes, type) && left_higher_byindex(length-1, i+1, array, indexes, type)){
                    LONGINT temp = indexes[i + 1];
                    indexes[i + 1] = indexes[length - 1];
                    for (int j = i + 2; j < length; j++) {
                        LONGINT temp2 = indexes[j];
                        indexes[j] = temp;
                        temp = temp2;
                    }
                }
            }
        }
    }
}

int equal_by_index(LONGINT a, LONGINT b, COL_TYPE *array, LONGINT *indexes, ENUM_TYPE type){
    return equal_union(array[indexes[a]], array[indexes[b]], type);
}

int left_higher_byindex(LONGINT a, LONGINT b, COL_TYPE *array, LONGINT *indexes, ENUM_TYPE type) {
    if(equal_by_index(a, b, array, indexes, type)){
        return EQUAL;
    }else if(equal_union(highest_union(array[indexes[a]], array[indexes[b]], type), array[indexes[a]], type)){
        return HIGHER;
    }else{
        return LOWER;
    }
}

int left_higher_or_eq_byindex(LONGINT a, LONGINT b, COL_TYPE *array, LONGINT *indexes, ENUM_TYPE type){
    if (equal_union(highest_union(array[indexes[a]], array[indexes[b]], type), array[indexes[a]], type)
    || equal_by_index(a, b, array, indexes, type)) {
        return 1;
    } else {
        return 0;
    }
}

int left_lower_byindex(LONGINT a, LONGINT b, COL_TYPE *array, LONGINT *indexes, ENUM_TYPE type) {
    if (equal_union(lowest_union(array[indexes[a]], array[indexes[b]], type), array[indexes[a]], type)
    ) {
        return 1;
    } else {
        return 0;
    }
}
int left_lower_or_eq_byindex(LONGINT a, LONGINT b, COL_TYPE *array, LONGINT *indexes, ENUM_TYPE type) {
    if (equal_union(lowest_union(array[indexes[a]], array[indexes[b]], type), array[indexes[a]], type
    || equal_by_index(a, b, array, indexes, type))
            ) {
        return 1;
    } else {
        return 0;
    }
}

int quick_sort(COL_TYPE *array, LONGINT *indexes, LONGINT length, int sort_dir, ENUM_TYPE type) {
    if (sort_dir == ASC) {
        if (length <= 2) {
            if (length == 2) {
                if (left_higher_byindex(0, 1, array, indexes, type) == HIGHER) {
                    LONGINT temp = indexes[0];
                    indexes[0] = indexes[1];
                    indexes[1] = temp;
                }
            } else {

            }
            return 1;
        } else {
            LONGINT pivot = length - 1;

            LONGINT item_from_right = length - 2; // must be lower than the pivot
            LONGINT item_from_left = 0; // must be higher than the pivot


            int loop = 1;
            while (loop) {
                for (int i = 0; i < length - 1; i++) {
                    item_from_left = i;
                    if (left_higher_byindex(i, pivot, array, indexes, type) == HIGHER) {
                        break;
                    }
                }
                for (int i = length - 2; i >= 0; i--) {
                    item_from_right = i;
                    if (left_higher_byindex(i, pivot, array, indexes, type) == LOWER) {
                        break;
                    }
                }
                if(item_from_left<item_from_right){
                    LONGINT temp = indexes[item_from_left];
                    indexes[item_from_left] = indexes[item_from_right];
                    indexes[item_from_right] = temp;
                } else {
                    break;
                }
            }
            if(left_higher_or_eq_byindex(item_from_left, pivot, array, indexes, type)){
                LONGINT temp = indexes[item_from_left];
                indexes[item_from_left] = indexes[pivot];
                indexes[pivot] = temp;

                temp = item_from_left;
                item_from_left = pivot;
                pivot = temp;
            }


            quick_sort(array, indexes, pivot, sort_dir, type);
            quick_sort(array, &indexes[pivot+1], length - pivot-1, sort_dir, type);
            return 1;
        }
    } else {
        if (length <= 2) {
            if (length == 2) {
                if (left_higher_byindex(0, 1, array, indexes, type) == LOWER) {
                    LONGINT temp = indexes[0];
                    indexes[0] = indexes[1];
                    indexes[1] = temp;
                }
            } else {

            }
            return 1;
        } else {

            LONGINT pivot = 0;

            LONGINT item_from_right = length - 1; // must be lower than the pivot
            LONGINT item_from_left = 1; // must be higher than the pivot


            int loop = 1;
            while (loop) {
                printf("\n");
                for (int i = 1; i < length; i++) {
                    item_from_left = i;
                    if (left_higher_byindex(i, pivot, array, indexes, type) == LOWER) {
                        break;
                    }
                }
                for (int i = length - 1; i >= 1; i--) {
                    item_from_right = i;
                    if (left_higher_byindex(i, pivot, array, indexes, type) == HIGHER) {
                        break;
                    }
                }
                if(item_from_left<item_from_right){
                    LONGINT temp = indexes[item_from_right];
                    indexes[item_from_right] = indexes[item_from_left];
                    indexes[item_from_left] = temp;
                } else {
                    break;
                }
            }
            if(left_higher_or_eq_byindex(item_from_right, pivot, array, indexes, type)){
                LONGINT temp = indexes[item_from_right];
                indexes[item_from_right] = indexes[pivot];
                indexes[pivot] = temp;

                temp = item_from_right;
                item_from_right = pivot;
                pivot = temp;
            }


            quick_sort(array, indexes, pivot, sort_dir, type);
            quick_sort(array, &indexes[pivot+1], length - pivot-1, sort_dir, type);
            return 1;
        }
    }
}

int search_value_in_column(COLUMN *col, void *val){ // dichotomic search
    LONGINT low = 0;
    LONGINT high = col->_used_size;
    LONGINT middle = col->_used_size/2;

    int loop = 1;
    if(col->_sort_dir == ASC) {
        while (loop) {
            if (equal_union(*(COL_TYPE *) val, col->_values[col->_index[middle]], col->_column_type)) {
                return middle;
            } else if (equal_union(
                    highest_union(*(COL_TYPE *) val, col->_values[col->_index[middle]], col->_column_type),
                    *(COL_TYPE *) val, col->_column_type)) {
                low = middle;
                middle = (high - low) / 2 + low;
            } else if (equal_union(
                    lowest_union(*(COL_TYPE *) val, col->_values[col->_index[middle]], col->_column_type),
                    *(COL_TYPE *) val, col->_column_type)) {
                high = middle;
                middle = high - (high - low) / 2;
            }

            printf("high %d low %d middle %d\n", high, low, middle);

            if (high - low == 1) {
                break;
            }
        }
    }
    else{
        while (loop) {
            if (equal_union(*(COL_TYPE *) val, col->_values[col->_index[middle]], col->_column_type)) {
                return middle;
            } else if (equal_union(
                    lowest_union(*(COL_TYPE *) val, col->_values[col->_index[middle]], col->_column_type),
                    *(COL_TYPE *) val, col->_column_type)) {
                low = middle;
                middle = (high - low) / 2 + low;
            } else if (equal_union(
                    highest_union(*(COL_TYPE *) val, col->_values[col->_index[middle]], col->_column_type),
                    *(COL_TYPE *) val, col->_column_type)) {
                high = middle;
                middle = high - (high - low) / 2;
            }

            printf("high %d low %d middle %d\n", high, low, middle);

            if (high - low == 1) {
                break;
            }
        }
    }

    if(equal_union(*(COL_TYPE*)val, col->_values[col->_index[low]], col->_column_type)){
        return low;
    }else
    if(equal_union(*(COL_TYPE*)val, col->_values[col->_index[high]], col->_column_type)){
        return middle;
    }
    else{
        printf("Value was not found");
        return -1;
    }
}










