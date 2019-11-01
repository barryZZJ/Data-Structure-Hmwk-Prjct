//确认是否是合理的出栈顺序
#include <iostream>
#include <stack>

using namespace std;

bool is_correct_pop_sequence(int* A, int n){
    stack<int> s;
    int i = 1;
    int ia = 0;
    while(i<=n and ia<n){
        while (s.empty() or i<=n and s.top()!=A[ia]){
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
    int a[] = {1,2,3,4,5};
    int b[] = {3,4,1,5,2};
    cout<<bool(is_correct_pop_sequence(a, 5))<<endl;
    cout<<bool(is_correct_pop_sequence(b, 5))<<endl;

    return 0;
}