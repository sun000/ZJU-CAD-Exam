//
//  main.cpp
//  双调排序
//
//  Created by 戴丹青 on 2018/6/1.
//  Copyright © 2018年 戴丹青. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <string>
#define EPS 0.00001

using namespace std;

//递归版本
void BitonicSort(float* data, int tot, bool asc) {
    if(tot < 2) return;
    float min_max = *data;
    int index = 0;
    //调整序列变成偶数长度序列，使其可以使用Batcher定理
    if(tot & 1) {
        if(asc) {  //需要单调递增时，将最大值放在末尾
            for(int i = 1; i < tot; ++i) {
                float now = *(data + i);
                if(now > min_max){
                    min_max = now;
                    index = i;
                }
            }
            for(int i = index + 1; i < tot; ++i)
                *(data + i - 1) = *(data + i);
            *(data + tot - 1) = min_max;
        }else { //需要单调递减时，将最小值放在末尾
            for(int i = 1; i < tot; ++i) {
                float now = *(data + i);
                if(now < min_max){
                    min_max = now;
                    index = i;
                }
            }
            for(int i = index + 1; i < tot; ++i)
                *(data + i - 1) = *(data + i);
            *(data + tot - 1) = min_max;
        }
    }
    
    int n = tot / 2;
    for(int i = 0; i < n; ++i) {
        float* a = data + i;
        float* b = data + i + n;
        if((asc && *a > *b) || (!asc && *a < *b)) swap(*a,*b);
    }
    BitonicSort(data, tot >> 1, asc);
    BitonicSort(data + (tot >> 1), tot >> 1, asc);
}

//非递归版
void BitonicSort2(float* data, int tot, bool asc, int* start) {
    if(tot < 2) return;
    int maxn = tot;//记录原始的数组长度
    int cnt = 1;//表示当前的分段段数
    *start = 0;//初始段段位置从数组下标0处开始
    int bas = 0; // 设置一个基数，表示当前的分段起点保存在基数下标之后的数组上。由于最小段长度是2，所以分段数不会超过n/2，故可以用一半储存当前的分段状态，另一半存储下一次的分段状态
    while(tot >= 2) { //段长度小于2时退出循环
        int n = tot >> 1; //表示当前对每一个分段的对半分的相对位置
        int cnt_next = 0; //记录下一次的分段段数
        for(int i = bas; i < bas + cnt; ++i) { //枚举分段起点。  PS:用分段的方式消除递归
            int pos = *(start + i); //表示当前段起始位置
            if(tot & 1) { //分段长度为奇数时，需要预处理一下多余的一位数据，使分段满足Batcher定理的要求
                float min_max = *(data + pos);
                int index = pos;
                if(asc) {  //需要排序成单调递增时，将最大值放在末尾
                    for(int i = pos + 1; i < pos + tot; ++i) {
                        float now = *(data + i);
                        if(now > min_max) {
                            min_max = now;
                            index = i;
                        }
                    }
                    for(int i = index + 1; i < pos + tot; ++i) // 最大值之后的数据往前挪，除最后一个最大值之外，剩余数据仍为双调序列
                        *(data + i - 1) = *(data + i);
                    *(data + pos + tot - 1) = min_max; //末尾赋值成最大值
                }else { //需要排序成单调递减时，将最小值放在末尾，与上面过程类似
                    for(int i = pos + 1; i < pos + tot; ++i) {
                        float now = *(data + i);
                        if(now < min_max) {
                            min_max = now;
                            index = i;
                        }
                    }
                    for(int i = index + 1; i < pos + tot; ++i)
                        *(data + i - 1) = *(data + i);
                    *(data + pos + tot - 1) = min_max;
                }
            }
            for(int j = pos; j < pos + n; ++j) { //Batcher定理，分成两个双调序列
                float* a = data + j;
                float* b = data + j + n;
                if((asc && *a > *b) || (!asc && *a < *b)) swap(*a,*b);
            }
            //将当前段一分为二后的段起始点记录到下一次的段起始点数组中.............
            if(tot > 3) { //只有当下一次段长度大于等于2时，才有记录的必要
                if(bas == 0) { //当前bas为0，下一次为maxn/2
                    *(start + (maxn >> 1) + cnt_next++) = pos;
                    *(start + (maxn >> 1) + cnt_next++) = pos + n;
                }else { //当前bas为maxn/2，下一次为0
                    *(start + cnt_next++) = pos;
                    *(start + cnt_next++) = pos + n;
                }
            }
        }
        cnt = cnt_next;
        tot >>= 1;//表示下一次的分段长度，由于上面对最大值最小值的处理，此处可以直接舍弃tot为奇数时产生的小数位
        if(bas == 0) bas = maxn >> 1; //下一次的bas值反转成maxn/2或者0；
        else bas = 0;
    }
    
}

