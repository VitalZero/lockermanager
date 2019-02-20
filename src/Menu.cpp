/*
 * Menu.cpp
 *
 *  Created on: 14 feb 2019
 *      Author: jmichel
 */
#include "Menu.h"
#include <iostream>

SimpleMenu::SimpleMenu(CLockManager& manager_in)
	:
	manager(manager_in)
{

}

void SimpleMenu::ShowMenu()
{
	int answer = 0;
	using namespace std;

	while(true)
	{
		cout << "\tMenu principal" << endl;
		cout << "\tTeclea una de las siguientes opciones:" << endl;
		cout << "1 Listar lockers" << endl;
		cout << "2 Cambiar usuario" << endl;
		cout << "3 Borrar usuario" << endl;
		cout << "-1 Salir" << endl;
		cin >> answer;
		cin.ignore();

		if(answer == 1)
			ShowLockers();
		else if(answer == 2)
			ChangeUser();
		else if(answer== 3)
			DeleteUser();
		else if (answer < 0)
			break;
		else
			cout << "\t\nOpcion incorrecta" << endl << endl;
	}

	cout << "\t\n...Hasta pronto!" << endl;
}

void SimpleMenu::ChangeUser()
{
	int answer = 0;
	std::string usuarioNuevo;

	std::cout << "\nCual locker quieres cambiar?: ";
	std::cin >> answer;
	std::cin.ignore();
	std::cout << "Escribe el nombre de nuevo usuario: ";
	std::getline(std::cin,usuarioNuevo);
	if(manager.ChangeUser(answer, usuarioNuevo.c_str()) == true)
		manager.SaveChanges();
	else
		std::cout << "\t\nNo se pudo cambiar el usuario" << std::endl;

	std::cout << "Cambiando usuario" << std::endl;
	std::cout << "Presione Enter para continuar..." << std::endl;
	//std::cin.get();
	std::cin.ignore();
}

void SimpleMenu::ShowLockers()
{
	std::vector<CLockers> v= manager.GetLockers(CLockManager::Buenos);

	std::cout << "Listando lockers:" << std::endl;
	for(CLockers l : v)
	{
		std::cout << "L" << l.GetNumber() << " -> " << l.GetAssigned() << std::endl;
	}

	std::cout << "Presione Enter para continuar..." << std::endl;
	//std::cin.get();
	std::cin.ignore();
}

void SimpleMenu::DeleteUser()
{
	std::cout << "Borrando usuario" << std::endl;
	std::cout << "Presione Enter para continuar..." << std::endl;
	//std::cin.get();
	std::cin.ignore();
}



