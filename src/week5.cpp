/*
 * week5.cpp
 *
 *  Created on: 2017年10月18日
 *      Author: Zack
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

#include "week5.h"
#include "week4.h"

using namespace std;

const long m = 2147483647;
const double D_alpha = 0.21012;
double r_array[100];
double n_array[100];

void ex4(long input[], int needSort) {
	if(needSort)
	sort(input, input + 100);
	double max;

	for (int i = 0; i < 100; i++) {
		r_array[i] = (double) input[i] / m;
		n_array[i] = (double) i / 100;
//		printf("input : %d | r: %f\n", input[i], r_array[i]);
//		printf("n: %f\n", n_array[i]);
		if ((r_array[i] - n_array[i]) > max) {
			max = r_array[i] - n_array[i];
		}
		if ((n_array[i] - r_array[i]) > max) {
			max = n_array[i] - r_array[i];
		}
	}

	printf("Max = %f\n", max);
	if (max < D_alpha) {
		printf("Not Reject\n");
	} else {
		printf("Reject\n");
	}
}

void ex5() {
	//Exercise 5
	int o_array[10];
	double x0squ = 0;
	for (int i = 0; i < 10; i++) {
		o_array[i] = 0;
	}
	for (int i = 0; i < sizeof(r_array) / sizeof(r_array[0]); i++) {
		o_array[(int) (r_array[i] * 10)] += 1;
	}
	for (int i = 0; i < 10; i++) {
//		printf("O : %d\n", o_array[i]);
		x0squ += (double) pow((o_array[i] - 10), 2) / 10;
	}
	printf("X0^2: %f \n", x0squ);
}

void ex6(long input_ex6[]) {
	ex4(input_ex6, 0);
	double tmp = 0;
	double prev = 0;
	double sum = 0;
	double rho = 0;
	double sigma = 0;
	int Big_M = 0;
	for (int i = 4; i < 100; i += 5) {
		if (i == 4) {
			prev = r_array[i];
			continue;
		}
		tmp = r_array[i];
		sum += prev * tmp;
		prev = tmp;
		Big_M++;
	}
	rho = (sum / (Big_M + 1)) - 0.25;
	sigma = pow(13 * Big_M + 7, 0.5) / (12 * (Big_M + 1));

	printf("M : %d \n", Big_M);
	printf("Rho : %f | Sigma : %f \n", rho, sigma);
	printf("Z0 : %f \n", rho / sigma);
}

week5::week5() {
	long input_ex4[100];
	long input_ex6[100];
	char filename[] = "/Users/Zack/Documents/DiscreteEventSim/week5_out.txt";
	const long a = 16807; //7^5
	const long m = 2147483647;
	const long c = 0;
	gen3(a, m, c, 2, 1, filename,100);
	ifstream fin;
	fin.open(filename);
	if (!fin) { //如果開啟檔案失敗，fp為0；成功，fp為非0
		cout << "Fail to open file: " << filename << endl;
		return;
	} else {
		int i = 0;
		string str;
		while (getline(fin, str)) {
			input_ex4[i] = atol(str.c_str());
//			cout << "Read from file: " << input[i] << endl;
			i++;
		}
	}

	copy(input_ex4,input_ex4 + 100, input_ex6);
	ex4(input_ex4, 1);

	ex5();

	ex6(input_ex6);
}

