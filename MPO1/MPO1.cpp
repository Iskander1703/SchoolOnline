// MPO1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include "Student.h"
#include "Teacher.h"
#include "Windows.h"
#include <fstream>
#include <list>
#include <string>
#include <chrono>
#include <ctime>  
#include "DZ.h"
#pragma warning(disable : 4996)

void GetTime();//Функция, которая записывает время запуска программы в файл
int GetChoice(int min, int max);//Выбор с минимальным и максимальным значением
int SignOrRegist();//Выбор входа или регистрация
int StudOrTeach();//Учитель или ученик
int chAction();//Функция возвращает число от 1 до 4. Числа-это сценарии(вход-ученик, вход-учитель, регистрация-ученик, регистрцаия-учитель)
void RegistrationStudent();//Регистрация нового студента и добавление его в хэш-файл и лист-файл
void RegistrationTeacher();//Регистрация нового студента и добавление его в хэш-файл и лист-файл
int MyHash(const string parol);//Функция хэширование. Получает на вход пароль-возвращает число-ячейку
list<student>  GetListRegStudent();//Берет из файла данные, заполняет ими список студентов и возвращает его
map<int, student>  GetMapRegStudent();//Берет из файла данные, заполняет ими хэш-таблиу студентов и возвращает его
map<int, teacher>  GetMapRegTeacher();//Берет из файла данные, заполняет ими хэш-таблицу учителей и возвращает его
list<teacher>  GetListRegTeacher();//Берет из файла данные, заполняет ими список учителей и возвращает его
void giveHomework();//При входе от учителя дать домашнее задание и записать его в файл
void studentEnter();//Вход для ученика
void teacherEnter();//Вход для учителя
list<DZ> GetListRegDZ();//Берет из файла данные, заполняет ими список домашнего задания и возвращает его
string CheckName();//Проверка имени фамилии на неразрешенные символы(при регистрации для учеников)
string CheckName2();//Проверка имени фамилии и отчества на неразрешенные символы(при регистрации для учителей)
int GetAge(int min, int max);//Предлагает ввести возвраст. Возвращет его. 
string CheckClas();//Ввод класса, проверка его на корректность и возврат класса
string GetDate(int min_year, int max_year);
string GetDate2(int min_year, int max_year);
string GetDate3(int min_year, int max_year);
bool compare_clas(const student& first, const student& second);//Компаратор для сортировки по названию класса.
void delDZ();//Функция удаления опреедленного домашнего задания из списка
void delAllDZ();//Функция удаления всего ДЗ
void changeDZ();//Функция изменения части домашнего задания

int main()
{
    GetTime();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
Menu:
    int choice=chAction();
    switch (choice)
    {
    case 1:
        studentEnter();
        break;
    case 2:
        teacherEnter();
        break;
    case 3:
        RegistrationStudent();
        system("cls");
        goto Menu;
        break;
    case 4:
        RegistrationTeacher();
        goto Menu;
        system("cls");
        break;
    }
   
}

void GetTime()//Функция фиксирует время запуска программы и записывает в файл time.txt
{
    auto start = std::chrono::system_clock::now();
    time_t start_t = std::chrono::system_clock::to_time_t(start);
    ofstream test1;
    test1.open("time.txt", ofstream::app);
    test1 << ctime(&start_t);
}

int GetChoice(int min, int max)//Функция для получения значения для действия в меню
{
    int choice;
    cin >> choice;
    while (choice<min || choice>max)
    {
        cin.clear();
        cin.ignore(20, '\n');
        cout << "Повторите ввод: ";
        cin >> choice;
    }
    return choice;
}

int SignOrRegist()//Функция регистрации или входа
{
    cout << "Добро пожаловать в элекронный журнал!" << endl << endl;
    cout << "Если вы уже зарегестрированы, выберите пункт Войти." << endl;
    cout << "Для создания нового аккаунта, выберите пунк Регистрация." << endl << endl;
    cout << "1.Войти\n2.Регистрация\n3.Выход\n";
    int choice;
    choice = GetChoice(1, 3);
    system("cls");
    return choice;
}

