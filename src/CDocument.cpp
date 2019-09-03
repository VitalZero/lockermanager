#include "CDocument.h"

bool CDocument::SaveData(std::vector<CLockers>& lockers)
{
	inFile.open(path.c_str(), std::ios_base::out | std::ios_base::trunc);

	if(inFile.is_open())
	{
		for(CLockers l : lockers)
		{
			inFile << l;
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

		while( (inFile.good()) && (inFile >> tmp) )
		{
			lockers.push_back(tmp);
		}

		inFile.close();

		return true;
	}
	else
	{
		std::cout << "\tThe file "
				<< path << " doesn't exist or can't be opened."<< std::endl;
	}
	return false;
}
