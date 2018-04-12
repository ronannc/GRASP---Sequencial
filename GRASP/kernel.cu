/*Bin Packing - two Dimensional
Problema da mochila com duas dimensoes.
Tal problema consiste em escolher o maior numero de itens que comportem em uma mochila (compartimento)

O dataset osado foi o presente na biblioteca ORLIB (OR-Library)

Cada arquivo contem:
Numero de problemas teste
Identificador do Problema
Capacidade do compartimento, numero de itens, numero de itens presentes na melhor solução conhecida.
Tamanho dos itens.
*/

#include "objeto.h"
#include "SimpleGRASP.h"
#include "EntradaDeDados.h"
#include "Selection_Sort.h"
#include "time.h"

#include "SaidaDados.h"

int maximo(int a, int b);
int knapSack(int W, item *itens, int n);

int main() {
	
	//semente para gerador de numeros aleatorios
	srand(time(NULL));
	int seed = rand();
	
	//temperatura inicial e o decaimento da temperatura para SA
	int temperatura = 100;
	int decaimento_temperatura = 1;

	//tamanha usado para tornar a geração da solução inicial e busca aleatoria, se 1 fica modo guloso
	int tamanho_RCL = 10;
	
	//numero de iterações que o GRASP fara
	int max_iter = 1000;

	// numero de elementos
	int quantidade_itens = 0;

	// capacidade mochia
	int capacidade_mochila = 0;

	//recebendo entrada, quantidade e capacidade da mochila
	entrada_dados(quantidade_itens, capacidade_mochila);

	//Vetor usado para guardar peso, valor e ganho
	item *itens;
	itens = (item *)malloc(quantidade_itens * sizeof(item));

	//verificando se alocou o vetor
	if (!itens) {
		printf("Sem memoria disponivel! (itens)\n");
		exit(1);
	}

	//recebendo peso e valor de cada item
	entrada_dados_vetor(itens, quantidade_itens);

	//ordenando os itens com relação ao valor/peso
	selection_sort(itens, quantidade_itens);

	//imprime os itens e seu indece de ganho de modo ordenado
	
	//for (int i = 0; i < quantidade_itens; i++) {
	//	printf("%d %d %f\n", itens[i].peso, itens[i].valor, itens[i].ganho);
	//}

	//system("pause");

	printf("====== Bin Packing - Bi Dimensional ======\n");
	printf("\n");
	printf("              IFMG - Formiga            \n");
	printf(" Desenvolvido por: Ronan Nunes Campos   \n");
	printf(" Matricula: 0011919                     \n");
	printf("\n");
	printf(" Dados do problema           \n\n");
	printf(" Numero de Itens: %d                    \n", quantidade_itens);
	printf(" Capacidade Mochila: %d                 \n", capacidade_mochila);
	printf(" Numero de Iterações: %d                \n", max_iter);
	printf(" Geradas %d solucões\n", max_iter);
	printf(" Rodando na CPU                          \n");
	printf("===========================================\n");

	//vetor para a solução do problema. se 1 esta na mochila de 0 esta fora
	bool *soluctions;
	soluctions = (bool *)malloc(quantidade_itens * sizeof(bool));

	//verificando se alocou o vetor
	if (!soluctions) {
		printf("Sem memoria disponivel! (soluctions)\n");
		exit(1);
	}

	//iniciando a solução com todos os itens fora da mochila == 0
	for (int i = 0; i < quantidade_itens; i++) {
		soluctions[i] = 0;
	}

	// Rodando GRASP sequencial recursivo e calculando o tempo de execução.
	clock_t t0, tf;
	double tempo_gasto;

	//t0 = clock();
		//printf("recursivo: %d\n", knapSack(capacidade_mochila, itens, quantidade_itens));
	//tf = clock();
	
	//tempo gasto pelo GRASP
	//tempo_gasto = ((double)(tf - t0)) / CLOCKS_PER_SEC;
	//printf("\n");
	//printf("Tempo gasto recursivo: %lf s\n", tempo_gasto);

	//rodadndo o GRASP sequncial
	//valor da solução
	int max_valor = 0;
	saida_header();
	for (int k = 0; k < 100; k++) {
	t0 = clock();
		simpleGRASP(max_iter, quantidade_itens, capacidade_mochila, itens, soluctions, temperatura, decaimento_temperatura, tamanho_RCL, seed, max_valor);
	tf = clock();

	tempo_gasto = ((double)(tf - t0)) / CLOCKS_PER_SEC;
	saida_body(max_valor, tempo_gasto, max_iter);
	printf("\n");
	printf("Tempo gasto GRASP: %lf s\n", tempo_gasto);

	printf("===========================================\n\n");
	printf("max valor: %d\n", max_valor);
	for (int i = 0; i < quantidade_itens; i++) {
		printf("%d ", soluctions[i]);
	}

	printf("\n");
	printf("fim :)\n\n");
	}
	free(itens);
	free(soluctions);
	system("pause");
	return 0;
}
// A utility function that returns maximum of two integers
int maximo(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, item *itens, int n)
{
	// Base Case
	if (n == 0 || W == 0)
		return 0;

	// If weight of the nth item is more than Knapsack capacity W, then
	// this item cannot be included in the optimal solution
	if (itens[n - 1].peso > W)
		return knapSack(W, itens, n - 1);

	// Return the maximum of two cases: 
	// (1) nth item included 
	// (2) not included
	else return maximo(itens[n - 1].valor + knapSack(W - itens[n - 1].peso, itens, n - 1),
		knapSack(W, itens, n - 1)
	);
}