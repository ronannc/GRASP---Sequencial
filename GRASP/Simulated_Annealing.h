#include <stdlib.h>

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

		roleta(solutionParcial, size_of_itens, number_of_itens, peso_parcial, valor_parcial);

		max_indice(number_of_itens, solutionParcial, size_of_itens, bin_capacity, 1, peso_parcial, valor_parcial, seed);

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
			if (rand() % temperatura < temperaturaFinal) {
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
