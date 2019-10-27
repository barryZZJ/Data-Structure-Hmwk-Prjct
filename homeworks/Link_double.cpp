template <typename E>
class Link
{
public:
    E value;
    Link *next;
    Link(const E& val, Link<E>* prevlink =NULL, Link<E>* nextlink =NULL) {
        value = val;
        prev = prevlink;
        next = nextlink;
    }
    Link( Link<E>* prevlink =NULL, Link<E>* nextlink =NULL){
        prev = prevlink;
        next = nextlink;
    }
};