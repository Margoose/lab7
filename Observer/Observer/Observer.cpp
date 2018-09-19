// Observer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>






using namespace std;

class SupervisedString;


class IObserver
{
public:
	virtual void handleEvent(const SupervisedString&) = 0;
};



class SupervisedString
{
	
	int _flag;
	// �������� ������ ��� �������	
	string _name_paper;

	list<IObserver*> _observers;

	void _Notify()
	{
		for (list<IObserver*>::iterator iter = _observers.begin(); iter != _observers.end(); ++iter)
		{
			(*iter)->handleEvent(*this);
		}
	}

public:

	void add(IObserver& ref)
	{
		_observers.push_back(&ref);
	}
	
	void remove(IObserver& ref)
	{
		_observers.remove(&ref);
	}


	const int get_type() const
	{
		return _flag;
	}

	
	const string& get_name() const
	{
		return _name_paper;
	}


	void new_paper(int flag, string name)
	{
		_name_paper = name;
		_flag = flag;
		_Notify();
	}
};





class PaperMan : public IObserver
{
public:
	virtual void handleEvent(const SupervisedString& ref)
	{
		if (ref.get_type() == 1) {
			cout << ref.get_name();
			cout << "-- get PaperMan" << endl;
		}
	}
};



class MagazineMan : public IObserver
{
public:
	virtual void handleEvent(const SupervisedString& ref)
	{
		if (ref.get_type() == 2) {
			cout << ref.get_name();
			cout << "-- get MagazineMan" << endl;
		}
	}
};


int main()
{

	SupervisedString str;
	// ������� �����������
	PaperMan pman;
	MagazineMan mman;


	str.add(pman);

	str.add(mman);

	str.new_paper(1, "����� ������� ������ 2000");
	str.new_paper(1, "������������� ������");
	str.new_paper(0, "������� �����");
	str.new_paper(2, "������");
	str.new_paper(1, "������");

	cout << endl;

	str.remove(mman);
	cout << endl;

	return 0;
}