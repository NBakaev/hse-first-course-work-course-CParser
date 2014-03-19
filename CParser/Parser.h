#pragma once

#include <string>
#include "SimpleList.h"
#include "Node.h"

using namespace std;

class CParser
{
public:
	//CParser();
	~CParser();

	// Url (http://site.com) or html inline //
	CParser(string url);





	auto makeDOM()->void;
	auto getBody()->string;
	auto getByTag(string tag)->vector<CNode*>;
	

	

	string html;
	vector<CNode*> allTags;


private:
	CNode* rootNode = nullptr;


	CParser();

	//eventually
	//string html;

	
};

