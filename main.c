//
// Created by arsma on 3/28/2024.
//

#include <stdio.h>
#include "Column.h"
#include "Dataframe.h"

int main(){
    printf("Welcome to our CDataFrame made by Arthur Smadja and Lucy Gros!\n");
    printf("Our application will allow you to create and manipulate a DataFrame and its columns.\n\n");
    printf("What do you want to do today?\n");
    printf("1. Create a CDataFrame\n");
    printf("2. Exit\n\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d",&choice);
    printf("\n");

    CDATAFRAME *cdf = NULL;
    CDATAFRAME **ptr = &cdf;

    switch(choice){
        case 1:
            cdf = user_fill_cdataframe();
            printf("This is your DataFrame\n");
            display_cdataframe_tab(cdf);
            printf("What do you want to do next?\n");
            printf("1.Add a column\n");
            printf("2.Delete a column with name\n");
            printf("3.Add a line of value\n");
            printf("4.Rename a column\n");
            printf("5.Delete the last line value\n");
            printf("6.Sort the CDataFrame\n");
            printf("7.Delete the CDataFrame\n");
            printf("8.Exit\n");

            printf("Enter your choice: ");
            int choice2;
            scanf("%d",&choice2);
            printf("\n");
            lnode *node_cpt = cdf ->tail;
            switch (choice2){
                case 1:
                    add_column(cdf);
                    display_cdataframe_tab(cdf);
                    break;
                case 2:
                    printf("Enter the name of the column you want to delete:");
                    char title[NAME_SIZE];
                    gets(title);
                    delete_column_data(cdf,title);
                    display_cdataframe_tab(cdf);
                    break;
                case 3:
                    add_value_col(cdf);
                    display_cdataframe_tab(cdf);
                    break;
                case 4:
                    rename_column(cdf);
                    display_cdataframe_tab(cdf);
                    break;
                case 5:
                    delete_last_line_value(cdf);
                    display_cdataframe_tab(cdf);
                    break;
                case 6:
                    while(node_cpt!=NULL){
                        COLUMN *col = (COLUMN*)node_cpt->data;
                        col = sort_column(col);
                        node_cpt=node_cpt->prev;
                    }
                    display_cdataframe_tab(cdf);
                    break;
                case 7:
                    delete_cdataframe(ptr);
                    break;
                case 8:
                    if(cdf!=NULL){
                        delete_cdataframe(ptr);
                    }
                    printf("Goodbye!\n");
                    break;
            }
            break;
        case 2:
            if(cdf!=NULL){
                delete_cdataframe(ptr);
            }
            printf("Goodbye!\n");
            break;
    }

    return 0;
}