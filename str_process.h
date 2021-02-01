/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    String processing library header file

    Author: Vitor Henrique Andrade Helfensteller Straggiotti Silva
    Created on: 30/10/2020
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _STR_PROCESS_H_
#define _STR_PROCESS_H_

#define ADDR_LABEL_BUFF_SIZE    40

struct textFile
{
    char **text;
    unsigned int totalLines;
    unsigned int maxLineWidth;
}; typedef struct textFile textFile_t;

struct addrLabel
{
    char       label[ADDR_LABEL_BUFF_SIZE];
    u_int16_t  addr;
}; typedef struct addrLabel addrLabel_t;

/* Returns the total number of lines in file. */
/*Return 0 if fail */
unsigned int num_lines(char *filename); /********************************************** WORKING */


/* Returns the number of characters in the longest line (before ';' or '\n') */
/* Return 0 if fail */
unsigned int max_width(char *filename); /********************************************** WORKING */


/* Return vector of pointers to string corresponding to each line of source code */
/* Return NULL if fail */
char **load_file(char *filename, unsigned int lines, unsigned int line_width); /******* WORKING */


/* Parse source code erasing comments and blank lines */
textFile_t clear_code(textFile_t sourceCode); /**************************************** WORKING */


/* Compare two strings ignoring excessive spaces between printable characters. */
/* If there is more than one space in sequence they are reduced to just one. */
/* Return 1 if equal and 0 if not equal */
/* Ex:  |  TEST1    R1,   R2  |  equal  */
/*      | TEST1 R1, R2        |         */

/* Ex:  |  TEST1    R1,   R2  | not equal  */
/*      | TEST1 R1,R2         |            */

int string_equal(char *string1, char *string2);

#endif  /* __STR_PROCESS__ */
