#include "../Lists_Link/LList.cpp"

void compress(LList<int>* A){
    if (A->length() == 1) return;
    A->moveToStart();
    int preV = A->getValue();
    int currV;
    A->next();
    while (A->currPos() < A->length())
    {
        currV = A->getValue();
        if(preV == currV)
            currV = A->remove();  
        preV = currV;
        A->next();
    }
}

template<typename E>
Link<E>* link_init(E* p, int l){
    Link<E>* head = new Link<E>(*p);
    Link<E>* tmp = head;
    for (int i = 1; i < l; i++)
    {
        tmp->next = new Link<E>(*(p+i));
        tmp = tmp->next;
    }
    return head;
}

template<typename E>
void link_del(Link<E>* head){
    Link<E>* tmp = head;
    while (head != NULL)
    {
        head = head->next;
        delete tmp;
        tmp = head;
    }
}

template<typename E>
int get_common_pos(Link<E>* a, Link<E>* b){
    Link<E>* tmpa = a;
    Link<E>* tmpb = b;
    int la=0, lb=0;
    // get length
    while(tmpa){
        la++;
        tmpa = tmpa->next;
    }
    while(tmpb){
        lb++;
        tmpb = tmpb->next;
    }
    
    int res = 0;
    tmpa = a;
    tmpb = b;
    for(; la>lb; la--){
        res++;
        tmpa = tmpa->next;
    }
    for(; la<lb; lb--){
        tmpb = tmpb->next;
    }
    while(tmpa && tmpb && tmpa->value != tmpb->value){
        tmpa = tmpa->next;
        tmpb = tmpb->next;
        res++;
    }
    return (tmpa or tmpb) ? res : -1;
}

template<typename E>
void print(Link<E> *head){
    Link<E>* tmp = head;
    while (tmp != NULL)
    {
        std::cout<<tmp->value<<" ";
        tmp=tmp->next;
    }
    std::cout<<std::endl;
}

int kth_last(Link<int>* A, int k){
    assert(k>0);
    Link<int>* tmp = A;
    int l =0;
    while(tmp){
        l++;
        tmp = tmp->next;
    }
    if(l<k) return -1;
    tmp = A;
    for (int i = 0; i < l-k; i++)
    {
        tmp=tmp->next;
    }
    return tmp->value;
    
}

int main(){
    std::cout<<"a";
    // LList<int>* a = new LList<int>;
    // a->append(1);
    // a->append(2);
    // // for (int i = 0; i < 10; i++)
    // // {
    // //     a->append(i);
    // //     if(i==2 or i==5 or i==9) a->append(i);
    // // }
    // a->print();
    // std::cout<<std::endl;
    // compress(a);
    // a->print();
    // Link<int> *A,*B,*C,*D,*E,*F;
    // int a[]={1};
    // int b[]={9,5,4,30,40,50,60};
    // int c[]={6,30,40,50,60};
    // int d[]={4,6,0,6,8,9,30,40,50,60};
    // int e[]={30,40,50,60};
    // int f[]={70,80,90};
    // A = link_init(a, sizeof(a)/sizeof(int));
    // kth_last(A,2);
    // std::cout<<kth_last(A,1);
    // B = link_init(b, sizeof(b)/sizeof(int));
    // C = link_init(c, sizeof(c)/sizeof(int));
    //D = link_init(d, sizeof(d)/sizeof(int));
    // E = link_init(e, sizeof(e)/sizeof(int));
    // F = link_init(f, sizeof(f)/sizeof(int));
    // print(A);
    // print(B);
    // print(C);
    // print(D);
    // print(E);
    // print(F);

    // std::cout<<get_common_pos(A,B)<<std::endl;
    // std::cout<<get_common_pos(A,C)<<std::endl;
    //std::cout<<get_common_pos(A,D)<<std::endl;
    // std::cout<<get_common_pos(A,E)<<std::endl;
    // std::cout<<get_common_pos(A,F)<<std::endl;
    // link_del(A);
    // link_del(B);
    // link_del(C);
    //link_del(D);
    // link_del(E);
    // link_del(F);

    return 0;
}

