#include <stdio.h>
#include "filemetrics.h"

#define TAB '\t'
#define SPACE ' '
#define NEWLINE '\n'


int getData(FILE *file, int *data)
{
    if (file == NULL) 
    {
        return -1;
    }

    data[0] = 0; // words
    data[1] = 0; // chars w/o whitespace
    data[2] = 0; // chars w whitespace
    data[3] = 0; // lines
    data[4] = 0; // sentences

    int c; 
    int lastc = 0; // so we can check if characters occurred between what we're checking

    while ((c = fgetc(file)) != EOF)
    {
        if ((c == NEWLINE || c == SPACE) && (lastc != SPACE && lastc != TAB && lastc != NEWLINE))
        {
            data[0]++;
        }

        // characters excluding whitespace
        if (c != SPACE && c != TAB && c != NEWLINE)
        {
            data[1]++;
        }

        data[2]++; // we should always count characters including whitespace

        // count our lines 
        if (c == NEWLINE) 
        {
            data[3]++;
        }

        // count sentences
        if ((lastc != '.' || lastc != '!' || lastc != '?') && (c == '.' || c == '!' || c == '?'))
        {
            data[4]++;
        }
        lastc = c;
    }

    // if our last character wasnt whitespace
    // then we have one more word and line to count 
    if (lastc != SPACE && lastc != TAB && lastc != NEWLINE)
    {
        data[0]++;
        data[3]++;
    }

    return 1;
}