int StudOrTeach()
{
    cout << "Вы ученик или учитель?" << endl << endl;
    cout << "1.Ученик\n2.Учитель\n3.Вернуться назад\n";
    int choice;
    choice = GetChoice(1, 3);
    system("cls");
    return choice;
}

int chAction()
{
Back1:
    int choice1 = SignOrRegist();
    int choice2=3;
    switch (choice1)
    {
    case 1:
        choice2 = StudOrTeach();
        break;
    case 2:
        choice2 = StudOrTeach();
        break;
    case 3:
        exit(0);
        break;
    }
    if (choice2 == 3)
        goto Back1;
    if (choice1 == 1 && choice2 == 1)//Вход за ученика
        return 1;
    else if (choice1 == 1 && choice2 == 2)//Регистрация за ученика
        return 2;
    else if(choice1 == 2 && choice2 == 1)//Вход за учителя
        return 3;
    else if (choice1 == 2 && choice2 == 2)//Регистрация за учителя
        return 4;
  
}

void RegistrationTeacher()
{
    cin.ignore(20, '\n');
    string name_m =CheckName2();
    int age_m = GetAge(20, 90);
    string clas_m = CheckClas();
    cout << "Введите до 3 предметов через запятую, которые вы преподаете: ";
    string predmet_m;
    getline(cin, predmet_m);
    string birthday_m = GetDate(1920, 2000);
    teacher a1(name_m, age_m, clas_m,predmet_m, birthday_m);
    cout << "Придумайте пароль: ";
    string parol_m;
    getline(cin, parol_m);
    ofstream teachRegMap;
    ofstream teachRegList;
    teachRegMap.open("TeacherRegistrationMap.txt", ofstream::app);
    teachRegList.open("TeacherRegistrationList.txt", ofstream::app);
    teachRegMap << MyHash(parol_m) << endl;
    teachRegMap << a1;
    teachRegList << a1;
    cout << "Регистрация прошла успешно. Для продолжения нажмити Enter...";
    cin.get();
}
 
void RegistrationStudent()//Регистрация для ученика
{
    
    cin.ignore(20, '\n');
    string name_m;
    name_m = CheckName();
    int age_m;
    age_m = GetAge(7, 20);
    string clas_m = CheckClas();
    string birthday_m= GetDate(2002,2015);
    student a1(name_m, age_m, clas_m, birthday_m);
    cout << "Придумайте пароль: ";
    string parol_m;
    getline(cin, parol_m);
    ofstream studRegMap;
    ofstream studRegList;
    studRegMap.open("StudentRegistrationMap.txt", ofstream::app);
    studRegList.open("StudentRegistrationList.txt", ofstream::app);
    studRegMap<< MyHash(parol_m)<<endl;
    studRegMap << a1;
    studRegList << a1;
    cout << "Регистрация прошла успешно. Для продолжения нажмити Enter...";
    cin.get();

}

int MyHash(const string parol)//Функция хэширования
{
    int res = 0;
    for(int i=0;i<size(parol);i++)
    {
        res += static_cast<int>(parol[i]) * static_cast<int>(parol[i]);
        i++;
    }

    return res%5000;
}

list<student>  GetListRegStudent()//Открывает файл со списком и записывает ее в созданный список
{
    ifstream in("StudentRegistrationList.txt");
    list <student> list1;
    while (!in.eof())
    {
        string name_m;
        getline(in, name_m);
        string birthday_m;
        getline(in, birthday_m);
        int age_m;
        in >> age_m;
        in.ignore(20, '\n');
        string clas_m;
        getline(in, clas_m);
        student a1(name_m, age_m, clas_m, birthday_m);
        list1.push_back(a1);
    }
    return list1;
}

