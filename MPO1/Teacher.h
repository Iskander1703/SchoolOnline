#pragma once
#include <iostream>
#include <vector>
using namespace std;

class teacher
{
private:
	string name;
	int age;
	string clas;
	string  predmet;
	string dateBirth;
public:
	teacher(string name_m, int age_m, string class_m, string predmet, string dateBirth);
	~teacher() {};
	string getName();
	void show();
	friend ostream& operator<< (std::ostream& out, const teacher& strudent_m);
};
