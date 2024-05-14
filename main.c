//
// Created by arsma on 3/28/2024.
//

#include <stdio.h>

#include "Column.h"
#include "Dataframe.h"

int main(){
    COLUMN* col = create_column(INT, "My first column");

    insert_value(col, (COL_TYPE)5);
    insert_value(col, (COL_TYPE)6);
    insert_value(col, (COL_TYPE)7);
    insert_value(col, (COL_TYPE)8);
    insert_value(col, (COL_TYPE)9);
    insert_value(col, (COL_TYPE)5655);
    insert_value(col, (COL_TYPE)5655);
    insert_value(col, (COL_TYPE)5655);
    insert_value(col, (COL_TYPE)5655);

    int value = 5655;
    printf("Occurences of %d : %d\n", 5655, occurences(col, &value));
    printf("Number of values greater than %d : %d\n", 9, values_strictly_greater_than(col, (COL_TYPE)9));
    printf("Number of values lower than %d : %d\n", 9, values_strictly_lower_than(col, (COL_TYPE)9));
    printf("Number of values equal to %d : %d\n", 5655, values_equal_to(col, (COL_TYPE)5655));

    print_col(col);
    delete_column(col);
/*

    //on se propose ici de créer un dataframe qui contiendra une colonne par jour de la semaine, et une ligne par heure
    //pour chaque heure on pourra remplir le nombre de calories brûlée
    DATAFRAME* dataframe = create_dataframe();
    char** days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for(int i = 0; i<7; i++){
        add_column(dataframe);
        rename_column_at_index(dataframe, i, days[i]);
    }
    for(int i = 0; i<24; i++){
        add_row(dataframe);
    }
    printf("Remplissage du dataframe");
    for(int i = 0; i<24; i++){
        fill_column_at_index(dataframe, i);
    }

    delete_dataframe(dataframe);*/


}