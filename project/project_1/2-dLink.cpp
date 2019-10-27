#include "1.cpp"
#include <iostream>

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

//return sum of a, b
Link<term>* sum(Link<term>* ha, Link<term>* hb, int& nc) {
	Link<term> *a = ha->next, *b = hb->next;

	Link<term> *hc, *c = new Link<term>();
	hc = c;

	int ic = 0;
	while (a || b) {
        //a的次方高，或者该次方只有a有，b没有
		while ((a && !b) or (a && b && a->value.expo > b->value.expo)) {
			if (a->value.coeff == 0) {
				a = a->next;
				break;
			}
				c->next = new Link<term>(term(a->value.coeff, a->value.expo), c);
				c = c->next; ic++;
				a = a->next;
		}
        //b的次方高，或者该次方只有b有，a没有
		while ((!a && b) or (a && b && a->value.expo < b->value.expo)) {
			c->next = new Link<term>(term(b->value.coeff, b->value.expo), c);
			c = c->next; ic++;
			b = b->next;
		}
        //a, b的次方相同
		while (a && b && a->value.expo == b->value.expo) {
			c->next = new Link<term>(term(a->value.coeff + b->value.coeff, a->value.expo), c);
			c = c->next; ic++;
			a = a->next;
			b = b->next;
		}
	}

	nc = ic;
	return hc;
}

//return product of a, b
Link<term>* product(Link<term>* ha, Link<term>* hb, int& nd) {
	Link<term> *a = ha->next, *b = hb->next;

	Link<term> *hd = new Link<term>();

	Link<term> *part_sum_h; //存ai * B的表达式
	Link<term> *part_sum;

	while (a) {
		part_sum = new Link<term>();
		part_sum_h = part_sum;
		while (b) {
			part_sum->next = new Link<term>(term(a->value.coeff * b->value.coeff, a->value.expo + b->value.expo), 
                                            part_sum);
			b = b->next;
			part_sum = part_sum->next;
		}
		hd = sum(hd, part_sum_h, nd);
		delete part_sum_h;
		// part_sum_h = hd;

		a = a->next;
		b = hb->next;
	}
	return hd;
}

void print(Link<term>* h) {
	Link<term>* tmp = h->next;
	while (tmp) {
		cout << tmp->value.coeff << " " << tmp->value.expo << endl;
		tmp = tmp->next;
	}
}

int main() {
	int na, nb;
	Link<term> *ha, *hb; //head link (不存数据)
	Link<term> *a = new Link<term>(), *b = new Link<term>();
	ha = a;
	hb = b;

	cout << "input:\n";

	cin >> na >> nb;

	int tco, tex;
	for (int i = 0; i < na; i++) {
		cin >> tco >> tex;
		a->next = new Link<term>(term(tco, tex), a);
		a = a->next;
	}

	for (int i = 0; i < nb; i++) {
		cin >> tco >> tex;
		b->next = new Link<term>(term(tco, tex), b);
		b = b->next;
	}

    cout<<"output:\n";
	int nc;
	Link<term> *hc = sum(ha, hb, nc);
	cout << nc << endl;
	print(hc);

	int nd;
	Link<term> *hd = product(ha, hb, nd);
	cout << nd << endl;
	print(hd);

}