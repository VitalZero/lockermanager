#include "Menu.h"
#include <iostream>
#include <iomanip>

SimpleMenu::SimpleMenu(CLockManager& manager_in)
	:
	manager(manager_in)
{
	if( !manager.LoadData() )
	{
		std::cerr << "Error!, database could not be loaded" << std::endl;
		error = true;
	}
}

void SimpleMenu::ShowMenu()
{
	bool running = true;
	int answer = 0;

	while(running && !error)
	{
		std::cout << "\n\t\tLocker Manager\n";
		std::cout << "\t\tMain Menu\n\n";
		std::cout << "\tType one of the following options:\n";

		std::cout << LIST_LOCKERS << "  List lockers\n";
		std::cout << CHANGE_USER << "  Change user\n";
		std::cout << DELETE_USER << "  Delete user\n";
		std::cout << ADD_LOCKER << "  Add locker\n";
		std::cout << FIND_USER << "  Find user\n";
		std::cout << EXIT_MENU << "  Exit" << std::endl;

		std::string stringAnswer;
		std::getline(std::cin, stringAnswer);

		if(std::cin.fail() )
		{
			std::cin.clear();
			std::cin.ignore();
			std::cerr << "Error!!! Datos introducidos son erroneos" << std::endl;
			error = true;
		}

		if(stringAnswer != "")
			answer = std::stoi(stringAnswer);

		switch( answer )
		{
		case LIST_LOCKERS:
			ShowLockers();
			break;
		case CHANGE_USER:
			ChangeUser();
			break;
		case DELETE_USER:
			DeleteUser();
			break;
		case ADD_LOCKER:
			AddUser();
			break;
		case FIND_USER:
			SearchUser();
		break;
		case EXIT_MENU:
			running = false;
		break;
		default:
			std::cout << "\t\nInvalid option\n" << std::endl;
			break;
		}
	}

	std::cout << "\t\n...See ya!" << std::endl;
}

void SimpleMenu::ChangeUser()
{
	std::cout << "\nWhich locker do you want to change?: ";

	std::string stringAnswer;
	std::getline(std::cin, stringAnswer);
	int answer = 0;

	if(stringAnswer != "")
		answer = std::stoi(stringAnswer);

	if( std::cin.fail() || answer == 0)
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Invalid data." << std::endl;
		error = true;
	}

	std::cout << "Type new user's name: ";
	std::string newUser;
	std::getline(std::cin,newUser);

	if(manager.ChangeUser(answer, manager.ToUpper(newUser)) )
	{
		std::cout << "changing user" << std::endl;
	}
	else
	{
		std::cerr << "\t\neERROR!!!\tCouldn't change user" << std::endl;
	}

	std::cout << "Press enter to continue..." << std::endl;

	//tmp will trap buffer contents to avoid sending it to the next menu
	std::getline(std::cin, stringAnswer);
}

void SimpleMenu::ShowLockers()
{
	// Show option to filter lockers
	std::cout << "\n\tType one of the following options\n";
	std::cout << (int)CLockers::Filter::All << " All\n";
	std::cout << (int)CLockers::Filter::Assigned <<" Assigned\n";
	std::cout << (int)CLockers::Filter::NotAssigned << " Not assigned\n";
	std::cout << (int)CLockers::Filter::Good << " Good (not damaged)\n";
	std::cout << (int)CLockers::Filter::Bad << " Bad (damaged)\n";
	std::cout << EXIT_MENU << " Go back\n";

	int answer = 0;

	std::string stringAnswer;
	std::getline(std::cin, stringAnswer);

	if(std::cin.fail() )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Invalid data." << std::endl;
		error = true;
	}

	if(stringAnswer != "")
		answer = std::stoi(stringAnswer);

	std::cout << "\n";

	if(answer == EXIT_MENU)
	{
		std::cout << "Returning to previous menu" << std::endl;
	}
	else if( (answer >= (int)CLockers::Filter::All)
			&& (answer <= (int)CLockers::Filter::Disabled) )
	{
		std::vector<CLockers> tmpLockers;

		if(manager.GetLockers(tmpLockers, (CLockers::Filter)answer))
		{
			for(unsigned int i = 0; i < tmpLockers.size(); ++i)
			{
				std::cout << "# " << std::setw(2) << tmpLockers.at(i).GetLockerNumber()
					<< std::setiosflags(std::ios_base::left) << " "
					<< std::setw(40) << tmpLockers.at(i).GetAssignedUser()
					<< std::setw(12) << tmpLockers.at(i).GetDate()
					<< std::setw(15) << (tmpLockers.at(i).Enabled() ? "Enabled" : "Disabled") << std::endl;
				std::cout << std::resetiosflags(std::ios_base::adjustfield);
			}

			std::cout << "\n" << tmpLockers.size() << " lockers found\n";
			std::cout << "Press enter to continue..." << std::endl;

			//tmp will trap buffer contents to avoid sending it to the next menu
			std::getline(std::cin, stringAnswer);
		}
	}
	else
	{
		std::cout << "Invalid option, try again...\n" << std::endl;
		//tmp will trap buffer contents to avoid sending it to the next menu
		std::getline(std::cin, stringAnswer);
	}
}

void SimpleMenu::DeleteUser()
{
	std::cout << "Deleting user" << std::endl;
	std::cout << "Press enter to continue..." << std::endl;

	std::cin.ignore();
}

void SimpleMenu::AddUser()
{
	std::cout << "Locker no: ";

	int lockerNum = 0;
	std::string stringAnswer;
	std::getline(std::cin, stringAnswer);

	if(std::cin.fail() )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Invalid data" << std::endl;
	}

	if(stringAnswer != "")
		lockerNum = std::stoi(stringAnswer);

	std::cout << "Name: ";
	std::string newUser;
	std::getline(std::cin, newUser);

	// TODO: Check for string length, date should not be more than 8 characters (not including \0)
	std::cout << "Date (dd/mm/yyyy): ";
	std::string newDate;
	std::getline(std::cin, newDate);

	bool result = manager.AddLocker(CLockers(manager.ToUpper(newUser), "", newDate, lockerNum, 1, 1));

	if(!result)
		std::cerr << "Couldn't save database" << std::endl;
}

void SimpleMenu::SearchUser()
{
	std::cout << "\nType user's name: ";
	std::string user;
	std::getline(std::cin, user);

	if(std::cin.fail() )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Invalid data." << std::endl;
	}

	std::vector<CLockers> tmpLockers;
	if(manager.SearchUser(user, tmpLockers))
	{
		std::cout << "\n" << tmpLockers.size() << " lockers were found, listing..." << "\n";

		for(unsigned int i = 0; i < tmpLockers.size(); ++i)
		{
			std::cout << "# " << std::setw(2) << tmpLockers.at(i).GetLockerNumber()
				<< std::setiosflags(std::ios_base::left) << " "
				<< std::setw(40) << tmpLockers.at(i).GetAssignedUser()
				<< std::setw(12) << tmpLockers.at(i).GetDate()
				<< std::setw(15) << (tmpLockers.at(i).Enabled() ? "Enabled" : "Disabled") << "\n";
			std::cout << std::resetiosflags(std::ios_base::adjustfield);
		}

		std::cout << std::endl;
	}
	else
	{
		std::cout << "\n\tNo results :( ...\n" << std::endl;
	}
	

}
