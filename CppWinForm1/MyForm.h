#pragma once
#include <string>
#include <fstream>
#include "MyForm.h"
#include <stdlib.h>
#include "msclr\marshal_cppstd.h"
#include <fstream>
#include <vector>

int i = 0;
int N = 0;

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

Kvartira **prohodPoSkisku(Spisok *_r)
{
	::i = 0;
	::N = 0;

	Spisok *pr = _r;
	while (_r)
	{
		N++;
		_r = _r->next;
	}
	Kvartira *buf;
	Kvartira **pKarta = new Kvartira*[N];
	_r = pr;
	while (_r)
	{
		pKarta[i] = _r->Kv;
		_r = _r->next;
		i++;
	}
	_r = pr;
	return pKarta;
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
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(142, 60);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 3;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(142, 86);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 4;
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
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	Spisok *r = NULL;

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (r == NULL)
			r = create(dobavlenieKv(int::Parse(textBox4->Text),int::Parse(textBox3->Text),double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)));
		else
			add(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)), r);

	};
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
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
		for (i = 0; i<N; i++)
			safeInFile(prohodPoSkisku(r)[i], i+1);
		richTextBox1->Text = "";
		for each (std::string var in showAll())
		{
			richTextBox1->Text += marshal_as<System::String^>(var);
		}
	}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}