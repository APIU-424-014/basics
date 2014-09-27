/*
 * choice.h
 *
 *  Created on: 21.09.2014
 *      Author: user
 */

#ifndef CHOICE_H_
#define CHOICE_H_

#include<string>

namespace input {
struct item {
	item(std::string *name, int value);
	item(item *i);
	void print();
	void init(std::string *name, int value);
	int value;
	std::string *name;
	~item();
};
class choice {
public:
	choice();
	void extend(item *list, int length);
	void print();
	virtual ~choice();
	int getChoice();
	item* getItemByValue(int i); //null pointer returned if not found
private:

	item **list;
	int listLength;
	int *lengths;
};

} /* namespace input */

#endif /* CHOICE_H_ */
