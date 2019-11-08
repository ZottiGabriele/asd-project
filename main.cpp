#include <iostream>
#include <stdlib.h>
#include <limits>
#include <chrono>
#include <math.h>
#include <functional>

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
long long compute_repetitions(long long size, double t_min, bool should_solve);
double get_timing(long long size, double t_min);
float get_random_number(double* seed);
input* get_random_input(long long size);


int main(int argc, char **argv) {

#ifdef GET_TIMINGS
    //mesure timings
    int size = 10;
    if(argc > 1) {
        size = atoi(argv[1]);
    }
    input *in = get_random_input(size);

    double clock_resolution = compute_clock_resolution();
    cout.precision(15);
    clog.precision(15);
    //clog << fixed << "Clock has resolution of " << clock_resolution  << "\n";

    float k = 0.05; //accepted error of 5%
    double t_min = clock_resolution / k + 0.5; //added 0.5 seconds to ensure better

    double timing = get_timing(size, t_min);
    clog << fixed << "Size: " << size << " | Average time elapsed: " << timing  << "\n";
    cout << fixed << size << "," << timing << "\n";
#else
    //just solve the problem without getting timings
    input *in = parseInput();
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

long long compute_repetitions(long long size, double t_min, bool should_solve) {
    chrono::high_resolution_clock::time_point t0, t1;
    long long rep = 1;
    double elapsed = 0;
    while(elapsed <= t_min) {
        rep *= 2;
        t0 = chrono::high_resolution_clock::now();
        for(int i = 0; i < rep; i++) {
            input *in = get_random_input(size);
            if(should_solve) solve(in);
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
            input *in = get_random_input(size);
            if(should_solve) solve(in);
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

double get_timing(long long size, double t_min) {
    long long rep_tara = compute_repetitions(size, t_min, false);
    long long rep_lordo = compute_repetitions(size, t_min, true);
    auto t0 = chrono::high_resolution_clock::now();
    for(long long i = 0; i < rep_tara; i++) {
        input * in = get_random_input(size);
    }
    auto t1 = chrono::high_resolution_clock::now();
    auto elapsed_tara = chrono::duration<double>(t1- t0).count();
    t0 = chrono::high_resolution_clock::now();
    for(long long i = 0; i < rep_lordo; i++) {
        input * in = get_random_input(size);
        solve(in);
    }
    t1 = chrono::high_resolution_clock::now();
    auto elapsed_lordo = chrono::duration<double>(t1- t0).count();
    auto elapsed_mean = elapsed_lordo / (double)rep_lordo - elapsed_tara / (double)rep_tara;
    return elapsed_mean;
}

float get_random_number(double* seed) {
    int a = 16807;
    int m = 2147483647;
    int q = 127773;
    int r = 2836;
    double hi = ceil(*seed / q);
    double lo = *seed - q * hi;
    double test = a * lo - r * hi;
    if(test < 0.0) {
        *seed = test + m;
    } else {
        *seed = test;
    }
    return *seed / m;
}

input* get_random_input(long long size) {
    input *out = (input*) malloc(sizeof(input));
    out->nums = (float*) malloc(sizeof(float) * size);
    out->count = size;
    double seed = time(NULL); //seed the current time of execution
    get_random_number(&seed); //seed initialization
    for(long long i = 0; i < size; i++) {
        out->nums[i] = get_random_number(&seed);
    }
    return out;
}