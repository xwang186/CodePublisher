/////////////////////////////////////////////////////////////////////////////
// Displayer.cpp - Display the html files in one folder                    //
// Author: Xiaohan Wang                                                    //
/////////////////////////////////////////////////////////////////////////////
#include "Displayer.h"
#include "../Process/Process.h"
#include "../FileSystem/FileSystem.h"
#include <iostream>

Displayer::Displayer(std::string folderpath)
{
	path_ = folderpath;
}
// -----< function DisplayFiles to display a folder >---------------
using namespace FileSystem;
void Displayer::DisplayFiles() {
	
	Process p;
	std::string appPath = "C:/Program Files (x86)/Google/Chrome/Application/chrome.exe";
	p.application(appPath);
	std::string cmdLine = "/A ";
	std::vector<std::string> files = FileSystem::Directory::getFiles("../convertedPages","*.*");
	for (std::string f : files) {
		p.commandLine(cmdLine + "\"" + path_+"/" + f+"\"");
		p.create();
		CBP callback = []() { std::cout << "\n  --- child process exited with this message ---"; };
		p.setCallBackProcessing(callback);
		p.registerCallback();
		WaitForSingleObject(p.getProcessHandle(), INFINITE);  // wait for created process to terminate
	}
}
#ifdef TEST_DISPLAYER_NO
#include <direct.h>
int main() {
	char* path = _getcwd(NULL, 0);
	std::string currentPath;
	if (path == NULL)
	{
		std::cout << "\nError getting path using windows system call!\n";
		exit(0);
	}
	currentPath = path;
	Displayer displayer(currentPath+"/displayerTestFiles");
	displayer.DisplayFiles();
	return 0;
}
#endif