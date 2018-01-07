/*
 * final.cpp
 *
 *  Created on: 2017年12月28日
 *      Author: Zack
 */

#include "final.h"
#include "week4.h"
#include "week7.h"
#include "week6.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <map>
#include <math.h>
#include "EventList.h"
#include "Queue.h"

using namespace std;

int CUR_CUST_NUM = 0;
const int TARGET_CUST_NUM = 5;
double cus_lamde = (double) 8;
double ser_mu_self = (double) 8;
double ser_mu_clerk = 1;
double ser_mu_casher = (double) 10;

int cus_seed_poi = 234;
int cus_seed_split = 647;
int ser_seed_self = 234542361;
int ser_seed_mm_help = 4324;
int ser_seed_mm_cash = 46748;
EventList mEvntList;
Queue mClerkQ, mCasherQ;

double curr_sys_time_;
double sum_sys_time_;

void start();
double getTime(double lamda, int *seed);
bool canSelf(int *seed);
int ClerkInUse = 0;
int CasherInUse = 0;
const int CLERK_MAX = 2;
const int CASHER_MAX = 1;
Cus cusArray[TARGET_CUST_NUM + 1];
int test_cnt = 0;

final::final() {
	runWarehouseMachine();
}
void init() {
	sum_sys_time_ = 0;
	CUR_CUST_NUM = 0;
	curr_sys_time_ = 0;
	ClerkInUse = 0;
	CasherInUse = 0;

}
void runWarehouseMachine() {
	init();
	start();
}

void runWarehouseMachine(int _cus_seed_poi, int _cus_seed_split,
		int _ser_seed_self, int _ser_seed_mm_help, int _ser_seed_mm_cash) {
	//init
	cus_seed_poi = _cus_seed_poi;
	cus_seed_split = _cus_seed_split;
	ser_seed_self = _ser_seed_self;
	ser_seed_mm_help = _ser_seed_mm_help;
	ser_seed_mm_cash = _ser_seed_mm_cash;

	init();
	start();
}

void doCustInSelf(Cus *cus) {
	cout << cus->cust_num << " - doCustInSelf at " << curr_sys_time_ << endl;
	(*cus).sys_arrive_time = curr_sys_time_;
	Event *e = new Event;
	e->eventType = EV_C_SELF_OUT;
	e->next = NULL;
	double self_serv_time = getTime(ser_mu_self, &ser_seed_self);
	e->occured_t = curr_sys_time_ + self_serv_time;
	e->cus = cus;
	mEvntList.insertEvent(e);
	cout << e->cus->cust_num << "---(doCustInSelf)INSERT SELF DEP----"
			<< e->occured_t << endl;
	sum_sys_time_ += self_serv_time;

	//TODO schedule next IN
	Event * next_arr = new Event;
	next_arr->next = NULL;
	double next_arrival_time = getTime(cus_lamde, &cus_seed_poi);
	next_arr->occured_t = curr_sys_time_ + next_arrival_time;
	if (canSelf(&cus_seed_split)) {
		next_arr->eventType = EV_C_IN;
	} else {
		next_arr->eventType = EV_C_CLERK_IN;
	}
	cusArray[CUR_CUST_NUM].cust_num = CUR_CUST_NUM;
	next_arr->cus = &cusArray[CUR_CUST_NUM];
	mEvntList.insertEvent(next_arr);
	cout << next_arr->cus->cust_num << "---(doCustInSelf)INSERT NEXT ARR----"
			<< next_arr->occured_t << endl;
}

void goCheckOut(Cus *cus) {
	cout << cus->cust_num << " - goCheckOut at " << curr_sys_time_ << endl;
	//go checkout
	if (CasherInUse >= CASHER_MAX) {
		//full
		cout << "casher busy : " << CasherInUse << endl;
		(*cus).arr_time = curr_sys_time_;
		mCasherQ.enqueue(cus);
		cout << "   Cust" << cus->cust_num << " goto mCasherQ" << endl;
	} else {
		//do checkout
		CasherInUse++;
		Event *checkout = new Event;
		checkout->next = NULL;
		checkout->eventType = EV_C_OUT;
		double checkout_t = getTime(ser_mu_casher, &ser_seed_mm_cash); //checkout service
		checkout->occured_t = curr_sys_time_ + checkout_t;
		cout << "*********" << cusArray[(*cus).cust_num].sys_leave_time << endl;
		(*cus).sys_leave_time = checkout->occured_t;
		cout << "*********" << cusArray[(*cus).cust_num].sys_leave_time << endl;

		test_cnt++;

		checkout->cus = cus;
		mEvntList.insertEvent(checkout);
		cout << checkout->cus->cust_num << "---(goCheckOut)INSERT DEP LEAVE----"
				<< checkout->occured_t << endl;
		sum_sys_time_ += checkout_t;
	}

}

