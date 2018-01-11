/*
 * week15ex26.cpp
 *
 *  Created on: 2017年12月21日
 *      Author: Zack
 */
#include "week11.h"
#include "week4.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "week15ex26.h"

using namespace std;
bool test1(int cut_at, int cust_cnt, int sep, double ans[]);
double res_mean, res_s;

week15_ex26::week15_ex26() {
	map<MAP_TAG, double>* mMap;
	double T_Value25_fd8000 = 2.24182477;
	double sample_mean_all;
	//run MM1
	int CUST_CNT = 256000;
	bool keepGoing = true;
	do {
		mMap = runMM1(4.5, 5, 3426, 21, CUST_CNT);
		sample_mean_all = (*mMap)[SAMPLE_MEAN];
		double* ser_t_list = getDetailList();
		delete mMap;
		bool test = test1(500, CUST_CNT, 10, ser_t_list);
		CUST_CNT *= 2;

		cout << "CNT:" << CUST_CNT << endl;

		double upper_bounds = sample_mean_all
				+ T_Value25_fd8000 * (sqrt(res_s) / sqrt(10 - 1));
		double lower_bounds = sample_mean_all
				- T_Value25_fd8000 * (sqrt(res_s) / sqrt(10 - 1));

		cout << "MEAN : " << res_mean << endl;
		cout << "UPPER : " << upper_bounds << endl;
		cout << "LOWER : " << lower_bounds << endl;
		double interval = abs(1-(upper_bounds / res_mean));
		cout << "C.I.% : " << interval << endl;

		if(test && interval<0.02){
			keepGoing=false;
		}

		cout << "##############################" << endl;
	} while (keepGoing);
	cout<<"FINISH"<<endl;
}

bool test1(int cut_at, int cust_cnt, int sep, double* ans) {
	int team_cnt = (cust_cnt - cut_at) / sep;
	map<int, double> s_map;
	double cut_mean = 0;
	int row_cnt = 0;
	int counter = 0;
	for (int i = cut_at; i < cust_cnt; i++) {
		cut_mean += ans[i]; //Y_bar
		s_map[row_cnt] += ans[i];
		counter++;
		if (counter == team_cnt) {
			s_map[row_cnt] = s_map[row_cnt] / team_cnt;
			counter = 0;
			row_cnt++;
		}
	}

	cut_mean = cut_mean / (cust_cnt - cut_at);
	cout << "maen : " << cut_mean << endl;
	res_mean = cut_mean;
	//S_2
	double S_sqr_sum = 0;
	for (int i = 0; i < sep; i++) {
		S_sqr_sum += pow((s_map[i] - cut_mean), 2);
	}
	cout << "S_sqr : " << S_sqr_sum / (sep - 1) << endl;
	res_s = S_sqr_sum / (sep - 1);
	double roh = 0;
	double roh_sum = 0;

	for (int i = 0; i < (sep - 1); i++) {
		roh_sum += (s_map[i] - cut_mean) * (s_map[i + 1] - cut_mean);
	}
	roh = roh_sum / S_sqr_sum;
	cout << "roh:" << roh << endl;
	return roh < 0.2 ? true : false;
}
