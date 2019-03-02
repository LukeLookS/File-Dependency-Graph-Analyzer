/////////////////////////////////////////////////////////////////////
// Key Value Table.h                                               //
// Mengjie Shi                                                     //
// SUID: 457056896                                                 //
/////////////////////////////////////////////////////////////////////

#pragma once
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>

#include "Utilities.h"

using Key = std::string;
using Keys = std::vector<Key>;

class Element
{
public:
	Element() {}
	std::string key;
	std::vector<std::string> filenames; // metadata
	std::string show();
};

inline std::string Element::show()  //  print the element
{
	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	std::vector<std::string> filenames_ = static_cast<std::vector<std::string>>(filenames);
	if (filenames_.size() == 0)
	{
		out << "\n  " << "Children" << " : " << "NULL";
	}

	if (filenames_.size() > 0)
	{
		out << "\n  " << "Children" << " : ";
		for (size_t i = 0; i < filenames_.size(); ++i)
		{
			out << filenames_[i];
			if (i < filenames_.size() - 1)
				out << ", ";
		}
	}
	out << "\n";
	return out.str();
}

class KeyValueTable
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;

	Keys keys();
	bool hasKey(Key key);
	bool saveRecord(Key key, Element elem);
	size_t count();
	Element value(Key key);
	//unsigned findmember(std::vector<std::string> v, std::string target);

private:
	using Item = std::pair<Key, Element>;
	std::unordered_map<Key, Element> store;
};

inline KeyValueTable::Keys KeyValueTable::keys()
{
	Keys keys;
	for (Item item : store)
		keys.push_back(item.first);
	return keys;
}

inline bool KeyValueTable::hasKey(Key key)
{
	if (store.find(key) == store.end())
		return false;
	return true;
}

inline bool KeyValueTable::saveRecord(Key key, Element elem)
{
	if (store.find(key) != store.end())
		store[key].filenames.push_back(elem.filenames[0]);
	else
		store[key] = elem;  //  save the unordered map
	return true;
}

inline Element KeyValueTable::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return Element();
}

inline size_t KeyValueTable::count()
{
	return store.size();
}


