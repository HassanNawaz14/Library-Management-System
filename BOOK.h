#pragma once
#include<iostream>
#include"BSTNode.h"
using namespace std;

class BOOK { //bst
	BSTNode* root;
public:
	BOOK();
	void insert();
	void insert(int issn, string title, vector<string> lan, int nic, int nrc);
	BSTNode* insHelper(BSTNode* r, BSTNode* newNode);
	void remove();
	void removeHelper(BSTNode* &parent, BSTNode* &toRemove);
	void update();
	BSTNode* findBook();
	BSTNode* findBook(int issn);
	BSTNode* findBookHelper(BSTNode* r, int issn);
	void findMostDemandedBook();
	void findMostDemandedBookHelper(BSTNode* r, int& maxDemand, BSTNode* &maxDemaned);
	void printAllBooks();
	void printHelper(BSTNode* r);
};