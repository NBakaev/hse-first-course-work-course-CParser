#include "stdafx.h"
#include "Parser.h"
#include "SimpleList.h"
#include <vector>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#pragma comment(lib,"ws2_32.lib")


using namespace std;




auto CParser::getByTag(string tag) -> vector<CNode*>{

	vector<CNode*> result;
	vector<string> tagToFind;


	//TODO
	// "tag1 tag2 tag3"

	// govnokod //

	vector<string> t;
	string sr;

	for (int i = 0; i < tag.size(); i++){
		
		if (i == 0){ sr += tag[i]; }
		
		if (tag[i] == ' '){

			tagToFind.push_back(sr);
			sr.clear();

		}


	}


	//////////////////////

	for (int i = 0; i < tagToFind.size(); i++){
		//this->getByTag(tagToFind.)
		// надо взять первый элемент

	}
	//////////////////////


	for (auto r : this->allTags){
		if (r->tagName == tag) result.push_back(r);

	}


	return result;
}





auto CParser::makeDOM() -> void{

	string html = this->html;
	
	bool onTagName = false;
	bool onTagLocation = false;
	string currentTag;

	int currentDeep=0;


	vector<map<string, string>> NodeAttributes;
	map<string, string> s;


	string tempStringForAttributeName, tempStringForAttributeValue;
	bool onAttributeName=false, onAttributeValue=false;

	CNode* prevElement=nullptr;
	CNode* parentElement = nullptr;
	CNode* rootNode = nullptr;
	
	char currentChar=0;
	char prevChar=0;

	for (unsigned int i = 0; i < html.length() ; i++){

		prevChar = currentChar;
		 currentChar = html[i];

		 // If we are in tag and this thar is last
		if ( onTagLocation && (currentChar=='>')){
			onTagName = false;
			onTagLocation = false;

			//if (rootNode != nullptr)
			currentDeep++;

			//TODO It can be <tagName .. / > ????? but not often
			if (prevChar == '/') currentDeep-=1; //  <tagName "/">


			if (currentTag[0] == '/'){ // </...>
				currentDeep-=1;
			}
			else {  }


			CNode* node = new CNode();
			node->setTagName(currentTag);
			node->setDeep(currentDeep);
			node->attributes = NodeAttributes;


			//////////////// one more time #1    /////////////////////////
			if (prevChar == '/') currentDeep -= 1; //  <tagName "/">


			if (currentTag[0] == '/'){ // </...>
				currentDeep -= 1;
			}
			else {}
			//////////////// one more time #2    /////////////////////////






			if (prevElement == nullptr){
				// If it's root element
				if (rootNode == nullptr) rootNode = node;

				
				prevElement = node;
			}
			else{
				// Not root element

				if (prevElement->deep == node->deep){
					// Here if current element is subling with some other
					//parentElement->addChildren(node);
					//node->deep = parentElement->deep;
				}
				else{
					// If it's a children 
				}
			}

			this->allTags.push_back(node);
			currentTag.clear();
		}


		//////////////////////////////////////////////////////////////////////////
		if (onTagName){

			if (currentChar == ' '){
				onTagName = false;
			}
			else{
				currentTag += currentChar;
			}
		}

		
		if (currentChar == '<'){
			onTagName = true;
			onTagLocation = true;

			NodeAttributes.clear();
		}

		/// Some HTML attribute ????



		if (onTagLocation && !onTagName){

			if (onAttributeValue && (currentChar == '"' ||  currentChar=='\'')){
				s[tempStringForAttributeName] = tempStringForAttributeValue;
				NodeAttributes.push_back(s);

				tempStringForAttributeName.clear();
				tempStringForAttributeValue.clear();

				s.clear();

				onAttributeName = false;
				onAttributeValue = false;
			}


			if (currentChar != ' ' && (currentChar != '"' && currentChar != '\'')){
				

				if (onAttributeValue && !onAttributeName){ tempStringForAttributeValue += currentChar; }

				if (onAttributeName && currentChar == '=') {
					i++;
					//break;
					onAttributeValue = true;
					onAttributeName = false;

				}
				else{


					if (onAttributeValue == false){
						onAttributeName = true;
						tempStringForAttributeName += currentChar;
					}
					}

			}
		

		}




	}


	/*if (rootNode != nullptr)
	rootNode->deep = rootNode->deep--;*/


}


