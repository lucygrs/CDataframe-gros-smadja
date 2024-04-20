//
// Created by arsma on 3/28/2024.
//

#include <stdio.h>

#include "Column.h"

int main(){
    COLUMN* col = create_column("My first column");

    insert_value(col, 5);
    insert_value(col, 6);
    insert_value(col, 7);
    insert_value(col, 8);
    insert_value(col, 9);
    insert_value(col, 5655);
    insert_value(col, 5655);
    insert_value(col, 5655);
    insert_value(col, 5655);

    printf("Occurences of %d : %d\n", 5655, occurences(col, 5655));
    printf("Number of values greater than %d : %d\n", 9, values_strictly_greater_than(col, 9));
    printf("Number of values lower than %d : %d\n", 9, values_strictly_lower_than(col, 9));
    printf("Number of values equal to %d : %d\n", 5655, values_equal_to(col, 5655));



    print_col(col);
    delete_column(col);

}