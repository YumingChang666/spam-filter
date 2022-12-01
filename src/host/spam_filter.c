//
// Created by 23503 on 2022/11/24.
//

// standard C/C++ headers
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

# include "../sw/sgd_sw.h"

// other headers
#include "utils.h"
#include "typedefs.h"
#include "check_result.h"

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

    printf("Spam Filter Application\n");

    char* path_to_data;
    char* str_points_filepath=NULL;
    char* str_labels_filepath=NULL;
    char str_points_filepath_array[150];
    char str_labels_filepath_array[150];

    path_to_data=parse_sdsoc_command_line_args(argc, argv, path_to_data);
//    path_to_data="./data";
    printf("path_to_data: %s \n",path_to_data);

    // allocate space
    // for software verification
    DataType*    data_points  = (DataType*)malloc(sizeof(DataType)*DATA_SET_SIZE);
    LabelType*   labels       = (LabelType*)malloc(sizeof(LabelType)*NUM_SAMPLES);
    FeatureType* param_vector = (FeatureType*)malloc(sizeof(FeatureType)*NUM_FEATURES);

    // read in dataset
    sprintf(str_points_filepath_array,"%s/shuffledfeats.dat",path_to_data);
    sprintf(str_labels_filepath_array,"%s/shuffledlabels.dat",path_to_data);
    str_points_filepath=str_points_filepath_array;
    str_labels_filepath=str_labels_filepath_array;

    FILE* data_file;
    FILE* label_file;

    data_file = fopen(str_points_filepath, "r");
    if (!data_file)
    {
        printf("Failed to open data file %s!\n", str_points_filepath);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < DATA_SET_SIZE; i ++ )
    {
        float tmp;
//        if(fscanf(data_file, "%f", &tmp));
        int r=fscanf(data_file, "%f", &tmp);
        if(r==-1)
        {
            printf("Fscanf Failed.\n");
            return EXIT_FAILURE;
        }
        data_points[i] = tmp;
    }
    fclose(data_file);

    label_file = fopen(str_labels_filepath, "r");
    if (!label_file)
    {
        printf("Failed to open label file %s!\n", str_labels_filepath);
        return EXIT_FAILURE;
    }
    for (int j = 0; j < NUM_SAMPLES; j ++ )
    {
        int tmp;
//        if(fscanf(label_file, "%d", &tmp));
        int d=fscanf(label_file, "%d", &tmp);
        if(d==-1)
        {
            printf("Fscanf Failed.\n");
            return EXIT_FAILURE;
        }
        labels[j] = tmp;
    }
    fclose(label_file);


    // reset parameter vector
    for (size_t k = 0; k < NUM_FEATURES; k++)
        param_vector[k] = 0;

    // timers
    struct timeval start, end;

    // sw version host code
    gettimeofday(&start, NULL);
    SgdLR_sw(data_points, labels, param_vector);
    gettimeofday(&end, NULL);


    // check results
    printf("Checking results:\n");
    check_results( param_vector, data_points, labels );

    // print time
    long long elapsed = (end.tv_sec - start.tv_sec) * 1000000LL + end.tv_usec - start.tv_usec;
    printf("elapsed time: %lld us\n", elapsed);

    // cleanup
    free(data_points);
    free(labels);
    free(param_vector);

    return EXIT_SUCCESS;
}
