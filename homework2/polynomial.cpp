#include "polynomial.h"

Polynomial::Polynomial(int minp, int maxp, int* ap)
{
	this->odds = new int[maxp - minp + 1];
	this->minp = minp;
	this->maxp = maxp;
	if (ap == NULL)
		this->odds = new int[1]{ 0 };
	else
		for(int i = 0; i < maxp-minp + 1; i++)
			this->odds[i] = ap[i];
}

Polynomial::Polynomial(const Polynomial& p)
{
	this->minp = p.minp;
	this->maxp = p.maxp;
	this->odds = new int[maxp - minp + 1];
	for (auto i = 0; i < maxp - minp + 1; i++)
		this->odds[i] = p.odds[i];
}

int Polynomial::operator[](int index) const
{
	if(this->odds != NULL && index >= 0 && minp + index <= maxp)
		return this->odds[index - minp];
	return 0;
}

int& Polynomial::operator[](int index)
{
	if (this->odds == NULL)
	{
		maxp = index;
		this->odds = new int[maxp - minp + 1];
		for (auto i = 0; i < maxp - minp + 1; i++)
			this->odds[i] = 0;
	}
	if (minp + index > maxp)
	{
		int* newOdds = new int[index + 1];
		for (int i = 0; i < index + 1; i++)
		{
			newOdds[i] = 0;
		}
		int newMax = index;
		for (int i = 0; i < maxp - minp + 1; i++)
			newOdds[i] = this->odds[i];
		for (int i = maxp - minp + 1; i < newMax + 1; i++)
			newOdds[i] = 0;
		maxp = newMax;
		delete[] this->odds;
		this->odds = new int[maxp - minp + 1];
		for (int i = 0; i < maxp - minp + 1; i++)
			this->odds[i] = newOdds[i];
	}
	return this->odds[index - minp];
}

Polynomial& Polynomial::operator+=(const Polynomial& p)
{
	int newMin = min(this->minp, p.minp);
	int newMax = max(this->maxp, p.maxp);
	int* newOdds = new int[newMax - newMin + 1];
	for (auto i = 0; i < newMax - newMin + 1; i++)
		newOdds[i] = 0;
	for (auto i = 0; i < newMax - newMin + 1; i++)
	{
		int nm = newMin + i;
		if (nm >= this->minp && nm <= this->maxp)
			newOdds[i] += this->odds[nm - this->minp];
		if (nm >= p.minp && nm <= p.maxp)
			newOdds[i] += p.odds[nm - p.minp];
	}
	delete[] this->odds;
	this->minp = newMin;
	this->maxp = newMax;
	this->odds = new int[newMax - newMin + 1];
	for (auto i = 0; i < newMax - newMin + 1; i++)
		this->odds[i] = newOdds[i];
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& p)
{
	*this += -p;
	return *this;
}

Polynomial& Polynomial::operator/=(int num)
{
	// fixed: use for each
	for_each(this->odds, this->odds + maxp - minp + 1, [&num](int& item) {item /= num; });
	return *this;
}

Polynomial operator/(const Polynomial& p, int num)
{
	Polynomial temp(p);
	temp /= num;
	return temp;
}

void operator*=(Polynomial& p1, const Polynomial& p2)
{
	int newMax = p1.maxp + p2.maxp;
	int newMin = p1.minp + p2.minp;
	int* newOdds = new int[newMax - newMin + 1];
	for (auto i = 0; i < newMax - newMin + 1; i++)
		newOdds[i] = 0;
	for (auto i = 0; i < p1.maxp - p1.minp + 1; i++)
	{
		for (auto j = 0; j < p2.maxp - p2.minp + 1; j++)
		{
			int odd = p1.odds[i] * p2.odds[j];
			int power = p1.minp + i + p2.minp + j;
			newOdds[power - newMin] += odd;
		}
	}
	p1.minp = newMin;
	p1.maxp = newMax;
	delete[] p1.odds;
	p1.odds = new int[newMax - newMin + 1];
	for (auto i = 0; i < newMax - newMin + 1; i++)
		p1.odds[i] = newOdds[i];
}

