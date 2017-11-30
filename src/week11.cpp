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
enum EventType {
	EV_C_IN, EV_C_OUT
};
struct Event {
	EventType eventType;
	double occured_time; //event happened
	int* next;
	int* head;
};
const int QUEUE_MAX = 1000;
Cus cusQ[QUEUE_MAX];
Event eventQ[QUEUE_MAX];
int head_cus = 0;
int tail_cus = 0;
int head_evnt = 0;
int tail_evnt = 0;
double lamda_cus = 1/0.9;
double mu_ser = 1;
int isCusQEmpty = 1;
int isCusQFull = 0;
int isEventQEmpty = 1;
int isEventQFull = 0;
void pushCusQ(Cus& cIn);
Cus popCustQ();
void pushEventQ(Event& eIn);
Event popEventQ();
double curr_sys_time;
double next_cust_t;
double seed_cust = 634278;
double seed_service = 43526859;
double R_arrive_time = 0;
double R_serv_time = 0;
double sum_sys_time_of_customers = 0;
int isServerBusy;
const long a = 16807; //7^5
const long m = 2147483647;
const long c = 0;

void pushCusQ(Cus& cIn) {
	if ((tail_cus + 1) % QUEUE_MAX == head_cus)
		isCusQFull = 1;
	if (isCusQFull) {
		cout << "ERROR:CustQ Full^^^^^^^^^^^^^^^^^^" << endl;
		return;
	}
	if (isCusQEmpty)
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
	if (head_cus >= 999)
		head_cus = 0;
	else
		head_cus++;

	if (head_cus == tail_cus) {
		isCusQEmpty = 1;
	}
	return ret;
}

void pushEventQ(Event& eIn) {
	if ((tail_evnt + 1) % QUEUE_MAX == head_evnt)
		isEventQFull = 1;
	if (isEventQFull) {
		cout << "ERROR:EventQ Full^^^^^^^^^^^^^^^^^^" << endl;
		return;
	}

	if (isEventQEmpty)
		isEventQEmpty = 0;

	eventQ[head_evnt] = eIn;

	tail_evnt++;
	if (tail_evnt >= 999)
		tail_evnt = 0;

}
void insertEventQ(Event& eIn) {
	if ((tail_evnt + 1) % QUEUE_MAX == head_evnt)
		isEventQFull = 1;
	if (isEventQFull) {
		cout << "ERROR:EventQ Full^^^^^^^^^^^^^^^^^^" << endl;
		return;
	}
	if (isEventQEmpty) {
		eventQ[head_evnt] = eIn;
		tail_evnt++;
		isEventQEmpty = 0;
	} else {
		for (int i = head_evnt; i <= tail_evnt; i++) {
			if (eIn.occured_time <= eventQ[i].occured_time) {
				for (int j = tail_evnt; j >= i; j--) {
					if (j + 1 >= 999)
						j = 0;
					eventQ[j + 1] = eventQ[j];
				}
				eventQ[i] = eIn;
				tail_evnt++;
			}
		}
	}

}
Event popEventQ() {
	if (isEventQEmpty) {
		cout << "ERROR:EventQ Empty--------------------" << endl;
	}
	Event ret = eventQ[head_evnt];
	if (head_evnt >= 999)
		head_evnt = 0;
	else
		head_evnt++;

	if (head_evnt == tail_evnt) {
		isEventQEmpty = 1;
	}
	return ret;
}

void showResult() {
	cout << "1/mu-lamda : " << 1.0 / (mu_ser - 1.0 / lamda_cus) << endl;
	cout << "Mean system time of the customers : "
			<< sum_sys_time_of_customers << endl;
}

double getServiceTime() {
	seed_service = gen1(1, a, m, c, seed_service);
	R_serv_time = (double) seed_service / m;
	double serv_time = getExpDisX(1.0 / mu_ser, R_serv_time);
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

void cusIn() {
	cout << "CustIn at " << curr_sys_time << endl;
	int nextDep = 0;
	Event next_dep;
	if (isServerBusy) {
		/*
		 * server正在服務 因此arrive 先進queue等待
		 */
		Cus cus;
		cus.arr_time = curr_sys_time;
		pushCusQ(cus);
	} else {
		/*
		 * 剛來馬上服務 不需進queue  因為是customer queue中的 第一位
		 * 也不生customer struct 因為沒有waiting time
		 */
		isServerBusy = 1;
		nextDep = 1;
		next_dep.eventType = EV_C_OUT;
		double serv_time = getServiceTime();
		next_dep.occured_time = curr_sys_time + serv_time;
		sum_sys_time_of_customers += serv_time;
		insertEventQ(next_dep);
	}
	//schedule next event
	Event next_arr;
	double next_arrival_time = getInterArrivalTime();
	next_arr.eventType = EV_C_IN;
	next_arr.occured_time = curr_sys_time + next_arrival_time;

	if (nextDep) {
		if (next_dep.occured_time < next_arr.occured_time) {
			insertEventQ(next_dep);
			insertEventQ(next_arr);
		} else {
			insertEventQ(next_arr);
			insertEventQ(next_dep);
		}
	} else {
		insertEventQ(next_arr);
	}

}

void cusOut() {
	cout << "CustOut at " << curr_sys_time << endl;
	if (isCusQEmpty) {
		isServerBusy = 0; //server 忙完且無下一位顧客
	} else { //有人在waiting
		Cus tmp = popCustQ();
		double waitInQTime = curr_sys_time - tmp.arr_time;
		cout << "&&&&&&&&&&& waitInQTime : "<<waitInQTime<<endl;
		sum_sys_time_of_customers += waitInQTime;
		Event dep;
		dep.eventType = EV_C_OUT;
		double service_t = getServiceTime();
		dep.occured_time = curr_sys_time + service_t;
		sum_sys_time_of_customers += service_t;
		insertEventQ(dep);
	}
}

void init() {
	//first cust_in event
	curr_sys_time = 0;
	isServerBusy = 0;
	sum_sys_time_of_customers = 0;
	Event first;
	first.eventType = EV_C_IN;
	first.occured_time = getInterArrivalTime(); //first arrive
	insertEventQ(first);
}
void machineStart() {
	int i = 0;
	while (i < 100) {
		Event tmp = popEventQ();
		curr_sys_time = tmp.occured_time;
		cout << "-------------------curr_sys_time : " << curr_sys_time << endl;
		switch (tmp.eventType) {
		case EV_C_IN:
			cusIn();
			i++;
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
	// TODO Auto-generated constructor stub
	init();
	machineStart();

}

