/*
 * main.cpp
 *
 *  Created on: 9 feb 2019
 *      Author: jmichel
 */
#include <iostream>
#include <string>
#include "CLockManager.h"
#include "Menu.h"

int main()
{
	CLockManager doc("basedatos.txt");
	SimpleMenu menu(doc);

	menu.ShowMenu();

	//std::vector<CLockers> v= doc.GetLockers(CLockManager::Malos);

	//doc.ShowLockers();
	//doc.AddLocker(CLockers("Jonathan Michel", "Sin asignar", "23/01/2018", 1, CLockers::Bueno));

	//doc.ChangeUser(10, "benito juarez anguiano");
	//doc.DeleteUser(39);
	//doc.SaveChanges();
	//doc.ShowLockers(CLockManager::Malos);

	//std::cout << "Locker " << v.at(0).GetNumber() << " = " << v.at(0).GetAssigned();
	//std::cout << " cantidad: " << v.size() << std::endl;

	return 0;
}


