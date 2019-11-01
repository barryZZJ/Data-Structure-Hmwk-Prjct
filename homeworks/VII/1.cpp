// 在10^9个数据中查找第10^5小的数据
// （1）如果按照顺序查找法，即依次找第1小，第2小，。。。 需要的执行多少次比较？

// （2）使用最小堆可以提高效率，设生成规模为n的最小堆的比较次数为n，从中取去最小值需要的次数为log(n), 计算用最小堆完成上述任务的总的比较次数。

// （3）用堆实现函数 int find_kth_smallest(int* A, int n, int k) 从A中找出第k小的值, n为A的规模

#include "../MinHeap.cpp"
#include <iostream>

using namespace std;
int find_kth_smallest(int* A, int n, int k){
    heap<int>h = heap<int>(A, n, n);
    int tmp;
    for (int i = 0; i < k; i++){
        tmp = h.pop();
    }
    return tmp;
}

int main() {
    int a[] = {7,256,2,4,573,45,67,23};
    cout<<find_kth_smallest(a, 8, 3);

}