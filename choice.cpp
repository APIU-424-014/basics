/*
 * choice.cpp
 *
 *  Created on: 21.09.2014
 *      Author: user
 */

#include "choice.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace input {
using namespace std;

item::item(std::string *name, int value) {
	init(name, value);
}

void item::print() { //debugging help
	cout << "Address: " << this << " N:" << &this->name << " V:" << &this->value
			<< endl;
	cout << "Values at(" << this << "): N:" << this->name << " V:"
			<< this->value << endl;
	cout << "Value at( " << this->name << "): N:" << *this->name << endl;
}

void item::init(string *name, int value) {
	this->name = (string*) malloc(name->length() * sizeof(char) + 1);
	memcpy(this->name, name, name->length() * sizeof(char) + 1);
	this->value = value;
}

item::item(item *i) {
	init(i->name, i->value);
}
item::~item() {
}
choice::choice() {
	// TODO Automatisch generierter Konstruktorstub
	this->lengths = (int*) malloc(0);

	this->list = (item**) malloc(0);
	this->listLength = 0;

}
int choice::getChoice() {
	int ret;
	int inputProblem = false;
	do {
		cin.clear();
		if (inputProblem) {
			cout << "Ein Problem ist aufgetreten. Bitte nochmals versuchen."
					<< endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		this->print();
		cout << endl << "Auswahl: ";
	} while ((inputProblem = !(bool) (cin >> ret))); //operator>> returns null pointer on failure

	return ret;

}
item* choice::getItemByValue(int value) {
	for (int a = 0; a < this->listLength; a++) {
		item* curList = *(this->list + a);
		int curLen = *(this->lengths + a);
		for (int i = 0; i < curLen; i++) {
			if ((curList + i)->value == value)
				return (curList + i);
		}
	}
	return 0; //not found, returning null pointer
}
void choice::extend(item *list, int length) {
//Listen-Array vergrössern
	item **old = this->list;
	this->list = (item**) malloc(sizeof(item*) * (this->listLength + 1));
	memcpy(this->list, old, this->listLength * sizeof(item*));
	free(old); //alter Speicher freigeben

//übergenenes Array kopieren
	item *newList = (item*) malloc(sizeof(item) * length);
	memcpy(newList, list, length * sizeof(item));

//kopiertes Array hinzufügen
	*(this->list + this->listLength) = newList;

//Array mit Längen vergrössern
	int *tmp = this->lengths;
	this->lengths = (int*) malloc(sizeof(int) * (this->listLength + 1));
	memcpy(this->lengths, tmp, sizeof(int) * this->listLength);
	free(tmp); //alter Speicher freigeben

//Länge hinzufügen
	*(this->lengths + this->listLength) = length;

//Neue Listen länge setzen
	this->listLength++;
}
void choice::print() {
	for (int i = 0; i < this->listLength; i++) {
		item *curList = *(this->list + i);
		int curLen = *(this->lengths + i);
		for (int ii = 0; ii < curLen; ii++) {
			item* curItem = (curList + ii);
			std::cout << *(curItem->name) << ": " << curItem->value << "\t";
		}
		cout << endl;
	}
}
choice::~choice() {
}

} /* namespace input */
