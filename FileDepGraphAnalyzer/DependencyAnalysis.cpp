/////////////////////////////////////////////////////////////////////
// DependencyAnalysis.cpp                                          //
// Mengjie Shi                                                     //
// SUID: 457056896                                                 //
/////////////////////////////////////////////////////////////////////

#include "DependencyAnalysis.h"

#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <fstream>
#include <exception>


DepAnal::DepAnal(std::string filewithfullname)
{
	Utilities ut_;
	_fullName = filewithfullname;
	std::vector<std::string> ve;
	ut_.split(filewithfullname, '/', ve);
	_file = ve[ve.size() - 1];
	saveToken(filewithfullname);
}

std::vector<std::string> DepAnal::saveToken(std::string fullname)
{
	Utilities ut;
	std::string str;

	std::ifstream file(fullname);  //  read the file from directory
	std::vector<std::string> elems;
	while (std::getline(file, str))
		ut.split(str, '"', elems);

	tokVec = elems;
	return elems;
}

Element DepAnal::DepAnalyzer(std::vector<std::string> files)
{
	Element tempElem;
	Utilities ut;

	tempElem.key = _file;

	for (unsigned i = 0; i < tokVec.size(); i++)
	{
		if (tokVec.size() < 2)
			break;

		if (tokVec[i].find("#include") != std::string::npos)
		{
			std::vector<std::string> tempVe;
			ut.split(tokVec[i + 1], '/', tempVe);
			std::string filename = tempVe[tempVe.size() - 1];

			for (unsigned i = 0; i < files.size(); i++)
			{
				if (filename == files[i])
					tempElem.filenames.push_back(files[i]);
			}
		}
	}
	return tempElem;
}

bool DepAnal::savetoDb(Element elem, KeyValueTable &kvt)
{
	kvt.saveRecord(elem.key, elem);
	return true;
}

