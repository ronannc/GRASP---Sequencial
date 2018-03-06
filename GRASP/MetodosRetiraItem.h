#pragma once

//#include "objeto.h"
#include <stdio.h>
#include <stdlib.h>

//retira os itens com menor indice de ganho - aleatorio segundo tamanho_RCL
void retira_menor_indice(int number_of_itens, bool *solutionParcial, item *size_of_itens, int &peso, int &valor, int tamanho_RCL, int seed) {

	float peso_valor = (float)valor;
	int idAux = 0;
	int	idRand = 0;

	int *rcl;
	rcl = (int *)malloc(tamanho_RCL * sizeof(int));
	if (!rcl) {
		printf("Sem memoria disponivel rcl SA id!\n");
		//exit(1);
	}

	//pega os n itens com menor relacao peso valor
	for (int i = 0; i < tamanho_RCL; i++) {
		for (int j = 0; j < number_of_itens; j++) {
			if (solutionParcial[j]) {
				if (((float)size_of_itens[j].valor / (float)size_of_itens[j].peso) < peso_valor) {
					idAux = j;
					peso_valor = (float)size_of_itens[j].valor / (float)size_of_itens[j].peso;
				}
			}
		}
		solutionParcial[idAux] = 0;
		rcl[i] = idAux;
		peso_valor = valor;
	}

	idRand = rand() % tamanho_RCL;
	//printf("idRand %d\n", idRand);
	for (int i = 0; i < tamanho_RCL; i++) {
		solutionParcial[rcl[i]] = 1;
	}

	//retiro o elemento da solucao
	solutionParcial[rcl[idRand]] = 0;
	valor -= size_of_itens[rcl[idRand]].valor;
	peso -= size_of_itens[rcl[idRand]].peso;

	//printf("depois de tirar o numero\n");
	//printf("numero retirado peso %d valor %d\n", size_of_itens[rcl[idRand]].peso, size_of_itens[rcl[idRand]].valor);
	//revisao(number_of_itens, solutionParcial, size_of_itens);

	free(rcl);
}

//retira o item com maior peso - aleatorio segundo tamanho_RCL
void retira_maior_peso(int number_of_itens, bool *solutionParcial, item *size_of_itens, int &peso, int &valor, int tamanho_RCL, int seed) {

	int peso_valor = peso;
	int idAux = 0;
	int idRand = 0;

	int *rcl;
	rcl = (int *)malloc(tamanho_RCL * sizeof(int));
	if (!rcl) {
		printf("Sem memoria disponivel rcl SA id!\n");
		//exit(1);
	}

	//pega os n itens com maior peso
	for (int i = 0; i < tamanho_RCL; i++) {
		for (int j = 0; j < number_of_itens; j++) {
			if (solutionParcial[j]) {
				if (size_of_itens[j].peso < peso_valor) {
					idAux = j;
					peso_valor = size_of_itens[j].peso;
				}
			}
		}
		solutionParcial[idAux] = 0;
		rcl[i] = idAux;
		peso_valor = peso;
	}

	idRand = rand() % tamanho_RCL;
	//printf("idRand %d\n", idRand);
	for (int i = 0; i < tamanho_RCL; i++) {
		solutionParcial[rcl[i]] = 1;
	}

	//retiro o elemento da solucao
	solutionParcial[rcl[idRand]] = 0;
	valor -= size_of_itens[rcl[idRand]].valor;
	peso -= size_of_itens[rcl[idRand]].peso;

	//printf("depois de tirar o numero\n");
	//printf("numero retirado peso %d valor %d\n", size_of_itens[rcl[idRand]].peso, size_of_itens[rcl[idRand]].valor);
	//revisao(number_of_itens, solutionParcial, size_of_itens);

	free(rcl);
}

//retira o item com menor valor - aleatorio segundo tamanho_RCL
void retira_menor_valor(int number_of_itens, bool *solutionParcial, item *size_of_itens, int &peso, int &valor, int tamanho_RCL, int seed) {

	int peso_valor = valor;
	int idAux = 0;
	int idRand = 0;

	int *rcl;
	rcl = (int *)malloc(tamanho_RCL * sizeof(int));
	if (!rcl) {
		printf("Sem memoria disponivel rcl SA id!\n");
		//exit(1);
	}

	//pega os n itens com maior peso
	for (int i = 0; i < tamanho_RCL; i++) {
		for (int j = 0; j < number_of_itens; j++) {
			if (solutionParcial[j]) {
				if (size_of_itens[j].valor < peso_valor) {
					idAux = j;
					peso_valor = size_of_itens[j].valor;
				}
			}
		}
		solutionParcial[idAux] = 0;
		rcl[i] = idAux;
		peso_valor = valor;
	}

	idRand = rand() % tamanho_RCL;
	//printf("idRand %d\n", idRand);
	for (int i = 0; i < tamanho_RCL; i++) {
		solutionParcial[rcl[i]] = 1;
	}

	//retiro o elemento da solucao
	solutionParcial[rcl[idRand]] = 0;
	valor -= size_of_itens[rcl[idRand]].valor;
	peso -= size_of_itens[rcl[idRand]].peso;

	//printf("depois de tirar o numero\n");
	//printf("numero retirado peso %d valor %d\n", size_of_itens[rcl[idRand]].peso, size_of_itens[rcl[idRand]].valor);
	//revisao(number_of_itens, solutionParcial, size_of_itens);

	free(rcl);
}