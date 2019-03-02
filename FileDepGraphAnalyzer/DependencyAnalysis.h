/////////////////////////////////////////////////////////////////////
// DependencyAnalysis.h                                            //
// Mengjie Shi                                                     //
// SUID: 457056896                                                 //
/////////////////////////////////////////////////////////////////////

#pragma once
#include "Key_Value_Table.h"
#include "Utilities.h"
#include <string>
#include <vector>

class DepAnal
{
public:
	std::vector<std::string> saveToken(std::string fullname);  // get token and save to a vector
	Element DepAnal::DepAnalyzer(std::vector<std::string> files);  //  compare the token with typetable and return the element
	bool savetoDb(Element elem, KeyValueTable&kvt);  //  save dependency to database
	DepAnal(std::string filewithfullname);
private:
	std::vector<std::string> tokVec;
	std::string _file;
	std::string _fullName;
};
