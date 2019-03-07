#pragma once
/*
 * Package Operations:
 * -------------------
 * This package contains 2 files --Convert.h and Convert.cpp.
 * This package implements a function to convert a file into html file in a created folder "convertedPages"
 * To use this package, use the function ConvertIt to convert.
 * Two arguments should be given: first one is the target file name, the second one is the path that the file is under.
 *
 * Required Files:
 * ---------------
 * Convert.h  Convert.cpp
 *
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 4 Feb 2019
 *
 */
/////////////////////////////////////////////////////////////////////
// Convert.h                                                       //
//                                                                 //
// Xiaohan Wang, Jim Fawcett, Spring 2019                          //
/////////////////////////////////////////////////////////////////////

#include <string>
#include <list>
enum  OP_TYPE {OP_COMMON, OP_METHOD, OP_CLASS,OP_DIV };
class ConvOp {
private:
	OP_TYPE type;
	int lineNumber;
public:
	ConvOp(OP_TYPE t,int line);
	~ConvOp();
	bool operator<(const ConvOp& conv) const { return lineNumber < conv.lineNumber; }
	int getLineNumber() { return lineNumber; }
	int getType() { return type; }
};
class Convert {
public:
	Convert();
	void ConvertIt(const std::string& filename, std::string path);
	void ConvertIt2(const std::string& filename, std::string filepath);
private:
  std::string str_;
};
std::string ConvertUsingOperations(std::string filepath, std::list<ConvOp> p);


