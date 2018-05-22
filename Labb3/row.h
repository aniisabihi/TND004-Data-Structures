#ifndef ROWS_H
#define ROWS_H
#include <String>


using namespace std;


class rows
{
public:

	rows()
	{
		word = "";
		counter = 0;
	}
	rows(string s)
	{
		word = s;
		counter = 1;
	}

	bool operator<(const rows &rhs)
	{
		return (word < rhs.word);
	}
	bool operator<(const rows &rhs) const
	{
		return (word < rhs.word);
	}
	void increment()
	{
		counter++;
	}
	string getW()
	{
		return word;
	}
	friend ostream& operator<<(ostream & os,const rows& row)
	{
		os << row.word << " occured : " << row.counter << endl;

		return os;
	}
private:

	string word;
	int counter;



};
#endif
//BinarySearchTree<string> T;
	//ifstream file("words.txt");


	//if (!file)
	//{
	//	cout << "couldn't open file words.txt" << endl;
	//	return 1;
	//}

	//vector<string> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
	//file.close();

	//for (auto j : V1)
	//	T.insert(j);

	///**************************************/
	//cout << "\nPHASE 1: contains\n\n";
	///**************************************/

	//vector<string> V2 = { "airborne", "stop", "yelp", "Sweden", "obligations", "unbridled" };

	//for (auto w : V2)
	//{
	//	if (T.contains(w) != T.end()) //NOTE: contains should now return a bidirectional iterator
	//		cout << "\"" << w << "\"" << " in the tree" << endl;
	//	else
	//		cout << "\"" << w << "\"" << " not in the tree" << endl;
	//}

	///**************************************/
	//cout << "\nPHASE 2: BiIterator, operator++\n\n";
	///**************************************/

	//for (BinarySearchTree<string>::BiIterator it = T.begin(); it != T.end(); ++it)
	//{
	//	cout << *it << endl;
	//}

	//cout << endl;

	///**************************************/
	//cout << "PHASE 3: BiIterator, operator--\n\n";
	///**************************************/

	//string largest = T.findMax();

	//for (auto it = T.contains(largest); it != T.end(); --it)
	//{
	//	cout << *it << endl;
	//}

	//cout << "\nFinished testing" << endl;


	///**************************************/
	//cout << "a frequency table" << endl;
	///**************************************/
	//BinarySearchTree<rows> X;


	//for (auto j : V1)
	//{
	//	rows row(j);
	//
	//	bool flag = true; // bool to check if to insert

	//		for (BinarySearchTree<rows>::BiIterator it = X.begin(); it != X.end(); ++it)
	//			{
	//				if (it->getW()== row.getW())
	//				{
	//					it->increment();
	//					flag = false;
	//					break;
	//				}
	//			}

	//		if (flag)
	//		X.insert(row);
	//}


	//for (BinarySearchTree<rows>::BiIterator it = X.begin(); it != X.end(); ++it)
	//{
	//	cout << *it << endl;
	//}
