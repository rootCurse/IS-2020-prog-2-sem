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
	for (int i = 0; i < countPoints; i++)
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
	this->points.~vector();
}

ClosedPolygonalChain::ClosedPolygonalChain(int countPoints = 0, Point* p = NULL):PolygonalChain(countPoints, p){}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& cpc) : PolygonalChain(cpc){}

double ClosedPolygonalChain::perimeter() const
{
	//todo use perimeter from base class
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
	//todo use ints
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
	//todo use operator= from base class
	this->points = cpc.points;
	return *this;
}

ClosedPolygonalChain::~ClosedPolygonalChain()
{
	//todo dont do it
	this->points.~vector();
}

Polygon::Polygon(int countPoints = 0, Point* p = NULL):ClosedPolygonalChain(countPoints, p){}

Polygon::Polygon(const Polygon& p): ClosedPolygonalChain(p){}

Polygon Polygon::operator=(const Polygon& p)
{
	this->points = p.points;
	return *this;
}

Polygon::~Polygon()
{
	this->points.~vector();
}

Triangle::Triangle(int countPoints = 0, Point* p = NULL): ClosedPolygonalChain(countPoints, p){}

Triangle::Triangle(const Triangle& t): ClosedPolygonalChain(t){}

Triangle Triangle::operator=(const Triangle& t)
{
	this->points = t.points;
	return *this;
}

bool Triangle::hasRightAngle() const
{
	//todo without sqrt
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
	this->points.~vector();
}

Trapezoid::Trapezoid(int countPoints, Point* p):ClosedPolygonalChain(countPoints, p){}

Trapezoid::Trapezoid(const Trapezoid& tr):ClosedPolygonalChain(tr){}

double Trapezoid::height() const
{
	double a = sqrt(pow((points[2].getX() - points[1].getX()), 2) + pow((points[2].getY() - points[1].getY()), 2));
	double b = sqrt(pow((points[0].getX() - points[3].getX()), 2) + pow((points[0].getY() - points[3].getY()), 2));
	return 2 * this->area() / (a + b);
}

Trapezoid Trapezoid::operator=(const Trapezoid& tr)
{
	this->points = tr.points;
	return *this;
}

Trapezoid::~Trapezoid()
{
	this->points.~vector();
}

RegularPolygon::RegularPolygon(int countPoints = 0, Point* p = NULL):ClosedPolygonalChain(countPoints, p){}

RegularPolygon::RegularPolygon(const RegularPolygon& rp):ClosedPolygonalChain(rp){}

RegularPolygon RegularPolygon::operator=(const RegularPolygon& rp)
{
	this->points = rp.points;
	return *this;
}

//todo area and perimeter O(1)
RegularPolygon::~RegularPolygon()
{
	this->points.~vector();
}
