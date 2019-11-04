#include <iostream>
#include <stdlib.h>
#include <limits>
#include <chrono>

using namespace std;

typedef struct input {
    float *nums;
    long long count;
};

input *parseInput();
void sort(input *arr);
void mergeSort(float *arr, int a, int b);
void merge(float *arr, int a, int r, int b);
float solve(input *in);
double compute_clock_resolution();
long long compute_repetitions(input* in, double t_min);
double get_timing(input* in, long long rep);

int main(int argc, char **argv) {

    freopen("/Users/gabrielezotti/Documents/asd-project/input.txt", "r", stdin);
    input *in = parseInput();

#ifdef GET_TIMINGS
    //mesure timings
    double clock_resolution = compute_clock_resolution();
    cout.precision(15);
    cout << fixed << "Clock has resolution of " << clock_resolution  << "\n";

    float k = 0.05; //accepted error of 5%
    double t_min = clock_resolution / k + 0.5; //added 0.5 seconds to ensure better
    long long rep = compute_repetitions(in, t_min);
    cout << "To make the program run for " << t_min << "s repetitions needed = " << rep << "\n";

    double timing = get_timing(in, rep);
    cout << fixed << "Time elapsed: " << timing  << " with average: " << timing/rep <<"\n";
#else
    //just solve the problem without getting timings
    float solution = solve(in);
    cout << to_string(solution) << "\n";
#endif
    return 0;
}

float solve(input *in) {
    sort(in);

    float W = 0;

    for(int i = 0; i < in->count; i++) {
        W += in->nums[i];
    }

    int i = 0;
    float weight = 0;
    while(true) {
        weight += in->nums[i];
        if(weight >= W/2) {
            break;
        } else {
            i++;
        }
    }

    return in->nums[i];
}

void sort(input *arr) {
    mergeSort(arr->nums, 0, arr->count - 1);
}

void mergeSort(float *arr, int a, int b) {
    if(a < b) {
        int r = (b + a) / 2;
        mergeSort(arr, a, r);
        mergeSort(arr, r+1, b);
        merge(arr, a, r, b);
    }
}

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
}

input *parseInput() {

    input *in = (input *) malloc(sizeof(input));
    in->nums = (float *) malloc(sizeof(float));
    in->count = 0;
    char sep;

    while(sep != '.') {
        in->count++;
        in->nums = (float *) realloc(in->nums, sizeof(float) * in->count);
        cin >> in->nums[in->count - 1] >> sep;
    }

    return in;
}

double compute_clock_resolution() {
    auto t0 = chrono::high_resolution_clock::now();
    auto t1 = chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<double>( t1 - t0 ).count();
    while(elapsed == 0) {
        t1 = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration<double>( t1 - t0 ).count();
    }

    return elapsed;
}

long long compute_repetitions(input* in, double t_min) {
    chrono::high_resolution_clock::time_point t0, t1;
    long long rep = 1;
    double elapsed = 0;
    while(elapsed <= t_min) {
        rep *= 2;
        t0 = chrono::high_resolution_clock::now();
        for(int i = 0; i < rep; i++) {
            solve(in);
        }
        t1 = chrono::high_resolution_clock::now();
        elapsed = chrono::duration<double>(t1 - t0).count();
    }

    long long max = rep;
    long long min = rep / 2;
    int err_cycles = 5;
    while(max - min >= err_cycles) {
        rep = (max + min) / 2;
        t0 = chrono::high_resolution_clock::now();
        for(int i = 0; i < rep; i++) {
            solve(in);
        }
        t1 = chrono::high_resolution_clock::now();
        elapsed = chrono::duration<double>(t1 - t0).count();
        if(elapsed <= t_min) {
            min = rep;
        } else {
            max = rep;
        }
    }
    return max;
}

double get_timing(input* in, long long rep) {
    auto t0 = chrono::high_resolution_clock::now();
    for(long long i = 0; i < rep; i++) {
        solve(in);
    }
    auto t1 = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration<double>(t1- t0).count();
    return elapsed;
}