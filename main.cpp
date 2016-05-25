#include "ShapeFactory.h"
#include <sstream>

std::string IntToStr(int x)
{
    std::stringstream r;
    r << x;
    return r.str();
}

void main()
{
    //Point p("p",1, 3);
    //Circle c("Circle", 2, p);
    //std::cout << "shapes:" << Shape::GetCount() << std::endl;
    //std::cout << "points:" << Point::GetCount() << std::endl;

    Container<Shape *> shapes;   

    for (int i = 0; i < 20; ++i)
    {
        shapes.AddFirst(ShapeFactory::CreateRandomShape("S" + IntToStr(i + 1)));
    }


    std::cout << "shapes:" << Shape::GetCount() << std::endl;
    std::cout << "points:" << Point::GetCount() << std::endl;
    std::cout << "circles:" << Circle::GetCount() << std::endl;
    std::cout << "rect:" << Rect::GetCount() << std::endl;
    std::cout << "polyline:" << Polyline::GetCount() << std::endl;
    std::cout << "polygon:" << Polygon::GetCount() << std::endl;
    std::cout << "square:" << Square::GetCount() << std::endl << std::endl;


    int i = 0;
    shapes.IteratorInitial();
    while (!shapes.IteratorIsEnd())
    {
        ++i;
        std::cout <<i<<") " << * dynamic_cast<Printable *>(shapes.IteratorGetValue());
        shapes.IteratorToNext();
        std::cout << std::endl;
    }


    shapes.IteratorInitial();
    while (!shapes.IteratorIsEnd())
    {
        delete shapes.IteratorGetValue();
        shapes.IteratorToNext();
    }
    shapes.Clear();
    std::cout << "Container count: " << shapes.GetCount() <<std::endl;        

    std::cout << std::endl;
    std::cout << "shapes:" << Shape::GetCount() << std::endl;
    std::cout << "points:" << Point::GetCount() << std::endl;
    std::cout << "circles:" << Circle::GetCount() << std::endl;
    std::cout << "rect:" << Rect::GetCount() << std::endl;
    std::cout << "polyline:" << Polyline::GetCount() << std::endl;
    std::cout << "polygon:" << Polygon::GetCount() << std::endl;
    std::cout << "square:" << Square::GetCount() << std::endl << std::endl;

    _getch();
}

