#include "stdafx.h"
#include "Parser.h"
#include <vector>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <set>

#pragma comment(lib,"ws2_32.lib")


using namespace std;


auto CParser::getByTag(string tag) -> vector<CNode*>{

	vector<CNode*> result;
	vector<string> tagToFind;

	vector<string> t;
	string sr;

	for (int i = 0; i < tag.size(); i++){
		if (i == 0){ sr += tag[i]; }
			if (tag[i] == ' '){
				tagToFind.push_back(sr);
				sr.clear();
		}
	}

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
	int currentDeep = 0;

	vector<map<string, string>> NodeAttributes;
	map<string, string> s;

	string tempStringForAttributeName, tempStringForAttributeValue;
	bool onAttributeName = false, onAttributeValue = false;

	CNode* prevElement = nullptr;
	CNode* parentElement = nullptr;
	CNode* rootNode = nullptr;

	auto reversedAllTags = this->allTags;

	char currentChar = 0;
	char prevChar = 0;

	for (unsigned int i = 0; i < html.length(); i++){

		prevChar = currentChar;
		currentChar = html[i];

		/// If it is closed tag we shoud use parent Node
		if (!onAttributeName && !onAttributeValue && !onTagLocation && !onTagName && currentChar != '<' && currentChar != '>'){
			if (prevElement != nullptr){
				if (prevElement->tagName[0] == '/'){
					reversedAllTags = this->allTags;
					std::reverse(reversedAllTags.begin(), reversedAllTags.end());
					for (auto a : reversedAllTags){
						if (a->deep == currentDeep && a->tagName != "br/" &&  a->tagName != "br"){
							prevElement = a;
							break;
						}
					}
				}
				prevElement->innerText += currentChar;
			}
		}

		// If we are in tag and this thar is last
		if (onTagLocation && (currentChar == '>')){
			onTagName = false;
			onTagLocation = false;

			currentDeep++;

			if (prevChar == '/') currentDeep -= 1; //  <tagName "/">

			if (currentTag[0] == '/'){ // </...>
				currentDeep -= 1;
			}

			if (prevChar == '/' && currentTag == "br/") currentDeep++;

			CNode* node = new CNode();
			node->setTagName(currentTag);
			node->setDeep(currentDeep);
			node->attributes = NodeAttributes;

			if (currentTag == "br") {
				currentDeep--;
			}

			if (prevChar == '/'){
				currentDeep -= 1; //  <tagName "/">
				node->isSelfClosing = true;
			}
			
			if (currentTag[0] == '/'){ // </...>
				currentDeep -= 1;
			}

			if (prevElement == nullptr){
				// If it's root element
				if (rootNode == nullptr) rootNode = node;

				prevElement = node;
			}
			else{
				prevElement = node;
				// Not root element
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

		///HTML attribute
		if (onTagLocation && !onTagName){
			if (onAttributeValue && (currentChar == '"' || currentChar == '\'')){
				s[tempStringForAttributeName] = tempStringForAttributeValue;
				NodeAttributes.push_back(s);

				tempStringForAttributeName.clear();
				tempStringForAttributeValue.clear();

				s.clear();

				onAttributeName = false;
				onAttributeValue = false;
			}


			if (currentChar != ' ' && (currentChar != '"' && currentChar != '\'')){
				if (onAttributeValue && !onAttributeName) tempStringForAttributeValue += currentChar;
				if (onAttributeName && currentChar == '=') {
					i++;
				
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

	// Unclosed tag or one more closed tag
	if (currentDeep != 0) this->hasError = true;

}

///////////////////////////////////////////////////////////////// 


CParser::CParser(string url){
	// TODO: refactoring, not funny
	if (url[0] == 'h' && url[1] == 't' && url[2] == 't' && url[3] == 'p'){

		/// Get DATA from url
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			cout << "WSAStartup failed.\n";
		}
		
		string hostname;
		hostname = url.substr(7);
		string t, suburl;

		for (int i = 0; i < hostname.length(); i++){
			if (hostname[i] != '/') { t += hostname[i]; }
			else{
				suburl = hostname.substr(t.length() + 1);
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
		string s1 = "GET /" + suburl + " HTTP/1.1\r\nHOST: "+t+"\r\nConnection: close\r\n\r\n";

		send(Socket, s1.c_str(), strlen(s1.c_str()), 0);
		char buffer[10];
		int nDataLength;
		while ((nDataLength = recv(Socket, buffer, 10, 0)) > 0){
			int i = 0;
			while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
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

