// builder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*
Программа, собирающая пакет документов для студента и выпускника

*/



// Классы документов
class Pasport
{
public:
	void info() {
		cout << "Pasport" << endl;
	}
};

class Diplom
{
public:
	void info() {
		cout << "Diplom" << endl;
	}
};

class MedSpravka
{
public:
	void info() {
		cout << "MedSpravka" << endl;
	}
};


// Класс "Пакет документов", содержащий все типы документов (что-то типа шаблона)
class AllDoc
{
public:
	vector<Pasport> vp;
	vector<Diplom>      vd;
	vector<MedSpravka>    vm;
	void info() {
		int i;
		for (i = 0; i<vp.size(); ++i)  vp[i].info();
		for (i = 0; i<vd.size(); ++i)  vd[i].info();
		for (i = 0; i<vm.size(); ++i)  vm[i].info();
	}
};


// AllDocBuilder что-то вроде интерфейса для стандартного набора (реализация по умолчанию)

class AllDocBuilder
{
protected:
	AllDoc* p;
public:
	AllDocBuilder() : p(0) {}
	virtual ~AllDocBuilder() {}
	virtual void createDoc() {}
	virtual void getPasport() {}
	virtual void getDiplom() {}
	virtual void getMedSpravka() {}

	virtual AllDoc* getAll() { return p; }
};


// У студента есть медсправка и паспорт
class StudentBuilder : public AllDocBuilder
{
public:
	void createDoc() { p = new AllDoc; }
	void getPasport() { p->vp.push_back(Pasport()); }
	void getMedSpravka() { p->vm.push_back(MedSpravka()); }

};


// У выпускника есть паспорт и диплом
class WorkerBuilder : public AllDocBuilder
{
public:
	void createDoc() { p = new AllDoc; }
	void getPasport() { p->vp.push_back(Pasport()); }
	void getDiplom() { p->vd.push_back(Diplom()); }
};


// Класс, поэтапно создающий набор документов для студента или выпускника.
class Rector
{
public:
	AllDoc* create(AllDocBuilder & builder)
	{
		builder.createDoc();
		builder.getPasport();
		builder.getDiplom();
		builder.getMedSpravka();
		return(builder.getAll());
	}
};


int main()
{
	Rector rect;
	StudentBuilder stud;
	WorkerBuilder work;

	AllDoc * st = rect.create(stud);
	AllDoc * wr = rect.create(work);
	cout << "Documents for student:" << endl;
	st->info();
	cout << "\nDocuments for worker:" << endl;
	wr->info();
	return 0;
}