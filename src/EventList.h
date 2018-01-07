/*
 * linkedlist.h
 *
 *  Created on: 2017年11月15日
 *      Author: Zack
 */

#ifndef EVENTLIST_H_
#define EVENTLIST_H_

#include "Queue.h"
enum EventType {
	EV_C_IN, EV_C_OUT, EV_C_CLERK_IN, EV_C_CLERK_OUT, EV_C_SELF_OUT
};
struct Event {
	EventType eventType;
	double occured_t;
	Event * next;
	Cus *cus;
};

class EventList {
private:
	Event * head;
	int listLength;

public:
	EventList();

	bool insertEvent(Event * newEvent);

	Event * popEvent();

	void printList();

	int getLength() {
		return listLength;
	}

	bool isEmpty();

//	~EventList();
};
#endif
