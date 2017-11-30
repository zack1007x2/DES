/*
 * week6.cpp
 *
 *  Created on: 2017年10月19日
 *      Author: Zack
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include "week6.h"
#include "week4.h"

long input[1000];

using namespace std;

const double e = exp(1);
const long a = 16807; //7^5
const long m = 2147483647;
const long c = 0;


double getExpDisX(double lambda, double R) {
	return -1 / lambda * log(1 - R);
}

void ex8() {
	int seed_1 = 129;
	int seed_2 = 423;
	long input1[1000];
	long input2[1000];

	char filename1[] =
			"/Users/Zack/Documents/DiscreteEventSim/week6_out_seed_1.txt";
	char filename2[] =
			"/Users/Zack/Documents/DiscreteEventSim/week6_out_seed_2.txt";

	gen3(a, m, c, seed_1, 1, filename1, 1000);
	gen3(a, m, c, seed_2, 1, filename2, 1000);

	ifstream fin;
	fin.open(filename1);
	if (!fin) {
		cout << "Fail to open file: " << filename1 << endl;
		return;
	} else {
		int i = 0;
		string str;
		while (getline(fin, str)) {
			input1[i] = atol(str.c_str());
			i++;
		}
	}
	fin.close();

	fin.open(filename2);
	if (!fin) {
		cout << "Fail to open file: " << filename2 << endl;
		return;
	} else {
		int i = 0;
		string str;
		while (getline(fin, str)) {
			input2[i] = atol(str.c_str());
			i++;
		}
	}
	fin.close();

	//inter arrival
	double lamda_arrive = (double) 1 / 10;
	long arr_mean_sum = 0;
	long arr_var_sq_sum = 0;

	for (int i = 0; i < 1000; i++) {
		double R = (double) input1[i] / m;
		input1[i] = getExpDisX(lamda_arrive, R);
		arr_mean_sum += input1[i];
		arr_var_sq_sum += pow(input1[i], 2);
	}
	double arr_mean_sq = pow((double) arr_mean_sum / 1000, 2);
	double arr_mean_of_var_sq = ((double) arr_var_sq_sum / 1000);
	cout << "arrive time mean : " << (double) arr_mean_sum / 1000 << endl;
	cout << "arrive time standard deviation : "
			<< pow(arr_mean_of_var_sq - arr_mean_sq, 0.5) << endl;

	//service
	double lamda_ser = 1.0/8;
	double ser_mean_sum = 0;
	double ser_var_sq_sum = 0;

	for (int i = 0; i < 1000; i++) {
		double X = getExpDisX(lamda_ser, (double)input2[i]/m);
		ser_mean_sum += X;
		ser_var_sq_sum += pow(X, 2);
	}
	double ser_mean_sq = pow((double) ser_mean_sum / 1000, 2);
	double ser_mean_of_var_sq = ((double) ser_var_sq_sum / 1000);

//	printf("E[X]2=%f\n", ser_mean_sq);
//	printf("E[X2]=%f\n", ser_mean_of_var_sq);
	cout << "service time mean : " << (double) ser_mean_sum / 1000 << endl;
	cout << "service time standard deviation : "
			<< pow(ser_mean_of_var_sq - ser_mean_sq, 0.5) << endl;

}

void ex7(){
		char filename[] = "/Users/Zack/Documents/DiscreteEventSim/week6_out.txt";

		gen3(a, m, c, 2, 1, filename, 1000);
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
				//			cout << "Read from file: " << input[i] << endl;
				i++;
			}
		}
		fin.close();

		long mean_sum = 0;
		long var_sq_sum = 0;
		double lambda = (double) 1 / 10;

		for (int i = 0; i < 1000; i++) {
			double R = (double) input[i] / m;
			input[i] = getExpDisX(lambda, R);
			mean_sum += input[i];
			var_sq_sum += pow(input[i], 2);
		}

		double mean_sq = pow((double) mean_sum / 1000, 2);
		double mean_of_var_sq = ((double) var_sq_sum / 1000);

		printf("E[X]2=%f\n", mean_sq);
		printf("E[X2]=%f\n", mean_of_var_sq);
		cout << "exercise 7 :" << endl;
		cout << (double) mean_sum / 1000 << endl;
		cout << pow(mean_of_var_sq - mean_sq, 0.5) << endl;
}

week6::week6() {
	ex7();

	cout << "exercise 8 :" << endl;
	ex8();
	return;
}

