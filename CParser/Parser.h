#pragma once

#include <string>
#include "Node.h"
using namespace std;

class CParser
{
public:
	~CParser();
	// Url (http://localhost) or html inline //
	CParser(string url);

	auto makeDOM()->void;
	auto getByTag(string tag)->vector<CNode*>;


	bool hasError = false;
	
	vector<CNode*> allTags;


private:
	CNode* rootNode = nullptr;
	string html;

	CParser();
	
};

