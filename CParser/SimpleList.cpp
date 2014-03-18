#include "stdafx.h"
#include "SimpleList.h"

#include <regex>

using namespace std;



///////////////////////////////////////////////////////////////////////

int SimpleList::getLength(){
	return length;
}

auto SimpleList::hasNext() -> bool{
	return (length > curIterator) ? true : false;
}

SimpleList::SimpleList()
{
}
SimpleList::~SimpleList()
{
}

///////////////////////////////////////////////////////////////////////


void SimpleList::append(string element){
	

	SimpleListElement*  myElement = new SimpleListElement;
	
	myElement -> value = element;

	if (length == 0 ){
	
		firstAdress = myElement;	
		lastAdress = myElement;
		myElement -> nextAdress = myElement;
		currIteratorAdress = myElement;
	}
	else{
				
		SimpleListElement* myTemp = lastAdress;
		myTemp ->nextAdress  = myElement;		

		myElement->prevAdress = lastAdress;

		lastAdress = myElement;
	
	}

	length++;
}



string SimpleList::getValue(){

tempCur = *currIteratorAdress;
if (  tempCur.nextAdress != NULL)
currIteratorAdress = tempCur.nextAdress;
curIterator++;

	return tempCur.value;

}




void SimpleList::pop(int number){

	
	currIteratorAdress = firstAdress;

	for (int i = 1; i < number+2; i++){

		
		tempCur = *currIteratorAdress;

		if (i == number -1) { forDeletingPrevElement = currIteratorAdress; }
		if (i == (number+1) ) forDeletingNextElement = currIteratorAdress;
if (tempCur.nextAdress != NULL) currIteratorAdress = tempCur.nextAdress;
		
	}

	// Magic :)
	SimpleListElement* myTempDel = forDeletingPrevElement;
	myTempDel->nextAdress = forDeletingNextElement;


	SimpleListElement* myTempDel2 = myTempDel->nextAdress;
	myTempDel2->prevAdress = forDeletingPrevElement;




	string result = myTempDel -> value;
	currIteratorAdress = firstAdress;

	length --;
	
}

