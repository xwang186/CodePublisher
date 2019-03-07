## How to test this project

Download and Test.

Run MyProject.sln in visual studio to see the package structure.

If you are not using visual studio 2019 preview, please right click the solution and choose "Retarget Solution"

The default path for chrome is in (x86) folder.

To test each package, find the cpp file names same as the package. There will be sub-main functions for each package. To invoke those sub-main functions, please modify the pre definations.

For example, if you want to test package "Displayer", here is the sub-main function:

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

simply change  TEST_DISPLAYER_NO to TEST_DISPLAYER, then set the package as the target project, change the output type to exe instead of "lib", then the sub project will be executable.

