/*
 * week8.cpp
 *
 *  Created on: 2017年11月9日
 *      Author: Zack
 */
#include "week8.h"
#include "week4.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

const long a = 16807; //7^5
const long m = 2147483647;
const long c = 0;

int getXEx13(double R, double q) {
	return (int) (((log(1 - R) / log(1 - q)) - 1) + 1);
}
void ex13() {
	double p = 0.2;
	double q = 0.8;
	char filename[] = "/Users/Zack/Documents/DiscreteEventSim/week8_13_out.txt";
	double input[1000] = { 0 };
	int ret[1000] = { 0 };

	long mean_sum = 0;
	long var_sq_sum = 0;
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
			input[i] = (double) atol(str.c_str()) / m;
			ret[i] = getXEx13(input[i], q);
			mean_sum += ret[i];
			var_sq_sum += pow(ret[i], 2);
			i++;
		}
	}
	fin.close();

	//cal
	double mean_sq = pow((double) mean_sum / 1000, 2);
	double mean_of_var_sq = ((double) var_sq_sum / 1000);

//	printf("E[X]2=%f\n", mean_sq);
//	printf("E[X2]=%f\n", mean_of_var_sq);
	cout << "\nexercise 13 :" << endl;
	cout << "平均：" << (double) mean_sum / 1000 << endl;
	cout << "標準差：" << pow(mean_of_var_sq - mean_sq, 0.5) << endl;

}
void ex14() {
	char filename[] = "/Users/Zack/Documents/DiscreteEventSim/week8_14_out.txt";
	double mean_sum = 0;
	double var_sq_sum = 0;

	gen3(a, m, c, 2, 1, filename, 10000);
	ifstream fin;
	fin.open(filename);
	if (!fin) { //如果開啟檔案失敗，fp為0；成功，fp為非0
		cout << "Fail to open file: " << filename << endl;
		return;
	} else {
		int i = 0;
		string str;
		while (getline(fin, str) && i < 1000) {
			double cur = (double) atol(str.c_str()) / m;
			if (cur >= 0.25) {
				mean_sum += cur;
				var_sq_sum += pow(cur, 2);
			} else
				continue;
			i++;
		}
	}
	fin.close();

	double mean_sq = pow((double) mean_sum / 1000, 2);
	double mean_of_var_sq = ((double) var_sq_sum / 1000);
	cout << "\nexercise 14 :" << endl;
	cout << "平均：" << (double) mean_sum / 1000 << endl;
	cout << "標準差：" << pow(mean_of_var_sq - mean_sq, 0.5) << endl;
}

double getLamda(double t) {
	int stat = t / 60;
	switch (stat) {
	case 0:
		return 1.0 / 15;
	case 1:
		return 1.0 / 12;
	case 2:
		return 1.0 / 7;
	case 3:
		return 1.0 / 5;
	case 4:
		return 1.0 / 8;
	case 5:
		return 1.0 / 10;
	case 6:
		return 1.0 / 15;
	case 7:
		return 1.0 / 20;
	default:
		return 1.0 / 20;
	}
}
void ex15() {
	int seed_1 = 312;
	int seed_2 = 44;
	const double max_lamda = 1.0 / 5;
	double t = 0;
	double E = 0;
	char filename1[] =
			"/Users/Zack/Documents/DiscreteEventSim/week8_15_1_out.txt";
	char filename2[] =
			"/Users/Zack/Documents/DiscreteEventSim/week8_15_2_out.txt";
	double input[101] = { 0 };
	double mean_sum = 0;
	double var_sq_sum = 0;
	gen3(a, m, c, seed_1, 1, filename1, 10000);
	gen3(a, m, c, seed_2, 1, filename2, 10000);
	ifstream fin1;
	ifstream fin2;
	fin1.open(filename1);
	fin2.open(filename2);
	if (!fin1 || !fin2) { //如果開啟檔案失敗，fp為0；成功，fp為非0
		cout << "Fail to open file " << endl;
		return;
	} else {
		int i = 0;
		string str;
		while (i < 100) {
			//get R
			getline(fin1, str);
			input[i] = (double) atol(str.c_str()) / m;
//			cout<<"R : "<<input[i] <<endl;
			E = -5 * log(input[i]);
			t = t + E;
			//get R'
			getline(fin2, str);
			input[i + 1] = (double) atol(str.c_str()) / m;
//			cout<<"R\'"<<input[i + 1] <<endl;

			double standard = getLamda(t) / max_lamda;

			if (input[i + 1] < standard) { 			//accept
				mean_sum += E;
				var_sq_sum += pow(E, 2);
				i++;
			} else 									//else reject
				continue;
		}
	}
	fin1.close();
	fin2.close();

	double mean_sq = pow((double) mean_sum / 1000, 2);
	double mean_of_var_sq = ((double) var_sq_sum / 1000);

//	printf("E[X]2=%f\n", mean_sq);
//	printf("E[X2]=%f\n", mean_of_var_sq);
	cout << "\nexercise 15 :" << endl;
	cout << "平均：" << (double) mean_sum / 1000 << endl;
	cout << "標準差：" << pow(mean_of_var_sq - mean_sq, 0.5) << endl;
}
week8::week8() {
	ex13();
	ex14();
	ex15();
}

