#ifndef MENU_H_
#define MENU_H_
/*
 * Menu.h
 * Just a quick, cheap and dirty menu class to demonstrate the use of CLockManager class
 */
#include "CLockManager.h"

class SimpleMenu
{
public:
	SimpleMenu(CLockManager& manager_in);
	SimpleMenu() = delete;
	SimpleMenu(const SimpleMenu&) = delete;
	void operator=(const SimpleMenu&) = delete;

public:
	void ShowMenu();
	void ChangeUser();
	void ShowLockers();
	void DeleteUser();
	void AddUser();
	void SearchUser();
private:
	CLockManager& manager;
	bool error = false;
	enum Options {
		LIST_LOCKERS = 1,
		CHANGE_USER,
		DELETE_USER,
		ADD_LOCKER,
		FIND_USER,
		EXIT_MENU = -1
	};
};


#endif /* MENU_H_ */
