#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RESOLUCAO 13

void media(unsigned char src[RESOLUCAO][RESOLUCAO], int kernel) {
	unsigned char image[RESOLUCAO][RESOLUCAO];
	int i, j, k, pixel;

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++) {
			pixel = 0;
			for(k=1; k<=(kernel/2); k++) {

				if((i-k) >= 0) {
					pixel += src[i-k][j];
					if((j+k) < RESOLUCAO)
						pixel += src[i-k][j+k];
					if((j-k) >= 0)
						pixel += src[i-k][j-k];
				}

				if((i+k) < RESOLUCAO) {
					pixel += src[i+k][j];
					if((j+k) < RESOLUCAO)
						pixel += src[i+k][j+k];
					if((j-k) >= 0)
						pixel += src[i+k][j-k];
				}

				if((j+k) < RESOLUCAO)
					pixel += src[i][j+k];
				if((j-k) >= 0)
					pixel += src[i][j-k];

			}
			pixel += src[i][j];

			image[i][j] = pixel/(kernel*kernel);
		}
	}

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++)
			printf("%-4d ", image[i][j]);
		printf("\n");
	}

}

unsigned char modav(unsigned char *vet, int len) {
	unsigned char bin[255];
	int i, j=0, max=0;

	for(i=0; i<255; i++) bin[i] = 0;

	for(i=0; i<len; i++) {
		bin[vet[i]] += 1;
		if(bin[vet[i]] > max) {
			max = bin[vet[i]];
			j=vet[i];
		}
	}

	return j;
}

void moda(unsigned char src[RESOLUCAO][RESOLUCAO], int kernel) {
	unsigned char image[RESOLUCAO][RESOLUCAO];
	int i, j, k, l;
	unsigned char *pixel = (unsigned char*)malloc((kernel*kernel)*(sizeof(unsigned char)));

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++) {
			l = 0;
			for(k=1; k<=(kernel/2); k++) {

				if((i-k) >= 0) {
					pixel[l] = src[i-k][j];
					l++;
					if((j+k) < RESOLUCAO) {
						pixel[l] = src[i-k][j+k];
						l++;
					}

					if((j-k) >= 0) {
						pixel[l] = src[i-k][j-k];
						l++;
					}
				}

				if((i+k) < RESOLUCAO) {
					pixel[l] = src[i+k][j];
					l++;
					if((j+k) < RESOLUCAO) {
						pixel[l] = src[i+k][j+k];
						l++;
					}

					if((j-k) >= 0) {
						pixel[l] = src[i+k][j-k];
						l++;
					}
				}

				if((j+k) < RESOLUCAO) {
					pixel[l] = src[i][j+k];
					l++;
				}
				if((j-k) >= 0) {
					pixel[l] = src[i][j-k];
					l++;
				}

			}
			pixel[l] = src[i][j];

			image[i][j] = modav(pixel, kernel);

		}
	}
	printf("\n");

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++)
			printf("%-4d ", image[i][j]);
		printf("\n");
	}
}

void merge(unsigned char *vet, int p, int q, int kernel) {
	int i, j, k, meio;
	unsigned char *aux = (unsigned char*)malloc((kernel*kernel)*sizeof(unsigned char));
	if (p == q) {
		free(aux);
		return;
	}
	//ordena as duas metades do vetor
	meio = (p+q)/2;
	merge(vet, p, meio, kernel);
	merge(vet, meio+1,q, kernel);
	//faz a ordenaçao em partes no vetor auxiliar
	i = p;
	j = meio+1;
	k = 0;;
	while(i <= meio || j <= q) {
		if(i == meio+1) {//primeira metade do vetor
			aux[k] = vet[j];
			j++;
			k++;
		} else if(j == q+1) {//final da segunda metade do vetor
			aux[k] = vet[i];
			i++;
			k++;
		} else if(vet[i] < vet[j]) {//ordenação no vetor auxiliar se o numero da primeira metade for menor
			aux[k] = vet[i];
			i++;
			k++;
		} else { //ordenação no vetor auxiliar se o numero da segunda metade for menor
			aux[k] = vet[j];
			j++;
			k++;
		}
	}
	//copia vetor intercalado para o vetor original
	for(i=p; i<=q ; i++) {
		vet[i] = aux[i-p];
	}
}

void mediana(unsigned char src[RESOLUCAO][RESOLUCAO], int kernel) {
	unsigned char image[RESOLUCAO][RESOLUCAO];
	int i, j, k, l;
	unsigned char *pixel = (unsigned char*)malloc((kernel*kernel)*(sizeof(unsigned char)));

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++) {
			l = 0;
			for(k=1; k<=(kernel/2); k++) {

				if((i-k) >= 0) {
					pixel[l] = src[i-k][j];
					l++;
					if((j+k) < RESOLUCAO) {
						pixel[l] = src[i-k][j+k];
						l++;
					}

					if((j-k) >= 0) {
						pixel[l] = src[i-k][j-k];
						l++;
					}
				}

				if((i+k) < RESOLUCAO) {
					pixel[l] = src[i+k][j];
					l++;
					if((j+k) < RESOLUCAO) {
						pixel[l] = src[i+k][j+k];
						l++;
					}

					if((j-k) >= 0) {
						pixel[l] = src[i+k][j-k];
						l++;
					}
				}

				if((j+k) < RESOLUCAO) {
					pixel[l] = src[i][j+k];
					l++;
				}
				if((j-k) >= 0) {
					pixel[l] = src[i][j-k];
					l++;
				}

			}
			pixel[l] = src[i][j];

			merge(pixel, 0, l, kernel);
			image[i][j] = pixel[(l/2)];

		}
	}
	printf("\n");

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++)
			printf("%-4d ", image[i][j]);
		printf("\n");
	}

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

	printf("\n");

	//media(image, 3);
	//mediana(image, 3);
	moda(image, 3);

	return 0;
}
