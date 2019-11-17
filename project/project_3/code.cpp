#include <iostream>
#include <cassert>
#include <cstddef> //for NULL
#include <cstdlib>

using namespace std;

class Rational{
friend bool operator<(const Rational& r1, const Rational& r2) {
    return r1.N*r2.D < r2.N*r1.D;
}
friend bool operator<=(const Rational& r1, const Rational& r2) {
    return r1.N*r2.D <= r2.N*r1.D;
}
friend bool operator>(const Rational& r1, const Rational& r2) {
    return r1.N*r2.D > r2.N*r1.D;
}
friend bool operator>=(const Rational& r1, const Rational& r2) {
    return r1.N*r2.D >= r2.N*r1.D;
}
friend bool operator==(const Rational& r1, const Rational& r2) {
    return r1.N*r2.D == r2.N*r1.D;
}
friend bool operator!=(const Rational& r1, const Rational& r2) {
    return r1.N*r2.D != r2.N*r1.D;
}

private:
    int N; //分子
    int D; //分母， 要求大于0
    int gcd(int a, int b){
        a = abs(a); b = abs(b);
        if (b == 0) return a;
        return gcd(b, a%b);
    }

public:
    //default constructor
    Rational() {
        N = 0;
        D = 1;
    }
    //constructor for integer value
    Rational(int n){
        N = n;
        D = 1;
    } 
    //normal constructor
    Rational(int n, int d) {
        //分母必须大于0
        assert(d > 0);
        //最简化
        int g = gcd(n, d);
        N = n/g;
        D = d/g;
    } 
    //copy constructor
    Rational(const Rational& r){
        N = r.N;
        D = r.D;
    } 
    // assignment override
    Rational& operator=(const Rational& r) {
        N = r.N;
        D = r.D;
        return *this;
    }

    char* getItem(){
        char *s = new char[10];
        if (D == 1)
            itoa(N, s, 10);
        else
            sprintf(s, "%d/%d", N, D);
        return s;
    }

};

class minHeap{
private:
    Rational* arr;
    int maxSize;
    int l; //length
    minHeap(){} //不允许不声明容量的构造函数

    inline int lc(int pos) {return pos*2+1;}
    inline int rc(int pos) {return pos*2+2;}
    inline int p(int pos) {return (pos-1)/2;}
    inline int isLeaf(int pos) {return pos>=l/2 && pos<l;}

    void siftUp(int pos){
        while(pos !=0 && arr[pos] < arr[p(pos)]){
            swap(arr[pos], arr[p(pos)]);
            pos = p(pos);
        }
    }

    void siftDown(int pos){
        while (!isLeaf(pos)){
            int sc = lc(pos); //smaller child
            int r = rc(pos);
            if (r<l && arr[r] < arr[sc])
                sc = r;
            if (arr[pos] < arr[sc]) return; //满足父亲比儿子小，结束
            swap(arr[pos], arr[sc]);
            pos = sc;
        }
    }

    void buildHeap(){
        for (int i = p(l-1); i >= 0; i--){
            siftDown(i);
        }
    }

public:
    minHeap(Rational* _arr, int length, const int _maxSize){
        arr = _arr;
        l = length;
        maxSize = _maxSize;
        buildHeap();
    }

    int size(){return l;}

    Rational pop(){
        assert(l > 0);
        l--;
        swap(arr[0], arr[l]);
        if (l != 0)
            siftDown(0);
        return arr[l];
    }

    void insert(const Rational& r){
        assert(l < maxSize);
        arr[l] = r;
        siftUp(l);
        l++;
    }
    
};

void print_heap(Rational *arr, int l){
    for (int i = 0; i < l; i++)
        cout<<arr[i].getItem()<<"  ";
}

void print_heapsort(minHeap *h){
    while(h->size())
        cout<<h->pop().getItem()<<"  ";
}

int main(){
    int T;
    cin>>T;
    Rational arr[T];
    int n, d;
    for (int i = 0; i < T; i++){
        cin>>n>>d;
        arr[i] = Rational(n, d);
    }
    minHeap *h = new minHeap(arr, T, T);
    print_heap(arr, T);
    cout<<endl;
    print_heapsort(h);
    
}

