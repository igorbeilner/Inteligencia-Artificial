#include <stdio.h>
#include <math.h>

#define RESOLUCAO 13

void media(unsigned char image[RESOLUCAO][RESOLUCAO], int kernel) {

}

void moda(unsigned char image[RESOLUCAO][RESOLUCAO], int kernel) {

}

void mediana(unsigned char image[RESOLUCAO][RESOLUCAO], int kernel) {

}

void imread(char *csvFile, unsigned char image[RESOLUCAO][RESOLUCAO]) {
	char 	caracter,
			valor[sizeof(int)];

	int 	i=0, j, k=0, l=0;

	FILE 	*F = fopen(csvFile, "rb");

	if(F == NULL)
		printf("Arquino nao encontrado\n");

	while((fgetc (F) != EOF)) {
		fseek(F, -1, 1);

		if(fread(&caracter, sizeof(char), 1, F)){
			if(caracter == ',') {
				image[k][l] = 0;
				for(j=0; j<i; j++) image[k][l] += (valor[j]-0x30)*(pow(10, (i-1)-j));
				l++;
				i=0;
				continue;
			}
			if(caracter == '\n') {
				image[k][l] = 0;
				for(j=0; j<i-1; j++) image[k][l] += (valor[j]-0x30)*(pow(10, (i-2)-j));
				k++; l=0;
				i=0;
				continue;
			}
			valor[i] = caracter;
			i++;
		}
	}

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++)
			printf("%-4d ", image[i][j]);
		printf("\n");
	}

}

int main(int argc, char *argv[]) {
	unsigned char image[RESOLUCAO][RESOLUCAO];

	imread(argv[1], image);

	return 0;
}
