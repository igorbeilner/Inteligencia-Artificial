#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 131					/* numero maximo de ponto */
#define w1 0.3					/* ponderacao para o atributo iluminacao */
#define w2 0.7					/* ponderacao para o atributo largura */
#define C_TOPOLOGY 8			/* numero de colunas do mapa */
#define L_TOPOLOGY 8			/* numero de linhas do mapa */
#define EUCLIDEANDISTANCE(x0,y0,x1,y1) sqrt(w1*pow(x1-x0,2)+w2*pow(y1-y0,2))	/* macro para calculo da distancia euclidiana */
#define N_ATTRIBUTES 2			/* quantidade de atributos */
#define T 131					/* numero de iteracoes para treinamento da rede */
#define MYRAND ((float)(random())/(float)(RAND_MAX) ) 		/* macro MYRAND: gera numeros float entre 0 e 1 */
#define N0 0.3					/* valor do aprendizado inicial */
#define D0 L_TOPOLOGY/2			/* valor da vizinhanca inicial */

void rateInit			(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES], float *learningRate, int *neighbors);
void showKohonenMap		(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES]);
void competitiveFase	(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES], float attributes[], int similarNeuron[]);
void collaborativeFase 	(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES], int i, int j, float *learningRate, float attVet[], int *neighbors);
void learning 			(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES], float attributesMatrix[MAX][N_ATTRIBUTES], float *learningRate, int *neighbors);
void application 		(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES], float attributesMatrix[MAX][N_ATTRIBUTES]);
void showPoints(float attributesMatrix[MAX][N_ATTRIBUTES], char type[]);

void rateInit(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES], float *learningRate, int *neighbors) {			/* inicializa os pesos do mapa */
	int i, j;

	for(i=0; i<L_TOPOLOGY; i++) {
		for(j=0; j<C_TOPOLOGY; j++) {
			kohonenMap[i][j][0] = 0.7;//MYRAND;	/* inicializa atributo iluminacao */
			kohonenMap[i][j][1] = 0.7;//MYRAND;	/* inicializa atributo largura */
		}
	}

	*learningRate = N0;						/* inicializa a taxa de aprendizado */
	*neighbors 	  = D0;						/* inicializa a vizinhanca */
}

void showKohonenMap(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES]) {
	int i, j;

	for(i=0; i<L_TOPOLOGY; i++) {
		for(j=0; j<C_TOPOLOGY; j++)
			printf(" %f", kohonenMap[i][j][0]);
		printf("\n");
	}

	printf("\n");

	for(i=0; i<L_TOPOLOGY; i++) {
		for(j=0; j<C_TOPOLOGY; j++)
			printf(" %f", kohonenMap[i][j][1]);
		printf("\n");
	}

	printf("\n");
}

void competitiveFase(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES], float attributes[], int similarNeuron[]) {
	int i, j;
	float mindist, dist;

	/* inicializa e menor distancia como sendo a do primeiro neuronio */
	mindist = EUCLIDEANDISTANCE(attributes[0],attributes[1],kohonenMap[0][0][0],kohonenMap[0][0][1]);

	for(i=0; i<L_TOPOLOGY; i++) {
		for(j=0; j<C_TOPOLOGY; j++) {
			dist = EUCLIDEANDISTANCE(attributes[0],attributes[1],kohonenMap[i][j][0],kohonenMap[i][j][1]);
			if(dist < mindist) {		/* verifica se a distancia atual e menor que a menor ate entao */
				mindist = dist;			/* se sim, atualiza a menor distancia */
				similarNeuron[0] = i;
				similarNeuron[1] = j;
			}
		}
	}
}

void collaborativeFase(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES], int i, int j, float *learningRate, float attVet[], int *neighbors) {
	int k;

	kohonenMap[i][j][0] = kohonenMap[i][j][0] + (*learningRate * (attVet[0] - kohonenMap[i][j][0]));
	kohonenMap[i][j][1] = kohonenMap[i][j][1] + (*learningRate * (attVet[1] - kohonenMap[i][j][1]));

	for(k=1; k<=*neighbors; k++) {
		if(i+k < L_TOPOLOGY) {
			kohonenMap[i+k][j][0] = kohonenMap[i+k][j][0] + (*learningRate * (attVet[0] - kohonenMap[i+k][j][0]));
			kohonenMap[i+k][j][1] = kohonenMap[i+k][j][1] + (*learningRate * (attVet[1] - kohonenMap[i+k][j][1]));
		}
		if(i-k >= 0) {
			kohonenMap[i-k][j][0] = kohonenMap[i-k][j][0] + (*learningRate * (attVet[0] - kohonenMap[i-k][j][0]));
			kohonenMap[i-k][j][1] = kohonenMap[i-k][j][1] + (*learningRate * (attVet[1] - kohonenMap[i-k][j][1]));
		}
		if(j+k < C_TOPOLOGY) {
			kohonenMap[i][j+k][0] = kohonenMap[i][j+k][0] + (*learningRate * (attVet[0] - kohonenMap[i][j+k][0]));
			kohonenMap[i][j+k][1] = kohonenMap[i][j+k][1] + (*learningRate * (attVet[1] - kohonenMap[i][j+k][1]));
		}
		if(j-k >= 0) {
			kohonenMap[i][j-k][0] = kohonenMap[i][j-k][0] + (*learningRate * (attVet[0] - kohonenMap[i][j-k][0]));
			kohonenMap[i][j-k][1] = kohonenMap[i][j-k][1] + (*learningRate * (attVet[1] - kohonenMap[i][j-k][1]));
		}
	}
}

