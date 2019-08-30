#include "CLockManager.h"
#include <ctime>
//#include <sstream>

CLockManager::CLockManager(const std::string& path_in)
	:
	doc(path_in)
{
	time_t now;

	time(&now);
	tm *ltm = localtime(&now);

 	currDate = (ltm->tm_mday < 10 ? "0" : "") + std::to_string(ltm->tm_mday);
	currDate += "/";
	currDate += (ltm->tm_mon < 9 ? "0" : "") + std::to_string(ltm->tm_mon+1);
	currDate += "/";
	currDate += std::to_string(ltm->tm_year+1900);
}

bool CLockManager::AddLocker(const CLockers& locker_in)
{
	const int tmpNumLoc = locker_in.GetLockerNumber();

	if(Search(tmpNumLoc) >= 0)
	{
		std::cout << "\tYa exsiste el locker " << tmpNumLoc << ", no se agregó"
				<< std::endl;

		return false;
	}
	else
	{
		lockers.push_back(locker_in);

		return doc.SaveData(lockers);
	}
}

CLockers CLockManager::GetLockers(int numLocker, CLockers::Filtro show)
{
	if(show == CLockers::Filtro::Todos)
	{
		return lockers.at(numLocker);
	}
	else if(show == CLockers::Filtro::Asignados)
	{
		if(lockers.at(numLocker).IsAssigned())
			return lockers.at(numLocker);
	}
	else if(show == CLockers::Filtro::SinAsignar)
	{
		if(!lockers.at(numLocker).IsAssigned())
			return lockers.at(numLocker);
	}
	else if(show == CLockers::Filtro::Buenos)
	{
		if(lockers.at(numLocker).GetStatusInt() == 0)
		return lockers.at(numLocker);
	}

	return CLockers(-1);
}

int CLockManager::GetLockersQty() const
{
	return lockers.size();
}

bool CLockManager::ChangeUser(int locker_in,const std::string& newAssigned, bool owned)
{
	const int foundLockerPos = Search(locker_in);

	if( (foundLockerPos >= 0) && (lockers.size() > 0) )
	{
		std::string tmp = lockers.at(foundLockerPos).GetAssignedUser();

		lockers.at(foundLockerPos).SetAssignedUser(ToUpper(newAssigned));
		lockers.at(foundLockerPos).SetPreviousUser(ToUpper(tmp));
		lockers.at(foundLockerPos).SetDate(currDate);
		lockers.at(foundLockerPos).SetOwnership(owned);
		std::cout << "\t\nLocker " << lockers.at(foundLockerPos).GetLockerNumber()
				<< " editado con exito." << std::endl;
		std::cout << "Nuevo usuario: " << lockers.at(foundLockerPos).GetAssignedUser() << std::endl;

		return true;
	}

	return false;
}

bool CLockManager::DeleteUser(int locker_in)
{
	return ChangeUser(locker_in, "", false);
}

void CLockManager::SaveChanges()
{
	if(doc.SaveData(lockers))
		doc.LoadData(lockers);
	else
		std::cout << "ERROR!!\tNo se pudo guardar el archivo" << std::endl;
}

int CLockManager::Search(int numLocker_in)
{
	const int NORESULTS = -1;
	for(unsigned int i = 0; i < lockers.size(); ++i)
	{
		if(lockers.at(i).GetLockerNumber() == numLocker_in)
		{
			return i;
		}
	}
	return NORESULTS;
}

bool CLockManager::SearchUser(const std::string& usuario, std::vector<CLockers>& lockers_in )
{
	lockers_in.clear();
	size_t result = std::string::npos;
	//std::cout << "\nValor de npos: " << std::string::npos << std::endl;

	for( CLockers l : lockers)
	{
		result = l.GetAssignedUser().find(ToUpper(usuario));
		if( result != std::string::npos )
		{
			//std::cout << "Se encontro un resultado: " << l.GetAssignedUser() << std::endl;
			lockers_in.push_back(l);
		}
	}

	if( lockers_in.size() > 0)
	{
		return true;
	}
	
	return false;
}

std::string CLockManager::ToUpper(const std::string& str_in)
{
	std::string tmp = str_in;

	for(unsigned int i = 0; i < tmp.size(); ++i)
	{
		tmp[i] = ::toupper(str_in[i]);
	}

	return tmp;
}

bool CLockManager::Init()
{
	lockers.clear();
	if( doc.LoadData(lockers) )
	{
		totalLockers = lockers.size();
		return true;
	}

	return false;
}