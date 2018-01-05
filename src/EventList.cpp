/*
 * linkedlist.cpp
 *
 *  Created on: 2017年11月15日
 *      Author: Zack
 */

#include "EventList.h"

#include <iostream>

using namespace std;

bool EventList::insertEvent(Event * newEvent) {
	if (head == NULL) {	// empty
		head = newEvent;
		listLength++;
		return true;
	}

	Event * cur = head;
	Event * pre = NULL;
	while (cur != NULL) {	// search insert location
		if (newEvent->occured_t < cur->occured_t)
			break;

		pre = cur;
		cur = cur->next;
	}

	if (pre == NULL) {	// insert head
		newEvent->next = head;
		head = newEvent;
	}
	else {
		newEvent->next = cur;
		pre->next = newEvent;
	}

	listLength++;
	return true;
}

Event * EventList::popEvent() {
	if(listLength==0){
		return NULL;
	}

	Event *tmp = head;
	head = head->next;
	listLength--;
	return tmp;
}

void EventList::printList() {
	cout << "\nStart printList..." << endl;
	int count = 1;
	Event * p = head;
	while (p) {
		cout << "---------------------\n";
		cout << "\t position: " << count << "\n";
		cout << "\t data: " << p->occured_t << "\n";
		count++;

		p = p->next;
		count++;
	}
}
bool EventList::isEmpty(){
	return head==NULL;
}
//constructor
EventList::EventList() {
	head = NULL;
	listLength = 0;
}


