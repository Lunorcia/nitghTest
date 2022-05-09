#include "MyForm.h"
using namespace ChineseChess;
[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::Run(gcnew(MyForm));

	return 0;
}