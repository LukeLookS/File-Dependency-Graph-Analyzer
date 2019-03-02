#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class Utilities
{
public:
	void Utilities::split(const std::string &s, char delim, std::vector<std::string> &elems)
	{
		std::string temp;
		for (size_t i = 0; i < s.size(); i++)
		{
			if (s.at(i) != delim)
			{
				temp.append(s, i, 1);
				if (i == s.size() - 1)
					elems.push_back(temp);
			}
			else if (temp != "")
			{
				elems.push_back(temp);
				temp = "";
			}
		}
	}


	unsigned Utilities::findmember(std::vector<std::string> v, std::string target)
	{
		if (v.size() == 0)  //  vector is empty
			return 0;
		unsigned c;
		for (c = 0; c < v.size(); c++)
		{
			if (v[c] == target)
			{
				c++;  //  in order to make a judgement
				break;
			}
		}
		if (v[c - 1] != target)
			return 0;  //  target does not exsit in v
		return c;  //  return the result
	}

	std::string Utilities::toString(int &t)
	{
		std::ostringstream out;
		out.precision(8);
		out << *const_cast<int*>(&t);
		return out.str();
	}

	std::string Utilities::toString(unsigned &n)
	{
		std::ostringstream out;
		out.precision(8);
		out << *const_cast<unsigned*>(&n);
		return out.str();
	}
};
