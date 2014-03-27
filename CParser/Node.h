#pragma once

#include <vector>
#include <map>


using namespace std;


class CNode
{
public:
	CNode();
	~CNode();

	auto setTagName(string tag)->void;
	auto setTagAttributes(vector<string> attributes) -> void;
	auto getAttributes()->vector<map<string, string>>;
	auto setDeep(int d) -> void;
		
	bool isSelfClosing = false;

	int deep=0;
	string tagName;
	vector<map<string, string>> attributes;
	string innerText;

private:
	
	
	string classHTML;
	string idHTML;
	
};

