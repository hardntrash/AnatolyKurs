#include "MyForm.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

using namespace System;
using namespace System::Windows::Forms;

struct base_condominium {
	//������� ������
	int n_room;
	int floor;
	int area;
	char address[40];
	//������ �� ��������� �������
	base_condominium *next;
};

typedef base_condominium *p_node;

// ������� ����� ������� ������
p_node create_node() {

	p_node new_node = (p_node)malloc(sizeof(base_condominium)); //��������� �� ����� ����
	printf("\nWrite address: ");
	scanf("%s", &new_node->address);
	printf("\nWrite area: ");
	scanf("%d", &new_node->area);
	printf("\nWrite floor: ");
	scanf("%d", &new_node->floor);
	printf("\nWrite number room: ");
	scanf("%d", &new_node->n_room);
	new_node->next = NULL; // ���������� ���� ���
	return (new_node);
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
