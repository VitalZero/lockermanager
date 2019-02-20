/*
 * CLockManager.cpp
 *
 *  Created on: 11 feb 2019
 *      Author: jmichel
 */
#include "CLockManager.h"
#include <ctime>
#include <sstream>

CLockManager::CLockManager(const std::string& path_in)
	:
	path(path_in)
{
	time_t now;

	time(&now);
	tm *ltm = localtime(&now);

 	currDate = std::to_string(ltm->tm_mday);
	currDate += "/";
	currDate += std::to_string(ltm->tm_mon+1);
	currDate += "/";
	currDate += std::to_string(ltm->tm_year+1900);

	lockers.clear();
	FillLockers();
}
/*
void CLockManager::ShowLockers(int show)
{
	if(lockers.size() == 0)
		std::cout << "No hay registros para mostrar" << std::endl;
	else
	{
		switch(show)
		{
			case Filtro::Todos:
			{
				for(CLockers loc : lockers)
				{

					std::cout << "Locker " << loc.GetLockerNumber()
							<< " -> Usuario: " << ( (loc.GetAssigned().size() == 0) ? "---" : loc.GetAssigned() )
							<< " / Fecha: " << ( (loc.GetDate().size() == 0) ? "---" : loc.GetDate() )
							//<< " / Anterior: " << ( (loc.GetPrevious().size() == 0) ? "---" : loc.GetPrevious() )
							<< ". Estado: " << loc.GetStatus()
							<< ". Llave: " << loc.GetWithKey() << std::endl;
				}

				std::cout << "\tSe encontraron " << lockers.size() << " lockers. Fin de la lista." << std::endl;
			}
			break;

			case Filtro::Asignados:
			{
				int i = 0;
				for(CLockers loc : lockers)
				{
					if(loc.assigned.compare("SIN ASIGNAR") != 0)
					{
						std::cout << "Locker " << loc.GetLockerNumber()
								<< " -> Usuario: " << ( (loc.GetAssigned().size() == 0) ? "---" : loc.GetAssigned() )
								<< " / Fecha: " << ( (loc.GetDate().size() == 0) ? "---" : loc.GetDate() )
								//<< " / Anterior: " << ( (loc.GetPrevious().size() == 0) ? "---" : loc.GetPrevious() )
								<< ". Estado: " << loc.GetStatus() << std::endl;
						++i;
					}
				}

				std::cout << "\tSe encontraron " << i << " lockers. Fin de la lista." << std::endl;
			}
			break;

			case Filtro::SinAsignar:
			{
				int i = 0;
				for(CLockers loc : lockers)
				{
					if(loc.assigned.compare("SIN ASIGNAR") == 0)
					{
						std::cout << "Locker " << loc.GetLockerNumber()
								<< " -> Usuario: " << ( (loc.GetAssigned().size() == 0) ? "---" : loc.GetAssigned() )
								<< " / Fecha: " << ( (loc.GetDate().size() == 0) ? "---" : loc.GetDate() )
								//<< " / Anterior: " << ( (loc.GetPrevious().size() == 0) ? "---" : loc.GetPrevious() )
								<< ". Estado: " << loc.GetStatus() << std::endl;
						++i;
					}
				}

				std::cout << "\tSe encontraron " << i << " lockers. Fin de la lista." << std::endl;
			}
			break;

			case Filtro::Buenos:
			case Filtro::Regulares:
			case Filtro::Malos:
			{
				int i = 0;
				for(CLockers loc : lockers)
				{
					if( loc.status == (show))
					{
						std::cout << "Locker " << loc.GetLockerNumber()
								<< " -> Usuario: " << ( (loc.GetAssigned().size() == 0) ? "---" : loc.GetAssigned() )
								<< " / Fecha: " << ( (loc.GetDate().size() == 0) ? "---" : loc.GetDate() )
								//<< " / Anterior: " << ( (loc.GetPrevious().size() == 0) ? "---" : loc.GetPrevious() )
								<< ". Estado: " << loc.GetStatus() << std::endl;
						++i;
					}
				}

				std::cout << "\tSe encontraron " << i << " lockers. Fin de la lista." << std::endl;
			}
			break;
		}
	}
}
*/
bool CLockManager::AddLocker(const CLockers& locker_in)
{
	bool agregado = false;
	archivo.open(path.c_str(), std::ios_base::out | std::ios_base::app);

	if(archivo.is_open())
	{
		const int tmpNumLoc = locker_in.GetNumber();

		if( Search(tmpNumLoc) )
		{
			std::cout << "\tYa existe este registro del locker "
					<< tmpNumLoc << ", no se agrego" << std::endl;
		}
		else
		{
			archivo << locker_in;
			lockers.push_back(locker_in);
			agregado = true;
		}
		archivo.close();
	}
	else
	{
		std::cout << "\tNo se pudo abrir el archivo: " << path << std::endl;
	}

	return agregado;
}

