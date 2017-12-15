/*
 * week14.cpp
 *
 *  Created on: 2017年12月14日
 *      Author: Zack
 */

#include "week14.h"
#include "week11.h"
#include "week12.h"
#include "week4.h"
#include <math.h>
#include <iostream>
#include <iomanip>;

using namespace std;

double ans[1000];
long double upper_bounds[1000];
long double lower_bounds[1000];
double* detailList;

week14::week14() {

	long a = 16807; //7^5
	long m = 2147483647;
	long c = 0;
	double seed_ser = 31534;
	double cust_arr = 9836;

	double table25_d9 = 2.26215716;

	map<MAP_TAG, double> mMap;
	for (int i = 0; i < 1000; i++) {
		seed_ser = gen1(1, a, m, c, seed_ser);
		cust_arr = gen1(1, a, m, c, cust_arr);
		mMap = runMM1(4.5, 5, cust_arr, seed_ser, i+1);
		sample_means[i%10] = mMap[SAMPLE_MEAN];
		means[i%10] = mMap[MEAN];
		mMap.clear();
//		mMap = runMM1(4.5, 5, 12234, 67547, i);
//		sample_means[1] = mMap[SAMPLE_MEAN];
//		means[1] = mMap[MEAN];
//		mMap.clear();
//		mMap = runMM1(4.5, 5, 24364, 23463, i);
//		sample_means[2] = mMap[SAMPLE_MEAN];
//		means[2] = mMap[MEAN];
//		mMap.clear();
//		mMap = runMM1(4.5, 5, 768574, 34554, i);
//		sample_means[3] = mMap[SAMPLE_MEAN];
//		means[3] = mMap[MEAN];
//		mMap.clear();
//		mMap = runMM1(4.5, 5, 6758574, 980765, i);
//		sample_means[4] = mMap[SAMPLE_MEAN];
//		means[4] = mMap[MEAN];
//		mMap.clear();
//		mMap = runMM1(4.5, 5, 639494, 837366, i);
//		sample_means[5] = mMap[SAMPLE_MEAN];
//		means[5] = mMap[MEAN];
//		mMap.clear();
//		mMap = runMM1(4.5, 5, 385, 546372, i);
//		sample_means[6] = mMap[SAMPLE_MEAN];
//		means[6] = mMap[MEAN];
//		mMap.clear();
//		mMap = runMM1(4.5, 5, 123, 45677, i);
//		sample_means[7] = mMap[SAMPLE_MEAN];
//		means[7] = mMap[MEAN];
//		mMap.clear();
//		mMap = runMM1(4.5, 5, 93527, 12435664, i);
//		sample_means[8] = mMap[SAMPLE_MEAN];
//		means[8] = mMap[MEAN];
//		mMap.clear();
//		mMap = runMM1(4.5, 5, 468952, 7866762, i);
//		sample_means[9] = mMap[SAMPLE_MEAN];
//		means[9] = mMap[MEAN];
//		mMap.clear();

		double sample_mean_all = (sample_means[i%10] + sample_means[i%10]
				+ sample_means[i%10] + sample_means[i%10] + sample_means[i%10]
				+ sample_means[i%10] + sample_means[i%10] + sample_means[i%10]
				+ sample_means[i%10] + sample_means[i%10]) / 10; //mean of rep'

		double mean_all = (means[i%10] + means[i%10] + means[i%10] + means[i%10] + means[i%10]
				+ means[i%10] + means[i%10] + means[i%10] + means[i%10] + means[i%10]) / 10; //mean of rep'

		double sum_of_var = 0;
		for (int j = 0; j < 10; j++)
			sum_of_var += pow(sample_means[j] - sample_mean_all, 2);

		double S_sqr = sum_of_var / 9; //var of rep'

		ans[i] = sample_mean_all;
		upper_bounds[i] = sample_mean_all + table25_d9 * (sqrt(S_sqr) / 3);
		lower_bounds[i] = sample_mean_all - table25_d9 * (sqrt(S_sqr) / 3);

		cout << ans[i] << endl;
	}
	cout << "-------------------------------------\n";

	for (int i = 0; i < 1000; i++)
		cout << upper_bounds[i] << endl;
	cout << "-------------------------------------\n";

	for (int i = 0; i < 1000; i++) {
		cout << lower_bounds[i] << endl;
	}

}

