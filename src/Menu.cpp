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
		std::cout << (int)Options::List << "  List lockers\n";
		std::cout << (int)Options::Change << "  Change user\n";
		std::cout << (int)Options::Delete << "  Delete user\n";
		std::cout << (int)Options::Add << "  Add locker\n";
		std::cout << (int)Options::Find << "  Find user\n";
		std::cout << (int)Options::Exit << "  Exit" << std::endl;

		std::string tmp;
		std::getline(std::cin, tmp);

		if(std::cin.fail() )
		{
			std::cin.clear();
			std::cin.ignore();
			std::cerr << "Error!!! Datos introducidos son erroneos" << std::endl;
			error = true;
		}

		if(tmp != "")
			answer = std::stoi(tmp);

		switch( (Options)answer )
		{
		case Options::List:
			ShowLockers();
			break;
		case Options::Change:
			ChangeUser();
			break;
		case Options::Delete:
			DeleteUser();
			break;
		case Options::Add:
			AddUser();
			break;
		case Options::Exit:
			running = false;
		break;
		case Options::Find:
			SearchUser();
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

	std::string tmp;
	std::getline(std::cin, tmp);
	int answer = 0;

	if(tmp != "")
		answer = std::stoi(tmp);

	if( std::cin.fail() || answer == 0)
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Invalid data." << std::endl;
		error = true;
	}

	std::cout << "Type new user's name: ";
	std::string usuarioNuevo;
	std::getline(std::cin,usuarioNuevo);

	if(manager.ChangeUser(answer, usuarioNuevo) )
	{
		//manager.SaveChanges();
		std::cout << "changing user" << std::endl;
	}
	else
	{
		std::cerr << "\t\neERROR!!!\tCouldn't change user" << std::endl;
	}

	std::cout << "Press enter to continue..." << std::endl;

	std::cin.ignore();
}

void SimpleMenu::ShowLockers()
{
	// Show option to filter lockers
	std::cout << "\n\tType one of the following options\n";
	std::cout << "0 All\n";
	std::cout << "1 Assigned\n";
	std::cout << "2 Not assigned\n";
	std::cout << "3 Good (not damaged)\n";
	std::cout << "4 Bad (damaged)\n";
	std::cout << "-1 Go back\n";

	int answer;

	std::string tmp;
	std::getline(std::cin, tmp);

	if(std::cin.fail() )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Invalid data." << std::endl;
		error = true;
	}

	if(tmp != "")
		answer = std::stoi(tmp);

	std::cout << "\n";

	// TODO: Change to a single if, for exit, for the rest use the function (function will filter correct input)
	switch((CLockers::Filter)answer)
	{
		case CLockers::Filter::All:
		case CLockers::Filter::Assigned:
		case CLockers::Filter::NotAssigned:
		case CLockers::Filter::Good:
		case CLockers::Filter::Bad:
		{
			std::vector<CLockers> tmpLockers;
			
			if(manager.GetLockers(tmpLockers, (CLockers::Filter)answer))
			{
				for(unsigned int i = 0; i < tmpLockers.size(); ++i)
				{
					std::cout << "# " << std::setw(2) << tmpLockers.at(i).GetLockerNumber() //<< "\t"
						<< std::setiosflags(std::ios_base::left) << " "
						<< std::setw(40) << tmpLockers.at(i).GetAssignedUser() //<< "\t"
						<< std::setw(12) << tmpLockers.at(i).GetDate() //<< "\t"
						//<< (l.HasKey() ? "Si" : "No") << "\t"
						//<< l.GetStatusDescription() << "\t"
						<< std::setw(15) << (tmpLockers.at(i).Enabled() ? "Enabled" : "Disabled") << std::endl;
					std::cout << std::resetiosflags(std::ios_base::adjustfield);
						//<< l.GetPreviousUser() << std::endl;
				}
			}
			std::cout << "\n" << tmpLockers.size() << " lockers found\n";
			std::cout << "Press enter to continue..." << std::endl;
			std::cin.ignore();
		}
		break;
		case CLockers::Filter::Exit:
			std::cout << "Returning to previous menu" << std::endl;
		break;
		default:
			std::cout << "Invalid option, try again...\n" << std::endl;
			std::cin.ignore();
		break;
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
	int numero;
	std::cin >> numero;
	if(std::cin.fail() )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Invalid data" << std::endl;
	}

	std::cin.ignore();

	std::cout << "Name: ";
	std::string nombre;
	std::getline(std::cin, nombre);

	// TODO: Check for string lenght, date should not be more then 8 characters (not including \0)
	std::cout << "Date (dd/mm/yyy): ";
	std::string fecha;
	std::getline(std::cin, fecha);
	std::cin.ignore();

	bool result = manager.AddLocker(CLockers(nombre, "SIN ASIGNAR", fecha, numero, 1, 1));

	if(!result)
		std::cerr << "Couldn't save database" << std::endl;
}

void SimpleMenu::SearchUser()
{
	std::cout << "\nTye user's name: ";
	std::string user;
	std::getline(std::cin, user);

	if(std::cin.fail() )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Invalid data." << std::endl;
	}

	std::vector<CLockers> tmp;
	if(manager.SearchUser(user, tmp))
	{
		std::cout << "\n" << tmp.size() << "Lockers were found, listing..." << "\n";

		for(unsigned int i = 0; i < tmp.size(); ++i)
		{
			std::cout << "# " << std::setw(2) << tmp.at(i).GetLockerNumber() //<< "\t"
				<< std::setiosflags(std::ios_base::left) << " "
				<< std::setw(40) << tmp.at(i).GetAssignedUser() //<< "\t"
				<< std::setw(12) << tmp.at(i).GetDate() //<< "\t"
				//<< (l.HasKey() ? "Si" : "No") << "\t"
				//<< l.GetStatusDescription() << "\t"
				<< std::setw(15) << (tmp.at(i).Enabled() ? "Enabled" : "Disabled") << "\n";
			std::cout << std::resetiosflags(std::ios_base::adjustfield);
				//<< l.GetPreviousUser() << std::endl;
		}

		std::cout << std::endl;
	}
	else
	{
		std::cout << "\n\tNo results :( ...\n" << std::endl;
	}
	

}
