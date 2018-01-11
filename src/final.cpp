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
#include <string.h>

using namespace std;

int CUR_CUST_NUM = 0;
const int TARGET_CUST_NUM = 400000;
double cus_lamde = (double) 8;
double ser_mu_self = (double) 8;
double ser_mu_clerk = 1;
double ser_mu_casher = (double) 10;

int cus_seed_poi = 1459708755;
int cus_seed_split = 747936906;
int ser_seed_self = 651607313;
int ser_seed_mm_help = 1521948955;
int ser_seed_mm_cash = 1883338725;
EventList mEvntList;
Queue mClerkQ, mCasherQ;

double curr_sys_time_;
double sum_sys_time_;

void start();
void dataParsing(double *cus_sys_time_arr);
double getTime(double lamda, int *seed);
bool canSelf(int *seed);
int ClerkInUse = 0;
int CasherInUse = 0;
const int CLERK_MAX = 2;
const int CASHER_MAX = 1;
Cus cusArray[TARGET_CUST_NUM + 1];
int test_cnt = 0;
double *cus_sys_time_arr;

const bool DEBUG=false;

char file_cust_wait_clerk[] =
		"/Users/Zack/Documents/DiscreteEventSim/final_cust_wait_clerk.txt";
char file_cust_wait_casher[] =
		"/Users/Zack/Documents/DiscreteEventSim/final_cust_wait_casher.txt";
char file_cust_sys_time_mean[] =
		"/Users/Zack/Documents/DiscreteEventSim/final_cust_sys_time_mean.txt";
char file_clerk_queue_size[] =
		"/Users/Zack/Documents/DiscreteEventSim/final_clerk_queue_size.txt";
char file_casher_queue_size[] =
		"/Users/Zack/Documents/DiscreteEventSim/final_casher_queue_size.txt";
//ofstream fout_cust_wait_clerk, fout_cust_wait_casher, fout_cust_sys_time_mean,
//		fout_clerk_queue_size, fout_casher_queue_size;

final::final() {
//	fout_cust_sys_time_mean.open(file_cust_sys_time_mean, ios::trunc);
//	fout_cust_wait_clerk.open(file_cust_wait_clerk, ios::trunc);
//	fout_cust_wait_casher.open(file_cust_wait_casher, ios::trunc);
//	fout_clerk_queue_size.open(file_clerk_queue_size, ios::trunc);
//	fout_casher_queue_size.open(file_casher_queue_size, ios::trunc);
	runWarehouseMachine();
//	fout_cust_sys_time_mean.close();
//	fout_cust_wait_clerk.close();
//	fout_cust_wait_casher.close();
//	fout_clerk_queue_size.close();
//	fout_casher_queue_size.close();

	dataParsing(cus_sys_time_arr);
}
bool test1(int cut_at, int cust_cnt, int batch_cnt, double* cus_sys_time_arr, double *res_mean, double *res_s) {
	int team_cnt = (cust_cnt - cut_at) / batch_cnt;
	map<int, double> s_map;
	double cut_mean = 0;
	int row_cnt = 0;
	int counter = 0;
	cout<<cut_at<<" | "<<cust_cnt<<endl;
	for (int i = cut_at; i < cust_cnt; i++) {
		cut_mean += cus_sys_time_arr[i]; //Y_bar
		s_map[row_cnt] += cus_sys_time_arr[i];
		counter++;
		if (counter == team_cnt) {
			s_map[row_cnt] = s_map[row_cnt] / team_cnt;
			counter = 0;
			row_cnt++;
		}
	}

	cut_mean = cut_mean / (cust_cnt - cut_at);
	cout << "maen : " << cut_mean << endl;
	*res_mean = cut_mean;
	//S_2
	double S_sqr_sum = 0;
	for (int i = 0; i < batch_cnt; i++) {
		S_sqr_sum += pow((s_map[i] - cut_mean), 2);
	}
	cout << "S_sqr : " << S_sqr_sum / (batch_cnt - 1) << endl;
	*res_s = S_sqr_sum / (batch_cnt - 1);
	double roh = 0;
	double roh_sum = 0;

	for (int i = 0; i < (batch_cnt - 1); i++) {
		roh_sum += (s_map[i] - cut_mean) * (s_map[i + 1] - cut_mean);
	}
	roh = roh_sum / S_sqr_sum;
	cout << "roh:" << roh << endl;
	return roh < 0.2 ? true : false;
}
void dataParsing(double *cus_sys_time_arr) {
//	char filename[] =
//			"/Users/Zack/Documents/DiscreteEventSim/final_sys_time_src.txt";
//	ifstream fin;
//	fin.open(filename);
//	if (!fin) { //如果開啟檔案失敗，fp為0；成功，fp為非0
//		cout << "Fail to open file: " << filename << endl;
//		return;
//	} else {
//		int i = 0;
//		string str;
//		do {
//			fin >> cus_sys_time_arr[i];
//			i++;
//		} while (getline(fin, str));
//	}
//	fin.close();
	//get 1-1000's sys mean & analysis;
//	strcpy(filename ,"/Users/Zack/Documents/DiscreteEventSim/1000sys_mean_output.txt");
//	ofstream fout;
//	fout.open(filename, ios::trunc);
//	double sum=0;
//	for (int i = 0; i < 1000; i++) {
//		sum+=cus_sys_time_arr[i];
////		cout<<sum<<" | "<<i+1<<" | "<<sum/i+1<<endl;
//		fout<<sum/(i+1)<<endl;
//	}
	double t_value_90_df8000=1.9602606;
	//do batch mean
	cout<< "Stage 1"<<endl;
	int cur_cust_cnt=1000;
	double res_mean,res_s=0;
	//cut at 600
//	while(!test1(600, cur_cust_cnt, 10, cus_sys_time_arr, &res_mean, &res_s)){
//		cur_cust_cnt*=2;
//	}
//	cout<< "Stage 2 "<<cur_cust_cnt<<endl;
	bool stage1_pass=false;
	bool stage2_pass = false;
	do{
		stage1_pass = test1(600, cur_cust_cnt, 10, cus_sys_time_arr, &res_mean, &res_s);
		double sample_mean_all=0;
		for(int i=600;i<cur_cust_cnt;i++){
			sample_mean_all+=cus_sys_time_arr[i];
		}

		sample_mean_all/=(cur_cust_cnt-600);
		double upper_bounds = res_mean
				+ t_value_90_df8000 * (sqrt(res_s/(10 - 1)));
		double lower_bounds = res_mean
				- t_value_90_df8000 * (sqrt(res_s /(10 - 1)));

		cout << "MEAN : " << res_mean << endl;
		cout << "UPPER : " << upper_bounds << endl;
		cout << "LOWER : " << lower_bounds << endl;
		double interval = abs(1-(res_mean/upper_bounds));
		cout << "C.I.% : " << interval << endl;
		cout << "CUSTOMER CNT:"<<cur_cust_cnt<<endl;
		if(interval<0.05){
			cout<<"SUCCESS"<<endl;
			stage2_pass=true;
		}
		cur_cust_cnt*=2;

	}while(!stage2_pass || !stage1_pass);


}
void init() {
	sum_sys_time_ = 0;
	CUR_CUST_NUM = 0;
	curr_sys_time_ = 0;
	ClerkInUse = 0;
	CasherInUse = 0;
	cus_sys_time_arr = new double[TARGET_CUST_NUM];
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
	if(DEBUG)
		cout << cus->cust_num << " - doCustInSelf at " << curr_sys_time_ << endl;
	(*cus).sys_arrive_time = curr_sys_time_;
	Event *e = new Event;
	e->eventType = EV_C_SELF_OUT;
	e->next = NULL;
	double self_serv_time = getTime(ser_mu_self, &ser_seed_self);
	e->occured_t = curr_sys_time_ + self_serv_time;
	e->cus = cus;
	mEvntList.insertEvent(e);
	if(DEBUG)
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
	if(DEBUG)
	cout << next_arr->cus->cust_num << "---(doCustInSelf)INSERT NEXT ARR----"
			<< next_arr->occured_t << endl;
}

