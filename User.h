#pragma once
#include"AVLNode.h"

class User {
public:	
	AVLNode* root;
	
	User();
	int avlHeight(AVLNode* r);
	int max(int a, int b);
	int getBalance(AVLNode* r);

	AVLNode* SingleRightRotation(AVLNode* r);
	AVLNode* SingleLeftRotation(AVLNode* r);
	AVLNode* LeftRightRotation(AVLNode* r);
	AVLNode* RightLeftRotation(AVLNode* r);

	void insertUser();
	void insertUser(int i, string n);
	AVLNode* insert(int data, AVLNode* r, string n);

	void deleteUser();
	void deleteUser(int data);
	AVLNode* delete1(int data, AVLNode* r);


	void display_inorder(AVLNode* r);
	void display_preorder(AVLNode* r);
	void display_postorder(AVLNode* r);
	void display_inorder_balances(AVLNode* r);
	void InOrder();
	void InOrderBalance();
	void print();

	
	bool isAVL();
	void checkAVL(AVLNode* r, bool& ans);

	AVLNode* search(int data);
	AVLNode* search(AVLNode* r, int data, bool& ans);

	void finMin();
	AVLNode* findMin(AVLNode* r);

	void BorrowBook(BOOK& Lib);
	void BorrowBook(int issn, BOOK& Lib);
	void BorrowBook(int id, int issn, BOOK& Lib);

	void ReturnBook(BOOK& Lib);
	void ReturnBook(int issn, BOOK& Lib);
	void ReturnBook(int id, int issn, BOOK& Lib);

	void printUser();
	void printUser(int i);

	void fineHelper(AVLNode* r);
	void calcFines();

	void printAllUsersHelper(AVLNode* r);
	void printAllUsers();

	//void printAllPathsRecursive(AVLNode* r, vector<int> path);
	//void printAllPaths();
};
