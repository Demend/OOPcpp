#pragma once

#include <conio.h>
#include <iostream>

template<class T>
class Container 
{
public:

    Container() : first(NULL), last(NULL), count(0), iterator(NULL)
    {}

	Container(const Container<T> & other): first(NULL), last(NULL), count(0)
    {
        for(int i = 0; i < other.GetCount(); ++i)
        {
            AddLast(other.GetByIndex(i));
        }
    }

    ~Container()
    {
        ClearList();
    }

    void AddFirst(T const &value)
    {
        first = new Element(value, first);
        if (count == 0)
            last = first;

        ++count;
    }

	void AddLast(T const &value)
    {
		Element * node = new Element<T>(value);
        if (count == 0)
        {
            first = node;   
        }
        else
        {
            last->next = node;
        }
		last = node;
        ++count;
    }

    void DeleteFirst()
    {
		if (IsEmpty())
			return;

        Element * temp = first;
        first = first->next;
        delete temp;

		if (count == 1)
			last = NULL;

        --count;
    }

    void DeleteLast()
    {
		if (IsEmpty())
			return;

		if (count == 1)
        {
            delete last;
			last = NULL;
            first = NULL;
		}
        else
        {
            Element *temp = first;
            while (temp->next != last)
                temp = temp->next; 

            delete last;
			last = temp;
            last->next = NULL;
        } 
        --count;
    }

    T &GetFirstValue() const
    {
        return first->value;
    }

    T &GetLastValue() const
    {
        return last->value;
    }

    int GetCount() const
    {
        return count;
    }

    bool IsEmpty() const
    {
        return count == 0;
    }

    void PrintContainer()
    {
        if (IsEmpty())
		{
            std::cout << "List is empty" <<    std::endl;
			return;
		}
        Element *temp = first;
        while (temp != NULL)
        {
            std::cout<< temp->value << std::endl;
            temp = temp->next;
        }
    }

    void ClearList()
    {
        if (IsEmpty())
            return;

        while (first != NULL)
        {
            Element * temp = first->next;
            delete first;
            first = temp;
        }
        last = NULL;
        count = 0;
    }

	void IteratorInitial() 
	{ 
		iterator = first; 
	}

	T IteratorGetValue() const 
	{ 
		return iterator->value;
	}

	void IteratorToNext() 
	{ 
		if (iterator != NULL)
			iterator = iterator->next; 
	}

	bool IteratorIsEnd() const 
	{
		return (iterator == NULL) ? true : false;
	}

private:
	struct Element
    {
        Element(T const &val, Element *nxt = NULL) : value(val), next(nxt) {}
        T value;
        Element *next;    
    };

    Element * first;
    Element * last;
	Element * iterator;

    int count;
};