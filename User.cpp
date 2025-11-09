#pragma once
//#include"AVLNode.h"
#include"User.h"


User::User()
{
	root = NULL;
}

int User::avlHeight(AVLNode* r)
{
	if (!r) return 0;
	return r->height;
}
int User::max(int a, int b)
{
	if (a >= b) return a;
	else return b;
}
int User::getBalance(AVLNode* r) // get balance factor of a node
{
	if (!r) return 0;
	return avlHeight(r->left) - avlHeight(r->right);
}

AVLNode* User::SingleRightRotation(AVLNode* r) //LL case
{
	AVLNode* parent = r;
	AVLNode* child = r->left;
	AVLNode* childRight = child->right;
	child->right = parent;
	parent->left = childRight;

	parent->height = 1 + max(avlHeight(parent->left), avlHeight(parent->right));
	child->height = 1 + max(avlHeight(child->left), avlHeight(child->right));

	return child;
}
AVLNode* User::SingleLeftRotation(AVLNode* r) //RR case
{
	AVLNode* parent = r;
	AVLNode* child = r->right;
	AVLNode* childLeft = child->left;
	child->left = parent;
	parent->right = childLeft;

	parent->height = 1 + max(avlHeight(parent->left), avlHeight(parent->right));
	child->height = 1 + max(avlHeight(child->left), avlHeight(child->right));

	return child;
}
AVLNode* User::LeftRightRotation(AVLNode* r) //LR case
{
	r->left = SingleLeftRotation(r->left);//middle rot
	return SingleRightRotation(r);
}
AVLNode* User::RightLeftRotation(AVLNode* r) //RL case
{
	r->right = SingleRightRotation(r->right);
	return SingleLeftRotation(r);
}

AVLNode* User::insert(int data, AVLNode* r, string name)
{
	if (!r) return new AVLNode(data, name);
	if (data > r->id)
		r->right = insert(data, r->right, name);
	else if (data < r->id)
		r->left = insert(data, r->left, name);
	else
	{
		cout << "I'm not allowing dups..." << endl;
		return r;
	}

	r->height = 1 + max(avlHeight(r->left), avlHeight(r->right));
	int balance = getBalance(r);

	if (balance < -1 && data > r->right->id)//RR
		return SingleLeftRotation(r);
	if (balance < -1 && data < r->right->id)//RL
		return RightLeftRotation(r);
	if (balance > 1 && data < r->left->id)//LL
		return SingleRightRotation(r);
	if (balance > 1 && data > r->left->id)//LR
		return LeftRightRotation(r);
	return r;
}
void User::insertUser()
{
	int i;
	string n;
	cout << "Enter id: ";
	cin >> i;
	cout << "Enter name: ";
	cin >> n;
	this->root = this->insert(i, this->root, n);
}
void User::insertUser(int i, string n)
{
	this->root = this->insert(i, this->root, n);
}

AVLNode* User::delete1(int data, AVLNode* r)
{
	if (!r) return NULL;
	if (data > r->id)
		r->right = delete1(data, r->right);
	else if (data < r->id)
		r->left = delete1(data, r->left);
	else//matchhh
	{
		if (!r->left && !r->right)//nochild
		{
			delete r;
			return NULL;
		}

		//1child
		if (r->left && !r->right)
		{
			AVLNode* temp = r->left;
			delete r;
			return temp;
		}
		if (!r->left && r->right)
		{
			AVLNode* temp = r->right;
			delete r;
			return temp;
		}

		//allchild
		//smallest(leftest)from the right:
		//ismy balance b khrb hoga... par khn hoga... (smalest from right se ya r se??)
		AVLNode* smallest = r->right;

		while (smallest && smallest->left)
			smallest = smallest->left;

		r->id = smallest->id;
		r->right = delete1(smallest->id, r->right); //I think ye handle kr ly ga for every case
	}

	if (!r) return r;

	r->height = 1 + max(avlHeight(r->left), avlHeight(r->right));

	int balance = getBalance(r);

	if (balance < -1 && getBalance(r->right) <= 0)//RR
		return SingleLeftRotation(r);
	if (balance < -1 && getBalance(r->right) > 0)//RL
		return RightLeftRotation(r);
	if (balance > 1 && getBalance(r->left) >= 0)//LL
		return SingleRightRotation(r);
	if (balance > 1 && getBalance(r->left) < 0)//LR
		return LeftRightRotation(r);
	//avlHeight(r->right->right) > avlHeight(r->right->left)
	return r;
}
void User::deleteUser()
{
	int i;
	cout << "Enter id: ";
	cin >> i;
	this->root = delete1(i, this->root);
}
void User::deleteUser(int data)
{
	this->root = delete1(data, this->root);
}


