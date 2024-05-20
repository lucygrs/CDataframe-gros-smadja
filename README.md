# pychatbot-gros-smadja

DataFrame Function: 

CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);
Takes as parameters pointer on an ENUM_TYPE list corresponding to the type of each column and a size corresponding to the number of columns in the DataFrame.

void delete_cdataframe(CDATAFRAME ** cdf);
Takes a pointer of pointer type CDATFRAME as parameter and deletes the entire CDataFrame.

int get_cdataframe_cols_size(CDATAFRAME *cdf);
Takes as parameter a jumper on a CDataFrame and returns its number of columns.

CDATAFRAME *user_fill_cdataframe();
Does not take any parameters but allows the user to choose the number of columns they want, the type of each column and to fill in each column manually. 

CDATAFRAME *create_umpty_cdataframe();
Does not take any parameters, but can be used to create an empty DataFrame

void display_cdataframe(CDATAFRAME *cdf);
Function for displaying each column of the CdataFrame one below the other

void add_value_col(CDATAFRAME *cdf);
Function used to enter a value row, which means that an additional value can be entered for each column.

void delete_last_line_value(CDATAFRAME *cdf);
Function used to delete the last line of each column of the DataFrame. It takes a pointer to a CDataframe as parameter.

void add_column(CDATAFRAME *cdf);
Function used to add a column to the CDF. It takes a pointer to a CDataframe as parameter.

void rename_column(CDATAFRAME *cdf);
Function for renaming a column based on its position in the CDF. It takes a pointer to a CDataframe as parameter.

void display_name_column(CDATAFRAME *cdf);
Function for displaying all the column names in the CDF. It takes a pointer to a CDataframe as parameter.

int display_nb_line(CDATAFRAME *cdf);
Function to return the number of rows in the first column of the CDF. It takes a pointer to a CDataframe as parameter.

void display_value(COLUMN* col, int index);
void display_cdataframe_tab(CDATAFRAME *cdf);
These two functions display the CDF in the form of an array. Note that they were created with the help of a youtube tutorial from the PortoFolio Courses channel. display_cdataframe_tab takes as parameter a pointer of type CDF and display_value takes as parameter a pointer of type column and an integer corresponds to the number of columns.
