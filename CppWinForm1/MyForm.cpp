#include "MyForm.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;

struct KARTA // ����
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

STR * create(KARTA * Karta) //��������� ������������ ������
{
	STR *r = new STR;
	r->Karta = Karta;
	r->next = NULL;
	return r;
}

void add(KARTA *Karta, STR* r) //���������� ������ �������� ������
{
	while (r->next)
		r = r->next;
	r->next = new STR;
	r->next->Karta = Karta;
	r->next->next = NULL;
}

void vyvodKARTA(KARTA *Karta) //����� �� �����
{
	/*
	cout << "���������� ������: " << Karta->nomer << endl;
	cout << "����: " << Karta->etag << endl;
	cout << "�������: " << Karta->procent << endl;
	cout << "�����:" << Karta->adres << endl;
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
	file << "huy xy�";
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
