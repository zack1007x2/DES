/*
 * week14.h
 *
 *  Created on: 2017年12月14日
 *      Author: Zack
 */

#ifndef WEEK14_H_
#define WEEK14_H_


class week14 {
	private:
		const static int ROUND_CNT = 10;
		const static int CUST_CNT = 1000;
		double ans[CUST_CNT];
		double sample_means[ROUND_CNT];
		long double upper_bounds[CUST_CNT];
		long double lower_bounds[CUST_CNT];
		double means[ROUND_CNT];
public:
	week14();
};


#endif /* WEEK14_H_ */
