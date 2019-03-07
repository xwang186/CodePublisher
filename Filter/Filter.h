#pragma once
/////////////////////////////////////////////////////////////////////////////
// Filter.h - Filter file names using regex match                          //
// Author: Xiaohan Wang                                                    //
/////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains 2 files --Filter.h and Filter.cpp.
 * This package is designed to find matched files by their file names given.
 * To initialize the filter a regex value will be given.
 * To do the filter, use the function RegIt and provide the vector of the file names.
 *
 * Required Files:
 * ---------------
 * Filter.h  Filter.cpp
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 4 Feb 2019
 *
 */
#include<string>
#include<vector>
class Filter {
public:
	Filter(std::string reger);
	std::vector<std::string> RegIt(std::vector<std::string> &target);
private:
	std::string reg_;
};