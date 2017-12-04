/*
 * week11.cpp
 *
 *  Created on: 2017年11月23日
 *      Author: Zack
 */

#include "week11.h"
#include "week4.h"
#include "week7.h"
#include "week6.h"
#include "EventList.h"
#include <queue>
#include <time.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

struct Cus {
	double arr_time; //arrive = sys_time+arrive time
	double stay_in_sys_time; //stay in sys = sys_time
	double service_time; //service cost
};

const int QUEUE_MAX = 1000;
const int CUSTOMER_TOTAL = 1000;
Cus cusQ[QUEUE_MAX];
int head_cus = 0;
int tail_cus = 0;
int head_evnt = 0;
int tail_evnt = 0;

int isCusQEmpty = 1;
int isCusQFull = 0;
int isEventQEmpty = 1;
int isEventQFull = 0;

void pushCusQ(Cus& cIn);
Cus popCustQ();
double curr_sys_time;
double next_cust_t;
double seed_cust = 136454765465;
double seed_service = 4357864754537;
double R_arrive_time = 0;
double R_serv_time = 0;
double sum_sys_time_of_customers = 0;
int isServerBusy;

const long a = 16807; //7^5
const long m = 2147483647;
const long c = 0;
double lamda_cus = 0.9;
double mu_ser = 1;
EventList mList;

void pushCusQ(Cus& cIn) {
	if ((tail_cus + 1) % QUEUE_MAX == head_cus)
		isCusQFull = 1;
	if (isCusQFull) {
		cout << "ERROR:CustQ Full^^^^^^^^^^^^^^^^^^" << endl;
		return;
	}
	isCusQEmpty = 0;
	cusQ[tail_cus] = cIn;
	tail_cus++;
	if (tail_cus >= 999)
		tail_cus = 0;
}

Cus popCustQ() {
	if (isCusQEmpty) {
		cout << "ERROR:CustQ Empty*****************" << endl;
	}

	Cus ret = cusQ[head_cus];
	head_cus++;
	if (head_cus >= QUEUE_MAX)
		head_cus = 0;

	if (head_cus == tail_cus) {
		isCusQEmpty = 1;
	}
	return ret;
}

void showResult() {
	cout << "1/mu-lamda : " << 1.0 / (mu_ser - lamda_cus) << endl;
	cout << "Mean system time of the customers : "
			<< sum_sys_time_of_customers / CUSTOMER_TOTAL << endl;
}

double getServiceTime() {
	seed_service = gen1(1, a, m, c, seed_service);
	R_serv_time = (double) seed_service / m;
	double serv_time = getExpDisX(mu_ser, R_serv_time);
	cout << "      service_time : " << serv_time << endl;
	return serv_time;
}

