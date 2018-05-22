#pragma once
#include <string>
#include <fstream>
#include "MyForm.h"
#include <stdlib.h>
#include "msclr\marshal_cppstd.h"
#include <fstream>
#include <vector>
#include <windows.h> 

int i;
int N;

struct Kvartira
{
	int komnat;
	int etag;
	double ploshad;
	std::string addres;
};

struct Spisok
{
	Kvartira *Kv;
	Spisok *next;
};

Spisok *r = NULL;

Spisok *create(Kvartira *Kv)
{
	Spisok *r = new Spisok;
	r->Kv = Kv;
	r->next = NULL;
	return r;
};

void add(Kvartira *Kv, Spisok *r) //добавление нового элемента списка
{
	while (r->next)
		r = r->next;
	r->next = new Spisok;
	r->next->Kv = Kv;
	r->next->next = NULL;
};

Kvartira *dobavlenieKv(int _komnat, int _etag, double _ploshad, std::string _addres)
{
	Kvartira *Karta = new Kvartira;
	Karta->komnat = _komnat;
	Karta->etag = _etag;
	Karta->ploshad = _ploshad;
	Karta->addres = _addres;
	return Karta;
}

void safeInFile(Kvartira *Karta, int _nomer)
{
	std::ofstream f("test.txt", std::ios::app);
	f << "Заявка №" << _nomer << '\n';
	f << Karta->addres << '\n';
	f << Karta->etag << '\n';
	f << Karta->ploshad << '\n';
	f << Karta->komnat << '\n';
	f << "/" << '\n';
	f.close();
}

Kvartira **prohodPoSkisku()
{
	::i = 0;
	::N = 0;

	Spisok *pr = ::r;
	while (::r)
	{
		N++;
		::r = ::r->next;
	}
	Kvartira *buf;
	Kvartira **pKv = new Kvartira*[N];
	::r = pr;
	while (::r)
	{
		pKv[i] = ::r->Kv;
		::r = ::r->next;
		i++;
	}
	::r = pr;
	return pKv;
}

std::vector<std::string> showAll()
{
	std::string a;
	std::vector<std::string> listKv;
	std::ifstream f("test.txt");
	while (getline(f,a))
	{
		if (a != "/")
			listKv.insert(listKv.end(), a);
		listKv.insert(listKv.end(), "\n");
	}
	f.close();
	return listKv;
}

std::vector<std::string> loadFromFile()
{
	std::string a;
	std::vector<std::string> listKv;
	std::ifstream f("test.txt");
	while (getline(f, a))
	{
		if (a != "/")
			listKv.insert(listKv.end(), a);
		else
		{
			if (r == NULL)
				r = create(dobavlenieKv(atoi(listKv[4].c_str()), atoi(listKv[3].c_str()), atof(listKv[2].c_str()), listKv[1].c_str()));			
			else
				add(dobavlenieKv(atoi(listKv[4].c_str()), atoi(listKv[3].c_str()), atof(listKv[2].c_str()), listKv[1].c_str()), r);
			listKv.clear();
		}
	}
	f.close();
	return listKv;
}

namespace CppWinForm1 {

