/*
 * CLocker.cpp
 *
 *  Created on: 11 feb 2019
 *      Author: jmichel
 */
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
		<< data.enabled << "|"; //\n opcional

	return stream;
}

std::istream& operator>>(std::istream& stream, CLockers& data)
{
	std::string temp;
	// lockerNum
	std::getline(stream, temp, '|'); // If the file is UNICODE, must ignore first 3 bytes of the file

	if(stream.fail())
		return stream;

	data.lockerNum = std::stoi(temp.c_str());

	std::getline(stream, data.assigned, '|');
	std::getline(stream, data.date, '|');
	std::getline(stream, data.previous, '|');
	// isOwned
	std::getline(stream, temp, '|');
	data.isOwned = std::stoi(temp.c_str());
	// hasKey
	std::getline(stream, temp, '|');
	data.hasKey = std::stoi(temp.c_str());
	// status
	std::getline(stream, temp, '|');
	data.status = std::stoi(temp.c_str());
	// enabled
	std::getline(stream, temp, '|');
	data.enabled = std::stoi(temp.c_str());
	//stream.ignore();

	return stream;
}

