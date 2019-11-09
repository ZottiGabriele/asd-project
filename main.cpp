#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <main.h>

using namespace std;

int main(int argc, char **argv) {

    //set precision of output stream
    cout.precision(15);
    clog.precision(15);

#ifdef GET_TIMINGS
    //setup timings measurement
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
    float solution = find_weighted_lower_median(in);
    cout << to_string(solution) << "\n";
#endif
    return 0;
}

/// Algorithm to find the weighted lower median of n float elements
/// \param in input structure, REQUIRES to be correctly initialized
/// \return weighted lower median value
float find_weighted_lower_median(input* in) {

    //sort the input
    sort(in);

    //compute the total sum of all values
    float W = 0;
    for(int i = 0; i < in->count; i++) {
        W += in->nums[i];
    }

    int i = 0;
    float weight = 0;
    while(true) {
        //accumulate the next value
        weight += in->nums[i];
        //if we reach or go over W/2 we found the wighted lower median
        if(weight >= W/2) {
            break;
        } else {
            i++;
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
void mergeSort(float *arr, int a, int b) {
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
void merge(float *arr, int a, int r, int b) {

    int i = a;
    int j = r+1;

    float *tmp = (float *) malloc(sizeof(float) * (b-a+1));

    for(int k = 0; k < b-a+1; k++) {

        float x = (i <= r) ? arr[i] : numeric_limits<float>::max();
        float y = (j <= b) ? arr[j] : numeric_limits<float>::max();

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