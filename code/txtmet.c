/*
 * This is a command line utility to get information from txt files.
 * It will return the number of words, characters, and lines in the file.
 * 
 * @author Hunter Baker
 * @version 1.01
 * @date Jan 26, 2025
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "filemetrics.h"

void usage();
void usage()
{
    printf("Usage: ./txtmet <option(s)> <input_file>\n");
    printf("Example: ./txtmet -a test.txt\n");
    printf("Supported filetypes: .txt\n");
    printf("Options:\n");
    printf("  -w: count words (default)\n");
    printf("  -c: count characters\n");
    printf("  -s: count sentences\n");
    printf("  -l: count lines\n");
    printf("  -a: count all\n");
}

int main(int argc, char **argv)
{
    bool defaultconfig = true;

    bool words = false; 
    bool chars = false;
    bool lines = false;
    bool sentences = false;

    if (argc < 2)
    {
        printf("No file or arguments provided\n");
        usage();
        exit(EXIT_FAILURE);
    }

    // parse the inputs 
    int i;
    while ((i = getopt(argc, argv, "wcsla")) != -1)
    {
        switch (i)
        {
        case 'w':
            words = true;
            defaultconfig = false;
            break;
        case 'c':
            chars = true;
            defaultconfig = false;
            break;
        case 's':
            sentences = true;
            defaultconfig = false;
            break;
        case 'l':
            lines = true;
            defaultconfig = false;
            break;
        case 'a':
            words = true;
            chars = true;
            lines = true;
            sentences = true;
            break;
        default:
            printf("ERROR: Invalid option\n");
            usage();
            exit(EXIT_FAILURE);
        }
    }

    if (optind != argc - 1)
    {
        printf("ERROR: No filename or extraneous input\n");
        usage();
        exit(EXIT_FAILURE);
    }

    char* filename = argv[optind];

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("ERROR: cannot open file\n");
        exit(EXIT_FAILURE);
    }

    // get the data from the file
    // words = 0, chars = 1, chars & spaces = 2, lines = 3, sentences = 4
    int data[5];
    getData(file, data);

    if (words || defaultconfig)
    {
        printf("Words\t\t %d\n", data[0]);
    }

    if (chars)
    {
        printf("Chars\t\t %d\n", data[1]);
        printf("Chars & Spaces\t% d\n", data[2]);
    }

    if (lines)
    {
        printf("Lines\t\t %d\n", data[3]);
    }

    if (sentences)
    {
        printf("Sentences\t %d\n", data[4]);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
