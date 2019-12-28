#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <math.h>
#include <timings.h>
#include <main.h>

using namespace std;

/// Computes the clock resolution
/// \return minimum delta time captured
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

/// Pseudo-random number generator implementation
/// \param seed seed to start the generation
/// \return pseudo-random generated float
double get_random_number(double* seed) {
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

/// Generates an input with "size" pseudo-randomly generated floats
/// \param size number of values
/// \return pseudo-randomly generated input
input* get_random_input(long long size) {
    input *out = (input*) malloc(sizeof(input));
    out->nums = (double*) malloc(sizeof(double) * size);
    out->count = size;

    double seed = time(NULL); //seed the current time of execution
    get_random_number(&seed); //seed initialization
    for(long long i = 0; i < size; i++) {
        out->nums[i] = get_random_number(&seed);
    }

    return out;
}

/// Compute the mean timing of execution of the solving algorithm applied to pseudo-randomly generated input
/// \param size size of pseudo-random generated input
/// \param t_min minimum execution time needed to ensure low system clock error
/// \return mean execution time
double get_timing(long long size, double t_min) {
    input * in;
    long long rep_tara = compute_repetitions(size, t_min, false);
    long long rep_lordo = compute_repetitions(size, t_min, true);

    auto t0 = chrono::high_resolution_clock::now();
    for(long long i = 0; i < rep_tara; i++) {
        in = get_random_input(size);
        free_input(in);
    }
    auto t1 = chrono::high_resolution_clock::now();
    auto elapsed_tara = chrono::duration<double>(t1- t0).count();

    t0 = chrono::high_resolution_clock::now();
    for(long long i = 0; i < rep_lordo; i++) {
        in = get_random_input(size);
        find_weighted_lower_median(in);
        free_input(in);
    }
    t1 = chrono::high_resolution_clock::now();
    auto elapsed_lordo = chrono::duration<double>(t1- t0).count();
    auto elapsed_mean = elapsed_lordo / (double)rep_lordo - elapsed_tara / (double)rep_tara;

    return elapsed_mean;
}

/// Compute the mean timing of execution of the solving algorithm applied to pseudo-randomly generated input
/// \param size size of pseudo-random generated input
/// \param t_min minimum execution time needed to ensure low system clock error
/// \param c number of iterations between error checks
/// \param za
/// \param max_error_percentage maximum accepted error as a percentage of average execution time
/// \return
result* get_timing(long long size, double t_min, int c, double za, double max_error_percentage) {
    double t = 0;
    double sum2 = 0;
    long long cn = 0;
    double m = 0;
    double e = 0;
    double s = 0;
    double delta = 0;

    do {
        clog << "Iterating: ";
        for(int i = 1; i <= c; i++) {
            m = get_timing(size, t_min);
            t += m;
            sum2 += m*m;
            clog << i << " ";
        }
        cn += c;
        e = t / cn;
        s = sqrt(sum2/cn - e*e);
        delta = (1/sqrt(cn)) * za * s;
        clog << "\nComputed delta: " << delta << " target: "<< e * max_error_percentage <<"\n";
    } while(delta > e * max_error_percentage);

    result *out = (result*) malloc(sizeof(result));
    out->avg_time = e;
    out->error = delta;

    return out;
}

/// Compute number of repetitions needed to ensure execution time of input preparation is above t_min
/// \param size size of pseudo-random generated input
/// \param t_min minimum execution time needed to ensure low system clock error
/// \param should_solve TRUE:computes the repetitions for preparing the input and solving, FALSE: only preparation
/// \return number of repetitions
long long compute_repetitions(long long size, double t_min, bool should_solve) {
    input *in;
    chrono::high_resolution_clock::time_point t0, t1;
    long long rep = 1;

    double elapsed = 0;
    while(elapsed <= t_min) {
        rep *= 2;
        t0 = chrono::high_resolution_clock::now();
        for(int i = 0; i < rep; i++) {
            in = get_random_input(size);
            if(should_solve) find_weighted_lower_median(in);
            free_input(in);
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
            in = get_random_input(size);
            if(should_solve) find_weighted_lower_median(in);
            free_input(in);
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