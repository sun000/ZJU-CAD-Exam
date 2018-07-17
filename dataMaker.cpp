/*
* @Author: sun000
* @Date:   2018-06-02 11:23:36
* @Last Modified by:   sun000
* @Last Modified time: 2018-06-03 19:36:09
*/

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
const int MIN_N = 0;
const int MAX_N = 2000000;
const int MAX_M = 1;
const int MAX_NUM = 999999999;
const int NAN_RATE = 1;// 1%

float getRandFloat() {
    float num1 = (rand() % MAX_NUM) * 2 - MAX_NUM;
    float num2 = (rand() % MAX_NUM) * 2 - MAX_NUM;
    if(num2 == 0) num2 = 1;
    return num1 / num2;
}

int tmp[2000100];

int main(void) {
    srand(time(NULL));
    int n = rand() % (MAX_N - MIN_N) + MIN_N;
    int m = rand() % MAX_M + 1;
    printf("%d %d\n", n, m);
    for(int i = 0; i < n; i++) {
        if(rand() % 100 <= NAN_RATE - 1) printf("nan ");
        else printf("%.6f ", getRandFloat());
    }
    printf("\n");
    // random_shuffle(tmp, tmp + n);
    // for(int i = 0; i < n; i++)
    //     printf("%d ", tmp[i]);
    // printf("\n");

    tmp[0] = 0; tmp[m] = n;
    for(int i = 1; i < m; i++)
        tmp[i] = rand() % (n + 1);
    sort(tmp, tmp + m + 1);
    for(int i = 0; i < m + 1; i++)
        printf("%d ", tmp[i]);
    printf("\n");   
    return 0;

}