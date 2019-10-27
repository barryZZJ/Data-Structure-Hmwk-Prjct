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

	cout << "input:\n";

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

	cout << "sum result:\n";
	LList<term> c;
	sum(a, b, c);
	cout << c.length() << endl;
	print(c);

	cout << "product result:\n";
	LList<term> d;
	product(a, b, d);
	cout << d.length() << endl;
	print(d);

}