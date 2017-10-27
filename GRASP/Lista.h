#include <stdio.h>
#include <stdlib.h>

struct Node {
	int num;
	struct Node *prox;
	int tam;
};
typedef struct Node node;

void inicia(node *LISTA)
{
	LISTA->prox = NULL;
	LISTA->tam = 0;
}

int vazia(node *LISTA)
{
	if (LISTA->prox == NULL)
		return 1;
	else
		return 0;
}

node *aloca(int x)
{
	node *novo = (node *)malloc(sizeof(node));
	if (!novo) {
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else {
		//printf("Novo elemento: "); scanf("%d", &novo->num);
		novo->num = x;
		return novo;
	}
}

void insereFim(node *LISTA, int x)
{
	node *novo = aloca(x);
	novo->prox = NULL;

	if (vazia(LISTA))
		LISTA->prox = novo;
	else {
		node *tmp = LISTA->prox;

		while (tmp->prox != NULL)
			tmp = tmp->prox;

		tmp->prox = novo;
	}
	LISTA->tam++;
}

void insereInicio(node *LISTA, int x)
{
	node *novo = aloca(x);
	node *oldHead = LISTA->prox;

	LISTA->prox = novo;
	novo->prox = oldHead;

	LISTA->tam++;
}

int numPos(node *LISTA, int id) {
	
	if (vazia(LISTA)) {
		printf("Lista vazia!\n\n");
		return NULL;
	}

	node *tmp;
	tmp = LISTA->prox;
	
	for(int i = 0; i < id; i++){
		tmp = tmp->prox;
	}
	return tmp->num;
}

void exibe(node *LISTA)
{
	if (vazia(LISTA)) {
		printf("Lista vazia!\n\n");
		return;
	}

	node *tmp;
	tmp = LISTA->prox;
	while (tmp != NULL) {
		printf("%d ", tmp->num);
		tmp = tmp->prox;
	}
	printf("\n");
}

void libera(node *LISTA)
{
	if (!vazia(LISTA)) {
		node *proxNode,
			*atual;

		atual = LISTA->prox;
		while (atual != NULL) {
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

void insere(node *LISTA, int x, int id)
{
	int count;

	if (id >= 0 && id < LISTA->tam) {
		if (id == 0)
			insereInicio(LISTA, x);
		else {
			node *atual = LISTA->prox,
				*anterior = LISTA;
			node *novo = aloca(x);

			for (count = 0; count < id; count++) {
				anterior = atual;
				atual = atual->prox;
			}
			anterior->prox = novo;
			novo->prox = atual;
			LISTA->tam++;
		}

	}
	else
		printf("Elemento invalido\n\n");
}

node *retiraInicio(node *LISTA)
{
	if (LISTA->prox == NULL) {
		printf("Lista ja esta vazia\n");
		return NULL;
	}
	else {
		node *tmp = LISTA->prox;
		LISTA->prox = tmp->prox;
		LISTA->tam--;
		return tmp;
	}

}

node *retiraFim(node *LISTA)
{
	if (LISTA->prox == NULL) {
		printf("Lista ja vazia\n\n");
		return NULL;
	}
	else {
		node *ultimo = LISTA->prox,
			*penultimo = LISTA;

		while (ultimo->prox != NULL) {
			penultimo = ultimo;
			ultimo = ultimo->prox;
		}

		penultimo->prox = NULL;
		LISTA->tam--;
		return ultimo;
	}
}

node *retira(node *LISTA, int id)
{
	int count;

	if (id >= 0 && id < LISTA->tam) {
		if (id == 0)
			return retiraInicio(LISTA);
		else {
			node *atual = LISTA->prox,
				*anterior = LISTA;

			for (count = 0; count < id; count++) {
				anterior = atual;
				atual = atual->prox;
			}

			anterior->prox = atual->prox;
			LISTA->tam--;
			return atual;
		}

	}
	else {
		printf("Elemento invalido\n\n");
		return NULL;
	}
}

int contens(node *LISTA, int item) {

	for (int i = 0; i < LISTA->tam; i++) {

		if (numPos(LISTA, i) == item) {
			return 1;
		}
	}
	return 0;
}