#ifndef CDOCUMENT_H_
#define CDOCUMENT_H_

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
		if(archivo.is_open())
			archivo.close();
	}
	bool SaveData(std::vector<CLockers>& lockers);
	bool LoadData(std::vector<CLockers>& lockers);

private:
	std::fstream archivo;
	std::string path;
};

#endif /* CDOCUMENT_H_ */
