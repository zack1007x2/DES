/*
 * linkedlist.h
 *
 *  Created on: 2017年11月15日
 *      Author: Zack
 */

#ifndef EVENTLIST_H_
#define EVENTLIST_H_

struct Node {
	int eventType;
	Node * next;
};

class EventList {
	private:
		Node * head;
		int listLength;

	public:
		EventList();

		bool insertNode(Node * newNode, int position);

		bool getNode(int position);

		void printList();

		int getLength(){
			return listLength;
		}

		~EventList();
};
#endif
