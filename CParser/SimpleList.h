#pragma once

using namespace std;

#include <string>


struct SimpleListElement
{
string value;
SimpleListElement* nextAdress=NULL;
SimpleListElement* prevAdress = NULL;
};

class SimpleList
{
private:
	int length=0;
	SimpleListElement* firstAdress;
	SimpleListElement* lastAdress;
	SimpleListElement tempCur;
	SimpleListElement tempCur2;

	SimpleListElement myTemp;
	SimpleListElement myElement ;
	SimpleListElement* prevElement;

	SimpleListElement* forDeletingPrevElement;
	SimpleListElement* forDeletingNextElement;

	int temp;


	int curIterator=0;
	SimpleListElement* currIteratorAdress=NULL;
	SimpleListElement* currIteratorAdress2 = NULL;
	SimpleListElement* currIteratorAdress3 = NULL;


public :
	bool hasNext();
	string getValue();
	

	SimpleList();
	~SimpleList();

	int getLength();

	void SimpleList::pop(int a); // From beginning

	int SimpleList::getValueByNumberOrderByBeginning(int number);
	int SimpleList::getValueByNumberOrderByEnd(int number);

	 void append(string el);
	void appendToBeginning(int a);
	void appendAfter(int a,int b);



};


