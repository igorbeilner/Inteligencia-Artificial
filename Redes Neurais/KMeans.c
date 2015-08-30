#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 131
#define K 2
#define w1 0.7
#define w2 0.3

char distancia(float centroide[K][2], float fish[]) {

	int i, j;
	double distancia[K], mindist;
	for(i=0; i<K; i++)
		distancia[i] = sqrt(w1*pow(fish[0] - centroide[i][0], 2) + w2*pow(fish[1] - centroide[i][1], 2));

	mindist = distancia[0];
	j=0;
	for(i=0; i<K; i++) {
		if(distancia[i] < mindist) {
			mindist = distancia[i];
			j=i;
		}
	}
	return j;
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

	int i, j, cont1, cont2;
	char M[MAX], N, flag, aux=0;
	float centroide[K][2] = {{1.58, 14.6},	{1.2 , 15.2}};

	while(1) {
		flag = 0;
		for(i=0; i<MAX; i++) {

			if(!aux) {
				M[i] = distancia(centroide, fish[i]);
				flag = 1;
			} else {
				N = distancia(centroide, fish[i]);
				if(N != M[i]) {
					M[i] = N;
					flag = 1;
				}
			}
		}

		for(i=0; i<K; i++) {
			centroide[i][0] = 0;
			centroide[i][1] = 0;
		}

		cont1 = cont2 = 0;
		for(i=0; i<MAX; i++) {
			if(!M[i]) {
				centroide[0][0] += fish[i][0];
				centroide[0][1] += fish[i][1];
				cont1++;
			} else {
				centroide[1][0] += fish[i][0];
				centroide[1][1] += fish[i][1];
				cont2++;
			}
		}

		if(cont1) {
			centroide[0][0] /= cont1;
			centroide[0][1] /= cont1;
		}

		if(cont2) {
			centroide[1][0] /= cont2;
			centroide[1][1] /= cont2;
		}

		aux++;
		if(!flag || aux > 100) break;
	}

	printf("centroide salmao: [%f, %f]\n", centroide[0][0], centroide[0][1]);
	printf("centroide robalo: [%f, %f]\n", centroide[1][0], centroide[1][1]);

	if(cont1 > cont2)
		printf("%d - SALMOES\n%d - ROBALOS\n", cont1, cont2);
	else
		printf("%d - SALMOES\n%d - ROBALOS\n", cont2, cont1);
	for(i=0; i<MAX; i++) {
		if(!(i%74)) printf("\n");
		printf("%d ", M[i]);
	}
	printf("\n");

	for(j=0; j<2; j++) {

		if 		(j==0) 	printf("\nsalmaox = [");
		else if (j==1) 	printf("\nrobalox = [");
		else 			printf("\nnaoseix = [");

		flag=0;
		for(i=0; i<MAX; i++) {
			if(M[i] == j) {
				if(flag) printf(", ");
				printf("%f", fish[i][0]);
				flag=1;
			}
		}
		printf("]\n");

		if 		(j==0) 	printf("\nsalmaoy = [");
		else if (j==1) 	printf("\nrobaloy = [");
		else 			printf("\nnaoseiy = [");

		flag=0;
		for(i=0; i<MAX; i++) {
			if(M[i] == j) {
				if(flag) printf(", ");
				printf("%f", fish[i][1]);
				flag=1;
			}
		}
		printf("]\n");
	}

	return 0;
}
