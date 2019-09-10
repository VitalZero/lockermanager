#include "CLockers.h"

CLockers& CLockers::operator=(const CLockers& rhs)
{
	this->assigned = rhs.assigned;
	this->date = rhs.date;
	this->enabled = rhs.enabled;
	this->hasKey = rhs.hasKey;
	this->isOwned = rhs.isOwned;
	this->lockerNum = rhs.lockerNum;
	this->previous = rhs.previous;
	this->status = rhs.status;

	return *this;
}

int CLockers::GetLockerNumber() const
{
	return lockerNum;
}

std::string CLockers::GetAssignedUser() const
{
	if(isOwned)
		return assigned;
	else
		return std::string("-----");
}

std::string CLockers::GetPreviousUser() const
{
	return previous;
}

std::string CLockers::GetStatusDescription() const
{
	return descStatus[status];
}

int CLockers::GetStatusInt() const
{
	return status;
}
std::string CLockers::GetDate() const
{
	return date;
}

bool CLockers::HasKey() const
{
	return hasKey;
}

bool CLockers::IsAssigned() const
{
	return isOwned;
}

bool CLockers::Enabled() const
{
	return enabled;
}

void CLockers::SetOwnership(bool owned)
{
	isOwned = owned;
}

void CLockers::SetAssignedUser(const std::string& newUser)
{
	assigned = newUser;
}

void CLockers::SetPreviousUser(const std::string& oldUser)
{
	previous = oldUser;
}

void CLockers::SetDate(const std::string& newDate)
{
	date = newDate;
}

std::ostream& operator<<(std::ostream& stream, const CLockers& data)
{
	stream << data.lockerNum << "|"
		<< data.assigned << "|"
		<< data.date << "|"
		<< data.previous << "|"
		<< data.isOwned << "|"
		<< data.hasKey << "|"
		<< data.status << "|"
		<< data.enabled << "|"; //\n optional, should not affect functionality

	return stream;
}

std::istream& operator>>(std::istream& stream, CLockers& data)
{
	std::string temp;
	// lockerNum
	std::getline(stream, temp, '|'); // If the file is saved as UNICODE, must ignore first 3 bytes of the file

	if(stream.fail()) // for some weird reason, even the stream sets fail bit, it gives another loop (in CDocument::LoadData)
		return stream;// so, sa the data is emtpy, it fills and emtpy string, then it is passed to std::stoi which in turn
					  // throws and exception and exits inmediately from the app. This check prevents that.
					  // also, using std::atoi fixes that, shows no error and everything works fine.

	data.lockerNum = std::stoi(temp);

	std::getline(stream, data.assigned, '|');
	std::getline(stream, data.date, '|');
	std::getline(stream, data.previous, '|');
	// isOwned
	std::getline(stream, temp, '|');
	data.isOwned = std::stoi(temp); // 1 = true, 0 = false, who cares
	if(!data.isOwned)
		data.assigned = "";
	// hasKey
	std::getline(stream, temp, '|');
	data.hasKey = std::stoi(temp);
	// status
	std::getline(stream, temp, '|');
	data.status = std::stoi(temp);
	// enabled
	std::getline(stream, temp, '|');
	data.enabled = std::stoi(temp);
	//stream.ignore();

	return stream;
}

