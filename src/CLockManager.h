#ifndef _CLOCKMANAGER_H
#define _CLOCKMANAGER_H

// <iostream> and <string> included in CLockers.h
#include <fstream>
#include <vector>
#include "CLockers.h"

class CLockManager
{
public:
	CLockManager(const std::string& path_in);
	~CLockManager()
	{
		archivo.close();
	}

public:
	//void ShowLockers(int show = Filtro::Todos);
	bool AddLocker(const CLockers& locker_in);
	std::vector<CLockers> GetLockers(int show = Filtro::Todos);
	bool ChangeUser(int locker_in,const std::string& newAssigned);
	bool DeleteUser(int locker_in);
	void SaveChanges();
	int Search(int numLocker);
	std::string ToUpper(const std::string& str_in);
	enum Filtro
	{
		Buenos,
		Regulares,
		Malos,
		Todos,
		Asignados,
		SinAsignar
	};

private:
	void FillLockers();
	std::string path;
	std::fstream archivo;
	std::vector<CLockers> lockers;
	std::string currDate;
};

#endif
