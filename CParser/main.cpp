#include "stdafx.h"
#include <regex>;
#include <string>
#include <iostream>
#include "Parser.h"
#include "SimpleList.h"

using namespace std;

auto main() -> int
{

	//auto parser = *new CParser("<html> start html <head> inside head </head> <body> <div insideDIV1 /> <div SecondInner2 /><div> inside DIV3 </div>BodyText</body>before close html</html> <div ll> third div4</div> ");
	auto parser = *new CParser("http://localhost/index.html");
	
	cout << "\n";
	/*
	cout << parser.getBody();
	cout <<  parser.getBody();

	sregex_iterator iterator = parser.getByTag("");
	sregex_iterator i;
	
	
	while (iterator != parser.getNullIterator())
	{
		cout << iterator->str();
		++iterator;
	
	auto myList = parser.getByTagString("div");
	while (myList.hasNext()){
		cout << myList.getValue() << "\n";
	}
	cout << parser.getByTagString("div");
	for (auto s : myList){
		cout << s << "\n";
	}
	parser.makeDOM();*/

	//cout << "html inline" << parser.html;

	cout << "\n";
	cout << "+++++++++ Printing DOM - All tags +++++++++\n";

	for (auto a : parser.allTags){
		
		for (int i = 0; i < a->deep; i++) cout << " ";
		cout << a->tagName << "<" << a->deep << ">";
			cout << "\n";
	}
	cout << "+++++++++ END +++++++++\n";

	cout << "\n\n";


	string tagToFind = "div";

	cout << "+++++++++ Finding in DOM by tag: \"" << tagToFind <<"\" +++++++++\n";
	
	for (auto a : parser.getByTag(tagToFind)){
		cout << "Tag name: " << a->tagName;
		cout << "\n  " << "Attributes: ";

		for (auto m : a->getAttributes()){
			
			

			for (auto ii = m.begin(); ii != m.end(); ii++)cout <<"\n    " << ii->first << ":" << ii->second;

			//cout << "Name: " << b[0] << "Value: " << b[1];

		//	cout << " | ";
		}

		cout << "\n" << "----------------------" << "\n";

	}





	cout << "\n";
	

	//cout << "\n\n\nhtml" << parser.html;

	return 0;

}