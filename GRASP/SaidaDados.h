#include <stdio.h>

void saida_header() {
	FILE *arq;

	arq = fopen("saida.txt", "a");

	if (arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");

	else {

		fprintf(arq, "\n\nSaida de Dados - GRASP Problema da Mochila 0 1 na CPU em modo sequencial\nPara instacia: knapPI_1_2000_1000_1.txt\n\n");
	}
	fclose(arq);
}


void saida_body(int valor, double tempo, int maxIter) {

	FILE *arq;

	arq = fopen("saida.txt", "a");

	if (arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");

	else {

		fprintf(arq, "Max Iter: %d   Tempo: %.2f   Valor: %d\n", maxIter, tempo, valor);
	}
	fclose(arq);
}