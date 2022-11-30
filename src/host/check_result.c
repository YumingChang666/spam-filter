//
// Created by 23503 on 2022/11/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "check_result.h"
#include "typedefs.h"

// data structure only used in this file
typedef struct DataSet_s
{
    DataType*    data_points;
    LabelType*   labels;
    FeatureType* parameter_vector;
    size_t num_data_points;
    size_t num_features;
} DataSet;

// sub-functions for result checking
// dot product
float dotProduct(FeatureType* param_vector, DataType* data_point_i, const size_t num_features)
{
    FeatureType result = 0.0f;

    for (int i = 0; i < num_features; i ++ )
        result += param_vector[i] * data_point_i[i];
    return result;
}

// predict
LabelType getPrediction(FeatureType* parameter_vector, DataType* data_point_i, size_t num_features, const double treshold = 0)
{
    float parameter_vector_dot_x_i = dotProduct(parameter_vector, data_point_i, num_features);
    return (parameter_vector_dot_x_i > treshold) ? 1 : 0;
}

// compute error rate
double computeErrorRate(
        DataSet data_set,
        double* cumulative_true_positive_rate,
        double* cumulative_false_positive_rate,
        double* cumulative_error)
{

    size_t true_positives = 0, true_negatives = 0, false_positives = 0, false_negatives = 0;

    for (size_t i = 0; i < data_set.num_data_points; i++)
    {
        LabelType prediction = getPrediction(data_set.parameter_vector, &data_set.data_points[i * data_set.num_features], data_set.num_features);
        if (prediction != data_set.labels[i])
        {
            if (prediction == 1)
            false_positives++;
            else
            false_negatives++;
        }
        else
        {
            if (prediction == 1)
            true_positives++;
            else
            true_negatives++;
        }
    }

    double error_rate = (double)(false_positives + false_negatives) / data_set.num_data_points;

    *cumulative_true_positive_rate += (double)true_positives / (true_positives + false_negatives);
    *cumulative_false_positive_rate += (double)false_positives / (false_positives + true_negatives);
    *cumulative_error += error_rate;

    return error_rate;
}

// check results
void check_results(FeatureType* param_vector, DataType* data_points, LabelType* labels)
{
    FILE *ofile=NULL;
    ofile=fopen("output.txt","w");
    if (ofile!=NULL)
    {
        fprintf(ofile,"\nmain parameter vector: \n");
        for(int i = 0; i < 30; i ++ )
            fprintf(ofile,"m[ %d ]: %lf | ",i,param_vector[i]);/////////

        fprintf(ofile,"\n");

        // Initialize benchmark variables
        double training_tpr = 0.0;
        double training_fpr = 0.0;
        double training_error = 0.0;
        double testing_tpr = 0.0;
        double testing_fpr = 0.0;
        double testing_error = 0.0;

        // Get Training error
        DataSet training_set;
        training_set.data_points = data_points;
        training_set.labels = labels;
        training_set.num_data_points = NUM_TRAINING;
        training_set.num_features = NUM_FEATURES;
        training_set.parameter_vector = param_vector;
        computeErrorRate(training_set, &training_tpr, &training_fpr, &training_error);

        // Get Testing error
        DataSet testing_set;
        testing_set.data_points = &data_points[NUM_FEATURES * NUM_TRAINING];
        testing_set.labels = &labels[NUM_TRAINING];
        testing_set.num_data_points = NUM_TESTING;
        testing_set.num_features = NUM_FEATURES;
        testing_set.parameter_vector = param_vector;
        computeErrorRate(testing_set, &testing_tpr, &testing_fpr, &testing_error);

        training_tpr *= 100.0;
        training_fpr *= 100.0;
        training_error *= 100.0;
        testing_tpr *= 100.0;
        testing_fpr *= 100.0;
        testing_error *= 100.0;

        fprintf(ofile,"Training TPR: %lf \n",training_tpr);
        fprintf(ofile,"\"Training FPR: %lf \n",training_fpr);
        fprintf(ofile,"Training Error: %lf \n",training_error);
        fprintf(ofile,"Testing TPR: %lf \n",testing_tpr);
        fprintf(ofile,"Testing FPR: %lf \n",testing_fpr);
        fprintf(ofile,"Testing Error: %lf \n",testing_error);
    }
    else
    {
        printf("Failed to create output file!\n");
    }
}
