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

	//auto parser = *new CParser("<html> start html <head> inside head </head> <body> <div insideDIV1 /> <div SecondInner2 /><div> inside DIV3 </div>BodyText</body>before close html</html> <div ll> third div4</div> ");
	auto parser = *new CParser("http://localhost/index.html");
	//auto parser = *new CParser("http://habrahabr.ru");


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


	//auto a = CParser
	//auto parser = *new CParser("http://habrahabr.ru");


	cout << "\n\n\n";
	cout << "All tags\n";

	for (auto a : parser.allTags){
		//cout << a << "\n";
		
		for (int i = 0; i < a->deep; i++) cout << " ";

		cout << a->tagName << "<" << a->deep << ">";

			cout << "\n";

	}


	//////////
	
	cout << "\n\n\n\n finding....\n";
	
	for (auto a : parser.getByTag("li")){
		cout << a->tagName << "\n";

	}





	cout << "\n";
	

	//cout << "\n\n\nhtml" << parser.html;


	return 0;

}