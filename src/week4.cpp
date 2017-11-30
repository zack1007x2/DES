/*
 * week4.cpp
 *
 *  Created on: 2017年10月18日
 *      Author: Zack
 */
#include <iostream>
#include <fstream>
#include "week4.h"

using namespace std;

long gen1(int n,long a,long m,long c,long seed){

	int prev_xn=seed;
	long xn;

	while(n>0){
		xn=(a*prev_xn)%m;
		prev_xn=xn;
		n--;
	}
	return xn;
}

void gen2(int n){
	const static long m1 = 2147483563;
	const static long m2 = 2147483399;
	const static long a1 = 40014;
	const static long a2 = 40692;
	const static long seed1 = 0;
	const static long seed2 = 0;
	long x1=235;
	long x2=332;
	long xn1, xn2, xn;
	while(n>0){
		x1 = gen1(n, a1, m1, 0, x1);
		x2 = gen1(n, a2, m2, 0, x2);
		n--;
	}
	long tmp = abs(x1-x2);
	xn = tmp%(m1-1);
	printf("2. Ans: %ld\n",xn);
}

void gen3(long a,long m,long c,long seed, int interval, char filename[], int cnt){

	fstream fp;
	fp.open(filename, ios::out);
	if(!fp){//如果開啟檔案失敗，fp為0；成功，fp為非0
		cout<<"Fail to open file: "<<filename<<endl;
	}


	long cur = seed;

	for(int i=0; i<cnt; i++){
		cur = gen1(interval, a, m, c, cur);
//		printf("%ld\n", cur);
		fp<<cur<<endl;
	}
	fp.close();
}

week4::week4() {
	//gen1
		int input;
		long a=16807;//7^5
		long m=2147483647;
		long c=0;
		long seed=2;//optional
		printf("enter i for 1.: \n");
		scanf("%d", &input);
		long ans = gen1(input, a, m, c, seed);
		printf("1.Ans : %ld\n", ans);

		//gen2
		printf("enter i for 2.: \n");
		scanf("%d", &input);
		gen2(input);

		//gen3
		int seed_gen3=2;
		int interval = 10000000;//10^7
		char filename[]="/Users/Zack/Documents/DiscreteEventSim/week4_out.txt";
		gen3(a, m ,c ,seed_gen3, interval, filename, 100);
		return;
}

