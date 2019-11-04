//确认是否是合理的出栈顺序
//限制栈内最多只能存k个数
#include <iostream>
#include <stack>

using namespace std;

bool is_correct_pop_sequence(int* A, int n, int k){
    stack<int> s;
    int i = 1;
    int ia = 0;
    while(i<=n and ia<n){
        while (s.empty() or i<=n and s.top()!=A[ia]){
            if (s.size() == k) return false;
            s.push(i);
            i++;
        }

        while (!s.empty() and s.top()==A[ia]){
            s.pop();
            ia++;
        }
    }
    if (s.empty()){
        return true;
    }
    
    return false;
}

int main(){
    // int a[] = {1,2,3,4,5};
    // int b[] = {3,4,1,5,2};
    int a[] = {1,2,3,4,5};
    int b[] = {3,2,1,5,4};
    int c[] = {1,5,4,3,2};
    cout<<bool(is_correct_pop_sequence(a, 5, 3))<<endl;
    cout<<bool(is_correct_pop_sequence(b, 5, 3))<<endl;
    cout<<bool(is_correct_pop_sequence(c, 5, 3))<<endl;
    // cout<<bool(is_correct_pop_sequence(b, 5))<<endl;

    return 0;
}