void learning(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES], float attributesMatrix[MAX][N_ATTRIBUTES], float *learningRate, int *neighbors) {
	int j, i, similarNeuron[2] = {0, 0};		/* posicao do neuronio mais similar na mapa */

	for(j=0; j<T; j++) {
		for(i=0; i<T; i++) {
			competitiveFase(kohonenMap, attributesMatrix[i], similarNeuron);
			collaborativeFase(kohonenMap, similarNeuron[0], similarNeuron[1], learningRate, attributesMatrix[i], neighbors);
		}

		*learningRate 	= (N0 * (1 - (float)((float)j/(float)(T-1))));
		*neighbors 		= (D0 * (1 - (float)((float)j/(float)(T-1))))+0.999999;
	}
}

void application(float kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES], float attributesMatrix[MAX][N_ATTRIBUTES]) {
	int similarNeuron[2] = {0, 0}, i, j;
	char recognizer[L_TOPOLOGY][C_TOPOLOGY], type[MAX];

	for(i=0; i<L_TOPOLOGY; i++) {
		for(j=0; j<C_TOPOLOGY; j++) {
			recognizer[i][j] = '-';			/* Inicializacao do reconecedor */
		}
	}

	for(i=0; i<MAX; i++) {
		competitiveFase(kohonenMap, attributesMatrix[i], similarNeuron);
		if(i < 74 && (recognizer[similarNeuron[0]][similarNeuron[1]] == '-' || recognizer[similarNeuron[0]][similarNeuron[1]] == 'S')) 	{
			recognizer[similarNeuron[0]][similarNeuron[1]] = 'S';		/* Area de reconhecimento de salmao */
			type[i] = 0;
		}
		else if(recognizer[similarNeuron[0]][similarNeuron[1]] == '-' || recognizer[similarNeuron[0]][similarNeuron[1]] == 'R') {
			recognizer[similarNeuron[0]][similarNeuron[1]] = 'R';		/* Area de reconhecimento de robalo */
			type[i] = 1;
		}
		else {
			recognizer[similarNeuron[0]][similarNeuron[1]] = 'T';		/* Area onde nao se sabe o tipo de peixe */
			type[i] = 2;
		}
	}

	for(i=0; i<L_TOPOLOGY; i++) {		/* Impressao do mapa de reconhecimento*/
		printf("\n\t");
		for(j=0; j<C_TOPOLOGY; j++) {
			printf(" %c", recognizer[i][j]);
		}
	}
	printf("\n");
	showPoints(attributesMatrix, type);
}

void showPoints(float attributesMatrix[MAX][N_ATTRIBUTES], char type[]) {
	int i, j, flag;
	for(j=0; j<3; j++) {

		if 		(j==0) 	printf("\nsalmaox = [");
		else if (j==1) 	printf("\nrobalox = [");
		else 			printf("\nnaoseix = [");

		flag=0;
		for(i=0; i<MAX; i++) {
			if(type[i] == j) {
				if(flag) printf(", ");
				printf("%f", attributesMatrix[i][0]);
				flag=1;
			}
		}
		printf("]\n");

		if 		(j==0) 	printf("\nsalmaoy = [");
		else if (j==1) 	printf("\nrobaloy = [");
		else 			printf("\nnaoseiy = [");

		flag=0;
		for(i=0; i<MAX; i++) {
			if(type[i] == j) {
				if(flag) printf(", ");
				printf("%f", attributesMatrix[i][1]);
				flag=1;
			}
		}
		printf("]\n");
	}
}

int main() {
	float attributesMatrix[MAX][N_ATTRIBUTES] = {		/******* SALMAO ********/
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
		{9.0 , 18.6},	{10.0, 20.2},	{10.2, 17.0}
	};
	float 	kohonenMap[L_TOPOLOGY][C_TOPOLOGY][N_ATTRIBUTES];/* = {
		{ {3.036612, 20.282764}, {5.384319, 20.453667}, {6.858189, 20.423548}, {7.806494, 19.801142} },
		{ {2.333054, 19.957819}, {4.070303, 19.510410}, {6.324040, 19.271618}, {7.734942, 18.759115} },
		{ {2.391735, 18.930984}, {3.627042, 17.993908}, {5.630729, 17.568308}, {7.563746, 17.676374} },
		{ {2.628274, 17.257336}, {3.336997, 16.261267}, {5.031539, 16.082054}, {7.065407, 16.316362} },
	};*/
	float 	learningRate;
	int 	neighbors;

	srandom(time(NULL));
	rateInit(kohonenMap, &learningRate, &neighbors);
	//showKohonenMap(kohonenMap);
	learning(kohonenMap, attributesMatrix, &learningRate, &neighbors);
	//showKohonenMap(kohonenMap);
	application(kohonenMap, attributesMatrix);

	return 0;
}
