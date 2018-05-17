#include "MyForm.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CppWinForm1::MyForm form;
	Application::Run(%form);
	return 0;
}
