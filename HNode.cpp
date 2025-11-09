#include"HNode.h"
using namespace std;

HNode::HNode() {}
HNode::HNode(int i, int y, int m, int d)
{
	this->id = i;
	this->date = new Date(d, m, y);
}