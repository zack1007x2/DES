/*
 * linkedlist.h
 *
 *  Created on: 2017年11月15日
 *      Author: Zack
 */

#ifndef EVENTLIST_H_
#define EVENTLIST_H_

enum EventType {
	EV_C_IN, EV_C_OUT
};
struct Event {
	EventType eventType;
	double occured_t;
	Event * next;
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