map<int, student>  GetMapRegStudent()//Открывает файл с хэштаблицей и записывает ее в соазданную хэштаблицу
{
    ifstream in("StudentRegistrationMap.txt");
    map <int, student> map1;
    while (!in.eof())
    {
        int hashParol_m;
        in >> hashParol_m;
        in.ignore(20, '\n');
        string name_m;
        getline(in, name_m);
        string birthday_m;
        getline(in, birthday_m);
        int age_m;
        in >> age_m;
        in.ignore(20, '\n');
        string clas_m;
        getline(in, clas_m);
        student a1(name_m, age_m, clas_m, birthday_m);
        map1.emplace(hashParol_m, a1);
    }
    map<int, student>  ::iterator  it = map1.begin();
    /*for (it = map1.begin(); it != map1.end(); it++)
    {
        cout << (it->first) << endl;
        cout << it->second << endl;
    }*/
    return map1;
}

list<teacher>  GetListRegTeacher()//Открывает файл со списком и записывает ее в созданный список
{
    ifstream in("TeacherRegistrationList.txt");
    list <teacher> list1;
    while (!in.eof())
    {
        string name_m;
        getline(in, name_m);
        string predmet_m;
        getline(in, predmet_m);
        string birthday_m;
        getline(in, birthday_m);
        int age_m;
        in >> age_m;
        in.ignore(20, '\n');
        string clas_m;
        getline(in, clas_m);
        teacher a1(name_m, age_m, clas_m, predmet_m, birthday_m);
        list1.push_back(a1);
    }
    list <teacher> ::iterator  it = list1.begin();
    /*for (it = list1.begin(); it != list1.end(); it++)
    {
        cout << (*it);
    }*/
    return list1;
}

map<int, teacher>  GetMapRegTeacher()//Открывает файл со списком и записывает ее в созданный список
{
    ifstream in("TeacherRegistrationMap.txt");
    map <int, teacher> map1;
    while (!in.eof())
    {
        int hashParol_m;
        in >> hashParol_m;
        in.ignore(20, '\n');
        string name_m;
        getline(in, name_m);
        string predmet_m;
        getline(in, predmet_m);
        string birthday_m;
        getline(in, birthday_m);
        int age_m;
        in >> age_m;
        in.ignore(20, '\n');
        string clas_m;
        getline(in, clas_m);
        teacher a1(name_m, age_m, clas_m, predmet_m, birthday_m);
        map1.emplace(hashParol_m,a1);
    }
    map<int, teacher>  ::iterator  it = map1.begin();
    /*for (it = map1.begin(); it != map1.end(); it++)
    {
        cout << (it->first) << endl;
        cout << it->second << endl;
    }*/
    return map1;
}

void studentEnter()
{
    cin.ignore(20, '\n');
    string name_m;
    cout << "Введите ваше имя и фамилию: ";
    getline(cin, name_m);
    cout << "Введите ваш пароль: ";
    string parol_m;
    getline(cin, parol_m);
    int hashPar = MyHash(parol_m);
    map<int, student> m1 = GetMapRegStudent();
    map<int, student>::iterator it = m1.find(hashPar);
    int flag = 0;
    while (flag == 0)
    {
        if (it == m1.end() || it->second.getName() != name_m)
        {
            system("cls");
            cout << "Неверный логин или пароль. Повторите ввод!" << endl;
            cout << "Введите ваше имя и фамилию: ";
            getline(cin, name_m);
            cout << "Введите ваш пароль: ";
            getline(cin, parol_m);
            hashPar = MyHash(parol_m);
            it = m1.find(hashPar);
        }
        else
        {
            flag++;
        }
    }
    system("cls");
    cout << "Авторизация прошла успешно!" << endl << endl;
    cout << "Ваш аккаунт: " << endl;
    it->second.show();
StudentMenu:
    cout <<"1.Посмотреть текущие домашние задания" << endl;
    cout << "2.Загрузить домашнее задание" << endl;
    cout << "3.Выход" << endl;
    int choice;
    choice = GetChoice(1, 3);
    system("cls");
    switch (choice)
    {
    case 1:
    {
        list<DZ> a2 = GetListRegDZ();
        list <DZ> ::iterator  ita = a2.begin();

        for (ita = a2.begin(); ita != a2.end(); ita++)
        {
            if (it->second.getClas() == ita->getClas())
            {
                (*ita).show();
            }
        }
        cout << "Нажмите Enter для того, что бы вернуться назад...";
        cin.ignore(20, '\n');
        cin.get();
        system("cls");
        goto StudentMenu;
        break;
    }
    case 2:
        cout << "Все домашние задания загружаются на почту вашему учителю." << endl<<endl;
        cout << "Нажмите Enter для того, что бы вернуться назад...";
        cin.ignore(20, '\n'); 
        cin.get();
        system("cls");
        goto StudentMenu;
        break;
    case 3:
        exit(0);
        break;
    }

}

