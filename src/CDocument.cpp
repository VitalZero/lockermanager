#include "CDocument.h"

bool CDocument::SaveData(std::vector<CLockers>& lockers)
{
	archivo.open(path.c_str(), std::ios_base::out | std::ios_base::trunc);

	if(archivo.is_open())
	{
		for(CLockers l : lockers)
		{
			archivo << l;
		}
		archivo.close();
		return true;
	}
	//std::cout << "ERROR!!\tNo sepudo leer el archivo" << std::endl;
	return false;
}

bool CDocument::LoadData(std::vector<CLockers>& lockers)
{
	archivo.open(path.c_str(), std::ios_base::in);

	if(archivo.is_open())
	{
		CLockers tmp;
		lockers.clear();
		while(( archivo >> tmp) && ( archivo.good()))
		{
			lockers.push_back(tmp);
		}

		/*std::cout << "bb: " << archivo.bad() << ", fb: " << archivo.fail()
				<< ", eb: " << archivo.eof() << ", gb: " << archivo.good() << std::endl;*/

		//std::cout << "Se leyeron " << lockers.size() << " registros\n" << std::endl;
		archivo.close();

		return true;
	}
	else
	{
		std::cout << "\tEl archivo "
				<< path << " no existe o no se puede abrir."<< std::endl;
	}
	return false;
}
