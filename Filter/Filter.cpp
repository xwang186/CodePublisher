/////////////////////////////////////////////////////////////////////////////
// Filter.cpp - Filter file names using regex match                          //
// Author: Xiaohan Wang                                                    //
/////////////////////////////////////////////////////////////////////////////
#include "Filter.h"


Filter::Filter(std::string reger)
{
	reg_ = reger;
}
#include<regex>
#include<iostream>
// -----< function realFilename to get the real name from the path >---------------
std::string realFilename(std::string target) {
	int pos = target.find_last_of('\\');
	std::string s(target.substr(pos + 1));
	return s;
}
// -----< function RegIt to get the target vector filtered >---------------
std::vector<std::string> Filter::RegIt(std::vector<std::string> &target)
{
	std::vector<std::string> result;
	std::regex matcher(reg_);
	std::cout << "The regex is " << reg_ << "\n";
	for (std::string i: target) {
		if (regex_match(realFilename(i),matcher))
		{
			result.push_back(i);
		}
	}
	return result;
}
#ifdef TEST_FILTER_NO
int main() {
	std::cout << "In this test case we will test the filter to find all the files start with character C.\n";
	Filter filter("(C)(.*)");
	std::vector<std::string> target;
	target.push_back("C:\\Users\\Xiaohan Wang\\Desktop\\proj1_2\\proj1\\DirExplorer-Naive\\Convert.h");
	target.push_back("C:\\Users\\Xiaohan Wang\\Desktop\\proj1_2\\proj1\\DirExplorer-Naive\\Convert.cpp");
	target.push_back("C:\\Users\\Xiaohan Wang\\Desktop\\proj1_2\\proj1\\DirExplorer-Naive\\Process.h");
	target.push_back("C:\\Users\\Xiaohan Wang\\Desktop\\proj1_2\\proj1\\DirExplorer-Naive\\Process.cpp");
	std::vector<std::string> result= filter.RegIt(target);
	for (std::string i : result) {
		std::cout << i << "\n";
	}
}
#endif
