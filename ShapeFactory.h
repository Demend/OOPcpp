#pragma once

//#include "Container.h"
#include "Shapes.h"

class ShapeFactory
{
public:

    static Point * CreatePoint(std::string const & name)
    {
        uint32_t x = rand() % 100;
        uint32_t y = rand() % 100;

        return new Point(name, x, y);
    }

    static Rect * CreateRect(std::string const & name)
    {
        Point * p1= CreatePoint("leftUp");
        Point * p2= CreatePoint("rightDown");

        return new Rect(name, *p1, *p2);
    }

    static Circle * CreateCircle(std::string const & name)
    {
        Point * center = CreatePoint("cent");
        uint32_t radius = rand() % 99 + 1;

        return new Circle(name, radius, * center);
    }

    static Square * CreateSquare(std::string const & name)
    {
        Point * leftUp = CreatePoint("leftUp");
        uint32_t side = rand() % 99 + 1;

        return new Square(name, *leftUp, side);
    }

    static Polyline * CreatePolyline(std::string const & name)
    {
        int numPoints = rand() % 4 + 2;//2...5 points
        Polyline * p = new Polyline(name);
    
        for (int i = numPoints; i>0; --i)
        {
            p->AddPoint(CreatePoint("P"));
        }
        return p;
    }

    static Polygon * CreatePolygon(std::string const & name)
    {
        int numPoints = rand() % 3 + 3;//3...5 points
        Polygon *p = new Polygon(name);

        for (int i = 0; i<numPoints; ++i)
        {
            p->AddPoint(CreatePoint("P"));
        }
        return p;
    }

    static Shape * CreateRandomShape(std::string const & name)
    {
        int i = rand() % 6;

        switch (i)
        {
            case 0: { return CreatePoint(name); }
            case 1: { return CreateRect(name); }
            case 2: { return CreateCircle(name); }
            case 3: { return CreatePolyline(name); }
            case 4: { return CreatePolygon(name); }
            default: { return CreateSquare(name); }
        }
    }
};