double getInterArrivalTime() {
	seed_cust = gen1(1, a, m, c, seed_cust);
	R_arrive_time = (double) seed_cust / m;
	double arrive_time = getExpDisX(lamda_cus, R_arrive_time);
	cout << "      arrive_time : " << arrive_time << endl;
	return arrive_time;
}
void custInFinal() {
	cout << "CustIn at " << curr_sys_time << endl;

	if (isServerBusy) {
		/*
		 * server正在服務 因此arrive 先進queue等待
		 */
		Cus cus;
		cus.arr_time = curr_sys_time;
		pushCusQ(cus);

		//		cout << "###################### PUSH CUST" << endl;
	} else {
		/*
		 * 剛來馬上服務 不需進queue  因為是customer queue中的 第一位
		 * 也不生customer struct 因為沒有waiting time
		 */
		isServerBusy = 1;
		Event * next_dep = new Event; // OUT
		next_dep->next = NULL;
		next_dep->eventType = EV_C_OUT;

		double serv_time = getServiceTime();
		next_dep->occured_t = curr_sys_time + serv_time;
		sum_sys_time_of_customers += serv_time;
		mList.insertEvent(next_dep);
		cout << "---(CusIn)INSERT DEP----" << next_dep->occured_t << endl;
	}
}
void cusIn() {
	cout << "CustIn at " << curr_sys_time << endl;

	if (isServerBusy) {
		/*
		 * server正在服務 因此arrive 先進queue等待
		 */
		Cus cus;
		cus.arr_time = curr_sys_time;
		pushCusQ(cus);

//		cout << "###################### PUSH CUST" << endl;
	} else {
		/*
		 * 剛來馬上服務 不需進queue  因為是customer queue中的 第一位
		 * 也不生customer struct 因為沒有waiting time
		 */
		isServerBusy = 1;
		Event * next_dep = new Event; // OUT
		next_dep->next = NULL;
		next_dep->eventType = EV_C_OUT;

		double serv_time = getServiceTime();
		next_dep->occured_t = curr_sys_time + serv_time;
		sum_sys_time_of_customers += serv_time;
		mList.insertEvent(next_dep);
		cout << "---(CusIn)INSERT DEP----" << next_dep->occured_t << endl;
	}

	//schedule next event (IN)
	Event * next_arr = new Event;
	next_arr->next = NULL;
	double next_arrival_time = getInterArrivalTime();
	next_arr->eventType = EV_C_IN;
	next_arr->occured_t = curr_sys_time + next_arrival_time;
	mList.insertEvent(next_arr);
	cout << "---(CusIn)INSERT ARR----" << next_arr->occured_t << endl;
}

void cusOut() {
	cout << "CustOut at " << curr_sys_time << endl;
	if (isCusQEmpty) {
		isServerBusy = 0; //server 忙完且無下一位顧客
	} else { //有人在waiting
		Cus tmp = popCustQ();
//		cout << "@@@@@@@@pop CUST" << endl;

		double waitInQTime = curr_sys_time - tmp.arr_time;
		cout << "&&&&&&&&&&& waitInQTime : " << waitInQTime << endl;
		sum_sys_time_of_customers += waitInQTime;

		Event * dep = new Event;
		dep->next = NULL;
		dep->eventType = EV_C_OUT;
		double service_t = getServiceTime();
		dep->occured_t = curr_sys_time + service_t;
		sum_sys_time_of_customers += service_t;
		mList.insertEvent(dep);
		cout << "---(CusOut)INSERT DEP----" << dep->occured_t << endl;
	}
}

void init() {
	//first cust_in event
	curr_sys_time = 0;
	isServerBusy = 0;
	sum_sys_time_of_customers = 0;
}
void machineStart() {
	int i = 1;

	Event * first = new Event;
	first->next = NULL;
	first->eventType = EV_C_IN;
	first->occured_t = getInterArrivalTime(); //first arrive
	mList.insertEvent(first);
	cout << "---INSERT ARR----" << endl;
	while (i < CUSTOMER_TOTAL) {
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << " Cust QUEUE EMPTY : " << isCusQEmpty << endl;
		cout << " Sys BUSY : " << isServerBusy << endl;
		mList.printList();
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		Event * tmp = mList.popEvent();
		curr_sys_time = tmp->occured_t;
		cout << "-------------------curr_sys_time : " << curr_sys_time << endl;
		switch (tmp->eventType) {
		case EV_C_IN:
			cusIn();
			i++;
			break;
		case EV_C_OUT:
			cusOut();
			break;
		}
	}

	/*
	 * stop generate IN event
	 * pop all event and skip IN only calculate OUT
	 */
	while (!mList.isEmpty()) {
		cout << "********************   " << mList.getLength() << endl;
		Event * tmp = mList.popEvent();
		curr_sys_time = tmp->occured_t;
		cout << "-------------------curr_sys_time : " << curr_sys_time << endl;
		switch (tmp->eventType) {
		case EV_C_IN:
			custInFinal();
			break;
		case EV_C_OUT:
			cusOut();
			break;
		}
	}
	showResult();
	return;
}

week11::week11() {
	init();
	machineStart();

}

