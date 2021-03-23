#ifndef HEADER_H
#define HEADER_H

#include <cmath>
#include <iostream>
using namespace std;

class Polynomial
{
public:
	int* odds;
	int minp, maxp;
public:
	Polynomial(int minp = 0, int maxp = 0, int* ap = NULL);

	Polynomial(const Polynomial& p);

	int operator[](int index) const;

	int& operator[](int index);

	friend void operator+=(Polynomial &p1, const Polynomial& p2);

	friend void operator-=(Polynomial &p1, const Polynomial& p2);

	friend void operator/=(Polynomial& p, int num);

	friend Polynomial operator/(const Polynomial& p, int num);

	friend void operator*=(Polynomial& p1, const Polynomial& p2);

	friend Polynomial operator*(const Polynomial& p, int num);

	friend Polynomial operator*(int num, const Polynomial& p);

	friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);

	friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);

	friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2);

	friend Polynomial operator-(const Polynomial& p);

	friend bool operator==(const Polynomial& p1, const Polynomial& p2);

	friend bool operator!=(const Polynomial& p1, const Polynomial& p2);

	friend ostream& operator<<(ostream& out, const Polynomial& p);

	friend istream& operator>>(istream& in, Polynomial& p);

	double get(int x);

	void operator=(const Polynomial& p1);

	~Polynomial();
};








#endif