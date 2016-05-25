#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Base.h"
#include "Container.h"
#include <cstdint>

class Shape : public virtual Named
{
public:
    virtual ~Shape() 
    { 
        --__counter; 
    }
    static uint32_t GetCount() 
    { 
        return __counter; 
    }
    Shape(std::string const & name) : Named(name) 
    { 
        ++__counter; 
    }

private:
    static uint32_t __counter;
};

class Point : public Printable, public Shape
{
public:
    Point(std::string const & name, uint32_t const & x, uint32_t const & y) : Shape(name), Printable(name), Named(name)
    {
        _x = x;  
        _y = y;
        ++__pointCounter;
    }

    Point() : Shape("some point"), Printable("some point"), Named("some point")
    {
        _x = 0;  
        _y = 0;
        ++__pointCounter;
    }

    Point(Point const & point) : Shape(point._name), Printable(point._name), Named(point._name)
    {
        _x = point._x;  
        _y = point._y;
        ++__pointCounter;
    }

    ~Point()
    {
        --__pointCounter;
    }

    static uint32_t GetCount() 
    { 
        return __pointCounter; 
    }

    virtual void Print(std::ostream & out)
    {
        out << Named::_name << "(" << _x << "," << _y << ")";
    }

    uint32_t GetX() const
    { 
        return _x; 
    }

    uint32_t GetY() const{ return _y; }

private:
    uint32_t _x, _y;
    static uint32_t __pointCounter;
};

class Rect : public Printable, public Shape
{
public:
    Rect(std::string const & name, Point const & leftUp, Point const & rightDown) : Shape(name), Printable(name), Named(name)
    {
        _leftUp = leftUp;
        _rightDown = rightDown;
        ++__rectCounter;
    }
    ~Rect()
    {
        _leftUp.~Point();
        _rightDown.~Point();

        --__rectCounter;
    }

    static uint32_t GetCount() 
    { 
        return __rectCounter; 
    }

    virtual void Print(std::ostream & out)
    {
        out << "Rectangle " << Named::_name << " ["
            << "left up point: " << _leftUp << ", "
            << "right down point: " << _rightDown << ")]";
    }

private:
    uint32_t _height, _width;
    Point _leftUp, _rightDown;
    static uint32_t __rectCounter;
};

class Circle : public Printable, public Shape
{
public:
    Circle(std::string const & name, uint32_t const & radius,
        Point const & center) : Shape(name), Printable(name), Named(name), _center(center), _radius(radius)
    {
        ++__circleCounter;
    }
    ~Circle()
    {
        _center.~Point();
        --__circleCounter;
    }

    static uint32_t GetCount() 
    { 
        return __circleCounter; 
    }

    virtual void Print(std::ostream & out)
    {
        out << "Circle " << Named::_name << " ["
            << "radius: " << _radius << ", "
            << "square: " << (M_PI*_radius*_radius) << ", "
            << "center position: (" << _center.GetX() << "," << _center.GetY() << ")]";
    }
private:
    uint32_t _radius;
    Point _center;
    static uint32_t __circleCounter;
};

class Polyline : public Printable, public Shape
{
public:
    Polyline(std::string const & name) : Shape(name), Printable(name), Named(name) 
    { 
        ++__polylineCounter;
    }

    Polyline(std::string const & name, Container<Point *> const & points) : Shape(name), Printable(name), Named(name) 
    { 
        _points = points;
        ++__polylineCounter;
    }

    ~Polyline()
    {
        _points.IteratorInitial();
        while (!_points.IteratorIsEnd())
        {
            (_points.IteratorGetValue())->~Point();
            _points.IteratorToNext();
        }
        --__polylineCounter;
    }

    void AddPoint(Point * point)
    {
        _points.AddFirst(point);
    }

    static uint32_t GetCount() { return __polylineCounter; }

    virtual void Print(std::ostream & out)
    {
        _points.IteratorInitial();

        out << "Polyline " << Named::_name;
        if (_points.GetCount() > 0)
        {
            out << "[Points: ";
            while (!_points.IteratorIsEnd())
            {
                (*_points.IteratorGetValue()).Print(out);
                _points.IteratorToNext();

                if (!_points.IteratorIsEnd()) out << ", ";
            }
            out << "]";
        }
    }
protected:
    Container<Point *> _points;
private:
    static uint32_t __polylineCounter;
};

class Polygon : public Polyline
{
public:
    Polygon(std::string const & name, Container<Point *> const & points) 
        : Named(name), Polyline(name)
    {
        _points = points;
        ++__polygonCounter;
    }
    Polygon(std::string const & name) 
        : Named(name), Polyline(name)
    {
        ++__polygonCounter;
    }

    ~Polygon()
    {
        --__polygonCounter;
    }
    
    static uint32_t GetCount() 
    { 
        return __polygonCounter; 
    }

    virtual void Print(std::ostream & out)
    {
        _points.IteratorInitial();

        out << "Polygon " << Named::_name;
        if (_points.GetCount() > 0)
        {
            out << "[Points: ";

            while (!_points.IteratorIsEnd())
            {
                (*_points.IteratorGetValue()).Print(out);
                _points.IteratorToNext();

                if (!_points.IteratorIsEnd()) out << ", ";
            }
            out << "]";
        }
    }
private:
    static uint32_t __polygonCounter;
};

class Square : public Printable, public Shape
{
public: 
    Square(std::string const & name, Point & p, uint32_t const & side) : Shape(name), Printable(name), Named(name),
        _side(side), _p(p)
    { 
        ++__squareCounter;
    }

    ~Square()
    {
        _p.~Point();
        --__squareCounter;
    }

    static uint32_t GetCount() 
    { 
        return __squareCounter; 
    }

    virtual void Print(std::ostream & out)
    {
        out << "Square " << Named::_name << " ["
            << "side: " << _side << ", "
            << "square: " << (_side*_side) << ", "
            << "left up position: (" << _p.GetX() << "," << _p.GetY() << ")]";
    }
private:
    static uint32_t __squareCounter;
    uint32_t _side;
    Point & _p;
};

uint32_t Shape::__counter = 0;
uint32_t Point::__pointCounter = 0;
uint32_t Rect::__rectCounter = 0;
uint32_t Circle::__circleCounter = 0;
uint32_t Polyline::__polylineCounter = 0;
uint32_t Polygon::__polygonCounter = 0;
uint32_t Square::__squareCounter = 0;

