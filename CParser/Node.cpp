#include "stdafx.h"
#include "Node.h"


CNode::CNode()
{
}


CNode::~CNode()
{
}

auto CNode::setDeep(int deep)->void{
	this->deep = deep;
}

auto CNode::setTagName(string tag)->void{
	this->tagName = tag;
}

auto CNode::getAttributes()->vector<map<string, string>>{
	return this->attributes;
}