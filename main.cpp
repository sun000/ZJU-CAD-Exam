/*
* @Author: sun000
* @Date:   2018-06-03 09:18:30
* @Last Modified by:   sun000
* @Last Modified time: 2018-06-03 16:05:17
*/

#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

void mySort(float *data, int n) {
    for (int unitLen = 2; unitLen <= n; unitLen <<= 1) {
        bool flag = true;
        for (int s = 0; s < n; s += unitLen, flag ^= true) {
            int e = s + unitLen;
            if (flag) {
                for (int step = unitLen; step > 1; step >>= 1) {
                    for (int s2 = s; s2 < e; s2 += step) {
                        int e2 = s2 + step;
                        int mid = (s2 + e2) >> 1;
                        for (int i = 0; i < (step >> 1); i++) {
                            if ((data[s2 + i] > data[mid + i]) || (!isnan(data[s2 + i]) && isnan(data[mid + i])) )
                                swap(data[s2 + i], data[mid + i]);
                        }
                    }
                }
            } else {
                for (int step = unitLen; step > 1; step >>= 1) {
                    for (int s2 = s; s2 < e; s2 += step) {
                        int e2 = s2 + step;
                        int mid = (s2 + e2) >> 1;
                        for (int i = 0; i < (step >> 1); i++) {
                            if ((data[s2 + i] < data[mid + i]) || (isnan(data[s2 + i]) && !isnan(data[mid + i])) )
                                swap(data[s2 + i], data[mid + i]);
                        }
                    }
                }
            }
        }
    }
}


void segmentedBitonicSort(float * data, int* seg_id, int* seg_start, int n, int m) {
    for (int i = 0; i < m; i++) {
        int len = seg_start[i + 1] - seg_start[i];
        int step = 1 << (int)log2(len);
        if(len == step) mySort(data + seg_start[i], len);
        else if (len <= step + (step >> 1))  {
            for (int j = 0; j < 2; j++) {
                mySort(data + seg_start[i], step);
                mySort(data + seg_start[i] + len - step, step);
            }
        }
        else {
            for (int j = 0; j < 3; j++) {
                mySort(data + seg_start[i], step);
                mySort(data + seg_start[i] + (len - step) / 2, step);
                mySort(data + seg_start[i] + len - step, step);
            }
        }
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