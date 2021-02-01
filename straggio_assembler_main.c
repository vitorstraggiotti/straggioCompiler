
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    Assembly compiler

    Author: Vitor Henrique Andrade Helfensteller Straggiotti Silva
    Created on: 29/10/2020
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include<stdio.h>
#include<stdlib.h>
#include"str_process.h"

#define ASSEMBLY_SOURCE_FILE   1
#define INSTRUCTION_SET_FILE   2


int main(int argc, char *argv[])
{
    /*===== Comand line input validation ====================================*/
    if(argc != 3)
    {
        printf("Incorrect use of program arguments!!\n");
        printf("Correct use: straggio_compiler <assembly_source_file>"
               " <instruction_set_file>\n");
        exit(EXIT_FAILURE);
    }

    /*===== Loading instruction set to memory ===============================*/
    textFile_t instructionSet;

    instructionSet.totalLines = num_lines(argv[INSTRUCTION_SET_FILE]);
    instructionSet.maxLineWidth = max_width(argv[INSTRUCTION_SET_FILE]);

    instructionSet.text = load_file(argv[INSTRUCTION_SET_FILE], instructionSet.totalLines,
                                 instructionSet.maxLineWidth);

    /*===== Loading source code to memory ===================================*/
    textFile_t sourceCode;

    sourceCode.totalLines = num_lines(argv[ASSEMBLY_SOURCE_FILE]);
    sourceCode.maxLineWidth = max_width(argv[ASSEMBLY_SOURCE_FILE]);

    sourceCode.text = load_file(argv[ASSEMBLY_SOURCE_FILE], sourceCode.totalLines,
                                 sourceCode.maxLineWidth);

    /*===== Cleaning sourceCode.text ========================================*/
    sourceCode = clear_code(sourceCode);

    /*===== Solving address labels ==========================================*/
    unsigned int numAddrLabels = 0;

    /* Calculate the number of address labels on sourceCode */
    for(unsigned int line = 0; line < sourceCode.totalLines; line++)
    {
        for(unsigned int charIndex = 0; charIndex < sourceCode.maxLineWidth; charIndex++)
        {
            if(sourceCode.text[line][charIndex] == '\0')
                break;

            if(sourceCode.text[line][charIndex] == ':')
                numAddrLabels++;
        }
    }

    /* relating address labels to physical addresses */
    unsigned long int totalAddrSpace = 0;
    addrLabel_t       *addrLabel;

    addrLabel = (addrLabel_t *)malloc(numAddrLabels * sizeof(addrLabel_t));

    if(addrLabel == NULL)
    {
        printf("Error: Could not allocate memory for address labels");
        exit(EXIT_FAILURE);
    }

    for(unsigned int line = 0; line < sourceCode.totalLines; line++)
    {
        for(unsigned int charIndex = 0; charIndex < sourceCode.maxLineWidth; charIndex++)
        {
           /* ? */
        }
    }

#if 1
    printf("****************************************************\n");
    printf("Filename: %s \n", argv[ASSEMBLY_SOURCE_FILE]);
    printf("Number of lines: %u \n", sourceCode.totalLines);
    printf("Largest line: %u characters \n", sourceCode.maxLineWidth);
    printf("line vectors content:\n");
    for(unsigned int i=0; i < sourceCode.totalLines; i++)
    {
        printf("Vector %u :%s\n", i, sourceCode.text[i]);
    }
#endif

#if 1
    printf("****************************************************\n");
    printf("Filename: %s \n", argv[INSTRUCTION_SET_FILE]);
    printf("Number of lines: %u \n", instructionSet.totalLines);
    printf("Largest line: %u characters \n", instructionSet.maxLineWidth);
    printf("line vectors content:\n");
    for(unsigned int i=0; i < instructionSet.totalLines; i++)
    {
        printf("Vector %u :%s\n", i, instructionSet.text[i]);
    }
#endif

/*
    - Alocate memory for first parsing
    - Analyze and account for addr labels and compiler commands
    - Translate assembly to machine code
    - Replace addr labels with real addr

    - Convert raw program to intel .hex  (new library?)
    - Export program to .hex file

*/

    exit(EXIT_SUCCESS);
}
/*****************************************************************************/



#if 0
    /* testing function string_equal */
    char teste1[] = " ADD    R3,  R4";
    char teste2[] = " ADD R3, R4";

    printf("String1:%s\n", teste1);
    printf("String2:%s\n\n", teste2);

    if(string_equal(teste1, teste2))
    {
        printf("Strings are equal !\n");
    }
    else
    {
        printf("Strings are not equal !\n");
    }
#endif
