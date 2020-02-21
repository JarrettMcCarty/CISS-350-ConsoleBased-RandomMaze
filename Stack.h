// File   : Stack.h
// Author : Jarrett McCarty

#ifndef STACK_H
#define STACK_H

#include "SLList.h"
#include <iostream>

class UnderflowError // An UnderflowError object is thrown if
{
public:
    const char * what () const throw ()
    {
        return "Caught UnderFlowError\n";
    }
    
};
// you execute pop() on an empty stack.
template < typename T >
class Stack
{
public:
    Stack()
    {
        SLList< T > list;
    }
    void push(T k)
    {
        list.insert_head(k);
    }
    void pop()
    {
        if (list.size() == 0) throw UnderflowError();
        list.remove_head();
    }
    T top() const
    {
        return list.front();
    }
    T & top()
    {
        return list.front();
    }
    int size()
    {
        return list.size();
    }
    bool is_empty()
    {
        return list.is_empty();
    }
    void clear()
    {
        list.clear();
    }
    T operator [](T k) const
    {
        return list[k];
    }
    T & operator [](T k)
    {
        return list[k];
    }
    
private:
    SLList< T > list;
};

#endif

