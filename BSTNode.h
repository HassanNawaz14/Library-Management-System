#pragma once
#include<iostream>
#include<vector>
#include"HNode.h"
#include"Demand.h"
using namespace std;

class BSTNode {
public:
	int ISSN;
	string title;
	vector<string> listOAuthorNames;
	int noRefCopies;
	int noIssCopies;
	Demand* demand;
	BSTNode* left; 
	BSTNode* right;
	BSTNode(int issn, string t, vector<string> lan, int nrc, int nic);
	void requeatForBookIssue(int i, int y, int m, int d);
	int returnABook();
	void printBook();
};