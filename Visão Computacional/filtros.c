#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define RESOLUCAO 13

void media(unsigned char src[RESOLUCAO][RESOLUCAO][21], unsigned char image[RESOLUCAO][RESOLUCAO][21], int m, int kernel) {
	int i, j, k, pixel;

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++) {
			pixel = 0;
			for(k=1; k<=(kernel/2); k++) {

				if((i-k) >= 0) {
					pixel += src[i-k][j][m];
					if((j+k) < RESOLUCAO)
						pixel += src[i-k][j+k][m];
					if((j-k) >= 0)
						pixel += src[i-k][j-k][m];
				}

				if((i+k) < RESOLUCAO) {
					pixel += src[i+k][j][m];
					if((j+k) < RESOLUCAO)
						pixel += src[i+k][j+k][m];
					if((j-k) >= 0)
						pixel += src[i+k][j-k][m];
				}

				if((j+k) < RESOLUCAO)
					pixel += src[i][j+k][m];
				if((j-k) >= 0)
					pixel += src[i][j-k][m];

			}
			pixel += src[i][j][m];

			image[i][j][m] = pixel/(kernel*kernel);
		}
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

void moda(unsigned char src[RESOLUCAO][RESOLUCAO][21], unsigned char image[RESOLUCAO][RESOLUCAO][21], int m, int kernel) {
	int i, j, k, l;
	unsigned char *pixel = (unsigned char*)malloc((kernel*kernel)*(sizeof(unsigned char)));

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++) {
			l = 0;
			for(k=1; k<=(kernel/2); k++) {

				if((i-k) >= 0) {
					pixel[l] = src[i-k][j][m];
					l++;
					if((j+k) < RESOLUCAO) {
						pixel[l] = src[i-k][j+k][m];
						l++;
					}

					if((j-k) >= 0) {
						pixel[l] = src[i-k][j-k][m];
						l++;
					}
				}

				if((i+k) < RESOLUCAO) {
					pixel[l] = src[i+k][j][m];
					l++;
					if((j+k) < RESOLUCAO) {
						pixel[l] = src[i+k][j+k][m];
						l++;
					}

					if((j-k) >= 0) {
						pixel[l] = src[i+k][j-k][m];
						l++;
					}
				}

				if((j+k) < RESOLUCAO) {
					pixel[l] = src[i][j+k][m];
					l++;
				}
				if((j-k) >= 0) {
					pixel[l] = src[i][j-k][m];
					l++;
				}

			}
			pixel[l] = src[i][j][m];

			image[i][j][m] = modav(pixel, kernel);

		}
	}
	free(pixel);
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
	free(aux);
}

void mediana(unsigned char src[RESOLUCAO][RESOLUCAO][21], unsigned char image[RESOLUCAO][RESOLUCAO][21], int m, int kernel) {
	int i, j, k, l;
	unsigned char *pixel = (unsigned char*)malloc((kernel*kernel)*(sizeof(unsigned char)));

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++) {
			l = 0;
			for(k=1; k<=(kernel/2); k++) {

				if((i-k) >= 0) {
					pixel[l] = src[i-k][j][m];
					l++;
					if((j+k) < RESOLUCAO) {
						pixel[l] = src[i-k][j+k][m];
						l++;
					}

					if((j-k) >= 0) {
						pixel[l] = src[i-k][j-k][m];
						l++;
					}
				}

				if((i+k) < RESOLUCAO) {
					pixel[l] = src[i+k][j][m];
					l++;
					if((j+k) < RESOLUCAO) {
						pixel[l] = src[i+k][j+k][m];
						l++;
					}

					if((j-k) >= 0) {
						pixel[l] = src[i+k][j-k][m];
						l++;
					}
				}

				if((j+k) < RESOLUCAO) {
					pixel[l] = src[i][j+k][m];
					l++;
				}
				if((j-k) >= 0) {
					pixel[l] = src[i][j-k][m];
					l++;
				}

			}
			pixel[l] = src[i][j][m];

			merge(pixel, 0, l, kernel);
			image[i][j][m] = pixel[(l/2)];

		}
	}
	free(pixel);
}

void roberts(unsigned char src[RESOLUCAO][RESOLUCAO][21], unsigned char image[RESOLUCAO][RESOLUCAO][21], int m) {
	int i, j;

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++)
			if((i+1) < RESOLUCAO && (j+1) < RESOLUCAO)
				image[i][j][m] = sqrt(pow(src[i][j][m] - src[i+1][j+1][m], 2)) + sqrt(pow(src[i+1][j][m] - src[i][j+1][m], 2));
	}
}

void laplaciano(unsigned char src[RESOLUCAO][RESOLUCAO][21], unsigned char image[RESOLUCAO][RESOLUCAO][21], int m) {
	int i, j, pixel, aux, aux1;

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++) {
			pixel = 0;
			aux1 = 0;

			if((i-1) >= 0)
				pixel += src[i-1][j][m];
			else aux1++;

			if((j-1) >= 0)
				pixel += src[i][j-1][m];
			else aux1++;

			if((j+1) < RESOLUCAO)
				pixel += src[i][j+1][m];
			else aux1++;

			if((i+1) < RESOLUCAO)
				pixel += src[i+1][j][m];
			else aux1++;

			aux = (4-aux1)*(int)(src[i][j][m]) - pixel;

			if(aux < 0) aux = 0;
			else if(aux > 255) aux = 255;
			image[i][j][m] = aux;

		}
	}
}

