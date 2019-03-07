/////////////////////////////////////////////////////////////////////
// Convert.cpp                                                     //
//                                                                 //
// Xiaohan Wang, Jim Fawcett, Spring 2019                          //
/////////////////////////////////////////////////////////////////////

#include <regex>
#include "Convert.h"


#include <fstream>
#include <iostream>

#include <sstream>
#include "../FileSystem/FileSystem.h"
#include"../AbstractSyntaxTree/AbstrSynTree.h"
#define COMMENTS_HEADER "<div class=\"toggleCommentDisplay\">"
#define CLASS_HEADER "<div class=\"toggleClassDisplay\">"
#define METHOD_HEADER "<div class=\"toggleMethodDisplay\">"
#define DIV_TEMP "</div>"
using namespace std;
using namespace CodeAnalysis;
// -----< function replacement to replace one elmenet in a string with anthor element >---------------
string& replacement(string& str, const string& old_value, const  string& new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length())
	{
		if ((pos = str.find(old_value, pos)) != string::npos)
		{
			str.replace(pos, old_value.length(), new_value);
		}
		else { break; }
	}
	return   str;
}
std::list<ConvOp> getTree(std::string filepath);
void TreeWalkSet(CodeAnalysis::ASTNode* pItem, std::list<ConvOp> &l);
// -----< function WriteTemplete write html headers and ends to a content, and highlight the file name >---------------
string writeTemplate(string content,string filename) {
	ifstream head("templateHead.txt");
	ifstream end("templateEnd.txt");
	if (!head.is_open()|| !end.is_open())
	{
		cout << "Error opening head or end file!"; exit(1);
	}
	stringstream bufferH;
	bufferH << head.rdbuf();
	stringstream bufferE;
	bufferE << end.rdbuf();
	string result = bufferH.str()+"<h3>" + filename +"</h3>"+content+bufferE.str();
	return result;
}

Convert::Convert()
{
}
#include<direct.h>
#include<conio.h>

// -----< function ConvertIt to do all the jobs of translating one file into html format >---------------
void Convert::ConvertIt2(const std::string& filename,std::string filepath)
{
	std::cout << "Converting " << filename << "...\n";
	stringstream buffer;
	ifstream in(filepath);
	string foldername = "convertedPages";
	int t=_mkdir(foldername.c_str());
	char* path = _getcwd(NULL, 0);
	string currentPath;
	if (path==NULL)
	{
		std::cout << "\nError getting path using windows system call!\n";
		exit(0);
	}
	currentPath = path;

	ofstream out(currentPath+"\\convertedPages\\"+filename+".html");
	if (!in.is_open())
	{
		cout << "Error opening file"<<filename << " from "<<filepath; 
	}
	
	if (!out.is_open())
	{
		cout << "Error Creating file"<<filename; 
	}
	buffer << in.rdbuf();
	in.close();
	string contents = buffer.str();
	std::cout << "Initializing content of file "<< filename <<".html"<<endl;
	//contents = replacement(contents, "<", "&lt");
	//contents = replacement(contents, ">", "&gt");
	//contents = replacement(contents, "\n", "<br>");
	contents = "<pre>" + contents + "</pre>";
	contents = writeTemplate(contents,filename);
	out << contents; 
	std::cout << "File " << filename << ".html has been generated!" << endl;
	out.close();
}

