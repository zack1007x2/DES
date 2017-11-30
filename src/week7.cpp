/*
 * week7.cpp
 *
 *  Created on: 2017年11月9日
 *      Author: Zack
 */
#include "week7.h"
#include "week4.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;
const long a = 16807; //7^5
const long m = 2147483647;
const long c = 0;

double getEx9X(double lower, double upper, double R) {
	return lower + ((upper - lower) * R);
}
void ex9() {
	double upper = 1500;
	double lower = 46;
	double input[1000];
	int result[10];
	for (int i = 0; i < 10; i++) {
		result[i] = 0;
	}
	char filename[] = "/Users/Zack/Documents/DiscreteEventSim/week7_9_out.txt";

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
			//getX
			input[i] = getEx9X(lower, upper, (double) atol(str.c_str()) / m);
			int status = input[i] / 150;
			switch (status) {
			case 0:
				result[0]++;
				break;
			case 1:
				result[1]++;
				break;
			case 2:
				result[2]++;
				break;
			case 3:
				result[3]++;
				break;
			case 4:
				result[4]++;
				break;
			case 5:
				result[5]++;
				break;
			case 6:
				result[6]++;
				break;
			case 7:
				result[7]++;
				break;
			case 8:
				result[8]++;
				break;
			case 9:
				result[9]++;
				break;
			}

			i++;
		}
	}
	fin.close();
	cout << "\nexercise 9:" << endl;
	for (int i = 0; i < 10; i++)
		cout << "Area" << i + 1 << " : " << result[i] << endl;
}

double getXEx10(double x_inter, double a, double R, double c) {
	return x_inter + a * (R - c);
}
void ex10() {
	const double a1 = 0.81;
	const double a2 = 5;
	const double a3 = 2;
	const double a4 = 1.47;

	char filename[] = "/Users/Zack/Documents/DiscreteEventSim/week7_10_out.txt";
	double input[100] = { 0 };
	int cnts[4] = { 0 };

	gen3(a, m, c, 2, 1, filename, 100);
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
			//			cout << "Read from file: " << input[i] << endl;
			if (input[i] <= 0.31) {
				input[i] = getXEx10(0.25, a1, input[i], 0);
			} else if (0.31 < input[i] <= 0.41) {
				input[i] = getXEx10(0.5, a2, input[i], 0.31);
			} else if (0.41 < input[i] <= 0.66) {
				input[i] = getXEx10(1, a3, input[i], 0.41);
			} else {
				input[i] = getXEx10(1.5, a4, input[i], 0.66);
			}

			if (0.25 < input[i] && input[i] <= 0.5) {
				cnts[0]++;
			} else if (0.5 < input[i] && input[i] <= 1.0) {
				cnts[1]++;
			} else if (1.0 < input[i] && input[i] <= 1.5) {
				cnts[2]++;
			} else if (1.5 < input[i] && input[i] <= 2.0) {
				cnts[3]++;
			}

			i++;
		}
	}
	fin.close();
	cout << "\nexercise 10:" << endl;
	for (int i = 0; i < 4; i++) {
		cout << cnts[i] << endl;
	}

}

double getXEx11(double R) {
	return (pow(R, 0.135) - pow((1 - R), 0.135)) / 0.1975;
}
void ex11() {
	char filename[] = "/Users/Zack/Documents/DiscreteEventSim/week7_9_out.txt";
	double input[1000];
	double mean_sum = 0;
	double var_sq_sum = 0;

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
			//cout << "Read from file: " << input[i] << endl;
			input[i] = getXEx11(input[i]);
			mean_sum += input[i];
			var_sq_sum += pow(input[i], 2);
			i++;
		}
	}
	fin.close();

	//cal
	double mean_sq = pow((double) mean_sum / 1000, 2);
	double mean_of_var_sq = ((double) var_sq_sum / 1000);

//	printf("E[X]2=%f\n", mean_sq);
//	printf("E[X2]=%f\n", mean_of_var_sq);
	cout << "\nexercise 11 :" << endl;
	cout << (double) mean_sum / 1000 << endl;
	cout << pow(mean_of_var_sq - mean_sq, 0.5) << endl;

}
void ex12() {
	char filename[] = "/Users/Zack/Documents/DiscreteEventSim/week7_10_out.txt";
	double input[100] = { 0 };
	int cnts[3] = { 0 };
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
//			cout<< input[i]<<endl;
			if (input[i] <= 0.5) {
				input[i] = 0;
				cnts[0]++;
			} else if (0.5 < input[i] && input[i] <= 0.8) {
				input[i] = 1;
				cnts[1]++;
			} else {
				input[i] = 2;
				cnts[2]++;
			}
			i++;
		}
	}
	fin.close();

	cout << "\nexercise12:" << endl;
	cout << (double) cnts[0] / 100 << endl;
	cout << (double) cnts[1] / 100 << endl;
	cout << (double) cnts[2] / 100 << endl;

}

week7::week7() {
	ex9();
	ex10();
	ex11();
	ex12();
}

