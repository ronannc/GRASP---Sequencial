#include "Lista.h"
#include "time.h"

void GreedyRandomizedConstruction(int size, node *solutionParcial, node *vectorPeso, int capacidade);
void LocalSearch(int size, node *solutionParcial, int capacidade, node *vectorPeso, node *vectorValor, int maxValor, int maxPeso);

void simplleGrasp(const int maxIter, const int size, int capacidade, node *vectorPeso, node *vectorValor){

	node *solutionParcial;
	solutionParcial = (node *)malloc(sizeof(node));

	if (!solutionParcial) {
		printf("Sem memoria disponivel!\n");
		exit(1);
	}

	node *solution;
	solution = (node *)malloc(sizeof(node));

	if (!solution) {
		printf("Sem memoria disponivel!\n");
		exit(1);
	}

	int maxValor = 0;

	inicia(solutionParcial);
	inicia(solution);

	int valorSolution = 0;
	int pesoSolution = 0;

	for (int i = 0; i < maxIter; i++) {

		valorSolution = 0;
		pesoSolution = 0;
		
		GreedyRandomizedConstruction(size, solutionParcial, vectorPeso, capacidade);

		//printf("\n--------------------------------------------------------------------\nSolucao gerada inicilmente: \n");
		//exibe(solutionParcial);

		for (int i = 0; i < solutionParcial->tam; i++) {

			valorSolution += numPos(vectorValor, numPos(solutionParcial,i));
			pesoSolution += numPos(vectorPeso, numPos(solutionParcial, i));
		}
		//printf("Valor: %d\nPeso: %d\n\n", valorSolution, pesoSolution);

		LocalSearch(size, solutionParcial, capacidade, vectorPeso, vectorValor, valorSolution, pesoSolution);

		//printf("Solucao gerada depois da busca local: \n");
		//exibe(solutionParcial);
		valorSolution = 0;
		pesoSolution = 0;
		for (int i = 0; i < solutionParcial->tam; i++) {

			valorSolution += numPos(vectorValor, numPos(solutionParcial, i));
			pesoSolution += numPos(vectorPeso, numPos(solutionParcial, i));
		}
		//printf("Valor: %d\nPeso: %d\n\n", valorSolution, pesoSolution);

		if (valorSolution > maxValor) {
			maxValor = valorSolution;
			libera(solution);
			inicia(solution);
			for (int i = 0; i < solutionParcial->tam; i++) {
				insereInicio(solution, numPos(solutionParcial, i));
			}
		}

		libera(solutionParcial);
		inicia(solutionParcial);

		
		//UpdateSolution();
	}
	printf("\n****************************************\nSolução final:\n");
	exibe(solution);
	pesoSolution = 0;
	for (int i = 0; i < solution->tam; i++) {

		pesoSolution += numPos(vectorPeso, numPos(solution, i));
	}
	printf("Valor: %d\nPeso: %d\n\n", maxValor, pesoSolution);
	free(solutionParcial);
	free(solution);

}

void GreedyRandomizedConstruction(int size, node *solutionParcial, node *vectorPeso, int capacidade) {
	
	int idRand = 0;
	int maxPeso = 0;
	srand(time(NULL));

	node *rcl;
	rcl = (node *)malloc(sizeof(node));
	inicia(rcl);
	for (int i = 0; i < size; i++) {

		if (numPos(vectorPeso, i) + maxPeso <= capacidade) {
			insereInicio(rcl, i);
		}
	}

	//printf("rcl:\n");
	//exibe(rcl);
	
	while (rcl->tam > 0) {
		
     	idRand = rand() % rcl->tam;
		
		insereInicio(solutionParcial, numPos(rcl, idRand));
		
		maxPeso += numPos(vectorPeso, numPos(rcl, idRand));
		
		retira(rcl, idRand);

		for (int i = 0; i < rcl->tam; i++) {
			if (numPos(vectorPeso, numPos(rcl, i)) + maxPeso > capacidade) {
				retira(rcl, i);
					i--;
			}		
		}
	}
	free(rcl);
}

void LocalSearch(int size, node *solutionParcial, int capacidade, node *vectorPeso, node *vectorValor, int maxValor, int maxPeso) {
	srand(time(NULL));
	node *rcl;
	rcl = (node *)malloc(sizeof(node));
	inicia(rcl);

	for (int i = 0; i < size; i++) {

		if ((numPos(vectorPeso, i) <= capacidade) && (!contens(solutionParcial, i))) {

			insereInicio(rcl, i);
		}
	}
	
	//id do elemento de troca
	int index = rand() % solutionParcial->tam;

	//ganho sem o elemento de troca
	int valor = maxValor - numPos(vectorValor, numPos(solutionParcial,index));

	//peso sem o elemento de troca
	int peso = maxPeso - numPos(vectorPeso, numPos(solutionParcial, index));

	int aux = -1;

	for (int i = 0; i < rcl->tam;i++) {

		if ((valor + numPos(vectorValor, numPos(rcl, i)) > maxValor) && (peso + numPos(vectorPeso, numPos(rcl, i))<=capacidade)) {
			
			aux = numPos(rcl, i);
		}
		else {
			retira(rcl, i);
			i--;
		}

	}
	if (aux > -1) {
		retira(solutionParcial, index);
		if (solutionParcial->tam > index)
			insere(solutionParcial, aux, index);
		else
			insereFim(solutionParcial, aux);
	}

	free(rcl);
}
