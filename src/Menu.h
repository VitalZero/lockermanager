/*
 * Menu.h
 *
 *  Created on: 14 feb 2019
 *      Author: jmichel
 */

#ifndef MENU_H_
#define MENU_H_
#include "CLockManager.h"

class SimpleMenu
{
public:
	SimpleMenu(CLockManager& manager_in);
public:
	void ShowMenu();
	void ChangeUser();
	void ShowLockers();
	void DeleteUser();
private:
	CLockManager& manager;
};


#endif /* MENU_H_ */
