#include "CDocument.h"

bool CDocument::SaveData(std::vector<CLockers>& lockers)
{
	inFile.open(path.c_str(), std::ios_base::out | std::ios_base::trunc);

	if(inFile.is_open())
	{
		for(unsigned int i = 0; i < lockers.size(); ++i)
		{
			inFile << lockers.at(i);
		}
		inFile.close();
		return true;
	}

	return false;
}

bool CDocument::LoadData(std::vector<CLockers>& lockers)
{
	inFile.open(path.c_str(), std::ios_base::in);

	if(inFile.is_open())
	{
		CLockers tmp;
		lockers.clear();

		while( (inFile.good()) && (inFile >> tmp) ) // here is the problem from CLockers, even though is being checked in here
		{											// it gives another extra loop after the fail bit is set
			lockers.push_back(tmp);
		}

		inFile.close();

		return true;
	}
	else
	{
		// Probably move this out to menu.cpp
		// interaction only should occur outside the class
		std::cout << "\tThe file "
				<< path << " doesn't exist or can't be opened.\n";
		std::cout << "Do you want to create it? y/n: ";
		std::string stringAnswer;
		std::getline(std::cin, stringAnswer);

		if( (stringAnswer == "y") || (stringAnswer == "Y") )
		{
			inFile.open(path, std::ios_base::out | std::ios_base::trunc);
			inFile.close();
			return true;
		}
	}
	return false;
}