void teacherEnter()
{
    cin.ignore(20, '\n');
    string name_m;
    cout << "Введите ваше имя, фамилию и отчество:  ";
    getline(cin, name_m);
    cout << "Введите ваш пароль: ";
    string parol_m;
    getline(cin, parol_m);
    int hashPar = MyHash(parol_m);
    map<int, teacher> m2 = GetMapRegTeacher();
    map<int, teacher>::iterator it = m2.find(hashPar);
    int flag = 0;
    while (flag == 0)
    {
        if (it == m2.end() || it->second.getName() != name_m)
        {
            system("cls");
            cout << "Неверный логин или пароль. Повторите ввод!" << endl;
            cout << "Введите ваше имя, фамилию и отчество:  ";
            getline(cin, name_m);
            cout << "Введите ваш пароль: ";
            getline(cin, parol_m);
            hashPar = MyHash(parol_m);
            it = m2.find(hashPar);
        }
        else
        {
            flag++;
        }
    }
    system("cls");
    cout << "Авторизация прошла успешно!" << endl << endl;
    cout << "Ваш аккаунт: " << endl<<endl;
    it->second.show();
    cout << endl;
  TeachMenu:
    cout<<"1.Создать домашнее задание" << endl;
    cout << "2.Проверить домашние задания" << endl;
    cout << "3.Посмотреть домашние задания" << endl;
    cout << "4.Показать список всех учеников" << endl;
    cout << "5.Удалить домашнее задание" << endl;
    cout << "6.Редактивровать домашнее задание" << endl;
    cout << "7.Удалить все домашние задания" << endl;
    cout << "8.Выход" << endl;
    int ch = GetChoice(1, 8);
    system("cls");
    switch (ch)
    {
    case 1:
    {
        giveHomework();
        cin.get();
        system("cls");
        goto TeachMenu;
        break;
    }
    case 2:
    {
        cout << "Выполненные задания учеников хранятся на вашей электронной почте." << endl;
        cout << "Нажмите Enter для того, что бы вернуться назад...";
        cin.ignore(20, '\n');
        cin.get();
        system("cls");
        goto TeachMenu;
        break;
    }
    case 3:
    {
        list<DZ> a2 = GetListRegDZ();
        list <DZ> ::iterator  ita = a2.begin();
        cin.ignore(20, '\n');
        cout << "Ввидете класс, у которого хотите показать все домашние задания: ";
        string pred;
        getline(cin, pred);
        for (ita = a2.begin(); ita != a2.end(); ita++)
        {
            if (pred == ita->getClas())
            {
                (*ita).show();
            }
        }
        cout << "Нажмите Enter для того, что бы вернуться назад...";
        cin.get();
        system("cls");
        goto TeachMenu;
        break;
    }
    case 4:
    {
        list<student> list1 = GetListRegStudent();
        list1.sort(compare_clas);
        list<student>::iterator it = list1.begin();
        for (list<student>::iterator it = list1.begin(); it != list1.end(); ++it)
            (*it).show();
        cout << "Нажмите Enter для того, что бы вернуться назад...";
        cin.ignore(20, '\n');
        cin.get();
        system("cls");
        goto TeachMenu;
        break;
    }
    case 5:
    {
        delDZ();
        cout << "Нажмите Enter для того, что бы вернуться назад...";
        cin.ignore(20, '\n');
        cin.get();
        system("cls");
        goto TeachMenu;
        break;
    }
    case 6:
    {
        changeDZ();
        cout << "Нажмите Enter для того, что бы вернуться назад...";
        cin.ignore(20, '\n');
        system("cls");
        goto TeachMenu;
        break;
    }
    case 7:
    {
        delAllDZ();  
        cout << "Все домашние задания успешно удалены."<<endl;
        cout << "Нажмите Enter для того, что бы вернуться назад...";
        cin.ignore(20, '\n');
        cin.get();
        system("cls");
        goto TeachMenu;
        break;
    }
    case 8:
        exit(0);
        break;
 
    }

}

