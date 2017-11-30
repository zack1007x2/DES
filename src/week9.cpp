/*
 * week9.cpp
 *
 *  Created on: 2017年11月9日
 *      Author: Zack
 */

#include "week9.h"
#include "week4.h"
#include "week7.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

#include "EventList.h"

using namespace std;

const long a = 16807; //7^5
const long m = 2147483647;
const long c = 0;
const double PI = 3.14;
const int k = 2;
const int theta = 5;

void ex18() {
	//cal f-1
	double R[15];
	cout << "\nexercise 18: " << endl;
	for (int i = 1; i <= 15; i++) {
		double input = (double) (i - 0.5) / 15;
		R[i] = getXEx11(input);
		cout << R[i] << endl;
	}
}

double getXEx17(double R1, double R2) {
	return -1.0 / (k * theta) * log(R1 * R2);
}
void ex17() {

	int seed_1 = 47;
	int seed_2 = 94;

	char filename1[] =
			"/Users/Zack/Documents/DiscreteEventSim/week9_17_1_out.txt";
	char filename2[] =
			"/Users/Zack/Documents/DiscreteEventSim/week9_17_2_out.txt";
	double R1[1000];
	double R2[1000];
	double X[1000];
	gen3(a, m, c, seed_1, 1, filename1, 1000);
	gen3(a, m, c, seed_2, 1, filename2, 1000);

	ifstream fin1, fin2;
	fin1.open(filename1);
	fin2.open(filename2);

	double mean_sum = 0;
	double var_sq_sum = 0;

	if (!fin1 || !fin2) { //如果開啟檔案失敗，fp為0；成功，fp為非0
		cout << "Fail to open file: " << filename1 << endl;
		return;
	} else {
		int i = 0;
		string str;
		while (i < 1000) {
			getline(fin1, str);
			R1[i] = (double) atol(str.c_str()) / m;

			getline(fin2, str);
			R2[i] = (double) atol(str.c_str()) / m;

			X[i] = getXEx17(R1[i], R2[i]);
			mean_sum += X[i];
			var_sq_sum += pow(X[i], 2);
			i++;
		}
	}
	fin1.close();
	fin2.close();

	double mean_sq = pow((double) mean_sum / 1000, 2);
	double mean_of_var_sq = ((double) var_sq_sum / 1000);

	cout << "exercise 17 :" << endl;
	cout << "X平均：" << (double) mean_sum / 1000 << endl;
	cout << "X標準差：" << pow(mean_of_var_sq - mean_sq, 0.5) << endl;
}

double getB(double R) {
	return sqrt(-2 * log(R));
}
void ex16() {
	int seed_1 = 523;
	int seed_2 = 249;
	double input1[1000] = { 0 };
	double input2[1000] = { 0 };
	char filename1[] =
			"/Users/Zack/Documents/DiscreteEventSim/week9_16_1_out.txt";
	char filename2[] =
			"/Users/Zack/Documents/DiscreteEventSim/week9_16_2_out.txt";

	gen3(a, m, c, seed_1, 1, filename1, 1000);
	gen3(a, m, c, seed_2, 1, filename2, 1000);

	ifstream fin1, fin2;
	fin1.open(filename1);
	fin2.open(filename2);

	double Z1_arr[1000];
	double Z2_arr[1000];

	double mean_sum_1 = 0;
	double var_sq_sum_1 = 0;

	double mean_sum_2 = 0;
	double var_sq_sum_2 = 0;

	if (!fin1 || !fin2) { //如果開啟檔案失敗，fp為0；成功，fp為非0
		cout << "Fail to open file" << endl;
		return;
	} else {
		int i = 0;
		string str;
		while (i < 1000) {
			getline(fin1, str);
			input1[i] = (double) atol(str.c_str()) / m;
			input1[i] = getB(input1[i]);
			getline(fin2, str);
			input2[i] = (double) atol(str.c_str()) / m;

			Z1_arr[i] = input1[i] * cos(2 * PI * input2[i]);
			Z2_arr[i] = input1[i] * sin(2 * PI * input2[i]);

			mean_sum_1 += Z1_arr[i];
			var_sq_sum_1 += pow(Z1_arr[i], 2);
			mean_sum_2 += Z2_arr[i];
			var_sq_sum_2 += pow(Z2_arr[i], 2);
			i++;
		}
	}
	fin1.close();
	fin2.close();

	double mean_sq_1 = pow((double) mean_sum_1 / 1000, 2);
	double mean_of_var_sq_1 = ((double) var_sq_sum_1 / 1000);

	cout << "\nexercise 16 :" << endl;
	cout << "Z1平均：" << (double) mean_sum_1 / 1000 << endl;
	cout << "Z1標準差：" << pow(mean_of_var_sq_1 - mean_sq_1, 0.5) << endl;

	double mean_sq_2 = pow((double) mean_sum_2 / 1000, 2);
	double mean_of_var_sq_2 = ((double) var_sq_sum_2 / 1000);

	cout << "Z2平均：" << (double) mean_sum_2 / 1000 << endl;
	cout << "Z2標準差：" << pow(mean_of_var_sq_2 - mean_sq_2, 0.5) << endl;
}
//void test() {
//	linkedlist myList;
//	Node * a = new Node;
//	a->data = 1;
//	Node * b = new Node;
//	b->data = 4;
//	Node * c = new Node;
//	c->data = 3;
//	myList.insertNode(a, 1);
//	myList.insertNode(b, 2);
//	myList.insertNode(c, 3);
//	myList.printList();
//}
week9::week9() {
//	ex16();
//	ex17();
//	ex18();
//	test();
}

