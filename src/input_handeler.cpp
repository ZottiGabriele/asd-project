#include <input_handeler.h>
#include <cstdlib>
#include <iostream>

using namespace std;

/// Parses the input from stdin
/// \return parsed input
input *get_input_from_stdin() {

    input *in = (input *) malloc(sizeof(input));
    in->nums = (double *) malloc(sizeof(double));
    in->count = 0;
    char sep;

    while(sep != '.') {
        in->count++;
        in->nums = (double *) realloc(in->nums, sizeof(double) * in->count);
        cin >> in->nums[in->count - 1] >> sep;
    }

    return in;
}

/// Deallocates the memory used by a input structure
/// \param in target structure
void free_input(input *in) {
    free(in->nums);
    free(in);
}