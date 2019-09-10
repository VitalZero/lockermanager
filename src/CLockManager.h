#ifndef _CLOCKMANAGER_H
#define _CLOCKMANAGER_H
/* CLockManager.h (probably should change name)
 * Usage: Just include CLockManager.h and create an instance of CLockManager using the "database" filename as an argument for
 * the constructor.
 *
 * Example: CLockManager manager("database.txt");
 *
 * It will create a database for lockers, using values separated by "|", using the following fields:
 * Locker no, assigned user's name, date of assginement (dd/mm/yyyy), previous user's name, is owned (true/false), has copy of key (true/false),
 * status (good = 0, regular = 1, bad = 2), and enabled (true/false)
 * Example:
 * 1|JOHN WICK|01/08/2019|SOME GUY|1|1|0|1|
 *
 * Uses an instance of CDocument class to handle file input/output
 *
 * To Add a new locker (not user), use AddLocker(locker);
 * Create an instance of CLockers.
 * feed it to the function
 *
 * To set user's name on a locker, use ChangeUser(locker number to change, new assigned user, owned (default true) );

 * Search(locker number to search for), searches for a locker number, returns it's position in the vector of lockers
 *
 * SearchUser(name to search, vector of lockers), returns true if finds matches, false otherwise. Fills the vector of lockers with the results
 * need to feed it an empty vector of lockers
 *
 * DeleteUser() paused ATM.
 *
 * GetLockers(vector of lockers, locker filter (defaults to all);
 * Feed it a vector of lockers and it will fill it with the results
 * use CLockers::Filter values
 * if results found, returns true, false otherwise.
 *
 * GetLockersQty() returns the total amount of lockers registered (no filter)
 *
 * To upper(string), it's just a helper function to convert to uppercase the strings, returns a string
 *
 * LoadData(), loads the database into the lockers vector, returns true if everything went ok, false otherwise
 *
 * SaveChanges(), saves the lockers vector to the file, returns true if everything went ok, false otherwise
 */
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
