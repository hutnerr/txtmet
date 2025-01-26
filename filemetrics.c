#include <stdio.h>
#include "filemetrics.h"

int getData(FILE *file, int *data)
{
    if (file == NULL) 
    {
        return -1;
    }

    // 0 = words, 1 = chars, 2 = lines
    data[0] = 0; 
    data[1] = 0;
    data[2] = 0; 

    // FIXME: add another character counter, one that includes whitespace and one that doesnt 

    int c;
    int lastC = 0;

    while ((c = fgetc(file)) != EOF)
    {
        if (lastC != '\n' && lastC != ' ' && lastC != '\t')
        {
            data[1]++; // count characters
        }

        if (c == ' ' || c == '\n' || c == '\t')
        {
            if (lastC != ' ' && lastC != '\n' && lastC != '\t')
            {
                data[0]++; // count words
            }
        }

        if (c == '\n')
        {
            data[2]++; // count lines
        }
        lastC = c;
    }

    if (data[1] > 0)
    {
        if (lastC != ' ' && lastC != '\n' && lastC != '\t')
        {
            data[0]++; // count the last word
        }
        data[2]++; // count the last line
    }
    return 1;
}