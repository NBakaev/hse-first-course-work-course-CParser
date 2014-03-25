#pragma once

#include <vector>
#include <map>


using namespace std;


class CNode
{
public:
	CNode();
	~CNode();

	auto getChildrens(CNode*)->vector<CNode*>;
	auto getSiblings(CNode*) ->vector<CNode*>;
	
	auto setTagName(string tag)->void;
	auto setTagAttributes(vector<string> attributes) -> void;
	auto addParent(CNode* p) ->void;
	auto addChildren(CNode* p) ->void;
	auto getAttributes()->vector<map<string, string>>;
	auto setDeep(int d) -> void;
	

	int deep=0;
	string tagName;
	vector<map<string, string>> attributes;
	string innerText;

private:
	
	
	string classHTML;
	string idHTML;
	CNode* parent;
	vector<CNode*> childrens;
	vector<CNode*> siblings;
	//TODO: Attributes


};

