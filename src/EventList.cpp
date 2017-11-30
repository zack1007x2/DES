/*
 * linkedlist.cpp
 *
 *  Created on: 2017年11月15日
 *      Author: Zack
 */

#include "EventList.h"

#include <iostream>

using namespace std;

bool EventList::insertNode(Node * newNode, int position) {
	cout << "\ninsertNode ..." << endl;
	if ((position <= 0) || (position > listLength + 1)) {
		cout << "Insert Error: position out of range." << endl;
		return false;
	}
	if (!head->next) {
		head->next = newNode;
		listLength++;
		cout << "Success: added '" << newNode->eventType << "' to position "
				<< position << ".\n";
		cout << "listLength = " << listLength << endl;
		return true;
	}
	int count = 0;
	Node * p = head;
	Node * q = head;
	while (q) {
		if (count == position) {
			p->next = newNode;
			newNode->next = q;
			listLength++;
			return true;
		}
		p = q;
		q = p->next;
		count++;
	}
	if (count == position) {
		p->next = newNode;
		newNode->next = q;
		listLength++;
		cout << "Success: added '" << newNode->eventType << "' to position "
				<< position << ".\n";
		cout << "listLength = " << listLength << endl;
		return true;
	}
	cout << "Error: song node was not added to list." << endl;
	return false;
}

bool EventList::getNode(int position) {
	cout << "\nEntering removeNode..." << endl;
	if ((position <= 0) || (position > listLength + 1)) {
		cout << "Error: the given position is out of range." << endl;
		return false;
	}
	if (!head->next) {
		cout << "Error: there is nothing to remove." << endl;
		return false;
	}

	int count = 0;
	Node * p = head;
	Node * q = head;
	while (q) {
		if (count == position) {
			p->next = q->next;
			delete q;
			listLength--;
			cout << "Success: node at position " << position << " was deleted."
					<< endl;
			cout << "listLength = " << listLength << endl;
			return true;
		}
		p = q;
		q = p->next;
		count++;
	}
	cout << "Error: nothing was removed from the list." << endl;
	return false;
}

void EventList::printList() {
	cout << "\nStart printList..." << endl;
	int count = 0;
	Node * p = head;
	Node * q = head;
	while (q) {
		p = q;
		q = p->next;
		if (count == 0) {
			count++;
			continue;
		}
		cout << "---------------------\n";
		cout << "\t position: " << count << "\n";
		cout << "\t data: " << p->eventType << "\n";
		count++;
	}
}
//constructor
EventList::EventList() {
	head = new Node;
	head->eventType = 0;
	head->next = NULL;
	listLength = 0;
}

EventList::~EventList() {
	Node * p = head;
	Node * q = head;
	while (q) {
		p = q;
		q = p->next;
		delete p;
	}
	cout << "\nlist deleted." << endl;
}

