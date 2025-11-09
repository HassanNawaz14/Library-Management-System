#include<iostream>
#include<vector>
#include"BOOK.h"
using namespace std;

//just a structure to order books (simple insert delete only, all others in BSTNode class)
BOOK::BOOK() { root = NULL; }

BSTNode* BOOK::insHelper(BSTNode* r, BSTNode* newNode)
{
	if (!r)
		return newNode;
	if (newNode->ISSN > r->ISSN)
		r->right = insHelper(r->right, newNode);
	if (newNode->ISSN < r->ISSN)
		r->left = insHelper(r->left, newNode);
	if (newNode->ISSN == r->ISSN)
	{
		cout << "You are entring an already present Book again!" << endl;
		return r;
	}
	return r;
}
void BOOK::insert()
{
	int issn;
	string title;
	vector<string> lan;
	int nrc;
	int nic;
	cout << "Enter ISSN for the new Book: ";
	cin >> issn;
	cout << "Enter Title for the new Book: ";
	cin >> title;
	string t;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do
	{
		cout << "Enter the list of Authors (or -1 to end list): ";
		cin >> t;
		if (t != "-1")
			lan.push_back(t);
	} while (t != "-1");
	cout << "Enter Number of Issuable Coppies of the new Book: ";
	cin >> nic;
	cout << "Enter Number of Reference Coppies of the new Book: ";
	cin >> nrc;
	BSTNode* newNode = new BSTNode(issn, title, lan, nrc, nic);
	this->root = BOOK::insHelper(this->root, newNode);
}
void BOOK::insert(int issn, string title, vector<string> lan, int nic, int nrc)
{
	BSTNode* newNode = new BSTNode(issn, title, lan, nrc, nic);
	this->root = BOOK::insHelper(this->root, newNode);
}

void BOOK::removeHelper(BSTNode* &parent, BSTNode* &toRemove)
{
	if (!toRemove->left && !toRemove->right)
	{
		if (parent->left == toRemove)
			parent->left = NULL;
		else
			parent->right = NULL;
		delete toRemove;
		return;
	}
	//one chils:
	if (toRemove->left && !toRemove->right)
	{
		if (parent->left == toRemove)
			parent->left = toRemove->left;
		else
			parent->right = toRemove->left;
		delete toRemove;
		return;
	}
	if (!toRemove->left && toRemove->right)
	{
		if (parent->left == toRemove)
			parent->left = toRemove->right;
		else
			parent->right = toRemove->right;
		delete toRemove;
		return;
	}
	//both chs:
	//following: left ky rightest sy swapping:
	BSTNode* temp = toRemove->left;
	BSTNode* pr = toRemove;
	while (temp->right)
	{
		pr = temp;
		temp = temp->right;
	}
	
	//swap(toRemove, temp);//this may not work, if not, simply swap manually all members
	toRemove->ISSN = temp->ISSN;
	toRemove->title = temp->title;
	toRemove->listOAuthorNames = temp->listOAuthorNames;
	toRemove->noIssCopies = temp->noIssCopies;
	toRemove->noRefCopies = temp->noRefCopies;
	toRemove->demand = new Demand(temp->demand); //handeled by deep copy ctr in Demand.cpp;;;;;

	if (pr->left == temp)
		pr->left = temp->left;
	else
		pr->right = temp->left;
	
	delete temp;
}
void BOOK::remove()
{
	BSTNode* toRemove = BOOK::findBook();
	if (!toRemove) return;
	BSTNode* parent = NULL;
	BSTNode* temp = this->root;
	if (temp == NULL || toRemove == NULL) 
	{
		cout << "Nothing removing!!!" << endl;
		return;
	}
	if (temp == toRemove)
	{
		delete temp;
		this->root = NULL;
		cout << "Emptied the Books List!" << endl;
		return;
	}
	while (temp->ISSN != toRemove->ISSN)
	{
		parent = temp;
		if (toRemove->ISSN > temp->ISSN)
		{
			temp = temp->right;
		}
		else if (toRemove->ISSN < temp->ISSN)
		{
			temp = temp->left;
		}
	}
	BOOK::removeHelper(parent, toRemove);
}

BSTNode* BOOK::findBookHelper(BSTNode* r, int issn)
{
	if (!r) return NULL;
	if (r->ISSN == issn) return r;
	if (issn > r->ISSN)
		return findBookHelper(r->right, issn);
	if (issn < r->ISSN)
		return findBookHelper(r->left, issn);
}
BSTNode* BOOK::findBook()
{
	int issn;
	cout << "Enter the ISSN of the book you want to find (or remove/update): ";
	cin >> issn;
	BSTNode* found =  BOOK::findBookHelper(this->root, issn);
	if (!found)
	{
		cout << "No Book found with this ISSN!" << endl;
		return NULL;
	}
	//found->printBook();
	return found;
}
BSTNode* BOOK::findBook(int issn)
{
	BSTNode* found = BOOK::findBookHelper(this->root, issn);
	if (!found)
	{
		cout << "No Book found with this ISSN!" << endl;
		return NULL;
	}
	//found->printBook();
	return found;
}

void BOOK::update()
{
	BSTNode* toUpdate = BOOK::findBook();
	if (!toUpdate) return;
	int c;
	cout << "What do you want to Update: \n1.Title\n2.Authors\n3.No of Issuable Copies\n4.No of Ref Copies\nEnter a number: ";
	cin >> c;
	if (c == 1)
	{
		string t;
		cout << "Enter new title: ";
		cin >> t;
		toUpdate->title = t;
	}
	else if (c == 2)
	{
		vector<string> lan;
		string t;
		do
		{
			cout << "Enter the list of Authors (or -1 to end list): ";
			cin >> t;
			if (t != "-1")
				lan.push_back(t);
		} while (t != "-1");
		toUpdate->listOAuthorNames = lan;
	}
	else if (c == 3)
	{

		int t;
		cout << "Enter new No of Iss Copeis: ";
		cin >> t;
		toUpdate->noIssCopies = t;
	}
	else if (c == 4)
	{

		int t;
		cout << "Enter new No of Iss Copeis: ";
		cin >> t;
		toUpdate->noRefCopies = t;
	}
	else
	{

	}
}

void BOOK::findMostDemandedBookHelper(BSTNode* r, int &maxDemand, BSTNode* &maxDemanded)
{
	if (!r) return;
	if (r->demand->totalBorrows > maxDemand)
	{
		maxDemand = r->demand->totalBorrows;
		maxDemanded = r;
	}
	findMostDemandedBookHelper(r->left, maxDemand, maxDemanded);
	findMostDemandedBookHelper(r->right, maxDemand, maxDemanded);
}
void BOOK::findMostDemandedBook()
{
	if (!this->root) 
	{
		cout << "Book list is empty!" << endl;
		return;
	}

	int maxDemand = 0;
	BSTNode* maxDemanded = NULL;
	BOOK::findMostDemandedBookHelper(this->root, maxDemand, maxDemanded);
	if (maxDemanded)
		cout << "The most demanded Book is: " << maxDemanded->title
		<< " with " << maxDemand << " borrows ever..." << endl;
	else
		cout << "There no most demanded book... band pri hai lib..." << endl;
}

void BOOK::printHelper(BSTNode* r)
{
	if (!r)return;
	printHelper(r->left);
	r->printBook();
	printHelper(r->right);
}
void BOOK::printAllBooks()
{
	printHelper(this->root);
}