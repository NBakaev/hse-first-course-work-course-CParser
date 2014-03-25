#include "stdafx.h"
#include <string>
#include <iostream>
#include "Parser.h"
#include "SimpleList.h"

using namespace std;

auto main() -> int
{
	//auto parser = *new CParser("<html> start html <head> inside head </head> <body> <div insideDIV1 /> <div SecondInner2 /><div> inside DIV3 </div>BodyText</body>before close html</html> <div ll> third div4</div> ");
	auto parser = *new CParser("http://localhost/index.html");	
	cout << "\n\n";

	cout << "+++++++++ Printing DOM - All tags +++++++++\n";

	for (auto a : parser.allTags){
		for (int i = 0; i < a->deep; i++) cout << " ";
			cout << a->tagName ;
			cout << "\n";
	}
	cout << "+++++++++ END +++++++++\n";
	cout << "\n\n";
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n";
	cout << "+++++++++ Printing DOM - All tags with inner text +++++++++\n";

	for (auto a : parser.allTags){
		for (int i = 0; i < a->deep; i++) cout << " ";
			cout << a->tagName << "<" << a->deep << ">" << "<<< " << a->innerText << " >>>";
			cout << "\n";
	}
	cout << "+++++++++ END +++++++++\n";
	cout << "\n\n";
//////////////////////////////////////////////////////////////////////////////////////////////////////////


	string tagToFind = "div";

	cout << "+++++++++ Finding in DOM by tag: \"" << tagToFind <<"\" +++++++++\n";
	
	for (auto a : parser.getByTag(tagToFind)){
		cout << "Tag name: " << a->tagName;
		cout << "\n  " << "Attributes: ";

		for (auto m : a->getAttributes()){
			for (auto ii = m.begin(); ii != m.end(); ii++)cout <<"\n" << ii->first << "=" << ii->second;
		}
		cout << "\n" << "----------------------" << "\n";
	}

	/*string tagToFind = "div div";

	cout << "+++++++++ Finding in DOM by complex tag: \"" << tagToFind << "\" +++++++++\n";

	for (auto a : parser.getByTag(tagToFind)){
		cout << "Tag name: " << a->tagName;
		cout << "\n  " << "Attributes: ";

		for (auto m : a->getAttributes()){
			for (auto ii = m.begin(); ii != m.end(); ii++)cout << "\n    " << ii->first << "=" << ii->second;


		}

		cout << "\n" << "----------------------" << "\n";

	}*/



/*
	string sublingTag = parser.getByTag("div").pop_back;

	cout << "+++++++++ Finding sublings in DOM by tag: \"" << sublingTag << "\" +++++++++\n";

	for (auto a : parser.getSublings(tagToFind)){
		cout << "Tag name: " << a->tagName;
		cout << "\n  " << "Attributes: ";

		for (auto m : a->getAttributes()){
			for (auto ii = m.begin(); ii != m.end(); ii++)cout << "\n    " << ii->first << "=" << ii->second;


		}

		cout << "\n" << "----------------------" << "\n";

	}
*/


	if (parser.hasError) cout << "Has an error!!";




	cout << "\n";
	
	return 0;

}