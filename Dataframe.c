#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dataframe.h"

lnode *lst_create_lnode() {
    lnode  *ptmp =(lnode *) malloc(sizeof(lnode));
    ptmp -> data = NULL;
    ptmp -> next = NULL;
    ptmp -> prev = NULL;
    return ptmp;
}

list *lst_create_list(){
    list *lst = (list *) malloc(sizeof(list));
    lst -> head = NULL;
    lst -> tail =NULL;
    return lst;
}

void lst_insert_tail(list * lst, lnode * pnew) {
    if (lst->head == NULL){
        lst -> head = pnew;
        lst -> tail = pnew;
        return;
    }
    pnew -> next = NULL;
    pnew -> prev = lst -> tail;
    lst -> tail = pnew;
    pnew -> prev -> next = pnew;
}

CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size){
    CDATAFRAME *cdf= lst_create_list();
    if(cdf !=NULL){
        for (int i = 0; i < size; i++) {
            printf("Enter the title of the column:");
            char title[NAME_SIZE];
            scanf(" %s",title);

            lnode *new_node = lst_create_lnode();
            if(new_node!=NULL)
            {
                COLUMN *column = create_column(cdftype[size - 1 - i], title);
                new_node -> data = column;

                if(cdf->tail == NULL){
                    cdf -> head = new_node;
                    cdf -> tail = new_node;
                }
                else{
                    new_node->next=cdf->head;
                    cdf->head->prev=new_node;
                    cdf -> head = new_node;
                }
            }
        }
        return cdf;
    }
}

void delete_cdataframe(CDATAFRAME ** cdf){
    if(*cdf !=NULL){
        lnode *node_tmp=(*cdf)->head;
        while(node_tmp != NULL){
            lnode *node_delete = node_tmp;
            node_tmp = node_tmp-> next;
            free(node_delete);
        }
        free(*cdf);
        *cdf=NULL;
    }
}

void delete_column_data(CDATAFRAME *cdf, char *col_name) {
    if (cdf == NULL || col_name == NULL) {
        return;
    }

    lnode *node_tmp = cdf->head;
    while (node_tmp != NULL) {
        COLUMN *col = (COLUMN *)node_tmp->data;
        printf("Column name: %s, col_name: %s\n", col->_name, col_name);
        if (strcmp(col->_name, col_name) == 0) {
            if (node_tmp == cdf->head && node_tmp == cdf->tail) {
                cdf->head = NULL;
                cdf->tail = NULL;
            }
            if (node_tmp == cdf->head) {
                cdf->head = node_tmp->next;
                if (cdf->head) {
                    cdf->head->prev = NULL;
                }
            }
            if (node_tmp == cdf->tail) {
                cdf->tail = node_tmp->prev;
                if (cdf->tail) {
                    cdf->tail->next = NULL;
                }
            }

            else {
                if (node_tmp->prev) {
                    node_tmp->prev->next = node_tmp->next;
                }
                if (node_tmp->next) {
                    node_tmp->next->prev = node_tmp->prev;
                }
            }

            delete_column(col);
            free(node_tmp);
            return;
        }
        node_tmp = node_tmp->next;
    }

    printf("Error: Column with name '%s' not found in DataFrame\n", col_name);
}

int get_cdataframe_cols_size(CDATAFRAME *cdf){
    int size=0;
    lnode *node_cpt= cdf ->head;
    if(cdf != NULL){
        while(node_cpt!=NULL){
            size++;
            node_cpt=node_cpt->next;
        }
    }
    return size;
}

CDATAFRAME *create_umpty_cdataframe(){
    CDATAFRAME *cdf= lst_create_list();
    return cdf;
}

void user_fill_column(COLUMN *col){
    int nb_val;
    printf("\n");
    printf("How many values for the column %s? :",col->_name);
    scanf("%d",&nb_val);
    for(int i=0; i<nb_val;i++){
        COL_TYPE val;
        switch(col->_column_type){
            case UINT:
                printf("Enter an unsigned integer: ");
                scanf("%u",&val.uint_value);
                printf("\n");
                break;
            case INT:
                printf("Enter an integer: ");
                scanf("%d",&val.int_value);
                printf("\n");
                break;
            case CHAR:
                printf("Enter a character: ");
                scanf(" %c",&val.char_value);
                printf("\n");
                break;
            case FLOAT:
                printf("Enter a float: ");
                scanf("%f",&val.float_value);
                printf("\n");
                break;
            case DOUBLE:
                printf("Enter a double: ");
                scanf("%lf",&val.double_value);
                printf("\n");
                break;
            case STRING:
                printf("Enter a string: ");
                val.string_value = (char*)malloc(REALOC_SIZE*sizeof(char));
                scanf("%s",val.string_value);
                printf("\n");
                break;
            default:
                printf("Error : column type do not exist!\n");

        }
        insert_value(col,val);
    }
}

