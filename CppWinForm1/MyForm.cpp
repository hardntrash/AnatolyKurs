#include "MyForm.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;

struct KARTA // Хата
{
	String ^nomer();
	String ^etag();
	String ^procent();
	String ^adres();
};


struct STR
{
	KARTA *Karta;
	STR *next;
};

STR * create(KARTA * Karta) //начальное формирование списка
{
	STR *r = new STR;
	r->Karta = Karta;
	r->next = NULL;
	return r;
}

void add(KARTA *Karta, STR* r) //добавление нового элемента списка
{
	while (r->next)
		r = r->next;
	r->next = new STR;
	r->next->Karta = Karta;
	r->next->next = NULL;
}

void vyvodKARTA(KARTA *Karta) //вывод на экран
{
	/*
	cout << "Количество комнат: " << Karta->nomer << endl;
	cout << "Этаж: " << Karta->etag << endl;
	cout << "Площадь: " << Karta->procent << endl;
	cout << "Адрес:" << Karta->adres << endl;
	cout << endl;
	*/
}

KARTA *dobavlenieKarta(String ^Etag, String ^Procent, String ^Addres, String ^Nomer)
{
	KARTA *Karta = new KARTA;

	/*Karta->etag = Etag;
	Karta->procent = Procent;
	Karta->adres = Addres;
	Karta->nomer = Nomer;*/
	std::ofstream file("test.txt");
	/*file << *Karta->etag;
	file << *Karta->procent;
	file << *Karta->adres;
	file << *Karta->nomer;*/
	file << "huy xyй";
	file.close();
	
	return Karta;
}

[STAThread]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CppWinForm1::MyForm form;
	Application::Run(%form);
	return 0;
}