void giveHomework()
{
    string predmet;
    string task;
    cin.ignore(20, '\n');
    cout << "Введите назвение предмета: ";
    getline(cin, predmet);
    string beginDate = GetDate2(2021, 2022);
    string endDate=GetDate3(2021, 2022);
    string clas = CheckClas();
    cout << "Введите задание: ";
    getline(cin, task);
    DZ a1(predmet, beginDate, endDate, clas, task);
    ofstream homework;
    homework.open("Homework.txt", ofstream::app);
    homework << a1;
    cout << "Задание успешно добавлено."<<endl;
    cout << "Нажмите Enter для того, что бы вернуться назад...";
}

list<DZ>  GetListRegDZ()//Открывает файл со списком и записывает ее в созданный список
{
    ifstream in("Homework.txt");
    list <DZ> list1;
    while (!in.eof())
    {
        string predmet_m;
        getline(in, predmet_m);
        string beginDate;
        getline(in, beginDate);
        string endDate;
        getline(in, endDate);
        string clas;
        getline(in, clas);
        string task;
        getline(in, task);
        DZ a1(predmet_m, beginDate, endDate,clas,task);
        list1.push_back(a1);
    }
    return list1;
}
string CheckName()
{
    string name;
    cout << "Введите ваше имя и фамилию: ";
    
    getline(cin, name);
    int flag = 0;
    while (flag !=name.size() || name.size() < 7)
    {
        flag = 0;
        for (int i = 0; i < name.size(); i++)
        {
            if ((name[i] <=-1 && name[i]>=-64 || name[i]==32))
            {
                flag = flag+1;
            }
        }
        if (flag == name.size() && name.size()>7)
        {
            break;
        }
        else
        {
            system("cls");
            cout << "Некорректный ввод!" << endl;
            cout << "Введите ваше имя и фамилию повторно: ";
            getline(cin, name);
        }
        
    }
    return name;
}

string CheckName2()
{
    string name;
    cout << "Введите ваше имя фамилию и отчество: ";
    getline(cin, name);
    int flag = 0;
    while (flag != name.size() || name.size() < 7)
    {
        flag = 0;
        for (int i = 0; i < name.size(); i++)
        {
            if ((name[i] <=-1 && name[i]>=-64 || name[i] == 32))
            {
                flag = flag + 1;
            }
        }
        if (flag == name.size())
        {
            break;
        }
        else
        {
            system("cls");
            cout << "Некорректный ввод!" << endl;
            cout << "Введите ваше имя фамилию и отчество повторно: ";
            getline(cin, name);
        }

    }
    return name;
}
int GetAge(int min, int max)//Функция для получения значения для действия в меню
{
    
    cout << "Введите ваш возраст: ";
    int age_m;
    cin >> age_m;
    while (age_m<min || age_m>max)
    {
        cin.clear();
        cout << "Введите корректный возраст: ";
        cin.ignore(20, '\n');
        cin >> age_m;
    }
    cin.ignore(20, '\n');
    return age_m;
}