std::vector<CLockers> CLockManager::GetLockers(int show)
{
	const int vSize = lockers.size();
	std::vector<CLockers> v;
	v.reserve(vSize);

	switch(show)
	{
	case Filtro::Asignados:
	{
		for(CLockers l : lockers)
		{
			if(l.assigned != "SIN ASIGNAR")
			{
				v.emplace_back(l);
			}
		}
	}
	return v;

	case Filtro::SinAsignar:
	{
		for(CLockers l : lockers)
		{
			if(l.assigned == "SIN ASIGNAR")
			{
				v.emplace_back(l);
			}
		}
	}
	return v;

	case Filtro::Buenos:
	case Filtro::Regulares:
	case Filtro::Malos:
	{
		for(CLockers l : lockers)
		{
			if(l.status == show)
			{
				v.emplace_back(l);
			}
		}
	}
	return v;

	default:
	break;
	}
	return lockers;
}

bool CLockManager::ChangeUser(int locker_in,const std::string& newAssigned)
{
	const int foundLockerPos = Search(locker_in);

	if( (foundLockerPos >= 0) && (lockers.size() > 0) )
	{
		std::string tmp = lockers.at(foundLockerPos).assigned;

		lockers.at(foundLockerPos).assigned = ToUpper(newAssigned);
		lockers.at(foundLockerPos).previous = ToUpper(tmp);
		lockers.at(foundLockerPos).date = currDate;
		std::cout << "\t\nLocker " << lockers.at(foundLockerPos).numLocker
				<< " editado con exito." << std::endl;
		return true;
	}
	return false;
}

bool CLockManager::DeleteUser(int locker_in)
{
	return ChangeUser(locker_in, "SIN ASIGNAR");
}

void CLockManager::SaveChanges()
{
	/*const char key[3] = {'K', '+', 'e'};
	std::string codificado;

	std::stringstream ss;*/
	archivo.open(path.c_str(), std::ios_base::out | std::ios_base::trunc);

		if(archivo.is_open())
		{
			for(CLockers l : lockers)
			{
				//ss << l;
				archivo << l;
			}
			/*const int size = ss.str().size();
			codificado.resize(size);
			for(int i = 0; i < size; ++i)
			{
				codificado += ss.str().c_str()[i] ^ key[i%3];
			}

			archivo.write(&codificado[0], size);
			archivo.write(&ss.str().c_str()[0], ss.str().size());*/
			archivo.close();

			FillLockers();
		}
		else
		{
			std::cout << "\tNo se pudo abrir el archivo: " << path << std::endl;
		}
}

int CLockManager::Search(int numLocker_in)
{
	for(unsigned int i = 0; i < lockers.size(); ++i)
	{
		if(lockers.at(i).GetNumber() == numLocker_in)
		{
			return i;
		}
	}
	return -1;
}

std::string CLockManager::ToUpper(const std::string& str_in)
{
	std::string tmp = str_in;

	for(unsigned int i = 0; i < tmp.size(); ++i)
	{
		tmp[i] = std::toupper(str_in[i]);
	}

	return tmp;
}

void CLockManager::FillLockers()
{
	archivo.open(path.c_str(), std::ios_base::in);

	if(archivo.is_open())
	{
		CLockers tmp;
		while(archivo >> tmp)
		{
			if(archivo.bad())
			{
				std::cout << "\tError de lectura\n\n";
				break;
			}
			archivo.clear();
			archivo.ignore(1000, '\n');

			lockers.push_back(tmp);
		}

		std::cout << "Se leyeron " << lockers.size() << " registros\n" << std::endl;
		archivo.close();
	}
	else
	{
		std::cout << "\tEl archivo "
				<< path << " no existe o no se puede abrir."<< std::endl;
	}
}




