#ifndef CDOCUMENT_H_
#define CDOCUMENT_H_
/*
 * CDocument.h
 * It is used by CLockManager.
 * Just used to load and save data from a file using a vector of CLockers
 * CLockers overloads stream operators >> and <<
 * Just feed a vector of CLockers and it's all good!
 */
#include <fstream>
#include <string>
#include <vector>
#include "CLockers.h"

class CDocument{
public:
	CDocument() = delete;
	CDocument(const std::string& path_in)
		:
		path(path_in)
	{
	}
	~CDocument()
	{
		if(inFile.is_open())
			inFile.close();
	}
	bool SaveData(std::vector<CLockers>& lockers);
	bool LoadData(std::vector<CLockers>& lockers);

private:
	std::fstream inFile;
	std::string path;
};

#endif /* CDOCUMENT_H_ */
