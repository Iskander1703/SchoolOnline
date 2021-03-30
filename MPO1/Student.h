#pragma once
#include <iostream>
using namespace std;

class student
{
private:
	string name;
	int age;
	string clas;
	string dateBirth;
public:
	student(string name_m, int age_m, string class_m,string dateBirth);
	~student() {};
	void show();
	friend ostream& operator<< (std::ostream& out, const student& strudent_m);
	string getName();
  string getClas() const;
	
};