/////////////////////////////////////////////////////////////////   Not Interesring


CParser::CParser(string url){

	if (url[0] == 'h' && url[1] == 't' && url[2] == 't' && url[3] == 'p'){


		////// Get from url

		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			cout << "WSAStartup failed.\n";
	//		system("pause");
//			return 1;
		}

		//std::string str;
		//const char * c = str.c_str();

	//	url = "ibakaev.ru";

		string hostname;
	
			hostname=url.substr(7);

			string t,suburl;

			for (int i = 0; i < hostname.length(); i++){
				if (hostname[i] != '/') { t += hostname[i]; }
				else{
					suburl = hostname.substr(t.length() +1);
					break;
				}
			}

			/// t - real hostname ( "localhost")
			/// suburl - all after / "localhost/blabla"

		SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		struct hostent *host;
		host = gethostbyname(t.c_str());
		SOCKADDR_IN SockAddr;
		SockAddr.sin_port = htons(80);
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
		if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0){
			cout << "Could not connect";
		}
		string result;
		string s1 = "GET /"+suburl+" HTTP/1.1\r\nHOST: localhost\r\nConnection: close\r\n\r\n";

		send(Socket, s1.c_str(), strlen(s1.c_str()), 0);
		char buffer[10];
		int nDataLength;
		while ((nDataLength = recv(Socket, buffer, 10, 0)) > 0){
			int i = 0;
			while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
				//cout << buffer[i];
				result += buffer[i];
				i += 1;
			}
		}
		closesocket(Socket);
		WSACleanup();
		url = result;
	}

	url.erase(url.find_last_not_of(" \n\r\t") + 1); // trim
	url.erase(std::remove(url.begin(), url.end(), '\t'), url.end());

	this->html = url;
	this->makeDOM();

}

CParser::CParser()
{
}


CParser::~CParser()
{
}



///////////// ===================== TRASH



//
//auto CParser::makeDOM() -> void{
//	
//	////////////////////
//	
//	//| <" + tag + "[^]*/>
//
//	string tag = "div";
//
//	regex bodyRegExp("(<" + tag + " (.*)" + ">(.*)</" + tag + ">) | (<" + tag + "(.*)/>)");
//
//	string str = this->html;
//	sregex_iterator it(str.begin(), str.end(), bodyRegExp);
//	sregex_iterator it_end;
//
//	vector<string> s;
//
//	while (it != it_end){
//
//		////////// Here are all html tags
//
//
//
//
//		//cout << "|||New expression||||";
//		//list.append(it->str());
//
//		//s.push_back(it->str());
//
//		cout << it->str();
//
//		++it;
//	}
//
//
//	///////////////
//
//
//
//
//
//
//	if (this->rootNode == nullptr){
//
//		CNode* myRootNode = this->getPointerByTag("html");
//
//	}
//
//
//
//
//
//
//}


//string CParser::getBody(){
//
//	regex bodyRegExp("(<body>[^]*</body>)");
//
//	string str = this->html;
//	sregex_iterator it(str.begin(), str.end(), bodyRegExp);
//	sregex_iterator it_end;
//	return it->str();
//}



//auto CParser::getByTagWithContext(string tag,string html) -> vector<string>{
//
//	//| <" + tag + "[^]*/>
//	regex bodyRegExp("(<" + tag + " (.*)" + ">(.*)</" + tag + ">) | (<" + tag + "(.*)/>)");
//
//		string str = this->html;
//		sregex_iterator it(str.begin(), str.end(), bodyRegExp);
//		sregex_iterator it_end;
//
//		vector<string> s;
//
//		while (it != it_end){
//	//cout << "|||New expression||||";
//		//list.append(it->str());
//			
//	s.push_back(it->str());
//			++it;
//		}
//
//	return s;
//}
