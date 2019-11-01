template <typename E>
class Link
{
public:
    E value;
    Link *next;
    Link(const E& val, Link<E>* nextlink =NULL) {
        value = val;
        next = nextlink;
    }
    Link(Link<E>* nextlink =NULL){
        next = nextlink;
    }
};