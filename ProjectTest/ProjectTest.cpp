/////////////////////////////////////////////////////////////////////////////
// ProjectTest.cpp - FinalTest of the Project                              //
// Author: Xiaohan Wang                                                    //
/////////////////////////////////////////////////////////////////////////////
#ifdef TEST_PROJECT
#include "../Displayer/Displayer.h"
#include <direct.h>
#include "../Filter/Filter.h"
#include "../Convert/Convert.h"
#include <iostream>
#include "../DirExplorer-Naive/DirExplorerN.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/CodeUtilities/CodeUtilities.h"
using namespace FileSystem;
using namespace Utilities;
// -----< function getFilename to get the real name from the path >---------------
inline std::string getFilename(std::string target) {
	int pos = target.find_last_of('\\');
	std::string s(target.substr(pos + 1));
	return s;
}
int main(int argc, char *argv[])
{
	Title("Demonstrate DirExplorer-Naive, " + DirExplorerN::version());
	ProcessCmdLine pcl(argc, argv);
	preface("Command Line: ");
	pcl.showCmdLine();
	putline();

	DirExplorerN de(pcl.path());

	de.addPattern("*.cpp");
	de.addPattern("*.h");

	if (pcl.hasOption('s'))
	{
		de.recurse();
	}
	std::cout << "\nSeaching for files...\n";
	std::vector<std::string> filenames = de.getFiles();

	for (std::string m : filenames) {
		std::cout << m << "\n";
	}

	if (de.fileCount() == 0) {
		std::cout << "Didn't find any files, please check again";
	}
	de.showStats();
	Filter filter(argv[3]);
	std::cout << "\nFiltering using regex match...\n";
	std::vector<std::string> matches = filter.RegIt(filenames);
	if (matches.empty())
	{
		std::cout << "\nNo files matches by regex...\n Program stops.\n"; exit(1);
	}
	Convert convert;
	for (std::string i : matches) convert.ConvertIt(getFilename(i), i);

	char* path = _getcwd(NULL, 0);
	std::string currentPath;
	if (path == NULL)
	{
		std::cout << "\nError getting path using windows system call!\n";
		exit(0);
	}
	currentPath = path;
	std::cout << "\nDisplaying\n";
	Displayer displayer(currentPath + "./convertedPages");
	displayer.DisplayFiles();


	return 0;
}

#endif