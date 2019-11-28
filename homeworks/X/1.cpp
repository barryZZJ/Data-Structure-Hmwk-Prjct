// （1）证明如果无向图的边权重各不相同，其最小生成树是唯一的。

//         即证明如果有边 e1,e2,e3,e4, 其权重满足w1 < w2 < w3 < w4 且w2+w3 = w1+w4，不存在两种最小生成树，一种仅包含e2和e3，另一种包含e1和e4。

// （2）排好序的数组int A[n], 用二分法查找包含在区间 [a,b)的元素个数 (a < b)

#include <iostream>

using namespace std;

int bs_range(int A[], int n, int a, int b){
    //A[l]<a, A[r]>=b
    int l = -1;
    int r = n;
    int i;
    int ia;
    //找第一个>=a的数
    while (l + 1 < r){
        i = (l + r)/2;
        if (A[i] < a)
            l = i;
        else
            r = i;
    }
    ia = r;

    l = -1;
    r = n;
    //找第一个<b的数
    while (l + 1 < r){
        i = (l + r)/2;
        if (A[i] >= b)
            r = i;
        else 
            l = i;
    }
    int ib = l;
    return ib-ia+1;
}

int main(){
    int a[] = {1,4,5,7,8,9,10};
    cout << bs_range(a, 7, 2, 11);
}