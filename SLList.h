// File   : SLList.h
// Author : Jarrett McCarty

#ifndef SLLIST_H
#define SLLIST_H

#include "SLNode.h"
#include <iostream>

class IndexError
{
public:
    const char * what () const throw ()
    {
        return "Caught IndexError\n";
    }
};

class ValueError
{
public:
    const char * what () const throw ()
    {
        return "Caught ValueError\n";
    }
};

template < typename T >
class SLList
{
public:
    /* Default Constructor */
    SLList()
        :  phead_(NULL)
      {}
    /* Copy Constructor */
    SLList(const SLList & src)
        : phead_(NULL)
    {
        // Temp node p recieves the originals head
        SLNode< T > * p = src.get_phead();
        // Copies values into the new node using insert tail
        while (p != NULL)
        {
            insert_tail(p->get_key());
            p = p->get_next();
        }
    }
    /* Deconstructor */
    ~SLList()
    {
        clear();
        delete phead_;
    }
    /* Variable to toggle the output */
    static bool debug_printing;

    /* Returns the phead if needed */
    SLNode< T > * get_phead() const
    {
        return phead_;
    }
    /* Overloaded assignment operator */
    const SLList & operator =(const SLList & rhs) // was not const
    {
        SLList temp(rhs);
        swap(temp);
        return *this;
    }
    /* Utility swap function */
    void swap(SLList & x)
    {
        SLNode< T > * temp = phead_;
        phead_ = x.phead_;
        x.phead_ = temp;
    }
    /* Inserts value at the beginning of the list */
    void insert_head(T key)
    {
        phead_ = new SLNode< T >(key, phead_);
    }
    /* Inserts value at the end of the list */
    void insert_tail(T key)
    {
        SLNode< T > * p = new SLNode< T >(key);

        // If the linked list is empty then set head = last
        if (phead_ == NULL)
        {
            phead_ = p;
        }
        else
        {
            // Creates a temp node and sets it to head
            SLNode< T > * temp;
            
            temp = phead_;
            
            // Uses temp to find the last node
            while (temp->get_next() != NULL)
            {
                temp = temp->get_next();
            }
            
            // Appends the last node with last
            temp->set_next(p);
        }
    }
    /* Removes values at the beginning of the list */
    T remove_head() // normally void, test.cpp needs a return value
    {
        // Similar to swap function
        SLNode< T > * p = phead_;
        if (phead_ == NULL)
        {
            throw IndexError();
        }
        p = phead_->get_next();
        T x = phead_->get_key();
        delete phead_;
        phead_ = p;
        return x;
    }
    /* Removes values at the end of the list */
    T remove_tail()
    {
        T x;
        if (is_empty())
        {
            throw ValueError();
        }
        else if (phead_->get_next() == NULL)
        {
            SLNode< T > * p = phead_;
            x = phead_->get_key();
            delete p;
            phead_ = NULL;
        }
        else
        {
            SLNode< T > * p = phead_;
            SLNode< T > * p_ = phead_->get_next();
            
            while (p_->get_next() != NULL)
            {
                p_ = p_->get_next();
                p = p->get_next();
            }
            p->set_next(NULL);
            x = p_->get_key();
            delete p_;
        }
        return x;
    }
    /* Function to find a value and return the node that points to it */
    SLNode< T > * find(T k) const
    {
        if (is_empty()) throw ValueError();
        SLNode< T > * p = phead_;
        while (p != NULL)
        {
            if (p->get_key() == k)
            {
                return (p);
            }
            p = p->get_next();
        }
        throw ValueError();
    }
    /* Removes a value thats specified by the node that is passed in */
    T remove(SLNode< T > * n)
    {
        T x = n->get_key();
        if (is_empty())
        {
            throw ValueError();
        }
        if (n->get_next() == NULL)
        {
            remove_tail();
            return x;
        }
        if (n != NULL)
        {
            SLNode< T > * nextNode = n->get_next();
            n->set_key(nextNode->get_key());
            n->set_next(nextNode->get_next());
            n = nextNode;
            delete n;
        }
        return x;
    }
    /* Function that clears all of list */
    void clear() 
    {
        while (!is_empty())
        {
            remove_tail();
        }
    }
    /* Function that returns the size of the list */
    int size() const
    {
        int s = 0;
        SLNode< T > * temp = phead_;
        while (temp != NULL)
        {
            ++s;
            temp = temp->get_next();
        }
        return s;
    }
    /* Function that returns a boolean value depending if the list is empty */
    bool is_empty() const
    {
        return ! phead_;
    }
    /* Overloaded []. Returns a value thats specified by the pos passed in */
    T operator[](int pos) const
    {
        if (pos < 0) throw IndexError();
        
        SLNode< T > * temp = phead_;
        int i = 0;
        while (temp != NULL)
        {
            if (i == pos)
            {
                return temp->get_key();
            }
            ++i;
            temp = temp->get_next();
        }
        throw IndexError();
         
    }
    T & operator[](int pos) 
    {
        if (pos < 0) throw IndexError();
        
        SLNode< T > * temp = phead_;
        int i = 0;
        while (temp != NULL)
        {
            if (i == pos)
            {
                return temp->get_key();
            }
            ++i;
            temp = temp->get_next();
        }
        throw IndexError();
         
    }

    /* Inserts a value after the node passed in and gives it the value of key */
    void insert_after(SLNode< T > * temp, const T & key)
    {
        SLNode< T > * p = new SLNode< T >(key, temp->get_next());
        temp->set_next(p);
    }
    /* Inserts a value before the node passed in and gives it the value key */
    void insert_before(SLNode< T > *temp, const T & key)
    {
        SLNode< T > * current = phead_;

        while(current->get_next() != NULL)
        {
            if(current->get_next()->get_key() == temp->get_key())
            {
                SLNode< T > * n = new SLNode< T >(key);
                n->set_next(current->get_next());
                current->set_next(n);
                return;
            }
            
            current = current->get_next();
        }
    }
    /* Overloaded == operator */
    bool operator ==(const SLList & rhs)
    {
        if (phead_ == NULL && rhs.phead_ == NULL)
        {
            return true;
        }
        SLNode< T > * p = phead_;
        SLNode< T > * q = rhs.phead_;
        while (p != NULL)
        {
            if (p->get_key() != q->get_key())
            {
                return false;
            }
            p = p->get_next();
            q = q->get_next();
            
        }
        return true;
    }
    /* Overloaded != operator */
    bool operator !=(const SLList & rhs)
    {
        return !(*this == rhs);
    }
    /* Returns the front of the list */
    T front() const
    {
        return phead_->get_key();
    }
    T & front()
    {
        return phead_->get_key();
    }
    /* Returns the back fo the list */
    T back() const
    {
        T x;
        SLNode< T > * p = phead_;
        while (p != NULL)
        {
            p = p->get_next();
            if (p->get_next() == NULL)
            {
                return x = p->get_key();
            }
        }
    }
    T & back()
    {
        SLNode< T > * p = phead_;
        while (p != NULL)
        {
            p = p->get_next();
            if (p->get_next() == NULL)
            {
                return p->get_key();
            }
        }
    }

private:
    SLNode< T > * phead_;
    
};
// Output for stack
template < typename T >
std::ostream & operator <<(std::ostream & cout, const SLList< T > & list)
{
    SLNode< T > * p = list.get_phead();
    while (p != NULL)
    {
        cout << p->get_key() << '\n';
        p = p->get_next();
    }
    return cout;
}

#endif

