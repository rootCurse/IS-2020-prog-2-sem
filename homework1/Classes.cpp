#include "Classes.h"

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::Point(const Point &p)
{
	this->x = p.x;
	this->y = p.y;
}

int Point::getX() const
{
	return this->x;
}

int Point::getY() const
{
	return this->y;
}

Point Point::operator=(const Point &p)
{
	this->x = p.x;
	this->y = p.y;
	return *this;
}

PolygonalChain::PolygonalChain(int countPoints = 0, Point* p = NULL)
{
	points.resize(countPoints);
	for (int i = 0; i < countPoints; i++)
	{
		points[i] = p[i];
	}
}

PolygonalChain::PolygonalChain(const PolygonalChain& pc)
{
	int newSize = pc.points.size();
	this->points.resize(newSize);
	for (int i = 0; i < newSize; i++)
		this->points[i] = pc.points[i];
}

PolygonalChain PolygonalChain::operator=(const PolygonalChain &pc)
{
	this->points.clear();
	int newSize = pc.points.size();
	this->points.resize(newSize);
	for (int i = 0; i < newSize; i++)
		this->points[i] = pc.points[i];
	return *this;
}

int PolygonalChain::getN() const
{
	return points.size();
}

Point PolygonalChain::getPoint(int index) const
{
	return this->points[index];
}

double PolygonalChain::perimeter() const
{
	double sum = 0;
	int size = points.size();
	for (int i = 0; i < size - 1; i++)
	{
		sum += sqrt(pow((points[i + 1].getX() - points[i].getX()), 2) + pow((points[i + 1].getY() - points[i].getY()), 2));
	}
	return sum;
}

PolygonalChain::~PolygonalChain()
{
	points.clear();
	points.resize(1);
}

ClosedPolygonalChain::ClosedPolygonalChain(int countPoints = 0, Point* p = NULL)
{
	this->points.resize(countPoints);
	for (int i = 0; i < countPoints; i++)
		this->points[i] = p[i];
}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& cpc)
{
	this->points.resize(cpc.points.size());
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = cpc.points[i];
}

double ClosedPolygonalChain::perimeter() const
{
	double sum = 0;
	int size = points.size();
	for (int i = 0; i < size - 1; i++)
	{
		sum += sqrt(pow((points[i + 1].getX() - points[i].getX()), 2) + pow((points[i + 1].getY() - points[i].getY()), 2));
	}
	sum += sqrt(pow((points[0].getX() - points[size - 1].getX()), 2) + pow((points[0].getY() - points[size - 1].getY()), 2));
	return sum;
}

double ClosedPolygonalChain::area() const
{
	double sum = 0;
	for (int i = 0; i < this->points.size(); i++)
	{
		if (i == this->points.size() - 1)
			sum += (double)this->points[i].getX() * (double)this->points[0].getY() - (double)this->points[i].getY() * (double)this->points[0].getX();
		else
			sum += (double)this->points[i].getX() * (double)this->points[i + 1].getY() - (double)this->points[i].getY() * (double)this->points[i + 1].getX();
	}
	sum = abs(sum / 2);
	return sum;
}

ClosedPolygonalChain ClosedPolygonalChain::operator=(const ClosedPolygonalChain& cpc)
{
	this->points.resize(cpc.points.size());
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = cpc.points[i];
	return *this;
}

ClosedPolygonalChain::~ClosedPolygonalChain()
{
	this->points.clear();
	this->points.resize(1);
}

Polygon::Polygon(int countPoint = 0, Point *p = NULL)
{
	this->points.resize(countPoint);
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = p[i];
}

Polygon::Polygon(const Polygon& p)
{
	this->points.resize(p.points.size());
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = p.points[i];
}

Polygon Polygon::operator=(const Polygon &p)
{
	this->points.resize(p.points.size());
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = p.points[i];
	return *this;
}

Polygon::~Polygon()
{
	this->points.clear();
	this->points.resize(1);
}

Triangle::Triangle(int countPoints = 0, Point* p = NULL)
{
	this->points.resize(countPoints);
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = p[i];
}

Triangle::Triangle(const Triangle& t)
{
	this->points.resize(t.points.size());
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = t.points[i];
}

Triangle Triangle::operator=(const Triangle &t)
{
	this->points.resize(t.points.size());
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = t.points[i];
	return *this;
}

bool Triangle::hasRightAngle() const
{
	double a, b, c;
	a = sqrt(pow((points[1].getX() - points[0].getX()), 2) + pow((points[1].getY() - points[0].getY()), 2));
	b = sqrt(pow((points[2].getX() - points[1].getX()), 2) + pow((points[2].getY() - points[1].getY()), 2));
	c = sqrt(pow((points[0].getX() - points[2].getX()), 2) + pow((points[0].getY() - points[2].getY()), 2));
	if (a > c)
		swap(a, c);
	if (b > c)
		swap(b, c);
	return pow(a, 2) + pow(b, 2) == pow(c, 2);
}

Triangle::~Triangle()
{
	this->points.clear();
	this->points.resize(1);
}

Trapezoid::Trapezoid(int countPoints, Point* p)
{
	this->points.resize(countPoints);
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = p[i];
}

Trapezoid::Trapezoid(const Trapezoid& tr)
{
	this->points.resize(tr.points.size());
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = tr.points[i];
}

double Trapezoid::height() const
{
	double a = sqrt(pow((points[2].getX() - points[1].getX()), 2) + pow((points[2].getY() - points[1].getY()), 2));
	double b = sqrt(pow((points[0].getX() - points[3].getX()), 2) + pow((points[0].getY() - points[3].getY()), 2));
	return 2 * this->area() / (a + b);
}

Trapezoid Trapezoid::operator=(const Trapezoid &tr)
{
	this->points.resize(tr.points.size());
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = tr.points[i];
	return *this;
}

Trapezoid::~Trapezoid()
{
	this->points.clear();
	this->points.resize(1);
}

RegularPolygon::RegularPolygon(int countPoints = 0, Point* p = NULL)
{
	this->points.resize(countPoints);
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = p[i];
}

RegularPolygon::RegularPolygon(const RegularPolygon& rp)
{
	this->points.resize(rp.points.size());
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = rp.points[i];
}

RegularPolygon RegularPolygon::operator=(const RegularPolygon &rp)
{
	this->points.resize(rp.points.size());
	for (int i = 0; i < this->points.size(); i++)
		this->points[i] = rp.points[i];
	return *this;
}

RegularPolygon::~RegularPolygon()
{
	this->points.clear();
	this->points.resize(1);
}
