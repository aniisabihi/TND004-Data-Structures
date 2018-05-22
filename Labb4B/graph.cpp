/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}



// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    // *** TODO ***
        Node *p;
        int s = 1;

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
                if ( (done[p->vertex] == false) && (dist[p->vertex] > W(v, p->vertex)) )
                {
                    dist[p->vertex] = W(v, p->vertex);
                    path[p->vertex] = v;
                }

                p = p->next;
                //array[v].getNext();

            }

            v = find_smallest_undone_distance_vertex();
            if (v == -1) break; //exit the loop

            done[v] = true;
        }

        printU();

        cout << "Total Weight: " << W(v,p->vertex);
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
//    Heap H;
//    DisjointSets D(n);
////    H.heapify(E);
//
//    int counter = 0;
//
//    while(counter < n-1)
//    {
//        (v, u) = H.deleteMin();
//
//        if( D.find(u) != D.find(v))
//        {
//            display(v, u, weight(v, u));
//            D.union(D.find(u), D.find(v));
//            counter ++;
//        }
//    }

    Heap<Edge> H;// min-heap by edges cost
	DSets D(size); //n trees with one node each
	heapify(H); //build the heap with all edges

	int counter = 0;
	int totW = 0;

	while (counter < size -1)
	{
		auto temp = H.deleteMin();

		if (D.find(temp.head) != D.find(temp.tail))
		{
			cout << " ( " << temp.head << "," << temp.tail << "," << temp.weight << " )" << endl;		//display(v, u, weight(v, u));

			D.join(D.find(temp.head), D.find(temp.tail));
			counter++;
			totW += temp.weight;
		}
	}
	cout << "Total weight: " << totW << endl;
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

int Graph::W(int v, int u) const
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

int Graph::find_smallest_undone_distance_vertex() const
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

void Graph::printU() const
{

	int totalW = 0;
	for (int v = 2; v <= size; v++)
	{
		cout << "(" << path[v] << "," << v << "," << dist[v]<< ")" << endl;
		totalW += dist[v];
	}

	cout <<"Total weight: " << totalW;

}
void Graph::heapify(Heap<Edge> & H) const
{
	for (int v = 1; v <= size; v++)
	{
		auto start = array[v].getFirst();

		while(start->next)
		{
			H.insert(Edge(start->vertex, v, start->weight));
			start = start->next;
		}
	}
}
