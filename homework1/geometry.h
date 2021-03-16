#ifndef HEADER_H
#define HEADER_H
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Point
{
private:
	int x, y;
public:
	Point(int x = 0, int y = 0);

	Point(const Point& p);

	int getX() const;

	int getY() const;

	Point operator=(const Point& p);

	~Point() = default;
};

class PolygonalChain
{
public:
	vector<Point> points;
public:
	PolygonalChain(int countPoints, Point* p);

	PolygonalChain(const PolygonalChain& pc);

	PolygonalChain operator=(const PolygonalChain& pc);

	int getN() const;

	double len(Point p1, Point p2) const;

	Point getPoint(int index) const;

	virtual double perimeter() const;

	virtual  ~PolygonalChain() = default;
};

class ClosedPolygonalChain : public PolygonalChain
{
public:
	ClosedPolygonalChain(int countPoints, Point* p);

	ClosedPolygonalChain(const ClosedPolygonalChain& cpc);

	virtual double perimeter() const;

	virtual double area() const;

	ClosedPolygonalChain operator=(const ClosedPolygonalChain& cpc);
	//fixed use default
	virtual ~ClosedPolygonalChain() = default;
};

class Polygon : public ClosedPolygonalChain
{
public:
	Polygon(int countPoints, Point* p);

	Polygon(const Polygon& p);

	Polygon operator=(const Polygon& p);

	virtual ~Polygon()  = default;
};

class Triangle : public ClosedPolygonalChain
{
public:
	Triangle(int countPoints, Point* p);

	Triangle(const Triangle& t);

	Triangle operator=(const Triangle& t);

	bool hasRightAngle() const;

	virtual ~Triangle()  = default;
};

class Trapezoid : public ClosedPolygonalChain
{
public:
	Trapezoid(int countPoints, Point* p);

	Trapezoid(const Trapezoid& tr);

	double height() const;

	Trapezoid operator=(const Trapezoid& tr);

	virtual ~Trapezoid() = default;
};

class RegularPolygon : public ClosedPolygonalChain
{
public:
	RegularPolygon(int countPoints, Point* p);

	RegularPolygon(const RegularPolygon& rp);

	RegularPolygon operator=(const RegularPolygon& rp);

	virtual double perimeter();

	virtual double area() const;

	virtual ~RegularPolygon() = default;
};

#endif
