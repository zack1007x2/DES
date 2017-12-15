/*
 * week12.cpp
 *
 *  Created on: 2017年12月5日
 *      Author: Zack
 */

#include "week12.h"
#include "week11.h"
#include <iostream>
#include <math.h>

using namespace std;

map<MAP_TAG, double> mMap;

double getRamVar(double SAMPLE_MEAN, double SAMPLE_VAR, double MEAN, int N) {
	return (SAMPLE_MEAN - MEAN) / SAMPLE_VAR / sqrt(N);
}
week12::week12() {
	// TODO Auto-generated constructor stub
	//100 200 400 800 1600 3200
	double conf;
	double sample_mean;
	double sample_var;
	double mean;
	//90%

	int N = 100;
	mMap = runMM1(4,5, 3428765, 879076, N);
	sample_mean = mMap[SAMPLE_MEAN];
	sample_var = mMap[SAMPLE_VAR];
	mean = mMap[MEAN];
	double S_100 = getRamVar(sample_mean, sample_var, mean, N);

	conf = 1.98421695;
	cout << "SAMPLE "<<N<<"'s RamVar : "<< S_100 << "\n-90% confidence intervals : +-"<<conf<<endl;
	if ((S_100 < conf) && (S_100 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;

	conf = 2.62640546;
	cout << "-99% confidence intervals : +-"<<conf<<endl;
	if ((S_100 < conf) && (S_100 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;

	N = 200;
	mMap = runMM1(4,5, 234246, 234624645, N);
	sample_mean = mMap[SAMPLE_MEAN];
	sample_var = mMap[SAMPLE_VAR];
	mean = mMap[MEAN];
	double S_200 = getRamVar(sample_mean, sample_var, mean, N);

	conf = 1.97195656;
	cout << "SAMPLE "<<N<<"'s RamVar : "<< S_200 << "\n-90% confidence intervals : +-"<<conf<<endl;
	if ((S_200 < conf) && (S_200 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;

	conf = 2.60076021;
	cout << "-99% confidence intervals : +-"<<conf<<endl;
	if ((S_200 < conf) && (S_200 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;


	N = 400;
	mMap = runMM1(4,5,5347, 56474, N);
	sample_mean = mMap[SAMPLE_MEAN];
	sample_var = mMap[SAMPLE_VAR];
	mean = mMap[MEAN];
	double S_400 = getRamVar(sample_mean, sample_var, mean, N);

	conf = 1.96592730;
	cout << "SAMPLE "<<N<<"'s RamVar : "<< S_400 << "\n-90% confidence intervals : +-"<<conf<<endl;
	if ((S_400 < conf) && (S_400 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;

	conf = 2.58820717;
	cout << "-99% confidence intervals : +-"<<conf<<endl;
	if ((S_400 < conf) && (S_400 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;


	N = 800;
	mMap = runMM1(4,5,423785, 8976312, N);
	sample_mean = mMap[SAMPLE_MEAN];
	sample_var = mMap[SAMPLE_VAR];
	mean = mMap[MEAN];
	double S_800 = getRamVar(sample_mean, sample_var, mean, N);

	conf = 1.96293744;
	cout << "SAMPLE "<<N<<"'s RamVar : "<< S_800 << "\n-90% confidence intervals : +-"<<conf<<endl;
	if ((S_800 < conf) && (S_800 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;

	conf = 2.58199653;
	cout << "-99% confidence intervals : +-"<<conf<<endl;
	if ((S_800 < conf) && (S_800 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;


	N = 1600;
	mMap = runMM1(4, 5, 2347896, 2438763, N);
	sample_mean = mMap[SAMPLE_MEAN];
	sample_var = mMap[SAMPLE_VAR];
	mean = mMap[MEAN];
	double S_1600 = getRamVar(sample_mean, sample_var, mean, N);

	conf = 1.96144867;
	cout << "SAMPLE "<<N<<"'s RamVar : "<< S_1600 << "\n-90% confidence intervals : +-"<<conf<<endl;
	if ((S_1600 < conf) && (S_1600 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;

	conf = 2.57890755;
	cout << "-99% confidence intervals : +-"<<conf<<endl;
	if ((S_1600 < conf) && (S_1600 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;


	N = 3200;
	mMap = runMM1(4,5, 234345, 2346, N);
	sample_mean = mMap[SAMPLE_MEAN];
	sample_var = mMap[SAMPLE_VAR];
	mean = mMap[MEAN];
	double S_3200 = getRamVar(sample_mean, sample_var, mean, N);

	conf = 1.96070586;
	cout << "SAMPLE "<<N<<"'s RamVar : "<< S_3200 << "\n-90% confidence intervals : +-"<<conf<<endl;
	if ((S_3200 < conf) && (S_3200 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;

	conf = 2.57736705;
	cout << "-99% confidence intervals : +-"<<conf<<endl;
	if ((S_3200 < conf) && (S_3200 > -conf))
		cout << "  Accept" << endl;
	else
		cout << "  Reject" << endl;

}

