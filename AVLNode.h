#pragma once
#include<iostream>
#include<vector>
#include"BOOK.h"
using namespace std;

class AVLNode {
public:
	int id;
	string name;
	vector<int> borrowedIssn;
	int fine;
	int height;
	AVLNode* left;
	AVLNode* right;
	AVLNode();
	AVLNode(int i);
	AVLNode(int i, string n);
	void insertBorrowBookIssn(int issn, BOOK& Lib);
	void deleteReturnedBook(int issn, BOOK& Lib);
	void printUser();
};