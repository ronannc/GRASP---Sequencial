

void selection_sort(item *num, int tam) {

	int i, j, min, peso, valor, ganho = 0;

	for (i = 0; i < (tam - 1); i++) {

		min = i;
		for (j = (i + 1); j < tam; j++) {

			if (num[j].ganho > num[min].ganho) {
				min = j;
			}
		}
		if (i != min) {

			peso = num[i].peso;
			valor = num[i].valor;
			ganho = num[i].ganho;
			num[i].peso = num[min].peso;
			num[i].valor = num[min].valor;
			num[i].ganho = num[min].ganho;
			num[min].peso = peso;
			num[min].valor = valor;
			num[min].ganho = ganho;
		}
	}
}
