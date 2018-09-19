// proxy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;



/**
* —убъект
*/
class Handler
{
public:
	virtual void get_big_image() = 0;
	virtual void get_big_video() = 0;
	virtual void get_big_file() = 0;
};


/* ќригинальный класс*/
class MyInternetHandler : public Handler
{
	int id;
	int superBigData;
public:
	MyInternetHandler(int i)
	{
		id = i;
		superBigData = 1; //представим, что это много :)
		cout << " Was created object with id : " << id << '\n';
	}
	~MyInternetHandler()
	{
		cout << " Was deleted object wiht id : " << id << '\n';
	}
	void get_big_image()
	{
		superBigData++; // какое-то действие с данными (можно что угодно сюда добавить)
		cout << "   some type of big image: " << id << '\n';
	}
	void get_big_video()
	{
		superBigData--;  // какое-то действие с данными 
		cout << "   some type of big video: " << id << '\n';
	}
	void get_big_file()
	{
		superBigData = 0; // какое-то действие с данными 
		cout << "   some type of big file: " << id << '\n';
	}
};


class MyProxyObject : public Handler
{
	// объ€вили класс 
	MyInternetHandler *m_the_real_thing;
	int id;
	static int s_next;
public:
	MyProxyObject()
	{
		id = s_next++;
		// инициализировали, но как 0
		m_the_real_thing = 0;
	}
	~MyProxyObject()
	{
		delete m_the_real_thing;
	}
	void get_big_image()
	{
		// только вот тут создали полноценный объект
		if (!m_the_real_thing)
			m_the_real_thing = new MyInternetHandler(id);
		// и выполнили какую-то его работу
		m_the_real_thing->get_big_image();
	}

	void get_big_video()
	{
		if (!m_the_real_thing)
			m_the_real_thing = new MyInternetHandler(id);
		m_the_real_thing->get_big_video();
	}

	void get_big_file()
	{
		if (!m_the_real_thing)
			m_the_real_thing = new MyInternetHandler(id);
		m_the_real_thing->get_big_file();
	}
};
int MyProxyObject::s_next = 1;

int main()
{
	MyProxyObject ob0;
	ob0.get_big_image();
	ob0.get_big_video();
	ob0.get_big_file();

	MyProxyObject ob1;
	ob1.get_big_video();

}
