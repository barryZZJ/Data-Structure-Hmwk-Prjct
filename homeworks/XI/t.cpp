
#include <iostream>
using namespace std;

void Bin_Insert_Sort(int* a, int n)

{

    int Low;
    int High;
    int Middle;
    for (int i = 1; i < n; ++i)
    {
        Low = 0;
        High = i - 1;
        // 求取插入位置
        while (Low <= High)
        {
            Middle = (Low + High) / 2;
            if (a[Middle] > a[i])
                High = Middle - 1;
            else
                Low = Middle + 1;
        }

        // 插入
        for (int j = i - 1; j > High; --j)
        {
            swap(a[j], a[j + 1]);     //这里也可以挨个移动元素后插入
        }
    }
}


int main(){
    int a[]={24,7,3,9,7,15};
    // cout<<bs(a, 4, a[4]);
    Bin_Insert_Sort(a, 6);

    for (auto &&i : a)
    {
        cout<<i<<endl;
    }
    
}
