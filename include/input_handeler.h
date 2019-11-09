//
// Created by Gabriele Zotti on 09/11/2019.
//

#ifndef ASD_PROJECT_INPUT_HANDELER_H
#define ASD_PROJECT_INPUT_HANDELER_H

typedef struct input {
    float *nums;
    long long count;
};

typedef struct result {
    double avg_time;
    double error;
};

input* get_input_from_stdin();
void free_input(input *in);

#endif //ASD_PROJECT_INPUT_HANDELER_H
