#pragma once

#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

class Named
{
public:
	Named(std::string const & name) 
	{ 
		_name = name; 
	};
protected:
	std::string _name;
};


class Printable : public virtual Named
{
public:
	Printable(std::string const & name) : Named(name){};

	virtual void Print(std::ostream & out) = 0;

	friend std::ostream & operator << (std::ostream & out, Printable & shape) {
		shape.Print(out);
		return out;
	}
};
