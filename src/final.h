/*
 * final.h
 *
 *  Created on: 2017年12月28日
 *      Author: Zack
 */

#ifndef FINAL_H_
#define FINAL_H_

class final {
public:
	final();
};
const long a = 16807; //7^5
const long m = 2147483647;
const long c = 0;
void runWarehouseMachine();
void runWarehouseMachine(int _cus_seed_poi, int _cus_seed_split,
		int _ser_seed_self, int _ser_seed_mm_help, int _ser_seed_mm_cash);


#endif /* FINAL_H_ */
