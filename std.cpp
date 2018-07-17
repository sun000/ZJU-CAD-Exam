/*
* @Author: sun000
* @Date:   2018-06-02 11:32:59
* @Last Modified by:   sun000
* @Last Modified time: 2018-06-03 09:34:35
*/


#include <cstdio>
#include <algorithm>

using namespace std;

void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {
    for (int i = 0; i < m; i++) {
        int s = seg_start[i], e = seg_start[i + 1];
        sort(data + s, data + e);
    }
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    float *data = new float[n];
    int *seg_start = new int[m + 1];
    for(int i = 0; i < n; i++)
        scanf("%f", &data[i]);
    for(int i = 0; i < m + 1; i++)
        scanf("%d", &seg_start[i]);

    segmentedBitonicSort(data, nullptr, seg_start, n, m);
        for (int i = 0; i < m; i++) {
        for (int j = seg_start[i]; j < seg_start[i + 1]; j++)
            printf("%f ", data[j]);
        printf("\n");
    }
}