/*
 * Queue.cpp
 *
 *  Created on: 2018年1月4日
 *      Author: Zack
 */


#include<iostream>
#include "Queue.h"

using namespace std;

//struct Cus {
//	double arr_time; //arrive = sys_time+arrive time
//	double sys_time; //stay in sys = sys_time
//	int cust_num;
//};
//template <class T>
Queue :: Queue()
{
	capacity = INITIAL_CAPACITY;
	data = new Cus[capacity];
	head = tail = 0;
}

//template <class T>
Queue :: ~Queue()
{
	delete [] data;
}

//template <class T>
int Queue :: size()
{
	return (tail + capacity - head) % capacity;
}

//template <class T>
bool Queue :: isEmpty()
{
	return head == tail;
}

//template <class T>
void Queue :: clear()
{
	head = tail = 0;
}

//template <class T>
void Queue :: enqueue(Cus value)
{
	if (size() == capacity - 1) expandCapacity();
	data[tail] = value;
	tail = (tail + 1) % capacity;
}

//template <class T>
Cus Queue :: dequeue()
{
	if (isEmpty()) cerr << "dequeue: Attempting to dequeue an empty queue";
	Cus result = data[head];
	head = (head + 1) % capacity;
	return result;
}

//template <class T>
Cus Queue :: peek()
{
	if (isEmpty()) cerr << "peek: Attempting to peek at an empty queue";
	return data[head];
}

//template <class T>
void Queue:: expandCapacity() {
	int count = size();
	capacity *= 2;
	Cus *oldArray = data;
	data = new Cus[capacity];
	for (int i = 0; i < count; i++) {
		data[i] = oldArray[(head + i) % capacity];
	}
	head = 0;
	tail = count;
	delete [] oldArray;
}

