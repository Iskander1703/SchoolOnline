#include "Teacher.h"

teacher::teacher(string name_m, int age_m, string class_m, string predmet_m, string dateBirth_m)
{
    this->predmet = predmet_m;
    this->name = name_m;
    this->age = age_m;
    this->clas = class_m;
    this->dateBirth = dateBirth_m;

}
ostream& operator<< (std::ostream& out, const teacher& teacher_m)
{
    out << teacher_m.name << endl;
    out << teacher_m.predmet << endl;
    out << teacher_m.dateBirth << endl;
    out << teacher_m.age << endl;
    out << teacher_m.clas << endl;
    return out;
}

string teacher::getName()
{
    return (this->name);
}

void teacher::show()
{
    cout << "Фамилия имя отчество учителя: " << this->name << endl;
    cout << "Дата рождения: " << this->dateBirth << endl;
    cout << "Возраст: " << this->age << " лет" << endl;
    cout << "Класс обучения: " << this->clas << endl;
    cout << "Предметная область: " << this->predmet << endl;
}