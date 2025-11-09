#include<iostream>
#include"Demand.h"
using namespace std;

Demand::Demand(int cap)
{
	this->capacity = cap;
	this->arr = new HNode[this->capacity];
	this->noOfCurrDemands = 0; //size
	this->totalBorrows = 0;
}
Demand::Demand(Demand*& other)
{
	this->capacity = other->capacity;
	this->arr = new HNode[other->capacity];		  //just for avie..........................|
	for (int i = 0; i < other->noOfCurrDemands && (other->noOfCurrDemands < other->capacity); i++)
	{
		this->arr[i] = other->arr[i];
	}
	this->noOfCurrDemands = other->noOfCurrDemands; //size
	this->totalBorrows = other->totalBorrows;
}
void Demand::requestBorrow(int i, int y, int m, int d)
{
	this->totalBorrows++;
	if (this->noOfCurrDemands == this->capacity)
	{
		cout << "Sorry!There are already too many demands for this book..." << endl;
		return;
	}

	HNode newReq(i, y, m, d);
	this->arr[noOfCurrDemands] = newReq;
	int index = noOfCurrDemands;
	this->noOfCurrDemands++;

	while (index > 0 && arr[((index - 1) / 2)].date->isGreater(arr[index].date))
	{
		swap(arr[((index - 1) / 2)], arr[index]);
		index = ((index - 1) / 2);
	}

}


void Demand::stepDown(int index)
{
	int smallest = index;
	int left = (2 * smallest) + 1;
	int right = (2 * smallest) + 2;

	if (left <= this->noOfCurrDemands && this->arr[left].date->isGreater(arr[smallest].date))
		smallest = left;
	if (right <= this->noOfCurrDemands && this->arr[right].date->isGreater(arr[smallest].date))
		smallest = left;

	if (smallest != index)
	{
		swap(arr[index], arr[smallest]);
		stepDown(smallest);
	}
}

HNode Demand::processRequest()
{
	if (noOfCurrDemands == 0)
	{
		cout << "No more demands for this Book!!!" << endl;
		return HNode();
	}
	HNode top = arr[0];
	arr[0] = arr[noOfCurrDemands - 1];
	this->noOfCurrDemands--;
	stepDown(0);
	return top;
}