void showImage(unsigned char image[RESOLUCAO][RESOLUCAO][21]) {
	int i, j, k;

	for(k=0; k<20; k++) {

			printf("\nImagem %d:\n", k+1);
			for(i=0; i<RESOLUCAO; i++) {
				for(j=0; j<RESOLUCAO; j++)
					printf("%-3d ", image[i][j][k]);
				printf("\n");
			}

	}
}

void imRead(char *csvFile, unsigned char image[RESOLUCAO][RESOLUCAO][21], int m) {
	char 	caracter,
			valor[sizeof(int)];

	int 	i=0, j, k=0, l=0;

	FILE 	*F = fopen(csvFile, "rb");

	if(F == NULL)
		printf("Arquivo nao encontrado\n");

	while((fgetc (F) != EOF)) {
		fseek(F, -1, 1);

		if(fread(&caracter, sizeof(char), 1, F)){
			if(caracter == ',') {			// Lê até o separador da coluna
				image[k][l][m] = 0;
				for(j=0; j<i; j++) image[k][l][m] += (valor[j]-0x30)*(pow(10, (i-1)-j));	// Converte de ASCII para decimal
				l++;
				i=0;
				continue;
			}
			if(caracter == '\n') {			// Lê até o fim da linha
				image[k][l][m] = 0;
				for(j=0; j<i-1; j++) image[k][l][m] += (valor[j]-0x30)*(pow(10, (i-2)-j));
				k++; l=0;
				i=0;
				continue;
			}
			valor[i] = caracter;	// Atribui o caracter à respectiva cada decimal
			i++;
		}
	}
	fclose(F);
}

void imWrite(char *csvFile, unsigned char image[RESOLUCAO][RESOLUCAO][21], int m) {
	char 	valor[4], aux[2];

	int 	i, j;

	FILE 	*F = fopen(csvFile, "w+");

	aux[0] = ','; 	// Fim de coluna no arquivo .csv
	aux[1] = '\n'; 	// Fim de linha no arquivo .csv

	if(F == NULL)
		printf("Arquivo nao encontrado\n");


	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++) {
			valor[0] = image[i][j][m]/100 + 0x30;
			valor[1] = (image[i][j][m]%100)/10 +0x30;
			valor[2] = image[i][j][m]%10 + 0x30;
			valor[3] = '\0';

			if(valor[0] != 0x30)
				fwrite(&valor[0], sizeof(char), 1, F);

			if(!(valor[0] == 0x30 && valor[1] == 0x30))
				fwrite(&valor[1], sizeof(char), 1, F);

			fwrite(&valor[2], sizeof(char), 1, F);

			if(j < RESOLUCAO-1)
				fwrite(&aux[0], sizeof(char), 1, F);

		};
		fwrite(&aux[1], sizeof(char), 1, F);
	}
	fclose(F);
}

void binariza(unsigned char src[RESOLUCAO][RESOLUCAO][21], unsigned char image[RESOLUCAO][RESOLUCAO][21], int m) {
	int i, j;

	for(i=0; i<RESOLUCAO; i++) {
		for(j=0; j<RESOLUCAO; j++) {
			if(src[i][j][m] < 27)
				image[i][j][m] = 0;
			else image[i][j][m] = 100;
		}
	}
}

int main(void) {
	unsigned char src[RESOLUCAO][RESOLUCAO][21];
	unsigned char baixa[RESOLUCAO][RESOLUCAO][21];
	unsigned char alta[RESOLUCAO][RESOLUCAO][21];
	unsigned char bin[RESOLUCAO][RESOLUCAO][21];
	int i;
	char fileName[21] = "ImageIrDA/dataxx.csv";
	char fileNameS[22] = "ImageIrDA/ALTASxx.csv";
	char fileNameT[22] = "ImageIrDA/BAIXAxx.csv";

	for(i=1; i<=20; i++) {
		fileName[14] = (i/10) + 0x30;		// Itera nos nomes dos arquivos
		fileName[15] = (i%10) + 0x30;

		imRead(fileName, src, (i-1));
	}
	showImage(src);

	for(i=0; i<20; i++) {

		mediana(src, baixa, i, 5);

	}
	//showImage(baixa);

	for(i=0; i<20; i++) {

		binariza(baixa, bin, i);

	}
	//showImage(bin);

	for(i=0; i<20; i++) {

		laplaciano(bin, alta, i);

	}
	//showImage(alta);

	for(i=1; i<=20; i++) {					// Salva arquivos das imagens pré processadas
		fileNameT[15] = (i/10) + 0x30;		// Itera nos nomes dos arquivos
		fileNameT[16] = (i%10) + 0x30;

		imWrite(fileNameT, baixa, (i-1));
	}

	for(i=1; i<=20; i++) {					// Salva arquivos das imagens pós processadas
		fileNameS[15] = (i/10) + 0x30;		// Itera nos nomes dos arquivos
		fileNameS[16] = (i%10) + 0x30;

		imWrite(fileNameS, alta, (i-1));
	}

	return 0;
}
