#ifndef _CLOCKMANAGER_H
#define _CLOCKMANAGER_H

// <iostream> and <string> included in CLockers.h
#include <iostream>
#include <vector>
#include <string>
#include "CLockers.h"
#include "CDocument.h"

class CLockManager
{
public:
	CLockManager() = delete;
	CLockManager(const std::string& path_in);
	~CLockManager()
	{
	}

public:
	bool AddLocker(const CLockers& locker_in);
	bool GetLockers(std::vector<CLockers>& lockers_in, CLockers::Filter show = CLockers::Filter::All);
	int GetLockersQty() const;
	bool ChangeUser(int locker_in,const std::string& newAssigned, bool owned = true);
	bool DeleteUser(int locker_in);
	int Search(int numLocker);
	bool SearchUser(const std::string& user, std::vector<CLockers>& lockers_in );
	std::string ToUpper(const std::string& str_in);
	bool LoadData();

private:
	CDocument doc;
	std::vector<CLockers> lockers;
	std::string currDate;
	int totalLockers;
	bool SaveChanges();
};

#endif