void leaveCheckOut() {
	cout << "LEAVE CheckOut" << endl;
	if (CasherInUse > 0)
		CasherInUse--;
	if (mCasherQ.isEmpty()) {
		//無下一位顧客
	} else { // handle waiting people from queue
//		Cus tmp = mCasherQ.dequeue();
//		double waitInQTime = curr_sys_time_ - tmp.arr_time;
//		cout << "&&&&&&&&&&& waitInCasherQTime : " << waitInQTime << endl;
//		Event * dep = new Event;
//		dep->next = NULL;
//		dep->eventType = EV_C_OUT;
//		double service_t = getTime(ser_mu_casher, &ser_seed_mm_cash);
//		dep->occured_t = curr_sys_time_ + service_t;
//		tmp.sys_leave_time = dep->occured_t;
//
//		test_cnt++;
//
//		dep->cus = &tmp;
//		mEvntList.insertEvent(dep);
//		cout << dep->cus->cust_num << "---(leaveCheckOut)INSERT DEP LEAVE----"
//				<< dep->occured_t << endl;
//		sum_sys_time_ += (waitInQTime + service_t);

		Cus* tmp = mCasherQ.dequeue();
		double waitInQTime = curr_sys_time_ - tmp->arr_time;
		cout << "&&&&&&&&&&& waitInCasherQTime : " << waitInQTime << endl;
		Event * dep = new Event;
		dep->next = NULL;
		dep->eventType = EV_C_OUT;
		double service_t = getTime(ser_mu_casher, &ser_seed_mm_cash);
		dep->occured_t = curr_sys_time_ + service_t;
		tmp->sys_leave_time = dep->occured_t;

		test_cnt++;

		dep->cus = tmp;
		mEvntList.insertEvent(dep);
		cout << dep->cus->cust_num << "---(leaveCheckOut)INSERT DEP LEAVE----"
				<< dep->occured_t << endl;
		sum_sys_time_ += (waitInQTime + service_t);

	}
}

void doCustInWithHelp(Cus *cus) {
	cout << cus->cust_num << " - doCustInWithHelp at " << curr_sys_time_
			<< endl;
	(*cus).sys_arrive_time = curr_sys_time_;
	if (ClerkInUse == CLERK_MAX) { //clerks all busy go queuing
		cout << "clerk all busy : " << ClerkInUse << endl;
		(*cus).arr_time = curr_sys_time_;
		mClerkQ.enqueue(cus);
	} else {
		//do service without any waiting
		ClerkInUse++;
		Event * next_dep = new Event; // OUT
		next_dep->next = NULL;
		next_dep->eventType = EV_C_CLERK_OUT;

		double serv_time = getTime(ser_mu_clerk, &ser_seed_mm_help);
		next_dep->occured_t = curr_sys_time_ + serv_time;
		sum_sys_time_ += serv_time;
		next_dep->cus = cus;
		mEvntList.insertEvent(next_dep);
		cout << next_dep->cus->cust_num << "---(CusIn)INSERT CLERK DEP----"
				<< next_dep->occured_t << endl;
	}

	//TODO schedule next IN
	Event * next_arr = new Event;
	next_arr->next = NULL;
	double next_arrival_time = getTime(cus_lamde, &cus_seed_poi);
	next_arr->occured_t = curr_sys_time_ + next_arrival_time;
	if (canSelf(&cus_seed_split)) {
		next_arr->eventType = EV_C_IN;
	} else {
		next_arr->eventType = EV_C_CLERK_IN;
	}
	cusArray[CUR_CUST_NUM].cust_num = CUR_CUST_NUM;
	next_arr->cus = &cusArray[CUR_CUST_NUM];
	mEvntList.insertEvent(next_arr);
	cout << next_arr->cus->cust_num << "---(CusIn)INSERT NEXT ARR----"
			<< next_arr->occured_t << endl;
}

