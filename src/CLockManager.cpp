#include "CLockManager.h"
#include <ctime>

CLockManager::CLockManager(const std::string& path_in)
	:
	doc(path_in),
	totalLockers(0)
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
		std::cout << "\tLocker already exist " << tmpNumLoc << ", not added."
				<< std::endl;

		return false;
	}
	else
	{
		lockers.push_back(locker_in);

		return doc.SaveData(lockers);
	}
}

bool CLockManager::GetLockers(std::vector<CLockers>& lockers_in, CLockers::Filter show)
{
	// TODO: Filter input
	lockers_in.clear();
	bool result = false;

	switch(show)
	{
		case CLockers::Filter::All:
			lockers_in = lockers;
			result = true;
		break;
		case CLockers::Filter::Assigned:
		{
			for(unsigned int i= 0; i < lockers.size(); ++i)
			{
				if(lockers.at(i).IsAssigned())
					lockers_in.push_back(lockers.at(i));
			}
			if(lockers_in.size() > 0)
				result = true;
		}
		break;
		case CLockers::Filter::NotAssigned:
		{
			for(unsigned int i= 0; i < lockers.size(); ++i)
			{
				if(!lockers.at(i).IsAssigned())
					lockers_in.push_back(lockers.at(i));
			}
			if(lockers_in.size() > 0)
				result = true;
		}
		break;
		case CLockers::Filter::Good:
		{
			for(unsigned int i= 0; i < lockers.size(); ++i)
			{
				if(!lockers.at(i).GetStatusInt() == 0)
					lockers_in.push_back(lockers.at(i));
			}
			if(lockers_in.size() > 0)
				result = true;
		}
		break;
		case CLockers::Filter::Bad:
		case CLockers::Filter::Disabled:
		case CLockers::Filter::Enabled:
		case CLockers::Filter::NoKey:
		case CLockers::Filter::WithKey:
		break;
		default:
			return false;
		break;
	}

	// result defaults to false, true will be set only if there are matches
	return result;
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
				<< " succesfully edited." << std::endl;
		std::cout << "New User: " << lockers.at(foundLockerPos).GetAssignedUser() << std::endl;

		return SaveChanges();
	}

	return false;
}

bool CLockManager::DeleteUser(int locker_in)
{
	return ChangeUser(locker_in, "", false);
}

bool CLockManager::SaveChanges()
{
	bool saved = doc.SaveData(lockers);

	if(saved)
		doc.LoadData(lockers);

	return saved;
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

bool CLockManager::SearchUser(const std::string& user, std::vector<CLockers>& lockers_in )
{
	lockers_in.clear();
	size_t result = std::string::npos;

	for( CLockers l : lockers)
	{
		result = l.GetAssignedUser().find(ToUpper(user));
		if( result != std::string::npos )
		{
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

bool CLockManager::LoadData()
{
	if( doc.LoadData(lockers) )
	{
		totalLockers = lockers.size();
		return true;
	}

	return false;
}
