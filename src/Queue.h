/*
 * Queue.h
 *
 *  Created on: 2018年1月4日
 *      Author: Zack
 */

#ifndef QUEUE_H_
#define QUEUE_H_

using namespace std;

struct Cus {
	double arr_time; //tmp arrive value
	double sys_arrive_time;
	double sys_leave_time;
	int cust_num;
};

//template <class T>
class Queue
{
public :
	Queue();
	~Queue();
	int size();
	bool isEmpty();
	void clear();
	void enqueue(Cus *value);
	Cus* dequeue();
	Cus* peek();
	void expandCapacity();
private :
	static const int INITIAL_CAPACITY = 1000;
	Cus** data;
	int capacity;
	int head;
	int tail;
};


#endif /* QUEUE_H_ */
