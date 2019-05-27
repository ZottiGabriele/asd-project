#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct input {
    float *nums;
    int count;
};

input *parseInput();
void sort(input *arr);
void mergeSort(float *arr, int a, int b);
void merge(float *arr, int a, int r, int b);
void solve(input *in);

int main(int argc, char **argv) {

    input *in = parseInput();

    cout << "Read " << in->count << " numbers -> ";
    for(int i = 0; i < in->count; i++) {
        cout << in->nums[i] << " ";
    }
    cout << endl;

    solve(in);

    return 0;
}

void solve(input *in) {
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

    cout << "The solution is " << in->nums[i] << endl;
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
    char sep;

    while(sep != '.') {
        in->count++;
        in->nums = (float *) realloc(in->nums, sizeof(float) * in->count);
        cin >> in->nums[in->count - 1] >> sep;
    }

    return in;
}