void Convert::ConvertIt(const std::string& filename, std::string filepath)
{
	std::cout << "Converting " << filename << "...\n";
	string foldername = "convertedPages";
	int t = _mkdir(foldername.c_str());
	char* path = _getcwd(NULL, 0);
	string currentPath;
	if (path == NULL)
	{
		std::cout << "\nError getting path using windows system call!\n";
		exit(0);
	}
	currentPath = path;

	ofstream out(currentPath + "\\convertedPages\\" + filename + ".html");
	if (!out.is_open())
	{
		cout << "Error Creating file" << filename;
	}
	
	std::list<ConvOp> myList =getTree(filepath);
	cout <<"file path is "<< filepath << endl;
	std::cout << "myList size is " << myList.size() << endl;
	ConvOp op = myList.front();
	std::cout << "myList first type is " << op.getLineNumber() << endl;
	string contents = ConvertUsingOperations(filepath, myList);
	std::cout << "Initializing content of file " << filename << ".html" << endl;
	//contents = replacement(contents, "<", "&lt");
	//contents = replacement(contents, ">", "&gt");
	//contents = replacement(contents, "\n", "<br>");
	contents = "<pre>" + contents + "</pre>";
	contents = writeTemplate(contents, filename);
	out << contents;
	std::cout << "File " << filename << ".html has been generated!" << endl;
	out.close();
}
bool compare_nocase( ConvOp op1, ConvOp op2){
	return (op1.getLineNumber() < op2.getLineNumber());
}
std::string ConvertUsingOperations(std::string filepath, std::list<ConvOp> p)
{
	stringstream buffer;
	p.sort(compare_nocase);
	ifstream in(filepath);	
	if (!in.is_open())
	{
		cout << "Error opening file" << filepath << " from " << filepath;
	}
	std::string line;
	int number=1;
	ConvOp *op=NULL;
	if (!p.empty())
	{
		op = &(p.front());
		std::cout << "OP TYPE IS :"<<op->getType() << endl;
	}
	while (getline(in, line)) // line中不包括每行的换行符
	{
		buffer << line << endl;
		if (op!=NULL) {
			while (number == op->getLineNumber())
			{
				string newLine;
				switch (op->getType())
				{
				case OP_DIV:
					newLine = DIV_TEMP;
					break;
				case OP_COMMON:
					newLine = COMMENTS_HEADER;
					break;
				case OP_CLASS:
					newLine = CLASS_HEADER;
					break;
				case OP_METHOD:
					newLine = METHOD_HEADER;
					break;
				default:
					newLine = "";
					break;
				}
				std::cout << "ADDing new LIne: " << newLine << endl;
				buffer << newLine << endl;
				p.pop_front();
				if (p.empty()) {
					op = NULL;
					break;
				}
				else {
					op = &(p.front());
				}
			}
		}
		number++;
	}


	return buffer.str();
}
#ifdef TEST_CONVERT  // only compile the following when defined
int main() {
	Convert con;
	
	char* path = _getcwd(NULL, 0);
	string currentPath;
	if (path == NULL)
	{
		std::cout << "\nError getting path using windows system call!\n";
		exit(0);
	}
	currentPath = path;
	con.ConvertIt( "Convert.cpp", currentPath+"\\Convert.cpp");
	std::cout << "Convert Finished!";
	return 0;
}
#endif

ConvOp::ConvOp(OP_TYPE t, int line)
{
	this->type = t;
	this->lineNumber = line;
}
ConvOp::~ConvOp()
{
}
#include "../Parser/Parser.h"
#include "../Parser/ConfigureParser.h"

std::list<ConvOp> getTree(std::string filepath) {
	ConfigParseForCodeAnal configure;
	std::string fileSpec = FileSystem::Path::getFullFileSpec(filepath);
	Parser* pParser = configure.Build();
	std::string name;
	ASTNode* pGlobalScope=NULL;
	std::list<ConvOp> opList;
	try {
		if (pParser)
		{
			name = FileSystem::Path::getName(fileSpec);
			std::cout << "name is " << name << "\n";
			if (!configure.Attach(fileSpec))
			{
				std::cout << "\n  could not open file " << name << std::endl;
			}
		}
		else
		{
			std::cout << "\n\n  Parser not built\n\n";
		}
		Repository* pRepo = Repository::getInstance();
		pRepo->package() = name;
		while (pParser->next())
		{
			pParser->parse();
		}
		std::cout << "\n";

		// final AST operations
		pGlobalScope = pRepo->getGlobalScope();
		// walk AST, computing complexity for each node
		// and record in AST node's element
		complexityEval(pGlobalScope);

		// Walk AST, displaying each element, indented
		// by generation

		TreeWalkSet(pGlobalScope,opList);
		cout << " Value is " << opList.front().getLineNumber() << endl;
	}
		catch (std::exception & ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
			std::cout << "\n  exception caught at line " << __LINE__ << " ";
			std::cout << "\n  in package \"" << name << "\"";
		}
		std::cout << "\n";
		return opList;
}
 void TreeWalkSet(ASTNode* pItem,std::list<ConvOp> &oplist)
{
	std::list<ConvOp*> myList;
	static std::string path;
	static size_t indentLevel = 0;
	//int lineNumber = pItem->startLineCount_;
	if (pItem->type_ == "class") {
		ConvOp m1(OP_CLASS,pItem->startLineCount_);
		oplist.push_back(m1);
		ConvOp m2(OP_DIV, pItem->endLineCount_);
		oplist.push_back(m2);
	}
	else if (pItem->type_ == "function") {
		ConvOp m1(OP_METHOD, pItem->startLineCount_);
		oplist.push_back(m1);
		ConvOp m2(OP_DIV, pItem->endLineCount_ );
		oplist.push_back(m2);
	}

	auto iter = pItem->children_.begin();
	++indentLevel;
	while (iter != pItem->children_.end())
	{
		TreeWalkSet(*iter,oplist);
		++iter;
	}
	--indentLevel;
	return ;
}