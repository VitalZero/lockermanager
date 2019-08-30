#include "Menu.h"
#include <iostream>
#include <iomanip>

SimpleMenu::SimpleMenu(CLockManager& manager_in)
	:
	manager(manager_in)
{
	if( !manager.Init() )
	{
		std::cerr << "Error!, no se pudo cargar la base de datos" << std::endl;
		error = true;
	}
}

void SimpleMenu::ShowMenu()
{
	bool running = true;
	int answer = 0;

	while(running && !error)
	{
		std::wcout << "\n\t\tGestion de Lockers\n";
		std::cout << "\t\tMenu principal\n\n";
		std::cout << "\tTeclea una de las siguientes opciones:\n";
		std::cout << (int)Opciones::Listar << "  Listar lockers\n";
		std::cout << (int)Opciones::Cambiar << "  Cambiar usuario\n";
		std::cout << (int)Opciones::Borrar << "  Borrar usuario\n";
		std::cout << (int)Opciones::Agregar << "  Agregar usuario\n";
		std::cout << (int)Opciones::Buscar << "  Buscar usuario\n";
		std::cout << (int)Opciones::Salir << "  Salir" << std::endl;
		std::cin >> answer;

		if(std::cin.fail() )
		{
			std::cin.clear();
			std::cin.ignore();
			std::cerr << "Error!!! Datos introducidos son erroneos" << std::endl;
			error = true;
		}

		std::cin.ignore();

		switch( (Opciones)answer )
		{
		case Opciones::Listar:
			ShowLockers();
			break;
		case Opciones::Cambiar:
			ChangeUser();
			break;
		case Opciones::Borrar:
			DeleteUser();
			break;
		case Opciones::Agregar:
			AddUser();
			break;
		case Opciones::Salir:
			running = false;
		break;
		case Opciones::Buscar:
			SearchUser();
		break;
		default:
			std::cout << "\t\nOpcion incorrecta\n" << std::endl;
			break;
		}
	}

	std::cout << "\t\n...Hasta pronto!" << std::endl;
}

void SimpleMenu::ChangeUser()
{
	std::cout << "\nCual locker quieres cambiar?: ";
	int answer = 0;
	std::cin >> answer;

	if( std::cin.fail() || answer == 0 )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Datos introducidos son erroneos" << std::endl;
		error = true;
	}

	std::cin.ignore();

	std::cout << "Escribe el nombre de nuevo usuario: ";
	std::string usuarioNuevo;
	std::getline(std::cin,usuarioNuevo);

	if(manager.ChangeUser(answer, usuarioNuevo) )
	{
		manager.SaveChanges();
		std::cout << "Cambiando usuario" << std::endl;
	}
	else
	{
		std::cerr << "\t\neERROR!!!\tNo se pudo cambiar el usuario" << std::endl;
	}

	std::cout << "Presione Enter para continuar..." << std::endl;

	std::cin.ignore();
}

void SimpleMenu::ShowLockers()
{
	// Show option to filter lockers
	std::cout << "\n\n\tSelecciona la opcion a mostrar\n";
	std::cout << "0 Todos\n";
	std::cout << "1 Asignados\n";
	std::cout << "2 Sin asignar\n";
	std::cout << "3 En buen estado\n";
	std::cout << "4 En mal estado\n";
	std::cout << "-1 Regresar al menu anterior\n";

	int answer;
	std::cin >> answer;
	if(std::cin.fail() )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Datos introducidos son erroneos" << std::endl;
		error = true;
	}

	std::cin.ignore();
	std::cout << "\n";

	switch((CLockers::Filtro)answer)
	{
		case CLockers::Filtro::Todos:
		case CLockers::Filtro::Asignados:
		case CLockers::Filtro::SinAsignar:
		case CLockers::Filtro::Buenos:
		case CLockers::Filtro::Malos:
		{
			// TODO: Change so it returns only the correct lockers (filtered)
			// maybe use a vector of lockers passed as reference
			// and return the amout of filtered lockers
			int c = 0;
			const int locQty = manager.GetLockersQty();
			
			for(int i = 0; i < locQty; ++i)
			{
				CLockers l = manager.GetLockers(i, CLockers::Filtro(answer));

				if(l.GetLockerNumber() <= 0)
				{
					continue;
				}
				++c;

				std::cout << "# " << std::setw(2) << l.GetLockerNumber() //<< "\t"
					<< std::setiosflags(std::ios_base::left) << " "
					<< std::setw(40) << l.GetAssignedUser() //<< "\t"
					<< std::setw(12) << l.GetDate() //<< "\t"
					//<< (l.HasKey() ? "Si" : "No") << "\t"
					//<< l.GetStatusDescription() << "\t"
					<< std::setw(15) << (l.Enabled() ? "Habilitado" : "Deshabilitado") << std::endl;
				std::cout << std::resetiosflags(std::ios_base::adjustfield);
					//<< l.GetPreviousUser() << std::endl;
			}

			std::cout << "\n" << c << " lockers encontrados\n";
			std::cout << "Presione Enter para continuar..." << std::endl;	
			std::cin.ignore();
		}
		break;
		case CLockers::Filtro::Exit:
			std::cout << "Regresando al menu anterior" << std::endl;
		break;
		default:
			std::cout << "Opcion invalida, intenta de nuevo...\n" << std::endl;
			std::cin.ignore();
		break;
	}
}

void SimpleMenu::DeleteUser()
{
	std::cout << "Borrando usuario" << std::endl;
	std::cout << "Presione Enter para continuar..." << std::endl;

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
		std::cerr << "Error!!! Datos introducidos son erroneos" << std::endl;
	}

	std::cin.ignore();

	std::cout << "Nombre: ";
	std::string nombre;
	std::getline(std::cin, nombre);

	// TODO: Check for string lenght, date should not be more then 8 characters (not including \0)
	std::cout << "Fecha: ";
	std::string fecha;
	std::getline(std::cin, fecha);
	std::cin.ignore();

	bool result = manager.AddLocker(CLockers(nombre, "SIN ASIGNAR", fecha, numero, 1, 1));

	if(!result)
		std::cerr << "No se pudo guardar el archivo al añadir usuario" << std::endl;
}

void SimpleMenu::SearchUser()
{
	std::cout << "\nEscribe el nombre a buscar: ";
	std::string user;
	std::getline(std::cin, user);
	if(std::cin.fail() )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cerr << "Error!!! Datos introducidos son erroneos" << std::endl;
	}

	std::vector<CLockers> tmp;
	if(manager.SearchUser(user, tmp))
	{
		std::cout << "\nSe encontraron " << tmp.size() << " lockers!. Listando..." << "\n";

		for(unsigned int i = 0; i < tmp.size(); ++i)
		{
			std::cout << "# " << std::setw(2) << tmp.at(i).GetLockerNumber() //<< "\t"
				<< std::setiosflags(std::ios_base::left) << " "
				<< std::setw(40) << tmp.at(i).GetAssignedUser() //<< "\t"
				<< std::setw(12) << tmp.at(i).GetDate() //<< "\t"
				//<< (l.HasKey() ? "Si" : "No") << "\t"
				//<< l.GetStatusDescription() << "\t"
				<< std::setw(15) << (tmp.at(i).Enabled() ? "Habilitado" : "Deshabilitado") << "\n";
			std::cout << std::resetiosflags(std::ios_base::adjustfield);
				//<< l.GetPreviousUser() << std::endl;
		}

		std::cout << std::endl;
	}
	else
	{
		std::cout << "\n\tNo se encontraron resultados :( ...\n" << std::endl;
	}
	

}