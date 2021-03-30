#include "DZ.h"

DZ::DZ(string predmet_m, string beginDate_m, string endDate_m, string clas_m, string task_m)
{
	this->predmet = predmet_m;
	this->clas = clas_m;
	this->beginDate = beginDate_m;
	this->endDate = endDate_m;
	this->task = task_m;
}

ostream& operator<< (std::ostream& out, const DZ& DZ_m)
{
	out << DZ_m.predmet << endl;
	out << DZ_m.beginDate << endl;
	out << DZ_m.endDate << endl;
	out << DZ_m.clas << endl;
	out << DZ_m.task << endl;
	return out;
}
string DZ::getClas()
{
	return this->clas;
}
string DZ::getBeginDate()
{
	return this->beginDate;
}
string DZ::getPredmet()
{
	return this->predmet;
}
void DZ::show()
{
	cout <<"Предмет: " <<this->predmet <<endl;
	cout << "Дата добавления: " <<this->beginDate<< endl;
	cout << "Предельная дата выполнения: "<<this->endDate<< endl;
	cout << "Класс: " <<this->clas<< endl;
	cout << "Задание: "<<this->task<< endl;
}
void DZ::change(int a, string b)
{
	switch (a)
	{
	case 1:
		this->predmet = b;
		break;
	case 2:
		this->beginDate = b;
		break;
	case 3:
		this->endDate = b;
		break;
	case 4:
		this->clas = b;
		break;
	case 5:
		this->task= b;
		break;
	}
}
