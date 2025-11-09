#include<iostream>
#include<vector>
#include"BSTNode.h"
//#include"HNode.h"
//#include"Demand.h"
#include <windows.h>
void setColor1(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
using namespace std;


BSTNode::BSTNode(int issn, string t, vector<string> lan, int nrc, int nic)
{
	this->ISSN = issn;
	this->title = t;
	this->listOAuthorNames = lan;
	this->noRefCopies = nrc;
	this->noIssCopies = nic;
	this->demand = new Demand(10);
	this->left = this->right = NULL;
}

void BSTNode::requeatForBookIssue(int i, int y, int m, int d)//to be called from the AVL
{
	this->demand->requestBorrow(i, y, m, d);
	if(noIssCopies > 0)
	{
		HNode issued = this->demand->processRequest(); //issue re k sath hi book mil gai
		this->noIssCopies--;
		cout << "Successfully Issued: " <<  this->title << endl;
	}
	else
	{
		cout << "You are entered in the Queue for the issuence of this Book!" << endl;
	}
}
int BSTNode::returnABook()
{
	//check return date!!!!!!!!
	int d, m, y;
	cout << "Enter Return date:\nDays:";
	cin >> d;
	cout << "\nMonth:";
	cin >> m;
	cout << "=\nYear:";
	cin >> y;

	Date* returnDate = new Date(d, m, y);
	int diff = returnDate->diffinDays(this->demand->arr[0].date);
	/*cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< endl;
	cout << "Diff: " << diff << endl;*/
	
	int f = 0;
	if (diff > 14)
	{
		f = diff - 14;
	}
	this->noIssCopies++;
	cout << "Thanks for returning the Book!" << endl;
	if (this->demand->noOfCurrDemands > 0)
	{
		this->demand->processRequest();
		this->noIssCopies--;
	}
	return f;
}

void BSTNode::printBook()
{
	setColor1(14);
	cout << "\n" << string(60, '-') << endl;
	cout << "    ISBN: " << ISSN << endl;
	cout << "    Title: " << title << endl;
	cout << "    Authors: ";
	for (int i = 0; i < listOAuthorNames.size(); i++) {
		cout << listOAuthorNames[i];
		if (i < listOAuthorNames.size() - 1) cout << ", ";
	}
	cout << "\n    Available Copies: " << noIssCopies;
	cout << "\n    Reference Copies: " << noRefCopies;
	cout << "\n    Total Borrows: " << demand->totalBorrows;
	cout << "\n" << string(60, '-') << endl;
	setColor1(7);
}