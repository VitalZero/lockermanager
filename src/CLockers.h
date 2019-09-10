#ifndef _CLOCKERS_H
#define _CLOCKERS_H
/*
 * CLockers.h
 * It is used by CLockManager.
 * Everything related to a locker (probably should change name to Locker instead)
 * Stores its number, assigned used, date on which it was assignated, status (good = 0, regular = 1, bad = 2)
 * enabled (available, probably should change this too), owned, and previous user name
 * It has enum for as filters, used by CLockManager
 * Not too much to look here, just some getters, setters and operator overloads (>>, << and =)
 */
#include <iostream>
#include <string>

class CLockers
{
private:
	std::string assigned;
	std::string previous;
	// TODO: In the future, use localtime to store date values, use date string to describe it
	// TODO: Maybe create a date class using the above instructions and remove date string
	// this is to use date differences if required (for days only, no hours or seconds or minutes)
	std::string date;
	int lockerNum;
	bool hasKey;
	int status;
	bool enabled;
	bool isOwned;
	const std::string descStatus[3] = {"Good", "Regular", "Bad"};
	const std::string withKey[2] = { "Yes", "No" };

public:
	CLockers()
		:
		assigned(""),
		previous(""),
		date(""),
		lockerNum(0),
		hasKey(false),
		status(0),
		enabled(true),
		isOwned(true)
	{
	}
	CLockers(const std::string& assigned_in, const std::string& previous_in, const std::string& date_in,
			int locker_in, int llave_in, int status_in)
		:
		assigned(assigned_in),
		previous(previous_in),
		date(date_in),
		lockerNum(locker_in),
		hasKey(llave_in),
		status(status_in),
		enabled(true),
		isOwned(true)
	{
	}
	CLockers& operator=(const CLockers& rhs);
	int GetLockerNumber() const;
	int GetStatusInt() const;
	std::string GetAssignedUser() const;
	std::string GetPreviousUser() const;
	std::string GetStatusDescription() const;
	std::string GetDate() const;
	bool HasKey() const;
	bool IsAssigned() const;
	bool Enabled() const;
	void SetOwnership(bool owned);
	void SetAssignedUser(const std::string& newUser);
	void SetPreviousUser(const std::string& oldUser);
	void SetDate(const std::string& newDate);
	friend std::ostream& operator<<(std::ostream& stream, const CLockers& data);
	friend std::istream& operator>>(std::istream& stream, CLockers& data);
	enum class Filter
	{
		All, Assigned, NotAssigned, Good, Bad, NoKey, WithKey, Enabled, Disabled
	};
};


#endif
