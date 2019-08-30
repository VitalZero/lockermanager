#include "CLockManager.h"
#include "Menu.h"

int main()
{
	CLockManager manager("basedatos.txt");
	SimpleMenu menu(manager);

	menu.ShowMenu();

	return 0;
}


