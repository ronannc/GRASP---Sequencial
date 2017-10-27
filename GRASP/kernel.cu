#include "SimplleGRASP.h"

// numero de elementos
int size = 0;
// numero maximo de iteraçoes
int maxIter = 0;
// numero capacidade mochia
int capacidade = 0;

int main(){
	
	node *vectorPeso;
	vectorPeso = (node *)malloc(sizeof(node));

	if (!vectorPeso) {
		printf("Sem memoria disponivel!\n");
		exit(1);
	}

	node *vectorValor;
	vectorValor = (node *)malloc(sizeof(node));

	if (!vectorValor) {
		printf("Sem memoria disponivel!\n");
		exit(1);
	}

	inicia(vectorPeso);
	inicia(vectorValor);

	FILE *arq;
	int aux = 0;
	char s;
	arq = fopen("entrada.txt", "r");

	if (arq == NULL) {

		printf("Erro, nao foi possivel abrir o arquivo\n");
	}else {

		fscanf(arq, "%c %d\n", &s, &size);
		fscanf(arq, "%c %d\n", &s, &capacidade);
		fscanf(arq, "%c %d\n", &s, &maxIter);
		fscanf(arq, "%c\n", &s);
		
		for (int i = 0; i < size; i++) {
			fscanf(arq, "%d\n", &aux);
			insereInicio(vectorPeso, aux);
		}
		
		fscanf(arq, "%c\n", &s);
		//printf("%c", s);
		for (int i = 0; i < size; i++) {
			fscanf(arq, "%d\n", &aux);
			insereInicio(vectorValor, aux);
		}
	}
			
	fclose(arq);

	printf("==========================================\n");
	printf("Dados do problema:\n");
	printf("Capacidade da mochila: %d\n", capacidade);
	printf("Numero de itens: %d\n", size);
	printf("Numero de iterações: %d\n", maxIter);
		
	clock_t t0, tf;
	double tempo_gasto;
	
	t0 = clock();
		simplleGrasp(maxIter, size, capacidade, vectorPeso, vectorValor);
	tf = clock();
	
	tempo_gasto = ((double)(tf - t0)) / CLOCKS_PER_SEC;
	
	printf("Tempo gasto: %lf s\n", tempo_gasto);

	printf("===========================================\n\n");
	
	free(vectorPeso);
	free(vectorValor);
	system("pause");
    return 0;
}