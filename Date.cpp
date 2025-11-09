#include<iostream>
using namespace std;
#include"Date.h"

Date::Date(int d, int m, int y)
{
	this->dd = d;
	this->mm = m;
	this->yy = y;
}

int Date::diffinDays(Date* other) //assuming that always:other > *this (other is alway ahead of *this)
{
	int y = this->yy - other->yy;
	int m = this->mm - other->mm;
	int d = this->dd - other->dd;
	return (d + (m * 30) + (y * 365));
}

bool Date::isGreater(Date* other)
{
	if (other->yy >= this->yy)
	{
		if (other->yy == this->yy)
		{
			if (other->mm >= this->mm)
			{
				if (other->mm == this->mm)
				{
					if (other->dd >= this->dd)
					{
						if (this->dd == other->dd)
							return 0;
						else
							return 1;
					}
					else 
						return 0;
				}
				else
					return 1;
			}
			else
				return 0;
		}
		else
			return 1;
	}
	else 
		return 0;
}


void Date::printDate()
{
	cout << this->dd << "/" << this->mm << "/" << this->yy << endl;
}