#pragma once
#include <cstddef> //for NULL
//Doubly link with freelist
template <typename E>
class Link
{
private:
	static Link<E>* freelist; //point to freelist head
public:
	E value;
	Link<E> *next;
	Link<E> *prev;

	//constructor
	Link(const E& val, Link<E>* prevlink = NULL, Link<E>* nextlink = NULL) {
		value = val;
		prev = prevlink;
		next = nextlink;
	}
	Link(Link<E>* prevlink = NULL, Link<E>* nextlink = NULL) {
		prev = prevlink;
		next = nextlink;
	}
	Link(const Link<E> &l) {
		value = l.value;
		next = l.next;
		prev = l.prev;
	}

	//overload new operator
	void * operator new(size_t) {
		if (freelist == NULL) return ::new Link;
		Link<E>* tmp = freelist;
		freelist = freelist->next;
		return tmp;
	}

	//overload delete operator
	void operator delete(void * ptrh) {
		Link<E> *tmph = (Link<E>*)ptrh;
		Link<E> *tmp = tmph;
		tmp->next = freelist;
		freelist = tmph;
	}
};
//create freelist head pointer
template <typename E>
Link<E>* Link<E>::freelist = NULL;