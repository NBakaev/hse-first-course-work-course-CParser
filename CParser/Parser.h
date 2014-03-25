#pragma once

#include <string>
#include "SimpleList.h"
#include "Node.h"

using namespace std;

class CParser
{
public:
	~CParser();
	// Url (http://site.com) or html inline //
	CParser(string url);

	auto getSublings(CNode* node)->vector<CNode*>;
	auto makeDOM()->void;
	auto getByTag(string tag)->vector<CNode*>;



	bool hasError = false;
	
	vector<CNode*> allTags;

private:
	CNode* rootNode = nullptr;
	string html;

	CParser();
	
};

