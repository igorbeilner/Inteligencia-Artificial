#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SALMON 0
#define SEABASS 1
#define MAX 131
#define K 6
#define w1 0.7
#define w2 0.3

char typefish(float fish[]) {
	float tSalmao[K][2] = {{2.8 , 16.2}, {2.9 , 16.6}, {3.1 , 16.8}, {3.3 , 17.0}, {3.1 , 17.8}, {2.7 , 17.4}},
		  tRobalo[K][2] = {{7.3 , 18.0}, {7.8 , 18.0}, {7.2 , 18.8}, {7.6 , 18.2}, {7.8 , 18.6}, {7.2 , 17.6}};

	int i;
	double dEs=0, dEr=0;
	for(i=0; i<K; i++) {
		dEs += w1*pow(fish[0] - tSalmao[i][0], 2) + w2*pow(fish[1] - tSalmao[i][1], 2);
		dEr += w1*pow(fish[0] - tRobalo[i][0], 2) + w2*pow(fish[1] - tRobalo[i][1], 2);
	}

	if((sqrt(dEr)/K) < (sqrt(dEs)/K)) return SEABASS;

	return SALMON;
}

int main() {					/******** SALMAO *********/
	float fish[MAX][2] = {
		{1.58, 14.6},	{1.2 , 15.2},	{1.58, 16.4},	{1.2 , 17.4},	{1.1 , 18.6},	{1.2 , 19.8},
		{0.8 , 20.7},	{1.2 , 21.4},	{1.4 , 21.0},	{1.4 , 18.2},	{1.5 , 21.1},	{1.6 , 20.0},
		{1.6 , 19.3},	{2.0 , 16.0},	{2.0 , 16.8},	{2.0 , 17.4},	{2.0 , 18.4},	{2.0 , 20.0},
		{2.1 , 20.8},	{2.2 , 19.2},	{2.3 , 18.2},	{2.5 , 15.2},	{2.8 , 16.2},	{2.7 , 17.4},
		{2.8 , 18.2},	{2.8 , 19.0},	{2.7 , 19.6},	{2.8 , 19.6},	{2.7 , 20.3},	{2.8 , 21.0},
		{2.9 , 16.6},	{3.2 , 15.6},	{3.1 , 16.8},	{3.1 , 17.8},	{3.0 , 20.6},	{3.5 , 15.0},
		{3.6 , 15.2},	{3.6 , 16.2},	{3.3 , 16.8},	{3.3 , 17.0},	{3.6 , 17.2},	{3.5 , 18.0},
		{3.2 , 18.6},	{3.3 , 18.8},	{3.3 , 19.6},	{3.3 , 20.2},	{3.6 , 19.8},	{3.7 , 19.2},
		{3.8 , 18.4},	{3.7 , 16.4},	{4.0 , 16.2},	{4.0 , 17.2},	{4.1 , 17.3},	{4.1 , 17.6},
		{4.1 , 18.6},	{4.4 , 16.6},	{4.4 , 15.8},	{4.5 , 15.0},	{5.0 , 14.4},	{5.2 , 15.0},
		{5.6 , 15.6},	{4.8 , 16.0},	{4.8 , 16.4},	{4.8 , 17.0},	{4.8 , 17.8},	{4.7 , 18.0},
		{5.2 , 16.6},	{5.8 , 16.2},	{4.7 , 19.2},	{4.4 , 20.2},	{5.2 , 19.6},	{6.0 , 18.8},
		{6.3 , 16.6},	{6.6 , 16.0},
								/******* ROBALO *********/
		{4.0 , 17.6},	{4.5 , 16.8},	{4.5 , 18.8},	{4.8 , 20.0},	{5.2 , 18.8},	{5.7 , 17.6},
		{6.6 , 16.0},	{7.7 , 15.0},	{5.2 , 20.0},	{5.6 , 19.0},	{6.0 , 18.2},	{6.6 , 17.6},
		{7.1 , 17.0},	{7.6 , 16.4},	{8.4 , 16.0},	{8.8 , 15.0},	{8.8 , 16.0},	{8.0 , 16.8},
		{7.7 , 17.6},	{7.2 , 17.6},	{7.3 , 18.0},	{6.8 , 18.2},	{6.4 , 19.0},	{6.0 , 19.4},
		{5.6 , 20.8},	{5.3 , 21.2},	{6.0 , 20.6},	{6.2 , 20.2},	{6.4 , 19.6},	{7.2 , 19.4},
		{6.8 , 19.0},	{7.3 , 19.0},	{7.2 , 18.8},	{7.2 , 18.4},	{7.6 , 18.2},	{7.8 , 18.6},
		{7.8 , 18.0},	{8.4 , 17.6},	{8.1 , 18.4},	{8.4 , 18.2},	{8.1 , 19.0},	{8.0 , 19.2},
		{7.6 , 19.4},	{7.0 , 20.2},	{6.4 , 21.0},	{6.4 , 22.0},	{7.0 , 21.8},	{7.4 , 21.0},
		{7.5 , 20.4},	{8.0 , 19.6},	{8.4 , 19.6},	{8.4 , 19.8},	{8.1 , 20.6},	{7.8 , 21.6},
		{9.0 , 18.6},	{10.0, 20.2},	{10.2, 17.0}};

	int i, qtdRobalo=0, qtdSalmao=0, type[MAX], eR=0, eS=0;
	for(i=0; i<MAX; i++) {
		type[i] = typefish(fish[i]);
		if(type[i] == SEABASS) qtdRobalo++;
		else qtdSalmao++;

		if(type[i] == SEABASS && i <  73) {
			eS++;
			printf("Salmao reconhecido como robalo[%f , %f]\n", fish[i][0], fish[i][1]);
		} else if(type[i] == SALMON  && i >= 73) {
			eR++;
			printf("Robalo reconhecido como salmao[%f , %f]\n", fish[i][0], fish[i][1]);
		}
	}

	printf("%d - SALMOES\n", qtdSalmao);
	printf("%d - ROBALOS\n", qtdRobalo);
	printf("%d - ERRO SALMAO\n", eS);
	printf("%d - ERRO ROBALO\n", eR);

	return 0;
}