CDATAFRAME *user_fill_cdataframe(){
    int nb_column;
    printf("How many column do you want in your CDataFrame?\n");
    printf("Please enter the number: ");
    scanf("%d",&nb_column);
    printf("\n");


    if(nb_column>0){
        ENUM_TYPE* cdftype = (ENUM_TYPE*)malloc(nb_column * sizeof(ENUM_TYPE));
        if(!cdftype){
            printf("Error in  construction of type column\n");
            printf("Creation of an umpty CDataFrame...\n");
            return create_umpty_cdataframe();
        }

        for(int i=0; i<nb_column;i++){
            printf("Please enter the type for the column number %d:\n",i+1);
            printf("Enter 1 for UINT\nEnter 2 for INT\nEnter 3 for CHAR\nEnter 4 for FLOAT\n");
            printf("Enter 5 for DOUBLE\nEnter 6 for STRING\n");
            printf("Please enter your choice: ");
            int choice;
            scanf("%d",&choice);
            printf("\n");


            switch(choice){
                case 1:
                    cdftype[i]=UINT;
                    break;
                case 2:
                    cdftype[i]=INT;
                    break;
                case 3 :
                    cdftype[i]= CHAR;
                    break;
                case 4:
                    cdftype[i]=FLOAT;
                    break;
                case 5:
                    cdftype[i]=DOUBLE;
                    break;
                case 6 :
                    cdftype[i]=STRING;
                    break;
                default:
                    printf("Error: choosen type by default : STRING");
                    cdftype[i]=STRING;
            }

        }

        CDATAFRAME *cdf = create_cdataframe(cdftype,nb_column);


        if(cdf!=NULL){
            lnode *tmp = cdf->tail;
            while(tmp!=NULL){
                user_fill_column(tmp->data);
                tmp=tmp->prev;
            }
        }
        free(cdftype);
        return cdf;
    }
    else{
        printf("Creation of an umpty CDataFrame...");
        CDATAFRAME *cdf= create_umpty_cdataframe();
        return cdf;

    }
}

void display_cdataframe(CDATAFRAME *cdf){
    if(cdf==NULL){
        printf("Error: display immposible: invalid pointer!\n");
    }
    else{
        lnode *tmp = cdf -> tail;
        while(tmp != NULL){
            print_col((COLUMN*)tmp->data);
            tmp = tmp->prev;
        }
    }
}

void add_value_col(CDATAFRAME *cdf){
    lnode *node =cdf->tail;
    while(node!=NULL){
        COLUMN *col = (COLUMN*)node->data;
        COL_TYPE val;
        switch (col->_column_type) {
            case UINT:
                printf("Enter an unsigned integer to add to the column %s: ",col->_name);
                scanf("%u",&val.uint_value);
                printf("\n");
                break;
            case INT:
                printf("Enter an integerto add to the column %s: ",col->_name);
                scanf("%d",&val.int_value);
                printf("\n");
                break;
            case CHAR:
                printf("Enter a character to add to the column %s: ",col->_name);
                scanf(" %c",&val.char_value);
                printf("\n");
                break;
            case FLOAT:
                printf("Enter a float to add to the column %s: ",col->_name );
                scanf("%f",&val.float_value);
                printf("\n");
                break;
            case DOUBLE:
                printf("Enter a double to add to the column %s: ",col->_name);
                scanf("%lf",&val.double_value);
                printf("\n");
                break;
            case STRING:
                printf("Enter a string to add to the column %s:",col->_name);
                val.string_value = (char*)malloc(REALOC_SIZE*sizeof(char));
                scanf("%s",val.string_value);
                printf("\n");
                break;
            default:
                printf("Error: column type do not exist!\n");
                continue;

        }
        insert_value(col,val);
        col->_used_size+1;
        node=node->prev;
    }
}

void delete_last_line_value(CDATAFRAME *cdf){
    lnode *node =cdf->tail;
    while(node!=NULL){
        COLUMN *col = (COLUMN*)node->data;
        if(col->_used_size>0){
            col->_used_size--;
        }
        node=node->prev;
    }
}

