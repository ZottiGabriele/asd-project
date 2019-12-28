#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <main.h>
#include <limits.h>

using namespace std;

int main(int argc, char **argv) {

    //set input and output streams precision
    cin.precision (numeric_limits<double>::max_digits10);
    cout.precision (numeric_limits<float>::max_digits10);
    clog.precision (numeric_limits<double>::max_digits10);

#ifdef GET_TIMINGS

    //setup timings measurement
    cout.precision (numeric_limits<double>::max_digits10);
    int size = 10000;
    if(argc > 1) {
        size = atoi(argv[1]);
    }

    //compute the clock resolution to compute t_min
    double clock_resolution = compute_clock_resolution();
    //accepted error of 5%
    float k = 0.05;
    //compute minimum execution time to ensure an error lower then k
    double t_min = clock_resolution / k + 0.25; //added 0.25 seconds to ensure better coverage

    //get the average timing of find_weighted_lower_median for random inputs of "size" elements with an error lower then 5% of average timing
    result* timing_result = get_timing(size, t_min, 5, 1.96, 0.05);

    clog << fixed << "Size: " << size << " | Average time elapsed: " << timing_result->avg_time << " | ";
    clog << fixed << "Error: " << timing_result->error << "\n";
    cout << fixed << size << "," << timing_result->avg_time << "," << timing_result->error  << "\n";
#else
    //just solve the problem without getting timings
    input *in = get_input_from_stdin();
    double solution = find_weighted_lower_median(in);
    cout << fixed << solution << "\n";
#endif
    return 0;
}

/// Algorithm to find the weighted lower median of n float elements
/// \param in input structure, REQUIRES to be correctly initialized
/// \return weighted lower median value
double find_weighted_lower_median(input* in) {

    //sort the input
    sort(in);

    //compute the total sum of all values
    double W = 0;
    for(int i = 0; i < in->count; i++) {
        W += in->nums[i];
    }

    int i = 0;
    double weight = 0;
    bool found = false;
    for(int j = 0; j < in->count; j++) {
        //accumulate the next value
        weight += in->nums[j];
        //if we reach or go over W/2 we found the wighted lower median
        if(!found && weight >= W/2) {
            i = j;
            found = true;
        }
    }

    return in->nums[i];
}

/// Wrapper for merge sort implementation
/// \param in input to sort
void sort(input *in) {
    mergeSort(in->nums, 0, in->count - 1);
}

/// Merge sort implementation
/// \param arr target array to sort
/// \param a start index
/// \param b end index
void mergeSort(double *arr, int a, int b) {
    if(a < b) {
        int r = (b + a) / 2;
        mergeSort(arr, a, r);
        mergeSort(arr, r+1, b);
        merge(arr, a, r, b);
    }
}

/// Orders the results of two mergeSort calls
/// \param arr target array
/// \param a start index 1
/// \param r end index 1
/// \param b end index 2
void merge(double *arr, int a, int r, int b) {

    int i = a;
    int j = r+1;

    double *tmp = (double *) malloc(sizeof(double) * (b-a+1));

    for(int k = 0; k < b-a+1; k++) {

        double x = (i <= r) ? arr[i] : numeric_limits<double>::max();
        double y = (j <= b) ? arr[j] : numeric_limits<double>::max();

        if(x < y) {
            tmp[k] = x;
            i++;
        } else {
            tmp[k] = y;
            j++;
        }
    }

    for(int k = 0; k < b-a+1; k++) {
        arr[a + k] = tmp[k];
    }

    free(tmp);
}