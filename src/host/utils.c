//
// Created by 23503 on 2022/11/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "utils.h"

void print_usage(char* filename)
{
    printf("usage: %s <options>\n", filename);
//    printf("  -f [kernel file]\n");
    printf("  -p [path to data]\n");
}

void parse_sdsoc_command_line_args(
        int argc,
        char** argv,
        char** path_to_data)
{

    int c = 0;

    while ((c = getopt(argc, argv, "p:")) != -1)
    {
        switch (c)
        {
            case 'p':
                *path_to_data = optarg;
                break;
            default:
            {
                print_usage(argv[0]);
                exit(-1);
            }
        } // matching on arguments
    } // while args present
}
