#pragma once
#include <string> //подключенные файлы
#include <fstream>
#include "MyForm.h"
#include <stdlib.h>
#include "msclr\marshal_cppstd.h"
#include <fstream>
#include <vector>
#include <windows.h> 

int i; // глобальная переменная для работы с циклами
int N; // глобалная переменная для работы с циклами (нужна для запоминаяния количества элементов в списке)

struct Kvartira //структура квартиры
{
	int komnat; //поле для хранения количества комнат
	int etag; //поле для хранения номера этажа
	double ploshad; //поле для хранения значения площади
	std::string addres; //поле для хранения адреса кваритры
};
 
struct Spisok //структура списка с квартирами
{
	Kvartira *Kv; //поле для хранения квартиры
	Spisok *next; //поле для хранения ссылки следующей квартиры в списке
};

Spisok *r = NULL; //список с квартирами

Spisok *create(Kvartira *Kv) //функция для создания списка с квартирами. аргументом *Kv является квартира, которая вноситься первой
{
	Spisok *r = new Spisok; //создание локальной переменной типа Spisok
	r->Kv = Kv; //присваиваем квартире локального списка *Kv
	r->next = NULL; //говорим, что следующей квартиры нет
	return r; //возвращем локальный список 
};

void add(Kvartira *Kv, Spisok *r) //функция добавление нового элемента списка. аргумент *Kv - квартира, *r - список со всеми квартирами
{
	while (r->next)  //цикл, чтобы
		r = r->next; //перейти в конец списка с квартирами
	r->next = new Spisok; //последнему элементу списка с квартирами, указываем что создаем новый элемент списка, с ссылкой на него
	r->next->Kv = Kv; //присваиваем полю с квартирой нового элемента списка значение *Kv
	r->next->next = NULL; ////говорим, что следующей квартиры нет
};

Kvartira *dobavlenieKv(int _komnat, int _etag, double _ploshad, std::string _addres) //функция создания новой квартиры.в аргументах _komnat - целое число с количеством комнат, _etag - целое число с номером этажа, _ploshad - вещественное число с ццислом площади, _addres - строка с адресом
{
	Kvartira *Karta = new Kvartira; //создаем локальную переменную квартиры
	Karta->komnat = _komnat; //присваиваем локальной переменной квартиры komnat количество комнат 
	Karta->etag = _etag; //присваиваем локальной переменной квартиры etag номер этажа
	Karta->ploshad = _ploshad; //присваиваем локальной переменной квартиры ploshad площадь
	Karta->addres = _addres; //присваиваем локальной переменной квартиры addres адрес
	return Karta; //в итоге возвращаем квартиру
}

void safeInFile(Kvartira *Karta, int _nomer) //функция сохранения в текстовый файл. в аргементах квартира для записи и номер записи
{
	std::ofstream f("test.txt", std::ios::app); //создаем и открываем переменную f, указываем название файла и то, что его нужно дозаписать
	f << "Заявка №" << _nomer << '\n'; //Записываем в файл номер Заявки
	f << Karta->addres << '\n'; //Записываем в файл адрес
	f << Karta->etag << '\n'; //Записываем в файл этаж
	f << Karta->ploshad << '\n'; //Записываем в файл площадь
	f << Karta->komnat << '\n'; //Записываем в файл количество комнат
	f << "/" << '\n'; //записываем в файл символ-разделитель
	f.close(); //закрываем файл
}

Kvartira **prohodPoSkisku() //функция для прохода по списку с квартирами
{
	::i = 0; //обнуляем глобальную переменную
	::N = 0; //обнуляем глобальную переменную

	Spisok *pr = ::r; //создаем локальную переменную с типом Spisok и присваиваем ей общий список с квартирами
	while (::r) //цикл в котором считается количество записей в списке
	{
		N++; //увеличиваем глобальную переменную N на 1
		::r = ::r->next; //передвигаем список дальше
	}
	Kvartira *buf;
	Kvartira **pKv = new Kvartira*[N]; //создаем массив с квартирами
	::r = pr; //возвращаем общий список с квартирами в начальное состояние
	while (::r) //цикл в котором заполняем массив с квартирами
	{
		pKv[i] = ::r->Kv; 
		::r = ::r->next;
		i++;
	}
	::r = pr; //возвращаем общий список с квартирами в начальное состояние
	return pKv; //возвращаем массив с квартирами
}

