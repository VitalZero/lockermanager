#ifndef MENU_H_
#define MENU_H_
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
	enum class Options {
		List = 1,
		Change,
		Delete,
		Add,
		Find,
		Exit
	};
};


#endif /* MENU_H_ */