string CheckClas()
{
    string a;
    cout << "Введите класс и букву: ";
    getline(cin, a);
    while (a != "1А" && a != "2А" && a != "3А" && a != "4А" && a != "5А" && a != "6А" && a != "7А" && a != "8А" &&
        a != "9А" && a != "10А" && a != "11А" && a != "1Б" && a != "2Б" && a != "3Б" && a != "4Б" && a != "5Б" &&
        a != "6Б" && a != "7Б" && a != "8Б" && a != "9Б" && a != "10Б" && a != "11Б" && a != "1В" && a != "2В" &&
        a != "3В" && a != "4В" && a != "5В" && a != "6В" && a != "7В" && a != "8В" && a != "9В" && a != "10В" &&
        a != "11В" && a != "1Г" && a != "2Г" && a != "3Г" && a != "4Г" && a != "5Г" && a != "6Г" && a != "7Г" &&
        a != "8Г" && a != "9Г" && a != "10Г" && a != "11Г")
    {
        cout << "Некорректный ввод!" << endl;
        cout << "Введите класс и букву повторно: ";
        getline(cin, a);
    }
    return a;
}

string GetDate(int min_year, int max_year)
{
    cout << "Введите вашу дату рождения: ";
    string dats;
    int flag = 0;
    getline(cin, dats);
    int day=0;
    int month=0;
    int year=0;
    if (isdigit(dats[0]) && isdigit(dats[1]) && isdigit(dats[3]) && isdigit(dats[4]) &&
        isdigit(dats[6]) && isdigit(dats[7]) && isdigit(dats[8]) && isdigit(dats[9]))
    {
        day = stoi(dats.substr(0, 2));
        month = stoi(dats.substr(3, 2));
        year = stoi(dats.substr(6, 4));
    } 
    else
    {
        goto Reser;
    }
    
    while (flag == 0)
    {
        if (year > min_year && year<max_year)
            flag = flag + 1;
        if (month > 0 && month < 12)
            flag = flag + 1;
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
            month == 10 || month == 12)
        {
            if (day > 0 && day < 32)
                flag = flag + 1;
        }
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            if (day > 0 && day < 31)
                flag = flag + 1;
        }
        if (month == 2)
        {
            if (year % 4 == 0)
            {
                if (day > 0 && day < 30)
                    flag = flag + 1;
            }
            else
            {
                if (day > 0 && day < 29)
                    flag = flag + 1;
            }
        }
        if (flag == 3)
            break;
        else
        {
            flag = 0;
        }
    Reser:
        cout << "Неправильный ввод или несуществующая дата. "<<endl;
        cout << "Формат даты : дд.мм.гггг" << endl;
        cout << "Введите вашу дату рождения повторно: ";
        getline(cin, dats);
        if (isdigit(dats[0]) && isdigit(dats[1]) && isdigit(dats[3]) && isdigit(dats[4]) &&
            isdigit(dats[6]) && isdigit(dats[7]) && isdigit(dats[8]) && isdigit(dats[9]))
        {
             day = stoi(dats.substr(0, 2));
            month = stoi(dats.substr(3, 2));
            year = stoi(dats.substr(6, 4));
        }
        else
        {
            goto Reser;
        }
    }
    return dats;
}

