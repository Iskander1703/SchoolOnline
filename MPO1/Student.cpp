#include "Student.h"


student::student (string name_m, int age_m, string class_m, string dateBirth_m)
{
    this->name = name_m;
    this->age = age_m;
    this->clas = class_m;
    this->dateBirth = dateBirth_m;

}
ostream& operator<< (std::ostream& out, const student& strudent_m)
{
    out <<  strudent_m.name << endl;
    out <<  strudent_m.dateBirth << endl;
    out <<  strudent_m.age << endl;
    out <<  strudent_m.clas<< endl;
    return out;
}
string student::getName() 
{
    return (this->name);
}
string student::getClas() const
{
    return (this->clas);
}

void student:: show()
{
    cout<<"��� ������� �������: " <<this->name << endl;
    cout << "���� ��������: " << this->dateBirth << endl;
    cout << "�������: " << this->age << " ���"<<endl;
    cout << "����� ��������: " << this->clas << endl<<endl;
}