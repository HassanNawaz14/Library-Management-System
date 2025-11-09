#pragma once
class Date {
public:
	int dd;
	int mm;
	int yy;
	Date(int d, int m, int y);
	int diffinDays(Date* other);
	bool isGreater(Date* other);
	void printDate();
};