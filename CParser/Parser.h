#pragma once

#include <string>
#include <regex>;

#include "SimpleList.h"

#include "Node.h"

using namespace std;


class CParser
{
public:
	CParser();
	~CParser();
	
	CParser(string url);

	

	string getHTMLfromHTTP(string url);

	auto makeDOM() -> void;

	vector<CNode*> allTags;


	string getBody();
	//sregex_iterator getByTag(string tag);


	/*auto getByTag(string tag)->vector<CNode*>;
	auto getByTagWithContext(string tag, string html)->vector<CNode*>;
*/

	auto getByTag(string tag)->vector<CNode*>;
	//auto getByTagWithContext(string tag, string html)->vector<string>;
	//auto getPointerByTag(string tag)->CNode*;


	sregex_iterator getNullIterator();

	string html;



private:

	sregex_iterator iteratorEnd;
	
	CNode* rootNode = nullptr;

	//eventually
	//string html;

	auto CParser::getContentFromURL(string url)->string;


};

