#include "geometry.h"
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::Point(const Point& p)
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

Point Point::operator=(const Point& p)
{
	this->x = p.x;
	this->y = p.y;
	return *this;
}

PolygonalChain::PolygonalChain(int countPoints = 0, Point* p = NULL)
{
	points.resize(countPoints);
	for (auto i = 0; i < countPoints; i++)
	{
		points[i] = p[i];
	}
}

PolygonalChain::PolygonalChain(const PolygonalChain& pc)
{
	this->points = pc.points;
}

PolygonalChain PolygonalChain::operator=(const PolygonalChain& pc)
{
	this->points = pc.points;
	return *this;
}

int PolygonalChain::getN() const
{
	return points.size();
}

double PolygonalChain::len(Point p1, Point p2) const
{
	return sqrt(pow((p1.getX() - p2.getX()), 2) + pow((p1.getY() - p2.getY()), 2));
}

Point PolygonalChain::getPoint(int index) const
{
	return this->points[index];
}

double PolygonalChain::perimeter() const
{
	double sum = 0;
	int size = points.size();
	for (auto i = 0; i < size - 1; i++)
	{
		sum += this->len(this->points[i], this->points[i + 1]);
	}
	return sum;
}

ClosedPolygonalChain::ClosedPolygonalChain(int countPoints = 0, Point* p = NULL):PolygonalChain(countPoints, p){}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& cpc) : PolygonalChain(cpc){}

double ClosedPolygonalChain::perimeter() const
{

	return PolygonalChain::perimeter() + sqrt(pow((points[0].getX() - points[this->getN() - 1].getX()), 2) + pow((points[0].getY() - points[this->getN() - 1].getY()), 2));;
}

double ClosedPolygonalChain::area() const
{
	int sum = 0;
	for (unsigned int i = 0; i < this->points.size(); i++)
	{
		if (i == this->points.size() - 1)
			sum += this->points[i].getX() * this->points[0].getY() - this->points[i].getY() * this->points[0].getX();
		else
			sum += this->points[i].getX() * this->points[i + 1].getY() - this->points[i].getY() * this->points[i + 1].getX();
	}
	return abs((double)sum / 2);
}

ClosedPolygonalChain ClosedPolygonalChain::operator=(const ClosedPolygonalChain& cpc)
{
	PolygonalChain::operator=(cpc);
	return *this;
}

Polygon::Polygon(int countPoints = 0, Point* p = NULL):ClosedPolygonalChain(countPoints, p){}

Polygon::Polygon(const Polygon& p): ClosedPolygonalChain(p){}

Polygon Polygon::operator=(const Polygon& p)
{
	ClosedPolygonalChain::operator=(p);
	return *this;
}

Triangle::Triangle(int countPoints = 0, Point* p = NULL): ClosedPolygonalChain(countPoints, p){}

Triangle::Triangle(const Triangle& t): ClosedPolygonalChain(t){}

Triangle Triangle::operator=(const Triangle& t)
{
	ClosedPolygonalChain::operator=(t);
	return *this;
}

bool Triangle::hasRightAngle() const
{
	//fixed you dont need doubles
	int a, b, c;
	a = pow((points[1].getX() - points[0].getX()), 2) + pow((points[1].getY() - points[0].getY()), 2);
	b = pow((points[2].getX() - points[1].getX()), 2) + pow((points[2].getY() - points[1].getY()), 2);
	c = pow((points[0].getX() - points[2].getX()), 2) + pow((points[0].getY() - points[2].getY()), 2);
	if (a > c)
		swap(a, c);
	if (b > c)
		swap(b, c);
	return a + b == c;
}

Trapezoid::Trapezoid(int countPoints, Point* p):ClosedPolygonalChain(countPoints, p){}

Trapezoid::Trapezoid(const Trapezoid& tr):ClosedPolygonalChain(tr){}

double Trapezoid::height() const
{
	double a = this->len(this->points[1], this->points[2]);
	double b = this->len(this->points[0], this->points[3]);
	return 2 * this->area() / (a + b);
}

Trapezoid Trapezoid::operator=(const Trapezoid& tr)
{
	ClosedPolygonalChain::operator=(tr);
	return *this;
}

RegularPolygon::RegularPolygon(int countPoints = 0, Point* p = NULL):ClosedPolygonalChain(countPoints, p){}

RegularPolygon::RegularPolygon(const RegularPolygon& rp):ClosedPolygonalChain(rp){}

RegularPolygon RegularPolygon::operator=(const RegularPolygon& rp)
{
	ClosedPolygonalChain::operator=(rp);
	return *this;
}

double RegularPolygon::perimeter()
{
	return this->len(this->points[0], this->points[1]) * this->getN();
}

double RegularPolygon::area() const
{
	double angle = 360 / (2 * this->getN()) * (M_PI / 180);
	double lenght = pow(this->len(this->points[0], this->points[1]), 2);
	double temp = ((double)this->getN() * lenght) / (4 * tan(angle));
	return temp;
}
