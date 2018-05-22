/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
    else
    {
        Queue<int> Q;
        Node *p;
        int v;

        for( v = 1; v<=size; v++)
        {
            dist[v] = INFINITY;
            path[v] = 0;
        }

        dist[s] = 0;
        Q.enqueue(s);

        while (!Q.isEmpty())
        {
            auto v1 = Q.getFront();
            Q.dequeue();
            p = array[v1].getFirst();


            while(p != nullptr)
            {
                int u = p->vertex;
                p = array[v1].getNext();

                if (dist[u] == INFINITY)
                {
                    dist[u] = dist[v1] + 1;
                    path[u] = v1;
                    Q.enqueue(u);
                }
            }
        }

    }
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
    else
    {
        Node *p;

        for(int v =1; v<=size; v++)
        {
                dist[v] = INFINITY;
                path[v] = 0;
                done[v] = false;
        }

        dist[s] = 0;
        done[s] = true;
        int v = s;

        while (true)
        {
            p = array[v].getFirst();


            while(p != nullptr)
            {
                if ( (done[p->vertex] == false) && (dist[p->vertex] > (dist[v] + W(v, p->vertex))) )
                {
                    dist[p->vertex] = dist[v] + W(v, p->vertex);
                    path[p->vertex] = v;
                }

                p = p->next;
                //array[v].getNext();

            }

            v = find_smallest_undone_distance_vertex();
            if (v == -1) break; //exit the loop

            done[v] = true;
        }
    }

}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
    else
    {
        printU(t);
        cout << t << "    (" << dist[t] << ")";
    }

}

void Digraph::printU(int n) const
{
    if(path[n] < 1)
        return;

    printU(path[n]);
    cout << path[n] << "       ";
}

int Digraph::W(int v, int u)
{
    if( v == u)
        return INFINITY;

    Node* current = array[v].getFirst();

    while((current->vertex != u) && current)
        current = current->next;

    if(!current)
        return INFINITY;

    return current->weight;
}

int Digraph::find_smallest_undone_distance_vertex()
{
    int smallestV = INFINITY;
    bool multipleSmallest = false;
    int temp;

    for(int v = 1; v<=size; v++)
    {
        if(!done[v])
        {
            if(dist[v] < smallestV)
            {
                smallestV = dist[v];
                multipleSmallest = false;
                temp = v;

            }

            else if( dist[v] == smallestV)
            {
                multipleSmallest = true;
                temp = v;
            }
        }
    }

    if(smallestV != INFINITY || multipleSmallest)
    {
        return temp;
    }

    return -1;
}