void add_column(CDATAFRAME *cdf){
    COLUMN *col = (COLUMN*)malloc(sizeof(COLUMN));

    printf("Enter the title of the column:");
    char title[NAME_SIZE];
    scanf(" %s",title);

    printf("Please enter the type for the new column :\n");
    printf("Enter 1 for UINT\n Enter 2 for INT\n Enter 3 for CHAR\n Enter 4 for FLOAT\n");
    printf("Enter 5 for DOUBLE\n Enter 6 for STRING\n");
    printf("Please enter your choice: ");

    int choice;
    scanf("%d",&choice);


    ENUM_TYPE cdftype;
    switch(choice){
        case 1:
            cdftype=UINT;
            break;
        case 2:
            cdftype=INT;
            break;
        case 3 :
            cdftype= CHAR;
            break;
        case 4:
            cdftype=FLOAT;
            break;
        case 5:
            cdftype=DOUBLE;
            break;
        case 6 :
            cdftype=STRING;
            break;
        default:
            printf("Error : choosen type by default : STRING");
            cdftype=STRING;
    }
    col = create_column(cdftype,title);
    user_fill_column(col);
    lnode *new_node = lst_create_lnode();
    new_node->data=col;
    if(cdf->tail == NULL){
        cdf -> head = new_node;
        cdf -> tail = new_node;
    }
    else{
        new_node->next=cdf->head;
        cdf->head->prev=new_node;
        cdf -> head = new_node;
    }
}

void rename_column(CDATAFRAME *cdf){
    int place;
    printf("Enter the position of the column you want to rename: ");
    scanf("%d",&place);
    place = place -1;
    printf("Enter the new title of the column:");
    char new_title[NAME_SIZE];
    scanf(" %s",new_title);
    int cpt = 0;
    lnode *node_cpt= cdf ->tail;
    while(cpt!=place && node_cpt!=NULL){
        node_cpt =node_cpt->prev;
        cpt++;
    }
    if(node_cpt != NULL){
        COLUMN * col = (COLUMN*)node_cpt->data;
        strcpy(col->_name,new_title);
        printf("Column at position %d renamed to '%s'.\n", place + 1, new_title);
    }
    else{
        printf("Error: column to rename not found!");
    }

}

void display_name_column(CDATAFRAME *cdf){
    lnode *node_cpt =cdf->tail;
    while(node_cpt!=NULL){
        printf("%s ",node_cpt->data->_name);
        node_cpt = node_cpt -> prev;
    }
}

int display_nb_line(CDATAFRAME *cdf){
    int nbline=0;
    lnode *node = cdf->tail;
    COLUMN *col1 =(COLUMN*)node->data;
    nbline = col1->_used_size;
    return nbline;
}

void display_value(COLUMN* col, int index) {
    if (!col) {
        printf("Error: the pointer column is invalid!");
        return;
    }
    if (index >= col->_used_size) {
        printf("| %-*s ", COLUMN_WIDTH, "no value");
        return;
    }
    switch (col->_column_type) {
        case INT:
            printf("| %-*d ", COLUMN_WIDTH, col->_values[index].int_value);
            return;
        case UINT:
            printf("| %-*u ", COLUMN_WIDTH, col->_values[index].uint_value);
            return;
        case CHAR:
            printf("| %-*c ", COLUMN_WIDTH, col->_values[index].char_value);
            return;
        case FLOAT:
            printf("| %-*.2f ", COLUMN_WIDTH, col->_values[index].float_value);
            return;
        case DOUBLE:
            printf("| %-*.4f ", COLUMN_WIDTH, col->_values[index].double_value);
            return;
        case STRING:
            printf("| %-*s ", COLUMN_WIDTH, col->_values[index].string_value);
            return;
    }
}

void display_cdataframe_tab(CDATAFRAME *cdf) {
    if (!cdf) {
        printf("Error: the pointer to the DataFrame is invalid!\n");
        return;
    }

    lnode *node_cpt = cdf->tail;
    while (node_cpt != NULL) {
        printf("| %-*s ", COLUMN_WIDTH, node_cpt->data->_name);
        node_cpt = node_cpt->prev;
    }
    printf("|\n");
    int nb = 0;
    node_cpt = cdf->tail;
    while (node_cpt != NULL) {
        if (node_cpt->data->_used_size > nb) {
            nb = node_cpt->data->_used_size;
        }
        node_cpt = node_cpt->prev;
    }

    for (int i = 0; i < nb; i++) {
        node_cpt = cdf->tail;
        while (node_cpt != NULL) {
            display_value(node_cpt->data, i);
            node_cpt = node_cpt->prev;
        }
        printf("|\n");
    }
}
