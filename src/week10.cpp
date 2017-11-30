/*
 * week10.cpp
 *
 *  Created on: 2017年11月16日
 *      Author: Zack
 */

#include "week10.h"
#include "week4.h"
#include "week7.h"
#include "week6.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

const long a = 16807; //7^5
const long m = 2147483647;
const long c = 0;

void ex19() {

	int seed1 = 234;
	int seed2 = 55;
	int muX1 = 2;
	int muX2 = 4;
	int sigX1 = 2;
	int sigX2 = 2;
	double ro = 0.7;

	char filename1[] =
			"/Users/Zack/Documents/DiscreteEventSim/week10_19_1_out.txt";
	char filename2[] =
			"/Users/Zack/Documents/DiscreteEventSim/week10_19_2_out.txt";
	double inputX1[100];
	double inputX2[100];
	double mean_sum_1 = 0;
	double var_sq_sum_1 = 0;
	double mean_sum_2 = 0;
	double var_sq_sum_2 = 0;

	gen3(a, m, c, seed1, 1, filename1, 100);
	gen3(a, m, c, seed2, 1, filename2, 100);

	ifstream fin1, fin2;
	fin1.open(filename1);
	fin2.open(filename2);
	if (!fin1 || !fin2) { //如果開啟檔案失敗，fp為0；成功，fp為非0
		cout << "Fail to open file" << endl;
		return;
	} else {
		int i = 0;
		string str;
		double Z1, Z2;
		while (i < 100) {
			//X1
			getline(fin1, str);
			inputX1[i] = (double) atol(str.c_str()) / m;
			inputX1[i] = getXEx11(inputX1[i]);
			Z1 = inputX1[i];
			inputX1[i] = muX1 + sigX1 * Z1;
//			cout << "Read from file: " << inputX1[i] << endl;
			mean_sum_1 += inputX1[i];
			var_sq_sum_1 += pow(inputX1[i], 2);

			getline(fin2, str);
			inputX2[i] = (double) atol(str.c_str()) / m;
			inputX2[i] = getXEx11(inputX2[i]);
			Z2 = inputX2[i];
			inputX2[i] = muX2 + sigX2 * (ro * Z1 + (sqrt(1 - pow(ro, 2)) * Z2));
			mean_sum_2 += inputX2[i];
			var_sq_sum_2 += pow(inputX2[i], 2);
			i++;
		}
	}
	fin1.close();
	fin2.close();

	//get R gen Var X1, X2

	double mean_sq_1 = pow((double) mean_sum_1 / 100, 2);
	double mean_of_var_sq_1 = ((double) var_sq_sum_1 / 100);
	double mean_sq_2 = pow((double) mean_sum_2 / 100, 2);
	double mean_of_var_sq_2 = ((double) var_sq_sum_2 / 100);
	cout << "exercise 19 :" << endl;

	double sample_mean_X1 = (double) mean_sum_1 / 100;
	double sample_mean_X2 = (double) mean_sum_2 / 100;
	cout << "X1平均：" << sample_mean_X1 << endl;
	cout << "X1標準差：" << pow(mean_of_var_sq_1 - mean_sq_1, 0.5) << endl;
	cout << "X2平均：" << sample_mean_X2 << endl;
	cout << "X2標準差：" << pow(mean_of_var_sq_2 - mean_sq_2, 0.5) << endl;
	double sample_sig_X1X2 = pow(mean_of_var_sq_1 - mean_sq_1, 0.5)
			* pow(mean_of_var_sq_2 - mean_sq_2, 0.5);
	double tmp = 0;
	for (int i = 0; i < 100; i++) {
		tmp += (inputX1[i] - sample_mean_X1) * (inputX2[i] - sample_mean_X2);
	}

	double cus_ro = tmp / (99 * sample_sig_X1X2);
	cout << "X1, X2 correlation：" << cus_ro << endl;
}