string GetDate2(int min_year, int max_year)
{
    cout << "Введите дату начала задания: ";
    string dats;
    int flag = 0;
    getline(cin, dats);
    int day = 0;
    int month = 0;
    int year = 0;
    if (isdigit(dats[0]) && isdigit(dats[1]) && isdigit(dats[3]) && isdigit(dats[4]) &&
        isdigit(dats[6]) && isdigit(dats[7]) && isdigit(dats[8]) && isdigit(dats[9]))
    {
        day = stoi(dats.substr(0, 2));
        month = stoi(dats.substr(3, 2));
        year = stoi(dats.substr(6, 4));
    }
    else
    {
        goto Reser;
    }

    while (flag == 0)
    {
        if (year >= min_year && year <= max_year)
            flag = flag + 1;
        if (month > 0 && month < 12)
            flag = flag + 1;
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
            month == 10 || month == 12)
        {
            if (day > 0 && day < 32)
                flag = flag + 1;
        }
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            if (day > 0 && day < 31)
                flag = flag + 1;
        }
        if (month == 2)
        {
            if (year % 4 == 0)
            {
                if (day > 0 && day < 30)
                    flag = flag + 1;
            }
            else
            {
                if (day > 0 && day < 29)
                    flag = flag + 1;
            }
        }
        if (flag == 3)
            break;
        else
        {
            flag = 0;
        }
    Reser:
        cout << "Неправильный ввод или несуществующая дата. " << endl;
        cout << "Формат даты : дд.мм.гггг" << endl;
        cout << "Введите дату начала задания повторно: ";
        getline(cin, dats);
        if (isdigit(dats[0]) && isdigit(dats[1]) && isdigit(dats[3]) && isdigit(dats[4]) &&
            isdigit(dats[6]) && isdigit(dats[7]) && isdigit(dats[8]) && isdigit(dats[9]))
        {
            day = stoi(dats.substr(0, 2));
            month = stoi(dats.substr(3, 2));
            year = stoi(dats.substr(6, 4));
        }
        else
        {
            goto Reser;
        }
    }
    return dats;
}
string GetDate3(int min_year, int max_year)
{
    cout << "Введите предельную дату выполнения задания: ";
    string dats;
    int flag = 0;
    getline(cin, dats);
    int day = 0;
    int month = 0;
    int year = 0;
    if (isdigit(dats[0]) && isdigit(dats[1]) && isdigit(dats[3]) && isdigit(dats[4]) &&
        isdigit(dats[6]) && isdigit(dats[7]) && isdigit(dats[8]) && isdigit(dats[9]))
    {
        day = stoi(dats.substr(0, 2));
        month = stoi(dats.substr(3, 2));
        year = stoi(dats.substr(6, 4));
    }
    else
    {
        goto Reser;
    }

    while (flag == 0)
    {
        if (year >= min_year && year <= max_year)
            flag = flag + 1;
        if (month > 0 && month < 12)
            flag = flag + 1;
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
            month == 10 || month == 12)
        {
            if (day > 0 && day < 32)
                flag = flag + 1;
        }
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            if (day > 0 && day < 31)
                flag = flag + 1;
        }
        if (month == 2)
        {
            if (year % 4 == 0)
            {
                if (day > 0 && day < 30)
                    flag = flag + 1;
            }
            else
            {
                if (day > 0 && day < 29)
                    flag = flag + 1;
            }
        }
        if (flag == 3)
            break;
        else
        {
            flag = 0;
        }
    Reser:
        cout << "Неправильный ввод или несуществующая дата. " << endl;
        cout << "Формат даты : дд.мм.гггг" << endl;
        cout << "Введите предельную дату выполнения повторно: ";
        getline(cin, dats);
        if (isdigit(dats[0]) && isdigit(dats[1]) && isdigit(dats[3]) && isdigit(dats[4]) &&
            isdigit(dats[6]) && isdigit(dats[7]) && isdigit(dats[8]) && isdigit(dats[9]))
        {
            day = stoi(dats.substr(0, 2));
            month = stoi(dats.substr(3, 2));
            year = stoi(dats.substr(6, 4));
        }
        else
        {
            goto Reser;
        }
    }
    return dats;
}