void goCheckOut(Cus *cus) {
	if(DEBUG)
	cout << cus->cust_num << " - goCheckOut at " << curr_sys_time_ << endl;
	//go checkout
	if (CasherInUse >= CASHER_MAX) {
		//full
		if(DEBUG)
		cout << "casher busy : " << CasherInUse << endl;
		cus->arr_time = curr_sys_time_;
		mCasherQ.enqueue(cus);
//		fout_casher_queue_size << mCasherQ.size() << endl;
	} else {
		//do checkout
		CasherInUse++;
		Event *checkout = new Event;
		checkout->next = NULL;
		checkout->eventType = EV_C_OUT;
		double checkout_t = getTime(ser_mu_casher, &ser_seed_mm_cash); //checkout service
//		cout<<"casher serv time : "<<checkout_t<<endl;
		checkout->occured_t = curr_sys_time_ + checkout_t;
		(*cus).sys_leave_time = checkout->occured_t;


		checkout->cus = cus;
		mEvntList.insertEvent(checkout);
		if(DEBUG)
		cout << checkout->cus->cust_num << "---(goCheckOut)INSERT DEP LEAVE----"
				<< checkout->occured_t << endl;
		sum_sys_time_ += checkout_t;
	}

}
double waitInQTime;
void leaveCheckOut() {
	if(DEBUG)
	cout << "LEAVE CheckOut" << endl;
	if (CasherInUse > 0)
		CasherInUse--;
	if (mCasherQ.isEmpty()) {
		//無下一位顧客
	} else { // handle waiting people from queue
		Cus* tmp = mCasherQ.dequeue();
		CasherInUse++;
		if(DEBUG)
		cout << "cust" << tmp->cust_num << " dequeue" <<" " << endl;
		waitInQTime = curr_sys_time_ - tmp->arr_time;
		if(DEBUG)
			cout << tmp->cust_num<< "&&&&&&&&&&&  waitInClerkQTime : "<<waitInQTime << endl;
//		fout_cust_wait_casher << waitInQTime << endl;
		Event * dep = new Event;
		dep->next = NULL;
		dep->eventType = EV_C_OUT;
		double service_t = getTime(ser_mu_casher, &ser_seed_mm_cash);
		dep->occured_t = curr_sys_time_ + service_t;
		tmp->sys_leave_time = dep->occured_t;

		dep->cus = tmp;
		mEvntList.insertEvent(dep);
		if(DEBUG)
		cout << dep->cus->cust_num << "---(leaveCheckOut)INSERT DEP LEAVE----"
				<< dep->occured_t << endl;
		sum_sys_time_ += (waitInQTime + service_t);
	}
}

