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
#include <map>
#include <math.h>

using namespace std;

map<MAP_TAG, double> mResultMap;
map<int, double> mDetailTable;


struct Cus {
	double arr_time; //arrive = sys_time+arrive time
	double stay_in_sys_time; //stay in sys = sys_time
	double service_time; //service cost
};
const bool DEBUG = false;
const int QUEUE_MAX = 1000;
int CUSTOMER_TOTAL;
Cus cusQ[QUEUE_MAX];
double * Yi;
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
double seed_cust;
double seed_service;
double R_arrive_time = 0;
double R_serv_time = 0;
double sum_sys_time_of_customers = 0;
int isServerBusy;

int cnt = 1;

const long a = 16807; //7^5
const long m = 2147483647;
const long c = 0;
double lamda_cus = 4.5;
double mu_ser = 5;
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
//	cout<< "<<<<<<<<<<<<<<  "<<sum_sys_time_of_customers<<endl;
	double sample_mean = sum_sys_time_of_customers / CUSTOMER_TOTAL;
	double sum_of_var = 0;
	double mean = 1.0 / (mu_ser - lamda_cus);
	if (DEBUG) {
		cout << "1/mu-lamda : " << mean << endl;
		cout << "Mean system time of the customers : " << sample_mean << endl;
	}
//	mResultMap.insert(pair<MAP_TAG, double>(SAMPLE_MEAN, sum_sys_time_of_customers / CUSTOMER_TOTAL));
	mResultMap[SAMPLE_MEAN] = sample_mean;
	for (int i = 0; i < 1000; i++) {
		sum_of_var += pow((double) (Yi[i] - sample_mean), 2.0);
	}
	mResultMap[SAMPLE_VAR] = sqrt(sum_of_var / (CUSTOMER_TOTAL - 1));
	mResultMap[MEAN] = mean;
	mResultMap[SUM_VAR] = sum_of_var;
}

double getServiceTime() {
	seed_service = gen1(1, a, m, c, seed_service);
	R_serv_time = (double) seed_service / m;
	double serv_time = getExpDisX(mu_ser, R_serv_time);
	if (DEBUG)
		cout << "      service_time : " << serv_time << endl;
	return serv_time;
}

double getInterArrivalTime() {
	seed_cust = gen1(1, a, m, c, seed_cust);
	R_arrive_time = (double) seed_cust / m;
	double arrive_time = getExpDisX(lamda_cus, R_arrive_time);
	if (DEBUG)
		cout << "      arrive_time : " << arrive_time << endl;
	return arrive_time;
}
void cusIn(bool isFinishing) {
	if (DEBUG)
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
//		cout<< "<<<<<<<<<<<<<<  "<<sum_sys_time_of_customers<<endl;
		mList.insertEvent(next_dep);
		if (DEBUG)
			cout << "---(CusIn)INSERT DEP----" << next_dep->occured_t << endl;
		Yi[cnt] = serv_time;
	}

//schedule next event (IN)
	if (!isFinishing) {
		Event * next_arr = new Event;
		next_arr->next = NULL;
		double next_arrival_time = getInterArrivalTime();
		next_arr->eventType = EV_C_IN;
		next_arr->occured_t = curr_sys_time + next_arrival_time;
		mList.insertEvent(next_arr);
		if (DEBUG)
			cout << "---(CusIn)INSERT ARR----" << next_arr->occured_t << endl;
	}
}

void cusOut() {
	if (DEBUG)
		cout << "CustOut at " << curr_sys_time << endl;
	if (isCusQEmpty) {
		isServerBusy = 0; //server 忙完且無下一位顧客
	} else { //有人在waiting
		Cus tmp = popCustQ();
		double waitInQTime = curr_sys_time - tmp.arr_time;
//		cout << "&&&&&&&&&&& waitInQTime : " << waitInQTime << endl;

		Event * dep = new Event;
		dep->next = NULL;
		dep->eventType = EV_C_OUT;
		double service_t = getServiceTime();
		dep->occured_t = curr_sys_time + service_t;
		mList.insertEvent(dep);
		if (DEBUG)
			cout << "---(CusOut)INSERT DEP----" << dep->occured_t << endl;

		sum_sys_time_of_customers += waitInQTime + service_t;
//		cout<< "<<<<<<<<<<<<<<  "<<sum_sys_time_of_customers<<endl;
		Yi[cnt] = waitInQTime + service_t;
	}
}

void init(int CUSTOMER_CNT, double cus_seed, double ser_seed) {
//first cust_in event
	seed_cust = cus_seed;
	seed_service = ser_seed;
	CUSTOMER_TOTAL = CUSTOMER_CNT;
	Yi = new double[CUSTOMER_CNT];
	curr_sys_time = 0;
	isServerBusy = 0;
	sum_sys_time_of_customers = 0;


	head_cus = 0;
	tail_cus = 0;
	head_evnt = 0;
	tail_evnt = 0;

	isCusQEmpty = 1;
	isCusQFull = 0;
	isEventQEmpty = 1;
	isEventQFull = 0;

	R_arrive_time = 0;
	R_serv_time = 0;

	cnt = 1;
//	cout<< "<<<<<<<<<<<<<<  "<<sum_sys_time_of_customers<<endl;
}
void machineStart() {

	Event * first = new Event;
	first->next = NULL;
	first->eventType = EV_C_IN;
	first->occured_t = getInterArrivalTime(); //first arrive
	mList.insertEvent(first);
	if (DEBUG)
		cout << "---INSERT ARR----" << endl;
	while (cnt < CUSTOMER_TOTAL) {
		if (DEBUG)
			cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
//		cout << " Cust QUEUE EMPTY : " << isCusQEmpty << endl;
//		cout << " Sys BUSY : " << isServerBusy << endl;
//		mList.printList();
//		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		Event * tmp = mList.popEvent();
		curr_sys_time = tmp->occured_t;
		if (DEBUG)
			cout << "-------------------curr_sys_time : " << curr_sys_time
					<< endl;
		switch (tmp->eventType) {
		case EV_C_IN:
			cusIn(false);
			cnt++;
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
		if (DEBUG)
			cout << "********************   " << mList.getLength() << endl;
		Event * tmp = mList.popEvent();
		curr_sys_time = tmp->occured_t;
		if (DEBUG)
			cout << "-------------------curr_sys_time : " << curr_sys_time
					<< endl;
		switch (tmp->eventType) {
		case EV_C_IN:
			cusIn(true);
			break;
		case EV_C_OUT:
			cusOut();
			break;
		}
	}
	showResult();
	return;
}

map<MAP_TAG, double> runMM1(double l, double u, double cus_seed,double ser_seed, int cust_cnt) {
	mu_ser = u;
	lamda_cus = l;
	init(cust_cnt, cus_seed, ser_seed);
	machineStart();
	return mResultMap;
}

double* getDetailList(){
	return Yi;
}

week11::week11(int CUSTOMER_CNT) {
	runMM1(4.5, 5, 54325, 345235, CUSTOMER_CNT);
}
week11::~week11() {
	cout << "RELEASE MEMO" << endl;
	mResultMap.clear();
	mDetailTable.clear();
}
