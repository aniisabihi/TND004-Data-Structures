/*********************************************
* file:	~\tnd004\lab\lab4b\dsets.cpp         *
* remark: implementation of disjoint sets    *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>

#include <cassert>

using namespace std;

#include "dsets.h"

// -- CONSTRUCTORS

DSets::DSets(int theSize)
{
    assert(theSize > 0);
    size = theSize;
    array = new int[size + 1];
    init();
}

// -- DESTRUCTOR

DSets::~DSets()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// create initial sets
void DSets::init()
{
    for (int i = 1; i <= size; i++)
    {
        array[i] = -1;
    }
}

// join sets named r and s where r != s
// i.e. join trees with roots r and s
void DSets::join(int r, int s)
{
    assert(r != s);
    assert(r >= 1 && r <= size);
    assert(s >= 1 && s <= size);
    assert(array[r] < 0);
    assert(array[s] < 0);

    // simple union
    //array[r]  = s;

    // *** TODO ***
    // weighted union (by size)
    if(  array[r]  <  array[s]  )  //  s  is  deeper
        array[s]  =  r;  //  Make  s  new  root
    else
    {
        if( array[r]  ==  array[s]  )
            --array[r];  //  Update  height  if  same

        array[s]  =  r;  //  Make  s  new  root
    }
}

// return name of current set for x
// i.e. return root of tree for x
int DSets::find(int x)
{
    assert(x >= 1 && x <= size);

    // simple find
    if (array[x] < 0)
    {
        return x;
    }
    else
    {
        return array[x] = find(array[x]);
    }

    // *** TODO ***
    // find with path compression
}

// just in case ...
void DSets::print() const
{
    cout << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << setw(4) << i;
    }
    cout << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << setw(4) << array[i];
    }
    cout << endl;
}