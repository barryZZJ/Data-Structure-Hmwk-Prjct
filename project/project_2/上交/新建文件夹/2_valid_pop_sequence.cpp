//确认是否是合理的出栈顺序
//限制栈内最多只能存k个数
#include <iostream>
#include "1_QStack.cpp"

using namespace std;

bool valid_pop_sequence(int* A, int n, int k){
    QStack<int> s(n);
    int i = 1;
    int ia = 0;
    while(i<=n and ia<n){

        while (!s.length() or (i<=n and s.topValue()!=A[ia])){
            if (s.length() == k) return false;
            s.push(i);
            i++;
        }

        while (s.length() and s.topValue()==A[ia]){
            s.pop();
            ia++;
        }
    }
    //s为空说明符合条件
    if (!s.length()){
        return true;
    }
    
    return false;
}

int main(){
    int N, k, m;
    cin>>N>>k>>m;
    int a[N];
    for (int i=0; i<m; i++){
        for (int j=0; j<N; j++)
            cin>>a[j];
        cout<<(valid_pop_sequence(a, N, k) ? "T" : "F")<<endl;
    }
        
    return 0;
}