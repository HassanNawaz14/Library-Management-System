#pragma once
#include<iostream>
#include"Date.h"
using namespace std;



class HNode {
public:
	int id;
	Date* date;
	HNode();
	HNode(int i, int y, int m ,int d);
};