void ex20() {
	int mu = 2;
	int sig_ep = 2;
	double fi = 0.7;
	int seed = 123;
	int seed_eps = 34;
	double sig_ep_sqr = pow(sig_ep, 2);

	double sig_X1 = sig_ep_sqr / (1 - pow(fi, 2));

	double mean_sum = 0;
	double var_sq_sum = 0;

	//eps_t
	double eps_ts[100] = { 0 };
	double Xi[100] = { 0 };
	char filename1[] =
			"/Users/Zack/Documents/DiscreteEventSim/week10_20_1_out.txt";

	gen3(a, m, c, seed_eps, 1, filename1, 100);

	ifstream fin1;
	fin1.open(filename1);
	if (!fin1) {
		cout << "Fail to open file" << endl;
		return;
	} else {
		int i = 0;
		string str;
		while (i < 100) {
			//X1
			getline(fin1, str);
			eps_ts[i] = (double) atol(str.c_str()) / m;
			eps_ts[i] = getXEx11(eps_ts[i]);
			eps_ts[i] = sig_ep * eps_ts[i]; // 0+sqrt(sig of exp);

			if (i != 0) {
				Xi[i] = mu + fi * (Xi[i - 1] - mu) + eps_ts[i];
			} else {
				double X1 = (double) gen1(1, a, m, c, seed) / m;
				X1 = getXEx11(X1); //get Z1~N(0,1)
//				cout << "X1 : " << X1 << endl;
						//get X1 = mu+sigX1*Z1
				X1 = mu + sqrt(sig_X1) * X1;
				Xi[i] = X1;
			}
			mean_sum += Xi[i];
			var_sq_sum += pow(Xi[i], 2);
			i++;
		}
	}
	fin1.close();

	double mean_sq = pow(mean_sum / 100, 2);
	double mean_of_var_sq = ((double) var_sq_sum / 100);
	double mean_Xi = (double) mean_sum / 100;
	double sig_sqr_Xi = pow(mean_of_var_sq - mean_sq, 0.5);
	cout << "exercise 20 :" << endl;
	cout << "Xt平均：" << mean_Xi << endl;
	cout << "Xt標準差：" << sig_sqr_Xi << endl;

	double sum_tmp = 0;
	for (int i = 0; i < 99; i++) {
		sum_tmp += (Xi[i] - mean_Xi) * (Xi[i + 1] - mean_Xi);
	}
	double cov = (sum_tmp / 98) / pow(sig_sqr_Xi, 2);
	cout << "COV：" << cov << endl;
}
void ex21() {

	int seed = 35127895982;
	int seed_eps = 9873126314;
	int seed_uni = 832957845;
	double FI = 0.7;
	double lamda = 1.0 / 5;

	double mean_sum = 0;
	double var_sq_sum = 0;

	char filename[] =
			"/Users/Zack/Documents/DiscreteEventSim/week10_20_1_out.txt";

	gen3(a, m, c, seed_eps, 1, filename, 100);
	double eps_arr[100] = { 0 };
	double x_arr[100] = { 0 };
	x_arr[0] = (double) gen1(1, a, m, c, seed) / m;
	x_arr[0] = getExpDisX(lamda, x_arr[0]);

	ifstream fin;
	fin.open(filename);
	if (!fin) {
		cout << "Fail to open file" << endl;
		return;
	} else {
		int i = 1;
		string str;
		while (i < 100) {
			getline(fin, str);
			eps_arr[i] = (double) atol(str.c_str()) / m;
			eps_arr[i] = getExpDisX(lamda, eps_arr[0]);
			double R = (double) gen1(1, a, m, c, seed_uni) / m;
			x_arr[i] = FI * x_arr[i - 1];
			if (R > FI) {
				x_arr[i] += eps_arr[i];
			}
			mean_sum += x_arr[i];
			var_sq_sum += pow(x_arr[i], 2);
			i++;
		}
	}
	fin.close();

	double mean_sq = pow(mean_sum / 100, 2);
	double mean_of_var_sq = ((double) var_sq_sum / 100);
	double mean_Xi = (double) mean_sum / 100;
	double sig_sqr_Xi = pow(mean_of_var_sq - mean_sq, 0.5);
	cout << "exercise 21 :" << endl;
	cout << "Xt平均：" << mean_Xi << endl;
	cout << "Xt標準差：" << sig_sqr_Xi << endl;

	double sum_tmp = 0;
	for (int i = 0; i < 99; i++) {
		sum_tmp += (x_arr[i] - mean_Xi) * (x_arr[i + 1] - mean_Xi);
	}
	double cov = (sum_tmp / 98) / pow(sig_sqr_Xi, 2);
	cout << "COV：" << cov << endl;

}
week10::week10() {
//	ex19();
	ex20();
	ex21();
}

