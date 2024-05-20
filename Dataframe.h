//
// Created by arsma on 3/28/2024.
//

#ifndef PROJET_CDATAFRAME_DATAFRAME_H
#define PROJET_CDATAFRAME_DATAFRAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"
#define COLUMN_WIDTH 15
/**
 * Element lnode
 */
typedef struct lnode_ {
    COLUMN *data;
    struct lnode_ *prev;
    struct lnode_ *next;
} lnode;

/**
 * A List
 */
typedef struct list_ {
    lnode *head;
    lnode *tail;
} list;

/**
 * Create a node
 */
lnode *lst_create_lnode();

/**
 * Create the list and return a pointer on this list
 */
list *lst_create_list();

/**
 * Insert a node at the tail of the list
 */
void lst_insert_tail(list *lst, lnode *node);

typedef list CDATAFRAME;

/**
 * Create CDataFrame
 */
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);

/** * @brief: Column deletion
 * * param1: Pointer to the CDataframe to delete
 * */
void delete_cdataframe(CDATAFRAME ** cdf);

/** * @breif: Delete column by name
 * * @param1: Pointer to the CDataframe
 * * @param2: Column name */
void delete_column_data(CDATAFRAME *cdf, char *col_name);

/** * @brief: Number of columns
 * * @param1: Point to the CDataframe
 * * @return: Number of columns in the CDataframe
 * */
int get_cdataframe_cols_size(CDATAFRAME *cdf);
/*
 * @return Pointer to the Cdataframe
 */

/*
 * Function that permit the user to fill the CDataframe
 */
CDATAFRAME *user_fill_cdataframe();

/** @brief : Create an umpty CDataFrame
 * @return:Pointer on a CDataFrame
 */
CDATAFRAME *create_umpty_cdataframe();

/** @brief : Display the column of the CDataFrame one below the other
 * @return:Pointer on a CDataFrame
 */
void display_cdataframe(CDATAFRAME *cdf);

/** @brief : Add a line of value to a column
 */
void add_value_col(CDATAFRAME *cdf);

/** @brief : Delete the last line of value of each column
 */
void delete_last_line_value(CDATAFRAME *cdf);

/** @brief : Add a column to the CDataframe
 */
void add_column(CDATAFRAME *cdf);

/** @brief : Rename a column of the CDataFrame
 */
void rename_column(CDATAFRAME *cdf);

/** @brief : Display the name of the column
 */
void display_name_column(CDATAFRAME *cdf);

/** @brief : Display the number of line of the CDF
 */
int display_nb_line(CDATAFRAME *cdf);

/** @brief : Dusplay the value of CDF
 * @param1 : A pointer to a column
 * @param2: An integer that represent the number max of line in the CDF
 * note: this function has been realised with help of a youtube tutorial
 */
void display_value(COLUMN* col, int index);

/** @brief : Display the CDF like a tab
 * note: this function has been realised with help of a youtube tutorial
 */
void display_cdataframe_tab(CDATAFRAME *cdf);

#endif //PROJET_CDATAFRAME_DATAFRAME_H