bool compare_clas(const student &first,  const student &second)
{
    
    if (first.getClas().size() <second.getClas().size())
        return true;
    if (first.getClas().size() > second.getClas().size())
        return false;
    if (first.getClas().size() == second.getClas().size())
    {
        int i = 0;
        while (i < 2)
        {
            if (first.getClas()[i] < second.getClas()[i])
                return true;
            else  if (first.getClas()[i] > second.getClas()[i])
                return false;
            ++i;
        }
    }
    return true;
}
void delDZ()
{
      list<DZ> a2 = GetListRegDZ();
      list <DZ> ::iterator  ita = a2.begin();
      string predmet;
      cin.ignore(20, '\n');
      cout << "Введите предмет, по которому было задано задание: ";
      getline(cin, predmet);
      string beginDate = GetDate2(2020,2021);
      string clas = CheckClas();
      int flag = 0;
      for (ita; ita != a2.end(); ++ita)
      {
          if (predmet == (*ita).getPredmet() && clas == (*ita).getClas() && beginDate == (*ita).getBeginDate())
          {
              flag++; 
              break;
          }
      }
      if (flag == 0)
      {
          cout << "Домашнее задание не найдено" << endl;
      }
      else
      {
          cout << "Домашнее задание найдено:" << endl << endl;
          (*ita).show();
          a2.erase(ita);
          cout << endl;
          ofstream in;
          in.open("Homework.txt");
          list <DZ> ::iterator  its = a2.begin();
          for (its; its != a2.end(); ++its)
          {
              in << (*its);
          }
          cout << "Домашнее задание успешно удалено."<<endl;
          in.close();
      }
}
void delAllDZ()
{
    ofstream in;
    in.open("Homework.txt");
    in.close();
    cout << "Все задания успешно удалены!"<<endl;
}

void changeDZ()
{
    list<DZ> a3 = GetListRegDZ();
    list <DZ> ::iterator  ita = a3.begin();
    string predmet;
    cin.ignore(20, '\n');
    cout << "Введите предмет, по которому было задано задание: ";
    getline(cin, predmet);
    string beginDate = GetDate2(2020, 2021);
    string clas = CheckClas();
    int flag = 0;
    for (ita; ita != a3.end(); ++ita)
    {
        if (predmet == (*ita).getPredmet() && clas == (*ita).getClas() && beginDate == (*ita).getBeginDate())
        {
            flag++;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "Домашнее задание не найдено" << endl;
    }
    else
    {
        cout << "Домашнее задание найдено:" << endl << endl;
        (*ita).show();
        cout << endl<<"Выберите пункт, который хотите изменить: " << endl;
        cout << "1.Предмет" << endl;
        cout << "2.Дата добавления" << endl;
        cout << "3.Предельная дата выполнения" << endl;
        cout << "4.Класс" << endl;
        cout << "5.Задание" << endl;
        int choice = GetChoice(1, 5);
        switch (choice)
        {
        case 1:
        {
            string predmet;
            cin.ignore(20, '\n');
            cout << "Введите предмет, по которому было задано задание: ";
            getline(cin, predmet);
            (*ita).change(1, predmet);
            break;
        }

        case 2:
        {
            cin.ignore(20, '\n');
            string beginDate = GetDate2(2020, 2021);
            (*ita).change(2, beginDate);
            break;
        }
        case 3:
        {
            cin.ignore(20, '\n'); 
            string endDate = GetDate2(2020, 2021);
            (*ita).change(3, endDate);
            break;
        }
        case 4:
        {
            cin.ignore(20, '\n'); 
            string clas = CheckClas();
            (*ita).change(4, clas);
            break;
        }
        case 5:
        {
            cin.ignore(20, '\n');
            string task;
            cout << "Введите задание: ";
            getline(cin, task);
            (*ita).change(5, task);
            break;
        }

        }
        cout << endl;
        ofstream in;
        in.open("Homework.txt");
        list <DZ> ::iterator  its = a3.begin();
        for (its; its != a3.end(); ++its)
        {
            in << (*its);
        }
        cout << "Домашнее задание успешно отредактировано." << endl;
        in.close();
    }
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
