#include <cstddef> //for NULL
#include <cassert>
#include <iostream>


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
	void* operator new(size_t) {
		if (freelist == NULL) return ::new Link;
		Link<E>* tmp = freelist;
		freelist = freelist->next;
		//tmp->next = NULL;
		return tmp;
	}

	//overload delete operator
	//只删除单个节点
	void operator delete(void * ptr) {
		Link<E> *tmp = (Link<E>*)ptr;
		tmp->next = freelist;
		freelist = tmp;
	}
};
//create freelist head pointer
template <typename E>
Link<E>* Link<E>::freelist = NULL;

//1


//双向链表
template <typename E>
class LList
{
private:
	Link<E>* head; //head不存数据
	Link<E>* tail; //tail存数据
	Link<E>* curr; //指的是当前元素
	int size;

	void init() {
		curr = tail = head = new Link<E>;
		size = 0;
	}

	void removeall() {
		while (head != NULL) {
			curr = head;
			head = head->next;
			delete curr;
		}
	}

public:
	LList() { init(); }

	~LList() { removeall(); }
	void clear() { removeall(); init(); }

	void insert(const E& val) {
		curr = new Link<E>(val, curr, curr->next);
		if (tail == curr) tail = curr;
		size++;
	}

	void append(const E& val) {
		tail->next = new Link<E>(val, tail, NULL);
		tail = tail->next;
		size++;
	}

	E remove() {
		// Assert(curr->next != NULL, "No element");
		assert(curr != NULL);
		E val = curr->value;
		Link<E>* tmp = curr;

		if (curr == tail) {
			tail = curr->prev;
			tail->next = NULL;
		}

		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;

		delete tmp;
		size--;
		return val;
	}

	void moveToStart() { curr = head; }

	void moveToEnd() { curr = tail; }

	bool atStart() const { return (curr == head); }
	bool atEnd() const { return (curr == tail->next); }

	void prev() {
		curr = curr->prev;
	}

	void next() {
		curr = curr->next;
	}

	int length() const { return size; }

	int currPos() const {
		Link<E>* tmp = head;
		int i;
		for (i = 0; curr != tmp; i++)
			tmp = tmp->next;
		return i;
	}

	void moveToPos(int pos) {

		// Assert((pos>=0) && (pos<=size), "Position out of range");
		assert((pos >= 0) && (pos <= size));
		curr = head;
		for (int i = 0; i < pos; i++) curr = curr->next;

	}

	const E& getValue() const{
		// Assert(curr->next != NULL, "No value");
		assert(curr != NULL);
		return curr->value;
	}
};

//2

using namespace std;

const int MAXTERM = 1024;

struct term
{
	int coeff;//系数
	int expo;//指数
	term() {}
	term(int _coeff, int _expo) {
		coeff = _coeff;
		expo = _expo;
	}
	term(const term & t) {
		coeff = t.coeff;
		expo = t.expo;
	}
};

//sum of a, b
void sum(LList<term> &a, LList<term> &b, LList<term> &sum) {

	//LList<term> sum;
	a.moveToStart();
	a.next();
	b.moveToStart();
	b.next();
	while (!a.atEnd() || !b.atEnd()) {
		//a的次方高，或者a还没到头，b到头了
		while ((!a.atEnd() && b.atEnd()) 
			   or (!a.atEnd() && !b.atEnd() && a.getValue().expo > b.getValue().expo)) {
			if (a.getValue().coeff != 0) {
				sum.append(term(a.getValue().coeff, a.getValue().expo));
			}
			a.next();
		}
		//b的次方高，或者b还没到头，a到头了
		while ((a.atEnd() && !b.atEnd()) 
			   or (!a.atEnd() && !b.atEnd() && a.getValue().expo < b.getValue().expo)) {
			if (b.getValue().coeff != 0) {
				sum.append(term(b.getValue().coeff, b.getValue().expo));
			}
			b.next();
		}
		//a, b的次方相同
		while (!a.atEnd() && !b.atEnd() && a.getValue().expo == b.getValue().expo) {
			if (a.getValue().coeff != 0 && b.getValue().coeff != 0) {
				sum.append(term(a.getValue().coeff + b.getValue().coeff, a.getValue().expo));
			}
				a.next();
				b.next();
		}

	}

}

//product of a, b
void product(LList<term> &a, LList<term> &b, LList<term> &product) {
	LList<term> part_sum; //存ai * B的表达式
	LList<term> tmp[1024]; //存每次求和后的结果
	int i = 0;

	a.moveToStart();
	a.next();
	b.moveToStart();
	b.next();
	while (!a.atEnd()){
		i++;
		part_sum.clear();
		while (!b.atEnd()) {
			if(a.getValue().coeff != 0 && b.getValue().coeff != 0)
				part_sum.append(term(a.getValue().coeff * b.getValue().coeff,
									 a.getValue().expo + b.getValue().expo));
			b.next();
		}
		sum(tmp[i - 1], part_sum, tmp[i]);
		a.next();
		b.moveToStart();
		b.next();
	}
	sum(tmp[i], tmp[i+1], product);
}

void print(LList<term> &l) {
	l.moveToStart();
	l.next();
	while (!l.atEnd()) {
		cout << l.getValue().coeff << " " << l.getValue().expo << endl;
		l.next();
	}
}

int main() {
	int na, nb;
	LList<term> a, b;

	// cout << "input:\n";

	cin >> na >> nb;

	int tco, tex;
	for (int i = 0; i < na; i++) {
		cin >> tco >> tex;
		a.append(term(tco, tex));
	}

	for (int i = 0; i < nb; i++) {
		cin >> tco >> tex;
		b.append(term(tco, tex));
	}

	// cout << "sum result:\n";
	LList<term> c;
	sum(a, b, c);
	cout << c.length() << endl;
	print(c);

	// cout << "product result:\n";
	LList<term> d;
	product(a, b, d);
	cout << d.length() << endl;
	print(d);

}