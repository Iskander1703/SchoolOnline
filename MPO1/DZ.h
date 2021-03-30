#pragma once
#include <iostream>
using namespace std;

class DZ
{
private:
	string predmet;
	string beginDate;
	string endDate;
	string clas;
	string task;
public:
	DZ(string predmet_m, string beginDate_m, string endDate_m, string clas_m, string task_m);
	~DZ() {};
	void show();
	friend ostream& operator<< (std::ostream& out, const DZ& DZ_m);
	string getClas();
	string getBeginDate();
	string getPredmet();
	void change(int a, string b);

};