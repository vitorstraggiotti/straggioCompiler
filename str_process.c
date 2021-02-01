/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    String processing library

    Author: Vitor Henrique Andrade Helfensteller Straggiotti Silva
    Created on: 30/10/2020
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include<stdio.h>
#include<stdlib.h>
#include"str_process.h"


unsigned int num_lines(char* filename)
{
    FILE *file_fp;
    char tmp;
    unsigned int line_count = 0;

    file_fp = fopen(filename, "r");
    if(file_fp == NULL)
    {
        return 0;
    }

    while(1)
    {
        tmp = fgetc(file_fp);

        if(tmp == '\n')
        {
            line_count++;
        }
        else if(feof(file_fp))
        {
            break;
        }
    }

    fclose(file_fp);
    return line_count+1;
}
/*****************************************************************************/
unsigned int max_width(char *filename)
{
    FILE *file_fp;
    char tmp;
    unsigned int max_width = 0;
    unsigned int current_with = 0;

    file_fp = fopen(filename, "r");
    if(file_fp == NULL)
    {
        return 0;
    }

    tmp = fgetc(file_fp);
    while(1)
    {
        current_with++;

        if((tmp == '\n') || (tmp == ';'))
        {
            current_with = 0;
        }
        else if(feof(file_fp))
        {
            break;
        }

        if(current_with > max_width)
        {
            max_width = current_with;
        }

        tmp = fgetc(file_fp);

    }

    fclose(file_fp);
    return max_width+1;
}

/*****************************************************************************/
char **load_file(char *filename, unsigned int numLines, unsigned int lineWidth)
{
    FILE *file_fp;
    char tmp;
    unsigned int line_index = 0, width_index = 0;

    file_fp = fopen(filename, "r");
    if(file_fp == NULL)
    {
        printf("Error: could not open source code file");
        return NULL;
    }

    char **sourceCode = (char**)calloc(numLines, sizeof(char*));

    for(unsigned int i=0; i < numLines; i++)
    {
        sourceCode[i] = (char*)calloc(lineWidth + 1, sizeof(char));
        sourceCode[i][lineWidth] = '\0';
    }

    while(!feof(file_fp))
    {
        tmp = fgetc(file_fp);

        if(tmp == '\n')
        {
            sourceCode[line_index][width_index] = tmp;
            line_index++;
            width_index = 0;
            continue;
        }

        sourceCode[line_index][width_index] = tmp;
        width_index++;
    }

    fclose(file_fp);
    return sourceCode;
}

/*****************************************************************************/
textFile_t clear_code(textFile_t sourceCode)
{
    for(int line = 0; line < sourceCode.totalLines ; line++)
    {
        /* erasing comments and blank lines */
        for(unsigned int charIndex = 0; charIndex < sourceCode.maxLineWidth;
             charIndex++)
        {
            if((sourceCode.text[line][charIndex] == '\n') ||
               (sourceCode.text[line][charIndex] == ';'))
            {
                for(; charIndex < sourceCode.maxLineWidth; charIndex++)
                {
                    sourceCode.text[line][charIndex] = '\0';
                }
            }
        }

        /* erasing lines with just space character */
        unsigned int allSpaceFlag;
        allSpaceFlag = 1;
        for(unsigned int charIndex = 0; charIndex < sourceCode.maxLineWidth;
             charIndex++)
        {
            if((sourceCode.text[line][charIndex] != ' ') &&
               (sourceCode.text[line][charIndex] != '\0'))
            {
                allSpaceFlag = 0;
                break;
            }
        }

        if(allSpaceFlag)
        {
            for(unsigned int charIndex = 0; charIndex < sourceCode.maxLineWidth;
                 charIndex++)
            {
                sourceCode.text[line][charIndex] = '\0';
            }
        }

        /* removing erased lines from the source code block */
        if((sourceCode.text[line][0] == '\0') && (line < sourceCode.totalLines-1))
        {
            for(unsigned int lineTmp = line; lineTmp < sourceCode.totalLines-1;
                 lineTmp++)
            {
                sourceCode.text[lineTmp] = sourceCode.text[lineTmp+1];
            }

            //free(sourceCode.text[sourceCode.totalLines-1]);
            sourceCode.totalLines--;
            line--;
        }
    }

    return sourceCode;
}
/*****************************************************************************/
int string_equal(char *string1, char *string2)
{
    unsigned int index;
    unsigned int lengthStr1, lengthStr2;

    /* calculating string length */
    index = 0;
    while(string1[index] != '\0')
    {
        lengthStr1 = index + 1;
        index++;
    }

    index = 0;
    while(string2[index] != '\0')
    {
        lengthStr2 = index + 1;
        index++;
    }

    /* clean up unnecessary spaces */
    index = 0;
    while(string1[index] != '\0')
    {
        if((string1[index] == ' ') && (string1[index+1] == ' '))
        {
            for(unsigned int tmp = index; tmp < lengthStr1 - 2; tmp++)
            {
                string1[tmp + 1] = string1[tmp + 2];

                if((tmp + 2) == (lengthStr1 - 1))
                    string1[tmp + 2] = '\0';
            }

            index--;
        }

        index++;
    }

    index = 0;
    while(string2[index] != '\0')
    {
        if((string2[index] == ' ') && (string2[index+1] == ' '))
        {
            for(unsigned int tmp = index; tmp < lengthStr2 - 2; tmp++)
            {
                string2[tmp + 1] = string2[tmp + 2];

                if((tmp + 2) == (lengthStr2 - 1))
                    string2[tmp + 2] = '\0';
            }

            index--;
        }

        index++;
    }

    /* compare each character */
    index = 0;
    while((string1[index] != '\0') && (string2[index] != '\0'))
    {
        if(string1[index] != string2[index])
        {
            return 0;
        }

        index++;
    }

    /* return false if different length */
    if((string1[index] != '\0') || (string2[index] != '\0'))
    {
        return 0;
    }

    return 1;
}
