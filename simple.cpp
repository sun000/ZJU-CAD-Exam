/*
* @Author: sun000
* @Date:   2018-06-02 10:38:10
* @Last Modified by:   sun000
* @Last Modified time: 2018-06-03 20:10:12
*/


#include <cstdio>
#include <algorithm>

const int DEBUG = 0;

using namespace std;

void sortUp(float* data, int n);
void sortDown(float* data, int n);
void mergeUp(float* data, int n);
void mergeDown(float* data, int n);

int step = 0;

void sortUp(float* data, int n) {
    if (DEBUG) {
        printf("> %d Up: ", step++);
        for (int i = 0; i < n; i++)
            printf("%.f ", data[i]);
        printf("\n");
    }
    if (n == 1) {
        if (DEBUG) {
            printf("> %d Up: ", --step);
            for (int i = 0; i < n; i++)
                printf("%.f ", data[i]);
            printf("\n");
        }
        return;
    }
    
    sortUp(data + (n + 1) / 2, n / 2);
    sortDown(data, (n + 1) / 2);
    mergeUp(data, n);
    if (DEBUG) {
        printf("< %d UP:", --step);
        for (int i = 0; i < n; i++)
            printf("%.f ", data[i]);
        printf("\n");
    }
}

void sortDown(float* data, int n) {
    if (DEBUG) {
        printf("> %d Down: ", step++);
        for (int i = 0; i < n; i++)
            printf("%.f ", data[i]);
        printf("\n");
    }
    if (n == 1) {
        if (DEBUG) {
            printf("> %d Down: ", --step);
            for (int i = 0; i < n; i++)
                printf("%.f ", data[i]);
            printf("\n");
        }
        return;
    }

    sortDown(data, (n + 1) / 2);
    sortUp(data + (n + 1) / 2, n / 2);
    mergeDown(data, n);
    if (DEBUG) {
        printf("< %d Down: ", --step);
        for (int i = 0; i < n; i++)
            printf("%.f ", data[i]);
        printf("\n");
    }
}

void mergeUp(float* data, int n) {
    if (n == 1) return;
    int mid;
    if (n & 1) {
        if (data[0] < data[1]) {
            mid = n / 2;
            for (int i = 0; i < n / 2; i++)
                if (data[i] > data[mid + i + 1])
                    swap(data[i], data[mid + i + 1]);
        } else {
            mid = (n + 1) / 2;
            for (int i = 0; i < n / 2; i++)
                if (data[i] > data[mid + i])
                    swap(data[i], data[mid + i]);
        }
    }
    else {
        mid = n / 2;
        for (int i = 0; i < n / 2; i++)
            if (data[i] > data[mid + i])
                swap(data[i], data[mid + i]);
    }
    mergeUp(data, mid);
    mergeUp(data + mid,  n - mid);
}

void mergeDown(float * data, int n) {
    if (n == 1) return;
    int mid;
    if (n & 1) {
        if(data[0] < data[1]) {
            mid = (n + 1) / 2;
            for (int i = 0; i < n / 2; i++)
                if (data[i] < data[mid + i])
                    swap(data[i], data[mid + i]);
        } else {
            mid = n / 2;
            for (int i = 0; i < n / 2; i++)
                if (data[i] < data[mid + i])
                    swap(data[i], data[mid + i]);
        }
    }
    else {
        mid = (n + 1) / 2;
        for (int i = 0; i < n / 2; i++)
            if (data[i] < data[mid + i])
                swap(data[i], data[mid + i]);
    }
    mergeDown(data, mid);
    mergeDown(data + mid, n - mid);
}


void segmentedBitonicSort(float * data, int* seg_id, int* seg_start, int n, int m) {
    for (int i = 0; i < m; i++) {
        int s = seg_start[i], e = seg_start[i + 1];
        sortUp(data + s, e - s);
    }
}

int main(void) {
    // int n, m;
    // scanf("%d %d", &n, &m);
    // float *data = new float[n];
    // int *seg_start = new int[m + 1];
    // for(int i = 0; i < n; i++)
    //     scanf("%f", &data[i]);
    // for(int i = 0; i < m + 1; i++)
    //     scanf("%d", &seg_start[i]);

    int n = 9, m = 1;
    float data[] = {7, 0, 1, 2, 3, 5, 6, 8, 4};
    
    int seg_start[] = {0, n};
    // mergeUp(data, n);
    segmentedBitonicSort(data, nullptr, seg_start, n, m);

    for (int i = 0; i < m; i++) {
        for (int j = seg_start[i]; j < seg_start[i + 1]; j++)
            printf("%.f ", data[j]);
        printf("\n");
    }
}