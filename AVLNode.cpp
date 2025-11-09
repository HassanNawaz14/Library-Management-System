#include<iostream>
#include <iomanip>  // Add this include
#include"AVLNode.h"
#include"BOOK.h"
#include <windows.h>
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
using namespace std;

AVLNode::AVLNode() {}//just beacuse...

AVLNode::AVLNode(int i, string n)
{
	id = i;
	name = n;
	borrowedIssn = {};
	fine = 0;
	height = 1;
	left = right = NULL;
}

AVLNode::AVLNode(int i)
{
	id = i;
	cout << "Enter Name: ";
	cin >> name;
	borrowedIssn = {};
	fine = 0;
	height = 1;
	left = right = NULL;
}

void AVLNode::insertBorrowBookIssn(int issn, BOOK& Lib)
{
	this->borrowedIssn.push_back(issn);
	BSTNode* book = Lib.findBook(issn);
	int d, m, y;
	cout << "Enter date:\nDays:";
	cin >> d;
	cout << "\nMonth:";
	cin >> m;
	cout << "=\nYear:";
	cin >> y;

	book->requeatForBookIssue(issn, y, m, d);
}

void AVLNode::deleteReturnedBook(int issn, BOOK& Lib)
{
	//this->borrowedIssn.pop_back();
	int i = 0;
	while (borrowedIssn[i] != issn && i < borrowedIssn.size()) i++;
	if (i >= borrowedIssn.size())
	{
		cout << "you have not borrowed this book yet!" << endl;
		return;
	}
	borrowedIssn.erase(borrowedIssn.begin() + i);
	
	BSTNode* book = Lib.findBook(issn);
	
	this->fine += book->returnABook();
}


void AVLNode::printUser()
{
	setColor(11);
	cout << "\n" << string(50, '=') << endl << endl;
	cout << "              USER PROFILE" << endl;
	cout << string(50, '=') << endl << endl;
	cout << "   ID: " << this->id << endl;
	cout << "   Name: " << this->name << endl;
	cout << "   Outstanding Fine: $" << this->fine << endl;

	if (this->borrowedIssn.size() > 0) {
		cout << "\n   Borrowed Books (" << this->borrowedIssn.size() << "):" << endl;
		for (int i = 0; i < this->borrowedIssn.size(); i++) {
			cout << "  " << (i + 1) << ". ISSN: " << this->borrowedIssn[i] << endl;
		}
	}
	else {
		cout << "\n   No books currently borrowed." << endl;
	}
	cout << string(50, '=') << endl << endl;
	setColor(7);
	cout << endl;
}