Polynomial operator*(const Polynomial& p, int num)
{
	Polynomial temp(p);
	for (int i = 0; i < temp.maxp - temp.minp + 1; i++)
		temp.odds[i] *= num;
	return temp;
}

Polynomial operator*(int num, const Polynomial& p)
{
	return p*num;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial temp(p1);
	temp *= p2;
	return temp;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial sum(p1);
	sum += p2;
	return sum;
}

Polynomial operator-(const Polynomial& p1, const Polynomial& p2)
{
	return p1+(-p2);
}

Polynomial operator-(const Polynomial& p)
{
	int* newOdds = new int[p.maxp - p.minp + 1];
	for (auto i = 0; i < p.maxp - p.minp + 1; i++)
		newOdds[i] = p.odds[i] * -1;
	return Polynomial(p.minp, p.maxp, newOdds);
}

bool operator==(const Polynomial& p1, const Polynomial& p2)
{
	bool flag = 1;
	for (auto i = 0; i < p1.maxp - p1.minp + 1; i++)
	{
		if (p1.minp + i >= p2.minp && p1.minp + i <= p2.maxp)
		{
			if (p1.odds[i] != p2.odds[p1.minp + i - p2.minp])
				return false;
		}
		else if (p1.odds[i] != 0) return false;
	}
	for (auto i = 0; i < p2.maxp - p2.minp + 1; i++)
	{
		if (p2.minp + i >= p1.minp && p2.minp + i <= p1.maxp)
		{
			if (p2.odds[i] != p1.odds[p2.minp + i - p1.minp])
				return false;
		}
		else if (p2.odds[i] != 0) return false;
	}
	return true;
}

bool operator!=(const Polynomial& p1, const Polynomial& p2)
{
	return !(p1 == p2);
}

ostream& operator<<(ostream& out, const Polynomial& p)
{
	for (auto i = p.maxp - p.minp; i >= 0; i--)
	{
		if (p.odds[i] == 0)
			continue;
		if (p.odds[i] > 0 && i != p.maxp - p.minp)
			out << "+";
		if (p.minp + i == 1 && p.odds[i] == 1)
		{
			out << "x";
			continue;
		}
		if (p.minp + i == 1)
		{
			out << p.odds[i] << "x";
			continue;
		}
		if (p.odds[i] == -1)
		{
			out << "-" << "x^" << p.minp + i;
			continue;
		}
		if (p.odds[i] == 1 && p.minp + i != 0)
		{
			out << "x^" << p.minp + i;
			continue;
		}
		if (p.minp + i == 0)
		{
			out << p.odds[i];
			continue;
		}
		out << p.odds[i] << "x^" << p.minp + i;
	}
	if (p.maxp - p.minp == 0)
		out << 0;
	return out;
}

istream& operator>>(istream& in, Polynomial& p)
{
	in >> p.minp;
	in >> p.maxp;
	delete[] p.odds;
	p.odds = new int[p.maxp - p.minp + 1];
	for (auto i = 0; i < p.maxp - p.minp + 1; i++)
		in >> p.odds[i];
	return in;
}

//fixed get O(n)
double Polynomial::get(int x)
{
	double temp = pow(x, minp);
	double result = this->odds[0] * temp;
	for (auto i = 1; i < this->maxp - this->minp + 1; i++)
	{
		temp *= x;
		result += (double)this->odds[i] * temp;
	}
	return result;
}

Polynomial& Polynomial::operator=(const Polynomial& p1)
{
	this->maxp = p1.maxp;
	this->minp = p1.minp;
	delete[] this->odds;
	this->odds = new int[maxp - minp + 1];
	for (int i = 0; i < maxp - minp + 1; i++)
	{
		this->odds[i] = p1.odds[i];
	}
	return *this;
}

Polynomial::~Polynomial()
{
	if (this->odds)
		delete[] this->odds;
}