//非递归版本的函数调用实现
void Sort2(float* data, int tot, bool asc,int* start) {
    if(tot == 2)
        if((*data > *(data + 1) && asc) || (*data < *(data + 1) && !asc))
            swap(*data, *(data + 1));
    for(int len = 2; len <= tot || (len >> 1) < tot; len <<= 1) { //由于存在当len>tot的时候，序列仍然是双调序列的情况（因为长度不为的幂次），所以需要再做一次双调排序
        bool flag = asc;
        for(int pos = 0; pos < tot; pos += len) {
            BitonicSort2(data + pos, len <= tot - pos ? len : tot - pos, flag, start);
            flag ^= 1;
        }
    }
}

//递归版本的函数调用实现
void Sort(float* data, int tot, bool asc) {
    if(tot == 2)
        if((*data > *(data + 1) && asc) || (*data < *(data + 1) && !asc))
            swap(*data, *(data + 1));
    for(int len = 2; len <= tot || (len >> 1) < tot; len <<= 1) {
        bool flag = asc;
        for(int pos = 0; pos < tot; pos += len) {
            BitonicSort(data + pos, len <= tot - pos ? len : tot - pos, flag);
            flag ^= 1;

        }
    }
}

//最终代码
void segmentedBitonicSort(float* data_in, int* seg_id, int* seg_start, int n, int m,bool temp_asc) {
    for(int o = 0; o < m; ++o) {         //**************可并行化循环，因为题目给定组与组之间顺序固定，不会互相影响，随机计算顺序不影响结果
        int start_pos = *(seg_start + o);
        int length = *(seg_start + o + 1) - start_pos;
        if(length < 2) continue;
        int* start = seg_id;
        for(int step = 2; step <= length || (step >> 1) < length; step <<= 1) { //***********不可并行化循环，小的step的双调排序是后续排序操作的基础
            bool asc = temp_asc;
            for(int pos = 0; pos < length; pos += step) {     //**********可并行化循环， 每一个分块都是独立计算互不感扰，随机顺序计算不影响结果
                float* data = data_in + start_pos + pos;
                int tot = step <= length - pos ? step : length - pos;
                
                //body code
                int maxn = tot;//记录原始的数组长度
                int cnt = 1;//表示当前的分段段数
                *start = 0;//初始段段位置从数组下标0处开始
                int bas = 0; // 设置一个基数，表示当前的分段起点保存在基数下标之后的数组上。由于最小段长度是2，所以分段数不会超过n/2，故可以用一半储存当前的分段状态，另一半存储下一次的分段状态
                while(tot >= 2) { //段长度小于2时退出循环      *********不可并行化循环，与前面的理由类似，大段的双调排序还未被拆分时，小段并非双调序列不可使用Batcher定理
                    int n = tot >> 1; //表示当前对每一个分段的对半分的相对位置
                    int cnt_next = 0; //记录下一次的分段段数
                    for(int i = bas; i < bas + cnt; ++i) { //枚举分段起点。  PS:用分段的方式消除递归。   *********可并行化循环，拆分后的子双调序列互相独立，后续拆分顺序不影响结果，随机计算顺序结果相同
                        int pos = *(start + i); //表示当前段起始位置
                        if(tot & 1) { //分段长度为奇数时，需要预处理一下多余的一位数据，使分段满足Batcher定理的要求   *********数据预处理显然不可并行化
                            float min_max = *(data + pos);
                            int index = pos;
                            if(asc) {  //需要排序成单调递增时，将最大值放在末尾
                                for(int i = pos + 1; i < pos + tot; ++i) {
                                    float now = *(data + i);
                                    if(isnan(min_max)|| (!isnan(now) && now > min_max)) {
                                        min_max = now;
                                        index = i;
                                    }
                                }
                                for(int i = index + 1; i < pos + tot; ++i) // 最大值之后的数据往前挪，除最后一个最大值之外，剩余数据仍为双调序列
                                    *(data + i - 1) = *(data + i);
                                *(data + pos + tot - 1) = min_max; //末尾赋值成最大值
                            }else { //需要排序成单调递减时，将最小值放在末尾，与上面过程类似
                                for(int i = pos + 1; i < pos + tot; ++i) {
                                    float now = *(data + i);
                                    if(isnan(now) || (!isnan(min_max) && now < min_max)) {
                                        min_max = now;
                                        index = i;
                                    }
                                }
                                for(int i = index + 1; i < pos + tot; ++i)
                                    *(data + i - 1) = *(data + i);
                                *(data + pos + tot - 1) = min_max;
                            }
                        }
                        for(int j = pos; j < pos + n; ++j) { //Batcher定理，分成两个双调序列。   ********可并行化运行Batcher定理的数据比较，数据两两对应比较，比较顺序不影响结果
                            float* a = data + j;
                            float* b = data + j + n;
                            //debug
                            //printf("%d %d\n\n",isnormal(*a),isnormal(*b));
                            
                            if(!isnan(*a) && !isnan(*b)) {
                                if((asc && *a > *b) || (!asc && *a < *b)) swap(*a,*b);
                            }
                            else if(isnan(*a) && !isnan(*b)) {
                                if(!asc) swap(*a,*b);
                            }
                            else if(!isnan(*a) && isnan(*b)) {
                                if(asc) swap(*a,*b);
                            }
                        }
                        //将当前段一分为二后的段起始点记录到下一次的段起始点数组中
                        if(tot > 3) { //只有当下一次段长度大于等于2时，才有记录的必要
                            if(bas == 0) { //当前bas为0，下一次为maxn/2
                                *(start + (maxn >> 1) + cnt_next++) = pos;
                                *(start + (maxn >> 1) + cnt_next++) = pos + n;
                            }else { //当前bas为maxn/2，下一次为0
                                *(start + cnt_next++) = pos;
                                *(start + cnt_next++) = pos + n;
                            }
                        }
                    }
                    cnt = cnt_next;
                    tot >>= 1;//表示下一次的分段长度，由于上面对最大值最小值的处理，此处可以直接舍弃tot为奇数时产生的小数位
                    if(bas == 0) bas = maxn >> 1; //下一次的bas值反转成maxn/2或者0；
                    else bas = 0;
                }
                asc ^= 1;
            }
        }
    }
}

