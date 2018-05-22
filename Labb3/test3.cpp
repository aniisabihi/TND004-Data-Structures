#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

#include "BinarySearchTree.h"

using namespace std;

class Row
{
  public:

    string word;
    int frequency;

    //Default Constructor
    Row(string s, int f): word{s}, frequency{f} {};

    //Copy Constructor
    Row(const Row &w): word{w.word}, frequency{w.frequency}{};

    //Increment
    bool operator<(const Row &rhs)
    {
        return(word < rhs.word);
    }

    //stream insertion
    friend ostream& operator<<(ostream& os,  const Row& w)
    {
        os << w.word << endl;
        os << w.frequency << endl;

        return os;
    }

};


 //Test program 3: BiIterator
int main( )
{
    BinarySearchTree<string> T;
    ifstream file("words.txt");

    if (!file)
    {
        cout << "couldn't open file words.txt" << endl;
        return 1;
    }

    vector<string> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
    file.close();

    for(auto j: V1)
        T.insert( j );

    /**************************************/
    cout << "\nPHASE 1: contains\n\n";
    /**************************************/

    vector<string> V2 = { "airborne", "stop", "yelp", "Sweden", "obligations", "unbridled" };

    for(auto w: V2)
    {
        if( T.contains( w ) != T.end() ) //NOTE: contains should now return a bidirectional iterator
            cout << "\""<< w << "\"" << " in the tree" << endl;
        else
            cout << "\""<< w << "\"" << " not in the tree" << endl;
    }

    /**************************************/
    cout << "\nPHASE 2: BiIterator, operator++\n\n";
    /**************************************/

    for(BinarySearchTree<string>::BiIterator it = T.begin(); it != T.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << endl;

    /**************************************/
    cout << "PHASE 3: BiIterator, operator--\n\n";
    /**************************************/

    string largest = T.findMax( );

    for(auto it = T.contains( largest ); it != T.end(); --it)
    {
        cout << *it << endl;
    }

    cout << "\nFinished testing" << endl;

    return 0;
}