void doCustInWithHelp(Cus *cus) {
	if(DEBUG)
	cout << cus->cust_num << " - doCustInWithHelp at " << curr_sys_time_
			<< endl;
	cus->sys_arrive_time = curr_sys_time_;
	if (ClerkInUse == CLERK_MAX) { //clerks all busy go queuing
		if(DEBUG)
		cout << "clerk all busy : " << ClerkInUse << endl;
		cus->arr_time = curr_sys_time_;
		mClerkQ.enqueue(cus);
//		fout_clerk_queue_size << mClerkQ.size() << endl;
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
//		if(DEBUG)
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
	if(DEBUG)
	cout << next_arr->cus->cust_num << "---(CusIn)INSERT NEXT ARR----"
			<< next_arr->occured_t << endl;
}

void cusOutFromClerk(Cus *cus) {
	//current cust goto casher
	if(DEBUG)
	cout << cus->cust_num << " - cusOutFromClerk at " << curr_sys_time_ << endl;
	goCheckOut(cus);

	if (ClerkInUse > 0)
		ClerkInUse--;
	if (mClerkQ.isEmpty()) {
		//無下一位顧客
	} else { // pop waiting people from queue
		Cus* tmp = mClerkQ.dequeue();
		ClerkInUse++;
		double waitInQTime = curr_sys_time_ - tmp->arr_time;
		if(DEBUG)
		cout << tmp->cust_num<<"&&&&&&&&&&&  waitInClerkQTime : " <<curr_sys_time_ <<  " | "<< tmp->arr_time<< " | "<<waitInQTime << endl;
//		fout_cust_wait_clerk << waitInQTime << endl;
		Event * dep = new Event;
		dep->next = NULL;
		dep->eventType = EV_C_CLERK_OUT;
		double service_t = getTime(ser_mu_clerk, &ser_seed_mm_help);
		dep->occured_t = curr_sys_time_ + service_t;
		dep->cus = tmp;
		mEvntList.insertEvent(dep);
		if(DEBUG)
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
	if(DEBUG)
	cout << "FIRST IN" << endl;

	int cnter = 0;
	bool finishing = false;
	bool stopMachine = false;
	while (!stopMachine) {
		if (CUR_CUST_NUM >= TARGET_CUST_NUM)
			finishing = true;
		Event *tmp = mEvntList.popEvent();
		curr_sys_time_ = tmp->occured_t;
//		if(tmp->eventType==0 || tmp->eventType==2) {
//			cout<<tmp->cus->cust_num<< " | "<< "ARR"<< tmp->eventType << " | "<< tmp->occured_t<<endl;
//		}else if(tmp->eventType==1){
//			cout<<tmp->cus->cust_num<< " | "<< "DEP" << " | "<< tmp->occured_t<<endl;
//		}

		if(DEBUG)
		cout <<tmp->cus->cust_num <<"-------------------curr_sys_time : " << curr_sys_time_ << endl;
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
			if(DEBUG)
			cout << cnter << endl;
			if (finishing && cnter == 0)
				stopMachine = true;
			break;
		}
	}
	cout << "MEAN SYS TIME: " << sum_sys_time_ / TARGET_CUST_NUM << endl;
//	fout_cust_sys_time_mean << "MEAN SYS TIME: "
//			<< sum_sys_time_ / TARGET_CUST_NUM << endl;
//	double sum=0;
	for (int i = 0; i < TARGET_CUST_NUM; i++) {
		cus_sys_time_arr[i]=cusArray[i].sys_leave_time - cusArray[i].sys_arrive_time;
//		cout << "--- " << cusArray[i].sys_leave_time <<"|"<< cusArray[i].sys_arrive_time<<" | " cusArray[i].sys_leave_time - cusArray[i].sys_arrive_time<< endl;
//		sum+=cusArray[i].sys_leave_time - cusArray[i].sys_arrive_time;
//		fout_cust_sys_time_mean << cusArray[i].sys_arrive_time << " "
//				<< cusArray[i].sys_leave_time << " "
//				<< cusArray[i].sys_leave_time - cusArray[i].sys_arrive_time
//				<< endl;
	}
//	cout << "MEAN SYS TIME: " << sum / TARGET_CUST_NUM << endl;

}

double getTime(double lamda, int *seed) {
	*seed = gen1(1, a, m, c, *seed);
	double R_time = (double) *seed / m;
	double time = getExpDisX(lamda, R_time);
	if(DEBUG)
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
