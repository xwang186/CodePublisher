#ifndef DISPLAYER_H
#define DISPLAYER_H

#pragma once

/////////////////////////////////////////////////////////////////////////////
// Displayer.h   - Display the html files in one folder                    //
// Author: Xiaohan Wang                                                    //
/////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains 2 files --Displayer.h and Displayer.cpp.
 * This package implements a function to display all the files from one folder on chrome browser.
 * One arguments should be given: The target folder's path.
 *
 * Required Files:
 * ---------------
 * Displayer.h  Displayer.cpp
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 4 Feb 2019
 *
 */

#include<string>
class Displayer {
public:
	Displayer(std::string folderpath);
	void DisplayFiles();
private:
	std::string path_;
	
};
#endif