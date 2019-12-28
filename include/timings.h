//
// Created by Gabriele Zotti on 09/11/2019.
//

#ifndef ASD_PROJECT_TIMINGS_H
#define ASD_PROJECT_TIMINGS_H

#include <input_handeler.h>

double compute_clock_resolution();
double get_random_number(double* seed);
input* get_random_input(long long size);
double get_timing(long long size, double t_min);
result* get_timing(long long size, double t_min, int c, double za, double max_error_percentage);
long long compute_repetitions(long long size, double t_min, bool should_solve);

#endif //ASD_PROJECT_TIMINGS_H
