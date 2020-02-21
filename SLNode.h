// File   : SLNode.h
// Author : Jarrett McCarty

#ifndef SLNODE_H
#define SLNODE_H

#include <iostream>

/******************************************************************************
This is the SLNode class. This contains all necessary methods/contructors
for the SLList class that is required for this assignment.

The required methods/constructors include the following:

SLNode< T >()
SLNode< T >(T)
SLNode< T >(t, SLNode * next)
SLNode * const & get_next() const
T get_key()
T set_key(T)
SLNode * & get_next(SLNode< T > * n)

This class also includes the static variable:

debug_printing

This variable can be toggeled on and off as demonstrated in test.cpp

Lastly this class contains an overloaded output operator <<.
This function prints differenly depending on 'debug_printing'.

 *****************************************************************************/

template < typename T >
class SLNode
{
public:
    /* Default Constructor */
    SLNode< T >()
    {}
    /* Contructor to only set a key value */
    SLNode< T >(const T & key)
        : key_(key), next_(NULL)
    {}
    /* Complete constructor to set key and next */
    SLNode< T >(const T & key, SLNode< T > * next)
        : key_(key), next_(next)
    {}
    /* Bool variable for printing */
    static bool debug_printing;
    
    /* Returns the dereference to a refernce that is next */
    SLNode * const & get_next() const
    {
        return next_;
    }
    /* Returns key value */
    T get_key() const 
    {
        return key_;
    }
    T & get_key()
    {
        return key_;
    }
    /* Sets key value */
    T set_key(T k)
    {
        key_ = k;
    }
    /* Sets next pointer */
    SLNode * & set_next(SLNode< T > * n)
    {
        next_ = n;
    }
private:
    
    T key_;
    SLNode< T > * next_;
};
    
#endif

