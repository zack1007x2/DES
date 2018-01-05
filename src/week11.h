/*
 * week11.h
 *
 *  Created on: 2017年11月23日
 *      Author: Zack
 */

#ifndef WEEK11_H_
#define WEEK11_H_
#include <map>
enum MAP_TAG {
	CUSTOMER_CNT, SAMPLE_MEAN, SAMPLE_VAR, MEAN, SUM_VAR
};
class week11 {

public:
	week11(int CUSTOMER_TOTAL);
	~week11();
};
//std::map<MAP_TAG, double> runMM1(double lamda, double mu, double cus_seed,double ser_seed, int cust_cnt);
std::map<MAP_TAG, double>* runMM1(double lamda, double mu, double cus_seed,double ser_seed, int cust_cnt);
double* getDetailList();
void release_MEMO();
#endif /* WEEK11_H_ */