std::vector<std::string> showAll() //функция для демонстрации всех квартир из файла
{
	std::string a; //локальная переменная, в которой будут хранится значения строк из файла
	std::vector<std::string> listKv; //создаем массив со списком строк
	std::ifstream f("test.txt"); //открываем файл
	while (getline(f,a)) //пока в файле есть строки, выполняем действия
	{
		if (a != "/") //если в строке нет разделительного символа
			listKv.insert(listKv.end(), a); //добавляем в конец массива строку
		else  //иначе
			listKv.insert(listKv.end(), "\n"); //добавляем в конец массива знак переноса на новую строку
	}
	f.close(); //закрываем файл
	return listKv; //возвращаем массив со строками
}

std::vector<std::string> loadFromFile() //функция для формирования общего списка с квартирами из файла
{
	std::string a; //локальная переменная, в которой будут хранится значения строк из файла
	std::vector<std::string> listKv; //создаем массив со списком строк с инфо-ией о квартире
	std::ifstream f("test.txt"); //Открываем файл
	while (getline(f, a)) //пока не конец файла
	{
		if (a != "/")						//если разделительный символ
			listKv.insert(listKv.end(), a); //добавляем его в конец списка
		else //иначе
		{
			if (r == NULL) //если общий список с квартирами пуст
				r = create(dobavlenieKv(atoi(listKv[4].c_str()), atoi(listKv[3].c_str()), atof(listKv[2].c_str()), listKv[1].c_str()));	//создаем список
			else //если не пустой
				add(dobavlenieKv(atoi(listKv[4].c_str()), atoi(listKv[3].c_str()), atof(listKv[2].c_str()), listKv[1].c_str()), r); //добавляем новую квартиру
			listKv.clear(); //очищаем массив
		}
	}
	f.close(); // закрываем файл
	return listKv; //возвращаем массив
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
			this->richTextBox1->Size = System::Drawing::Size(230, 145);
			this->richTextBox1->TabIndex = 11;
			this->richTextBox1->Text = L"";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(258, 331);
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

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) //событие, вызывающееся при нажатие на кнопку "добавить заявку"
	{
		if (textBox1->Text != "" &&textBox2->Text != "" && textBox3->Text != "" && textBox4->Text != "") //проверка на то, что все поля заполнены
		{
			if (r == NULL) //если общий список пустой
			{
				r = create(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text))); //создаем его
				safeInFile(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)), 1); //добавляем первую квартиру
				MessageBox::Show("Заявка успешно добавлена"); //уведомление об успешном добавлении
			}
			else //если не пустой
			{
				Kvartira **pKarta = prohodPoSkisku(); //получаем массив с уже добавленными квартирами
				bool flag = false; //логическа переменая, чтобы знать, есть ли данная квартира в списке

				for (::i = 0; ::i < ::N; ::i++) //цикл для проверки введых данных на присутствие квартиры в списке
				{
					if (pKarta[::i]->addres == marshal_as<std::string>(textBox1->Text)) //если адрес введнной квариры уже есть в списке
					{
						flag = true; //то говорим, что такая квартира уже есть
						MessageBox::Show("Такая заявка уже есть"); //уведомляем об этом пользователя
						break; //останавливаем цикл
					}
				}

				if (!flag) //если такой квартиры не найдено
				{
					add(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)), r); //то добавляем ее 
					safeInFile(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)), ::i + 1); //и записываем в файл
					MessageBox::Show("Заявка успешно добавлена"); //уведомляем об этом пользователя
				}
			}
		}
		else //если не все поля заполнены
			MessageBox::Show("Не все поля заполнены"); //уведомляем об этом пользователя
	};
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) //событие вызываемое нажатием на кнопку  "показать все"
	{
		richTextBox1->Text = ""; //очищаем область для показа квартир
		int k = 0; //локальная переменная, с ключом
		for each (std::string var in showAll()) //пока есть строки в массиве
		{
			switch (k)
			{
			case 0: //если строка с заявкой
				richTextBox1->Text += marshal_as<System::String^>(var + '\n'); //выводим ее
				k++;
				break;
			case 1: //если строка с Адресом
				richTextBox1->Text += marshal_as<System::String^>("Адрес: " + var + '\n');
				k++;
				break;
			case 2: //если строка с Этажом
				richTextBox1->Text += marshal_as<System::String^>("Этаж: " + var + '\n');
				k++;
				break;
			case 3: //если строка с Площадью
				richTextBox1->Text += marshal_as<System::String^>("Площадь: " + var + '\n');
				k++;
				break;
			case 4: //если строка с Количеством комнат
				richTextBox1->Text += marshal_as<System::String^>("Количество комнат: " + var + '\n');
				k++;
				break;
			case 5: //если строка с символом переноса на новую строку
				richTextBox1->Text += marshal_as<System::String^>(var);
				k = 0;
				break;
			}
		}
		loadFromFile(); //загружаем список с квартирами из файла
	}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) //событие вызываемое нажатием на кнопку  "Найти подходящий вариант"
{ 
	if (textBox2->Text != "" && textBox3->Text != "" && textBox4->Text != "") //если поля не пустые
	{
		bool flag = false; //логическая переменная, чтобы знать, есть ли совпадения
		Kvartira **pKarta = prohodPoSkisku(); //получем массив с квартирами
		for (::i = 0; ::i < ::N; ::i++) //цикл для прохода по массиву
		{
			if (pKarta[::i]->etag == int::Parse(textBox3->Text) && pKarta[::i]->komnat == int::Parse(textBox4->Text)) //если есть соответствия
			{
				Kvartira *var = pKarta[::i]; //запоминаем вариант, чтобы удалить из списка
				std::string s("Найден вариант для обмена. Адрес: ");
				s += pKarta[::i]->addres;
				s += "\nПринять обмен?";
				if (MessageBox::Show(marshal_as<System::String^>(s), "Результат поиска", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) //окно с сообщением, если пользователь готов к обмену
				{
					flag = true; //говорим, что нашли подходящий вариант
					::r = NULL; //обнуляем список
					System::IO::File::Delete("test.txt"); //удаляем файл
					for (::i = 0; ::i < ::N-1; ::i++) //цикл для составления списка с квартирами без той, которую нашли
					{
						if (pKarta[::i] != var) //проверяем, не найденая ли это квартира
						{
							if (::r == NULL) //если список пуст
							{
								r = create(pKarta[::i]); //создаем его
								safeInFile(pKarta[::i], ::i + 1); //записываем в файл
							}
							else //иначе
							{
								add(dobavlenieKv(int::Parse(textBox4->Text), int::Parse(textBox3->Text), double::Parse(textBox2->Text), marshal_as<std::string>(textBox1->Text)), r); //добавляем в конец
								safeInFile(pKarta[::i], ::i + 1); //записываем в файл
							}
						}
					}
					break; //останавливаем цикл
				}			
			}
		}
		if (!flag) //если не нашли квартиру
			MessageBox::Show("Нет подходящих вариантов."); //уведомляем об этом пользователя
	}
	else //если не все поля заполнены
		MessageBox::Show("Не все поля заполнены.");  //уведомляем об этом пользователя
}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) //событие, которое вызывается при загрузке программы
{
	int k = 0; //локальная переменная, с ключом
	for each (std::string var in showAll())
	{
		switch (k)
		{
		case 0: //если строка с заявкой
			richTextBox1->Text += marshal_as<System::String^>(var + '\n');
			k++;
			break;
		case 1: //если строка с Адресом
			richTextBox1->Text += marshal_as<System::String^>("Адрес: " + var + '\n');
			k++;
			break;
		case 2: //если строка с Этажом
			richTextBox1->Text += marshal_as<System::String^>("Этаж: " + var + '\n');
			k++;
			break;
		case 3: //если строка с Площадь
			richTextBox1->Text += marshal_as<System::String^>("Площадь: " + var + '\n');
			k++;
			break;
		case 4: //если строка с Количеством комнат
			richTextBox1->Text += marshal_as<System::String^>("Количество комнат: " + var + '\n');
			k++;
			break;
		case 5:  //если строка с символом переноса на новую строку
			richTextBox1->Text += marshal_as<System::String^>(var);
			k = 0;
			break;
		}
	}
	loadFromFile(); //создаем общий список с квартирами
}
private: System::Void textBox3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) //событие вызывающееся при нажатии клавиши в поле с Этажом
{
	if ((e->KeyChar < 48 || e->KeyChar > 57) && e->KeyChar != '\b') //если цифра
		e->Handled = true; //добавляется символ
}
private: System::Void textBox4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) //событие вызывающееся при нажатии клавиши в поле с Количеством комнат
{
	if ((e->KeyChar < 48 || e->KeyChar > 57) && e->KeyChar != '\b') //если цифра
		e->Handled = true; //добавляется символ
}
private: System::Void textBox2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) //событие вызывающееся при нажатии клавиши в поле с Площадью
{
	if (e->KeyChar == '.' || e->KeyChar == ',') //если точка или запятая
	{
		e->KeyChar = ','; //заменяем на зяпятую
		if (textBox2->Text->IndexOf(',') != -1) //если первая запятая в поле
		{
			e->Handled = true; //добавляется символ
		}
	}

	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && e->KeyChar != ',') //если не буква, не запятая, не служебный символ
	{
		e->Handled = true;//добавляется символ
	}
}

};
}