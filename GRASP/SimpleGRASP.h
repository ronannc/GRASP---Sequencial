#include <stdio.h>
#include <stdlib.h>
#include "MetodosCompletaSolucao.h"
#include "MetodosRetiraItem.h"

//função conferi o andamento do algoritmo - debug
 void revisao(int number_of_itens, bool *solutionParcial, item *size_of_itens);
 //gera a solução inicial - aleatorizado
 void GreedyRandomizedConstruction(int number_of_itens, bool *solutionParcial, item *size_of_itens, int bin_capacity, int seed, int tamanho_RCL, int &peso, int &valor);
 //faz a busca local
 void LocalSearch(int number_of_itens, bool *solutionParcial, int bin_capacity, item *size_of_itens, int seed, int &valor_parcial, int &peso_parcial, int tamanho_RCL);
 //Simulated Annealing - metodo para a busca local
 void SA(int number_of_itens, bool *solutionParcial, int bin_capacity, item *size_of_itens, int seed, int valor_parcial, int peso_parcial, int temperatura, int decaimento_temperatura, int tamanho_RCL);
 //Atualiza a solução final com a melhor solução maximizando o ganho (valor)
 void UpdateSolution(bool *solutionParcial, bool *solutionFinal, int number_of_itens);
 
 //GRASP 
 void simpleGRASP(int max_iter, int number_of_itens, int bin_capacity, item *size_of_itens, bool *soluctions, int temperatura, int decaimento_temperatura, int tamanho_RCL, int seed, int &max_valor) {

	//solução parcial da iteração
	bool *solutionParcial;
	solutionParcial = (bool *)malloc(number_of_itens * sizeof(bool));
	//verificando se foi alocado
	if (!solutionParcial) {
		printf("Sem memoria disponivel!\n");
		//exit(1);
	}
	//inicializando - todos itens fora da solução == 0
	for (int i = 0; i < number_of_itens; i++) {
		solutionParcial[i] = 0;
	}

	int  i, j = 0;

	int valor_parcial, peso_parcial = 0;

	for (i = 0; i < max_iter; i++) {

		/*inicio grasp*/

		//gera solução inicial
		GreedyRandomizedConstruction(number_of_itens, solutionParcial, size_of_itens, bin_capacity, seed + i, tamanho_RCL, peso_parcial, valor_parcial);

		//printf("Solucao gerada inicialmente\n");
		//printf("peso: %d  valor: %d\n\n", peso_parcial, valor_parcial);

		//revisao(number_of_itens, solutionParcial, size_of_itens);

		//faz a busca local tentando melhorar a solução gerada
		LocalSearch(number_of_itens, solutionParcial, bin_capacity, size_of_itens, seed + i, valor_parcial, peso_parcial, tamanho_RCL);
		//SA(number_of_itens, solutionParcial, bin_capacity, size_of_itens, seed + i, valor_parcial, peso_parcial, temperatura, decaimento_temperatura, tamanho_RCL);

		//printf("Solucao gerado depois da busca \n");
	    //printf("peso: %d  valor: %d\n\n", peso_parcial, valor_parcial);

		//revisao(number_of_itens, solutionParcial, size_of_itens);

		//atualiza a solução
		if (valor_parcial > max_valor) {
			max_valor = valor_parcial;
			UpdateSolution(solutionParcial, soluctions, number_of_itens);
		}

		//a cada iteração reseta peso, valor e a solução parcial
		peso_parcial = 0;
		valor_parcial = 0;

		for (j = 0; j < number_of_itens; j++) {
			solutionParcial[j] = 0;
		}
	}

	free(solutionParcial);
}

 void GreedyRandomizedConstruction(int number_of_itens, bool *solutionParcial, item *size_of_itens, int bin_capacity, int seed, int tamanho_RCL, int &peso, int &valor) {
	
	 //completa com os melhor elementos segundo seus indeces
	 max_indice(number_of_itens, solutionParcial, size_of_itens, bin_capacity, tamanho_RCL, peso, valor, seed);
}

 void LocalSearch(int number_of_itens, bool *solutionParcial, int bin_capacity, item *size_of_itens, int seed, int &valor_parcial, int &peso_parcial, int tamanho_RCL) {

	int valor_parcial_busca = valor_parcial;

	bool flag = true;

	while (flag) {
		flag = false;
		
		retira_menor_indice(number_of_itens, solutionParcial, size_of_itens, peso_parcial, valor_parcial, 5, seed);

		//retira_maior_peso(number_of_itens, solutionParcial, size_of_itens, peso_parcial, valor_parcial, 1, seed);

		//retira_menor_valor(number_of_itens, solutionParcial, size_of_itens, peso_parcial, valor_parcial, 1, seed);
		
		//max_valor(number_of_itens, solutionParcial, size_of_itens, bin_capacity, peso_parcial, valor_parcial);

		max_indice(number_of_itens, solutionParcial, size_of_itens, bin_capacity, 10, peso_parcial, valor_parcial, seed);

		if (valor_parcial > valor_parcial_busca) {
			valor_parcial_busca = valor_parcial;
			flag = true;
		}
	}

}

 void SA(int number_of_itens, bool *solutionParcial, int bin_capacity, item *size_of_itens, int seed, int valor_parcial, int peso_parcial, int temperatura, int decaimento_temperatura, int tamanho_RCL) {

	//salvando a solucao gerada inicialmente
	int temperaturaFinal = temperatura;

	bool *current_soluctoin;
	current_soluctoin = (bool *)malloc(number_of_itens * sizeof(bool));

	if (!solutionParcial) {
		printf("Sem memoria disponivel!\n");
		//exit(1);
	}
	int i = 0;
	for (i = 0; i < number_of_itens; i++) {
		current_soluctoin[i] = solutionParcial[i];
	}
	int currente_valor = valor_parcial;
	int current_peso = peso_parcial;

	while (temperaturaFinal > 0) {

		retira_menor_indice(number_of_itens, solutionParcial, size_of_itens, peso_parcial, valor_parcial, 7, seed);

		//completa_solucao2(number_of_itens, solutionParcial, size_of_itens, bin_capacity, peso_parcial, valor_parcial);

		max_indice(number_of_itens, solutionParcial, size_of_itens, bin_capacity, 80, peso_parcial, valor_parcial, seed);

		if (valor_parcial > currente_valor) {
			//aceita a solucao
			currente_valor = valor_parcial;
			current_peso = peso_parcial;
			for (i = 0; i < number_of_itens; i++) {
				current_soluctoin[i] = solutionParcial[i];
			}
		}
		else {
			//verifica temperatura
			if (rand() % temperatura > temperaturaFinal) {
				valor_parcial = currente_valor;
				peso_parcial = current_peso;

				for (i = 0; i < number_of_itens; i++) {
					solutionParcial[i] = current_soluctoin[i];
				}
				
			}
			temperaturaFinal -= decaimento_temperatura;
		}

		
	}
}

 void UpdateSolution(bool *solutionParcial, bool *solutionFinal, int number_of_itens) {

	for (int j = 0; j < number_of_itens; j++) {
		if (solutionParcial[j]) {
			solutionFinal[j] = 1;
		}
		else {
			solutionFinal[j] = 0;
		}
	}
}

 void revisao(int number_of_itens, bool *solutionParcial, item *size_of_itens) {
	int peso_parcial = 0;
	int valor_parcial = 0;

	for (int j = 0; j < number_of_itens; j++) {
		if (solutionParcial[j]) {
			peso_parcial += size_of_itens[j].peso;
			valor_parcial += size_of_itens[j].valor;
		}
	}

	printf("(revisao)\n");
	printf("peso: %d  valor: %d\n\n", peso_parcial, valor_parcial);
}