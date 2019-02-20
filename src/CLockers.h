#ifndef _CLOCKERS_H
#define _CLOCKERS_H
#include <iostream>
#include <string>

class CLockers
{
private:
	std::string assigned;
	std::string previous;
	std::string date;
	int numLocker;
	int conLlave;
	int status;
	const std::string descStatus[3] = {"Bueno", "Regular", "Malo"};
	const std::string withKey[2] = { "Si", "No" };
	friend class CLockManager;

public:
	friend std::ostream& operator<<(std::ostream& stream, const CLockers& data);
	friend std::istream& operator>>(std::istream& stream, CLockers& data);
	CLockers()
		:
		assigned(""),
		previous(""),
		date(""),
		numLocker(0),
		conLlave(0),
		status(0)
	{
	}
	CLockers(const std::string& assigned_in, const std::string& previous_in, const std::string& date_in,
			int locker_in, int llave_in, int status_in)
		:
		assigned(assigned_in),
		previous(previous_in),
		date(date_in),
		numLocker(locker_in),
		conLlave(llave_in),
		status(status_in)
	{
	}
	int GetNumber() const;
	std::string GetAssigned() const;
	std::string GetPrevious() const;
	std::string GetStatus() const;
	std::string GetDate() const;
	std::string GetWithKey() const;
};


#endif