void cusOutFromClerk(Cus *cus) {
	//current cust goto casher
	cout << cus->cust_num << " - cusOutFromClerk at " << curr_sys_time_ << endl;
	goCheckOut(cus);

	if (ClerkInUse > 0)
		ClerkInUse--;
	if (mClerkQ.isEmpty()) {
		//無下一位顧客
	} else { // pop waiting people from queue
//		Cus tmp = mClerkQ.dequeue();
//		double waitInQTime = curr_sys_time_ - tmp.arr_time;
//		cout << "&&&&&&&&&&&  waitInClerkQTime : " << waitInQTime << endl;
//
//		Event * dep = new Event;
//		dep->next = NULL;
//		dep->eventType = EV_C_CLERK_OUT;
//		double service_t = getTime(ser_mu_clerk, &ser_seed_mm_help);
//		dep->occured_t = curr_sys_time_ + service_t;
//		dep->cus = &tmp;
//		mEvntList.insertEvent(dep);
//		cout << dep->cus->cust_num << "---(CusOut)INSERT CLERK DEP----"
//				<< dep->occured_t << endl;
//		sum_sys_time_ += (waitInQTime + service_t);

		Cus* tmp = mClerkQ.dequeue();
		double waitInQTime = curr_sys_time_ - tmp->arr_time;
		cout << "&&&&&&&&&&&  waitInClerkQTime : " << waitInQTime << endl;

		Event * dep = new Event;
		dep->next = NULL;
		dep->eventType = EV_C_CLERK_OUT;
		double service_t = getTime(ser_mu_clerk, &ser_seed_mm_help);
		dep->occured_t = curr_sys_time_ + service_t;
		dep->cus = tmp;
		mEvntList.insertEvent(dep);
		cout << dep->cus->cust_num << "---(CusOut)INSERT CLERK DEP----"
				<< dep->occured_t << endl;
		sum_sys_time_ += (waitInQTime + service_t);

	}
}

void start() {
	//first cust
	Event * first = new Event;
	if (canSelf(&cus_seed_split)) {
		first->eventType = EV_C_IN;
	} else {
		first->eventType = EV_C_CLERK_IN;
	}
	first->next = NULL;
	first->occured_t = getTime(cus_lamde, &cus_seed_poi);
	cusArray[CUR_CUST_NUM].cust_num = CUR_CUST_NUM;
	first->cus = &cusArray[CUR_CUST_NUM];
	mEvntList.insertEvent(first);
	cout << "FIRST IN" << endl;
	int cnter = 0;
	bool finishing = false;
	bool stopMachine = false;
	while (!stopMachine) {
		if (CUR_CUST_NUM >= TARGET_CUST_NUM)
			finishing = true;
		Event *tmp = mEvntList.popEvent();
		curr_sys_time_ = tmp->occured_t;
		cout << "-------------------curr_sys_time : " << curr_sys_time_ << endl;
		switch (tmp->eventType) {
		case EV_C_IN:
			if (!finishing) {
				CUR_CUST_NUM++;
				doCustInSelf(tmp->cus);
				cnter++;
			}
			break;
		case EV_C_SELF_OUT:
			goCheckOut(tmp->cus);
			break;
		case EV_C_CLERK_IN:
			if (!finishing) {
				CUR_CUST_NUM++;
				doCustInWithHelp(tmp->cus);
				cnter++;
			}
			break;
		case EV_C_CLERK_OUT:
			cusOutFromClerk(tmp->cus);
			break;
		case EV_C_OUT: //leave system
			leaveCheckOut();
			cnter--;
			cout << cnter << endl;
			if (finishing && cnter == 0)
				stopMachine = true;
			break;
		}
	}
	cout << "MEAN SYS TIME: " << sum_sys_time_ / TARGET_CUST_NUM << endl;
	double sum=0;
	for (int i = 0; i < TARGET_CUST_NUM; i++) {
		cout << "--- " << cusArray[i].sys_leave_time - cusArray[i].sys_arrive_time << endl;
		sum+=cusArray[i].sys_leave_time - cusArray[i].sys_arrive_time;
	}
	cout << "MEAN SYS TIME: " << sum / TARGET_CUST_NUM << endl;


}

double getTime(double lamda, int *seed) {
	*seed = gen1(1, a, m, c, *seed);
	double R_time = (double) *seed / m;
	double time = getExpDisX(lamda, R_time);
	cout << "  gen time : " << time << endl;
	if (time < 0) {
		cerr << "ERROR TIME" << endl;
		exit(0);
	}

	return time;
}

bool canSelf(int *seed) {
	*seed = gen1(1, a, m, c, *seed);
	double R = (double) *seed / m;
	if (R < 0.8)
		return true;
	else
		return false;
}
