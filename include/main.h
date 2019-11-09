//
// Created by Gabriele Zotti on 09/11/2019.
//

#ifndef ASD_PROJECT_MAIN_H
#define ASD_PROJECT_MAIN_H

#include <input_handeler.h>
#include <timings.h>

void sort(input *in);
void mergeSort(float *arr, int a, int b);
void merge(float *arr, int a, int r, int b);
float find_weighted_lower_median(input* in);

#endif //ASD_PROJECT_MAIN_H
