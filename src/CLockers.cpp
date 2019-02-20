/*
 * CLocker.cpp
 *
 *  Created on: 11 feb 2019
 *      Author: jmichel
 */
#include "CLockers.h"


int CLockers::GetNumber() const
{
	return numLocker;
}

std::string CLockers::GetAssigned() const
{
	return assigned;
}

std::string CLockers::GetPrevious() const
{
	return previous;
}

std::string CLockers::GetStatus() const
{
	return descStatus[status];
}

std::string CLockers::GetDate() const
{
	return date;
}

std::string CLockers::GetWithKey() const
{
	return withKey[conLlave];
}
std::ostream& operator<<(std::ostream& stream, const CLockers& data)
{
	stream << data.numLocker << " "
		<< data.assigned.size() << " "
		<< data.assigned << " "
		<< data.date.size() << " "
		<< data.date << " "
		<< data.previous.size() << " "
		<< data.previous << " "
		<< data.status << " "
		<< data.conLlave << "\n"
		;
	return stream;
}

std::istream& operator>>(std::istream& stream, CLockers& data)
{
	int size;

	stream >> data.numLocker >> size;
	stream.ignore(256, ' ');
	data.assigned.resize(size);
	stream.read(&data.assigned[0], size);
	stream.ignore(256, ' ');

	stream >> size;
	stream.ignore(256, ' ');
	data.date.resize(size);
	stream.read(&data.date[0], size);
	stream.ignore(256, ' ');

	stream >> size;
	stream.ignore(256, ' ');
	data.previous.resize(size);
	stream.read(&data.previous[0], size);
	stream.ignore(256, ' ');

	stream >> data.status >> data.conLlave;

	return stream;
}

