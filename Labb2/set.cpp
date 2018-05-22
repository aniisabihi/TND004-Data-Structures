#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set () // FUNKAR FUNKAR
	: counter(0)
{
    head = new Node();
    tail = new Node(0, nullptr, head);
    head->next = tail;
}


//Conversion constructor
Set::Set (int n) // FUNKAR FUNKAR
	: counter(0)
{
	head = new Node();
    tail = new Node(0, nullptr, head);
    head->next = tail;
    inserter(tail, n);
}

void Set::inserter(Node *p, int val) // FUNKAR FUNKAR
{
	Node* newNode = new Node(val, p, p->prev); //steps 1 and 2
	p->prev = p->prev->next = newNode; //steps 3 and 4
	counter++;
}

void Set::eraser(Node *temp)           // F€RDIG OCH FUNKAR
{
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    counter--;

    delete temp;
}


//Constructor to create a Set from a sorted array
Set::Set (int a[], int n) // a is sorted // FUNKAR FUNKAR
	: counter(0)
{
    head = new Node();
    tail = new Node(0, nullptr, head);
    head->next = tail;

	for (int i = 0; i < n;i++)
	{
		inserter(tail, a[i]);
	}
}

Set::~Set() // FUNKAR FUNKAR
{
	make_empty();
	delete head;
	delete tail;

    counter = 0;
}


//Copy constructor
Set::Set (const Set& source) // FUNKAR FUNKAR
	:counter(0)
{
    head = new Node();
    tail = new Node(0, nullptr, head);
    head->next = tail;

    Node *dummy = source.head->next;

	if (dummy != source.tail)
	{
		while (dummy->next != nullptr)
		{
			inserter(tail, dummy->value);
            dummy = dummy->next;
		}
	}
}

//Move constructor

Set::Set(Set && source)
{
	head = source.head;
	tail = source.tail;
	counter = source.counter;

	source.head = nullptr;
	source.tail = nullptr;
	source.counter = 0;
}

//Copy-and-swap assignment operator
//Note that call-by-value is used for source parameter // FUNKAR FUNKAR
Set& Set::operator=(Set source)
{
	if(this != &source)
    {
        swap(head, source.head);
        swap(tail, source.tail);
        swap(counter, source.counter);
    }

	return *this;
}


//Test whether a set is empty
bool Set::_empty () const // FUNKAR FUNKAR
{
    return (!counter);
}


//Test set membership
bool Set::is_member (int val) const    // FUNKAR FUNKAR
{
	Node *temp = head->next;

    while(temp != tail)
    {
        if(temp->value == val)
        {
            return true;
        }

        temp = temp->next;
    }
    return false;
}



//Return number of elements in the set
unsigned Set::cardinality() const           // F€RDIG OCH FUNKAR
{
	return counter;
}


//Make the set empty
void Set::make_empty()            // F€RDIG OCH FUNKAR
{
    if (!head)
		return;

	Node *temp = head->next;

    while( temp != tail)
    {
        Node *p = temp;
        temp = temp->next;
        delete p;
        counter--;
    }
    head->next = tail;
    tail->prev = head;
}

//Modify *this such that it becomes the union of *this with Set S
//Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S)          // F€RDIG OCH FUNKAR
{
    Node *t = head->next; // iterator in this set
	Node *s = S.head->next; // iterator in  b set

	while (s != S.tail && t != tail)
	{
        if ( s->value == t->value)
        {
            s = s->next;
            t = t->next;
        }

		else if (t->value < s->value)
		{
			t = t->next;
		}

		else if (t->value > s->value)
		{
			inserter(t, s->value);
			s = s->next;
		}
	}

	while( s && s != S.tail)
    {
        inserter(tail, s->value);
        s = s->next;
    }

	return *this;
}


//Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)                    // F€RDIG OCH FUNKAR
{
    Node *t = head->next; // iterator in this set
	Node *s = S.head->next; // iterator in  b set

	while (t != nullptr && s != nullptr)
	{
        if (s->value == t->value)
        {
            s = s->next;
            t = t->next;
        }

		else if (t->value < s->value)
		{
			t = t->next;
            eraser(t->prev);

		}

		else if (t->value > s->value)
		{
			s = s->next;
		}
	}

    while( t && t != tail)
    {
        t = t->next;
        eraser(t->prev);
    }

	return *this;
}


//Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S)
{
	Node *t = head->next; // iterator in this set
	Node *s = S.head->next; // iterator in  b set

	while (t->next != nullptr && s->next != nullptr)
	{
		if (t->value > s->value)
		{
			s = s->next;
		}

		else if (t->value < s->value)
		{
			t = t->next;
		}

        else if ( s->value == t->value)
        {
            s = s->next;
            t = t->next;
            eraser(t->prev);
        }
	}

    while( t && t != tail)
    {
        t = t->next;
    }

	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b             // F€RDIG OCH FUNKAR
bool Set::operator<=(const Set& b) const
{
	Node *t = head->next; // iterator in this set
	Node *p = b.head->next;

    while(t != tail && p != b.tail)
    {
        if(t->value == p->value)
        {
            t = t->next;
            p = p->next;
        }

        else if(t->value < p->value)
        {
            return false;
        }

        else if(t->value > p->value)
        {
            p = p->next;
        }
    }
	return true; //remove this line
}


//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a                     // F€RDIG OCH FUNKAR
bool Set::operator==(const Set& b) const
{
	if( b <= *this && *this <= b)
        return true;

    else
        return false;
}


//Return true, if the set is different from set b
//a == b, iff a <= b and b <= a                     // F€RDIG OCH FUNKAR
bool Set::operator!=(const Set& b) const
{
    if(!(b <= *this && *this <= b))
        return true;

    else
        return false;
}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, iff a <= b but not b <= a                     // F€RDIG OCH FUNKAR
bool Set::operator<(const Set& b) const
{
	if(*this <= b)
        return true;

    else
        return false; //remove this line
}


// Overloaded operator<<
ostream& operator<<(ostream& os, const Set& b)
{
	if (b._empty())
		os << "Set is empty!" << endl;
	else
	{
		auto temp = b.head->next;

		os << "{ ";
		while (temp != b.tail)
		{
			os << temp->value << " ";
			temp = temp->next;
		}

		os << "}" << endl;
	}

	return os;
}


