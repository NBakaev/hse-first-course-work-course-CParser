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
	auto getContent(CNode*)->string;
	
	
	auto setTagName(string tag)->void;
	auto setTagAttributes(vector<string> attributes) -> void;
	auto addParent(CNode* p) ->void;
	auto addChildren(CNode* p) ->void;

	auto getClass()->string;
	auto getId()->string;

	int deep=0;

	auto setDeep(int d) -> void;
	
	//CNode(string tagName,);

	string tagName;

	auto getAttributes()->vector<map<string, string>>;
	vector<map<string, string>> attributes;

private:
	
	
	string classHTML;
	string idHTML;

	CNode* parent;
	vector<CNode*> childrens;

	vector<CNode*> siblings;

	//TODO: Attributes


};