void User::display_inorder(AVLNode* r)
{
	if (!r) return;
	display_inorder(r->left);
	cout << "Id: " << r->id << " Name: " << r->name;
	display_inorder(r->right);
}
void User::display_preorder(AVLNode* r)
{
	if (!r) return;
	cout << "Id: " << r->id << " Name: " << r->name;
	display_preorder(r->left);
	display_preorder(r->right);
}
void User::display_postorder(AVLNode* r)
{
	if (!r) return;
	display_postorder(r->left);
	display_postorder(r->right);
	cout << "Id: " << r->id << " Name: " << r->name;
}
void User::display_inorder_balances(AVLNode* r)//just to check k balance hua b k ni...
{
	if (!r) return;
	display_inorder_balances(r->left);
	cout << "Id: " << r->id << " Name: " << r->name << " Balance: " << getBalance(r) << endl;
	display_inorder_balances(r->right);
}
void User::InOrderBalance()
{
	display_inorder_balances(this->root);
	cout << endl;
}
void User::InOrder()
{
	display_inorder(this->root);
	cout << endl;
	cout << endl;
}
void User::print()
{
	display_preorder(this->root);
	cout << endl;
	display_inorder(this->root);
	cout << endl;
	display_postorder(this->root);
	cout << endl;
	cout << endl;
}


void User::checkAVL(AVLNode* r, bool& ans)
{
	if (!r) return;
	if (ans)
	{
		checkAVL(r->left, ans);
		if (getBalance(r) > 1 && getBalance(r) < -1)
			ans = 0;
		checkAVL(r->right, ans);
	}
}
bool User::isAVL()
{
	bool ans = 1;
	checkAVL(this->root, ans);
	return ans;
}

AVLNode* User::search(AVLNode* r, int data, bool& ans)
{
	if (!r) return NULL;
	if (!ans)
	{
		if (data > r->id)
			return search(r->right, data, ans);
		else if (data < r->id)
			return search(r->left, data, ans);
		else//matchhh
		{
			ans = 1;
			return r;
		}
	}
}
AVLNode* User::search(int data)
{
	bool ans = 0;
	AVLNode* found = search(this->root, data, ans);
	if (ans)
		return found;
	cout << "Not found..." << endl << endl;
	return NULL;
}

AVLNode* User::findMin(AVLNode* r)
{
	if (!r->left) return r;
	//left most is sb se chota always
	return findMin(r->left);
}
void User::finMin()
{
	cout << "First Id: " << findMin(this->root)->id << endl << endl;
}


void User::BorrowBook(BOOK& Lib)
{
	int issn;
	cout << "Enter ISSN: ";
	cin >> issn;
	int id;
	cout << "Enter ID: ";
	cin >> id;
	AVLNode* user = User::search(id);
	user->insertBorrowBookIssn(issn, Lib);
}
void User::BorrowBook(int issn, BOOK& Lib)
{
	int id;
	cout << "Enter ID: ";
	cin >> id;
	AVLNode* user = User::search(id);
	user->insertBorrowBookIssn(issn, Lib);
}
void User::BorrowBook(int id, int issn, BOOK& Lib)
{
	AVLNode* user = User::search(id);
	user->insertBorrowBookIssn(issn, Lib);
}

void User::ReturnBook(BOOK& Lib)
{
	int issn;
	cout << "Enter ISSN: ";
	cin >> issn;
	int id;
	cout << "Enter ID: ";
	cin >> id;
	AVLNode* user = User::search(id);
	user->deleteReturnedBook(issn, Lib);
}
void User::ReturnBook(int issn, BOOK& Lib)
{
	int id;
	cout << "Enter ID: ";
	cin >> id;
	AVLNode* user = User::search(id);
	user->deleteReturnedBook(issn, Lib);
}
void User::ReturnBook(int id, int issn, BOOK& Lib)
{
	AVLNode* user = User::search(id);
	user->deleteReturnedBook(issn, Lib);
}


void User::printUser()
{
	cout << "Enter id:";
	int i;
	cin >> i;
	AVLNode* user = this->search(i);
	user->printUser();
}
void User::printUser(int i)
{
	AVLNode* user = this->search(i);
	user->printUser();
	cout << endl;
}

void User::fineHelper(AVLNode* r)
{
	if (!r)return;
	fineHelper(r->left);
	if (r->fine > 0)
		cout << r->id << ": Name: " << r->name << " ows: " << r->fine << " ";
	fineHelper(r->right);
}
void User::calcFines()
{
	cout << "Fines of all users are given below:" << endl;
	fineHelper(this->root);
	cout << endl;
}

void User::printAllUsersHelper(AVLNode* r)
{
	if (!r) return;
	printAllUsersHelper(r->left);
	r->printUser();
	printAllUsersHelper(r->right);
}
void User::printAllUsers()
{
	User::printAllUsersHelper(this->root);
}

//void User::printAllPathsRecursive(AVLNode* r, vector<int> path)
//{
//	if (!r) return;
//	path.push_back(r->id);
//	printAllPathsRecursive(r->left, path);
//	if (!r->left && !r->right)
//	{
//		for (int i = 0; i < path.size(); i++)
//			cout << path[i] << " ";
//		cout << endl;
//	}
//	printAllPathsRecursive(r->right, path);
//}
//void User::printAllPaths()
//{
//	vector<int>path;
//	printAllPathsRecursive(this->root, path);
//	cout << endl;
//}











