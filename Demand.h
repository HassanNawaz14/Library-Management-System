#pragma once
#include"HNode.h"


class Demand {
public:
	HNode* arr;
	int capacity;
	int noOfCurrDemands;
	int totalBorrows;
	Demand(int cap);
	Demand(Demand*& other);
	void requestBorrow(int i, int y, int m, int d);//insert
	HNode processRequest();//delete(top)
	void stepDown(int smallest);
};