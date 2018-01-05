/*
 * week13.cpp
 *
 *  Created on: 2017年12月7日
 *      Author: Zack
 */

#include "week13.h"
#include "week11.h"
#include "week4.h"
#include <iostream>
#include <map>
#include <math.h>
#include <fstream>

using namespace std;

double epsilon = 0.02;
map<int, double> tTable95;
double sample_means[5];
double R, H;

week13::week13() {
	map<MAP_TAG, double>* mMap;
	// TODO Auto-generated constructor stub
	tTable95[4] = 3.494;
	tTable95[5] = 3.164;
	tTable95[6] = 2.969;
	tTable95[7] = 2.841;
	tTable95[8] = 2.752;
	tTable95[9] = 2.685;
	tTable95[10] = 2.634;
	tTable95[50] = 2.0085;
	tTable95[1432] = 1.96162196;
	tTable95[1431] = 1.96162312;
	tTable95[1430] = 1.96162428;
	tTable95[878] = 1.96266952;
	tTable95[879] = 1.96266644;

	mMap = runMM1(4.5, 5, 7534, 548764, 1000);
	sample_means[0] = (*mMap)[SAMPLE_MEAN];

	mMap = runMM1(4.5, 5, 12234, 67547, 1000);
	sample_means[1] = (*mMap)[SAMPLE_MEAN];

	mMap = runMM1(4.5, 5, 24364, 23463, 1000);
	sample_means[2] = (*mMap)[SAMPLE_MEAN];

	mMap = runMM1(4.5, 5, 768574, 34554, 1000);
	sample_means[3] = (*mMap)[SAMPLE_MEAN];

	mMap = runMM1(4.5, 5, 6758574, 980765, 1000);
	sample_means[4] = (*mMap)[SAMPLE_MEAN];

	double mean_all = (sample_means[0] + sample_means[1] + sample_means[2]
			+ sample_means[3] + sample_means[4]) / 5; //mean of rep'

	double sum_of_var = 0;
	for (int i = 0; i < 5; i++)
		sum_of_var += pow(sample_means[i] - mean_all, 2);

	double S_sqr = sum_of_var / 4; //var of rep'

	//R=879
	H = tTable95[878] * sqrt(S_sqr) / sqrt(879); //H0

	cout << "H : " << H << endl;

	R = pow((tTable95[878] * sqrt(S_sqr) / epsilon), 2);

	cout << "R : " << R << endl;

	//R=880
	H = tTable95[879] * sqrt(S_sqr) / sqrt(880); //H0

	cout << "H : " << H << endl;

	R = pow((tTable95[879] * sqrt(S_sqr) / epsilon), 2);

	cout << "R : " << R << endl;

}