	using namespace std;
	using namespace msclr::interop;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 116);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(115, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Добавить заявку";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(142, 8);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(142, 34);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 2;
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox2_KeyPress);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(142, 60);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 3;
			this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox3_KeyPress);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(142, 86);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 4;
			this->textBox4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox4_KeyPress);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(98, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(38, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Адрес";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(82, 37);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(54, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Площадь";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(103, 63);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(33, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Этаж";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(30, 89);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(106, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Количество комнат";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(142, 116);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 23);
			this->button2->TabIndex = 9;
			this->button2->Text = L"Показать все";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(12, 145);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(230, 23);
			this->button3->TabIndex = 10;
			this->button3->Text = L"Поиск подходящего варианта";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(12, 174);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(230, 96);
			this->richTextBox1->TabIndex = 11;
			this->richTextBox1->Text = L"";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 277);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"Картотека";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	//Spisok *r = NULL;

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (textBox1->Text != "" &&textBox2->Text != "" && textBox3->Text != "" && textBox4->Text != "")
		{
			if (r == NULL)
			{
				r = create(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)));
				safeInFile(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)), 1);
				MessageBox::Show("Заявка успешно добавлена");
			}
			else {
				Kvartira **pKarta = prohodPoSkisku();
				bool flag = false;

				for (::i = 0; ::i < ::N; ::i++)
				{
					if (pKarta[::i]->addres == marshal_as<std::string>(textBox1->Text))
					{
						flag = true;
						MessageBox::Show("Такая заявка уже есть");
						break;
					}
				}

				if (!flag)
				{
					add(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)), r);
					safeInFile(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)), ::i + 1);
					MessageBox::Show("Заявка успешно добавлена");
				}
			}
		}
		else
			MessageBox::Show("Не все поля заполнены");
	};
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		/*int i = 0;
		int N = 0;

		Spisok *pr = r;
		while (r)
		{
			N++;
			r = r->next;
		}
		Kvartira *buf;
		Kvartira **pKarta = new Kvartira*[N];
		r = pr;
		while (r)
		{
			pKarta[i] = r->Kv;
			r = r->next;
			i++;
		}
		r = pr;
		*/
		/*Kvartira **pKarta = prohodPoSkisku();
		for (::i = 0; ::i<::N; i++)
			safeInFile(pKarta[::i], ::i+1);*/

		richTextBox1->Text = "";
		for each (std::string var in showAll())
		{
			richTextBox1->Text += marshal_as<System::String^>(var);
		}
	}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	if (textBox2->Text != "" && textBox3->Text != "" && textBox4->Text != "")
	{
		bool flag = false;
		Kvartira **pKarta = prohodPoSkisku();
		for (::i = 0; ::i < ::N; ::i++)
		{
			if (pKarta[::i]->etag == int::Parse(textBox3->Text) && pKarta[::i]->komnat == int::Parse(textBox4->Text))
			{
				Kvartira *var = pKarta[::i];
				std::string s("Найден вариант для обмена. Адрес: ");
				s += pKarta[::i]->addres;
				s += "\nПринять обмен?";
				if (MessageBox::Show(marshal_as<System::String^>(s), "Результат поиска", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
				{
					flag = true;
					::r = NULL;
					System::IO::File::Delete("test.txt");
					for (::i = 0; ::i <= ::N - 1; ::i++)
					{
						if (pKarta[::i] != var)
						{
							if (::r == NULL)
							{
								r = create(pKarta[::i]);
								safeInFile(pKarta[::i], ::i + 1);
							}
							else
							{
								add(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)), r);
								safeInFile(pKarta[::i], ::i + 1);
							}
						}
					}
					break;
				}
				
				//loadFromFile();
				//break;
				
			}
		}
		if (!flag)
			MessageBox::Show("Нет подходящих вариантов.");
	}
	else
		MessageBox::Show("Не все поля заполнены.");
}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	for each (std::string var in showAll())
	{
		richTextBox1->Text += marshal_as<System::String^>(var);
	}
	loadFromFile();
}
private: System::Void textBox3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if ((e->KeyChar < 48 || e->KeyChar > 57) && e->KeyChar != '\b')
		e->Handled = true;
}
private: System::Void textBox4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if ((e->KeyChar < 48 || e->KeyChar > 57) && e->KeyChar != '\b')
		e->Handled = true;
}
private: System::Void textBox2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == '.' || e->KeyChar == ',')
	{
		e->KeyChar = ',';
		if (textBox2->Text->IndexOf(',') != -1)
		{
			e->Handled = true;
			//return;
		}
	}

	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && e->KeyChar != ',')
	{
		e->Handled = true;
		//return;
	}
}
};
}