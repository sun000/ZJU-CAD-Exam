/*
* @Author: sun000
* @Date:   2018-06-02 21:41:30
* @Last Modified by:   sun000
* @Last Modified time: 2018-06-02 22:55:03
*/

#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

void segmentedBitonicSort(float * data, int* seg_id, int* seg_start, int n, int m) {
    int unitLen = 1 << (int)log2(n);
    if (n <= unitLen + unitLen / 2)  {
        for (int i = 0; i < 2; i++) {
            sort(data, data + unitLen);
             // sort(data + (n - unitLen) / 2, data + (n - unitLen) / 2 + unitLen);
            sort(data + n - unitLen, data + n);
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            sort(data, data + unitLen);
            sort(data + (n - unitLen) / 2, data + (n - unitLen) / 2 + unitLen);
            sort(data + n - unitLen, data + n);
        }
    }
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    float *data = new float[n];
    int *seg_start = new int[m + 1];
    for (int i = 0; i < n; i++)
        scanf("%f", &data[i]);
    for (int i = 0; i < m + 1; i++)
        scanf("%d", &seg_start[i]);

    segmentedBitonicSort(data, nullptr, seg_start, n, m);
    for (int i = 0; i < m; i++) {
        for (int j = seg_start[i]; j < seg_start[i + 1]; j++)
            printf("%f ", data[j]);
        printf("\n");
    }
}