float getRandData(int min,int max)
{
    float m1=(float)(rand()%101)/101;
    min++;
    float m2=(float)((rand()%(max-min+1))+min);
    m2=m2-1;
    return m1+m2;
}

int getRandInt(int min,int max) {
    int ret = (rand() % (min-max+1))+ min;
    return ret;
}

string getTime()
{
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
    return tmp;
}

float arr[5000000];
int arr_id[5000000];
int arr_start[5000001];

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    float *data = new float[n];
    int *seg_id = new int[n];
    int *seg_start = new int[m + 1];
    for(int i = 0; i < n; i++)
        scanf("%f", &data[i]);
    for(int i = 0; i < m + 1; i++)
        scanf("%d", &seg_start[i]);

    segmentedBitonicSort(data, seg_id, seg_start, n, m, true);
        for (int i = 0; i < m; i++) {
        for (int j = seg_start[i]; j < seg_start[i + 1]; j++)
            printf("%f ", data[j]);
        printf("\n");
    }
}


// int main() {
//     freopen("data.out", "w", stdout);
//     srand((unsigned)time(NULL));
//     int n,m;
//     //输入数据量和组数
//     scanf("%d%d",&n,&m);
//     string time = getTime();
//     cout << time << endl;
//     arr_start[0] = 0;
//     arr_start[m] = n;
//     int num = n;
//     int rest = m;
//     //随机分组
//     for(int i = 1; i < m; ++i) {
//         int temp = getRandInt(1, num - rest + 1);
//         arr_start[i] = arr_start[i - 1] + temp;
//         num -= temp;
//         rest--;
//     }
//     //随机数据
//     for(int i = 0; i < n; ++i) arr[i] = getRandData(-100, 100);
    
//     //鲁棒性测试
//     for(int i = 0; i < n / 1000; ++i) {
//         int pos = getRandInt(1, n);
//         arr[pos] = sqrt(-1);
//     }

//     segmentedBitonicSort(arr, arr_id, arr_start, n, m, true);

//     //结果打印
//     int cnt = 0;
//     for(int i = 0; i < m ; ++i) {
//         printf("segment %d number %d: ",cnt++,arr_start[i + 1] - arr_start[i]);
//         for(int j = arr_start[i]; j < arr_start[i + 1]; ++j) {
//             printf("%.3f ",arr[j]);
//         }
//         printf("\n");
//     }
    
//     time = getTime();
//     cout << time << endl;
//     return 0;
// }
