// （1）实现插入排序，在排序中用二分法查找插入位置。

// （2）分析上述算法的时间复杂度（解释时间复杂度为何还是O(n^2))

#include <cstdlib>
#include <iostream>

using namespace std;

int bs(int A[], int n, int key){
    int l = -1, r = n;
    int mid;
    do{
        mid = (l+r)/2;
        if (key < A[mid])
            r = mid;
        else if (key > A[mid])
            l = mid;
        else
            return mid;
    }while (l + 1 < r);

    return r;
}

void insert_bs(int A[], int n){
    
    int tmp, pos;
    for (int i = 1; i < n; i++){
        tmp = A[i];
        pos = bs(A, i, A[i]);

        for (int j = i; j > pos; j--){
            A[j] = A[j-1];
        }
        A[pos] = tmp;
    }
}

int main(){
    int a[]={24,7,3,9,7,15};
    // cout<<bs(a, 4, a[4]);
    insert_bs(a, 6);

    for (auto &&i : a)
    {
        cout<<i<<endl;
    }
    
}


// 由于二分查找只减少了比较次数，而数据交换的次数与非二分时一样，因此二分插入排序时间复杂度与非二分一样，都是O(n^2)