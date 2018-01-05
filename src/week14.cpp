/*
 * week14.cpp
 *
 *  Created on: 2017年12月14日
 *      Author: Zack
 */

#include "week14.h"
#include "week11.h"
#include "week4.h"
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;



week14::week14() {

	long a = 16807; //7^5
	long m = 2147483647;
	long c = 10;
//	double seed_ser = 0;
//	double seed_cus = 0;

	double seed_sers[ROUND_CNT] = { 0 };
	double seed_cuss[ROUND_CNT] = { 0 };

	double T_Value25_fd9 = 2.26215716;

	map<MAP_TAG, double>* mMap;
	//generate seeds
//	for (int i = 0; i < ROUND_CNT; i++) {
//		if (i > 0) {
//			seed_ser = seed_sers[i - 1];
//			seed_cus = seed_cuss[i - 1];
//		}
//		seed_sers[i] = gen1(1, a, m, c, seed_ser);
//		seed_cuss[i] = gen1(1, a, m, c, seed_cus);
//	}

	//gen seed list
	long input[1000];
	char filename[] = "/Users/Zack/Documents/DiscreteEventSim/week14_seed.txt";
//
//	gen3(a, m, c, 4, 1, filename, 1000);
	ifstream fin;
	fin.open(filename);
	if (!fin) { //如果開啟檔案失敗，fp為0；成功，fp為非0
		cout << "Fail to open file: " << filename << endl;
		return;
	} else {
		int i = 0;
		string str;
		while (getline(fin, str)) {
			input[i] = atol(str.c_str());
			i++;
		}
	}
	fin.close();

	for (int i = 0; i < ROUND_CNT; i++) {
		seed_cuss[i] = input[(20+i*2+1)%100];
		seed_sers[i] = input[(7+i*2)%100];
	}

	char file_out[] = "/Users/Zack/Documents/DiscreteEventSim/week14_out.txt";
	ofstream fout;
	fout.open(file_out, ios::out);
	//run MM1
	double sample_mean_all = 0;
	for (int i = 0; i < CUST_CNT; i++) {
		for (int j = 0; j < ROUND_CNT; j++) {
			mMap = runMM1(4.5, 5, seed_cuss[j], seed_sers[j], i + 1);
			sample_means[j] = (*mMap)[SAMPLE_MEAN];
			sample_mean_all += (*mMap)[SAMPLE_MEAN];
			delete mMap;
		}
		sample_mean_all = sample_mean_all / ROUND_CNT; //mean of rep'

		double sum_of_var = 0;
		for (int j = 0; j < ROUND_CNT; j++)
			sum_of_var += pow(sample_means[j] - sample_mean_all, 2);

		double S_sqr = sum_of_var / (ROUND_CNT - 1); //var of rep'

		ans[i] = sample_mean_all;
		upper_bounds[i] = sample_mean_all + T_Value25_fd9 * (sqrt(S_sqr) / sqrt(ROUND_CNT-1));
		lower_bounds[i] = sample_mean_all - T_Value25_fd9 * (sqrt(S_sqr) / sqrt(ROUND_CNT-1));

		cout << ans[i] << endl;
		fout << ans[i] << endl;
	}

	cout << "-------------------------------------\n";
	fout << "-------------------------------------\n";

	for (int i = 0; i < CUST_CNT; i++){
		cout << upper_bounds[i] << endl;
		fout << upper_bounds[i] << endl;
	}

	cout << "-------------------------------------\n";
	fout << "-------------------------------------\n";

	for (int i = 0; i < CUST_CNT; i++){
		cout << lower_bounds[i] << endl;
		fout << lower_bounds[i] << endl;
	}
	fout.close();
}


