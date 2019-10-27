

while(a or b){
    if((a && !b) or (a && b && a->element2>b->element2)){
        Link<int> *res_r = new Link<int>(a->element1, a->element2, NULL, NULL);
        a = a->next;
    }
    else if ((!a && b) or (a && b && a->element2<b->element2){
        Link<int> *res_r = new Link<int>(b->element1, b->element2, NULL, NULL);
        b = b->next;
    }
    else if (a && b && a->element2==b->element2){
        Link<int> *res_r = new Link<int>(a->element1+b->element1, a->element2, NULL, NULL);
        a = a->next;
        b = b->next;
    }
    //五行
    
}
