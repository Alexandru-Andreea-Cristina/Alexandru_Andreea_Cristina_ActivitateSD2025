#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct StructuraMasina {
	int id; 
	int nrUsi; 
	float pret;
	char* model; 
	char* numeSofer; 
	unsigned char serie; 
};

typedef struct StructuraMasina Masina; 

struct Heap { //ce retinem: vector+ dimnesiune+ nr elem curente
	int lungime; 
	Masina* masini; //vector
	int nrMasini; 
};

typedef struct Heap Heap; 

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100]; 
	char sep[3] = ",\n";
	fgets(buffer,100, file); 
	char* aux; 
	Masina m1; //il cream 
	aux = strtok(buffer, sep); 
	m1.id = atoi(aux); 
	m1.nrUsi = atoi(strtok(NULL, sep)); 
	m1.pret = atof(strtok(NULL, sep)); 
	aux = strtok(NULL, sep); 
	m1.model = malloc(strlen(aux) + 1); 
	strcpy_s(m1.model, strlen(aux) + 1, aux); 
	aux = strtok(NULL, sep); 
	m1.numeSofer = malloc(strlen(aux) + 1); 
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux); 
	m1.serie = *strtok(NULL, sep); //preia primul caracter
	return m1; 
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id); 
	printf("Nr usi: %d\n", masina.nrUsi); 
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

Heap intializareHeap(int lungime) { //creaza un vector alocat pt lungime elemente 
	Heap heap; 
	heap.lungime = lungime; 
	heap.masini = (Masina*)malloc(sizeof(Masina) * lungime); 
	heap.nrMasini = 0; 
	return heap; 
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	if (pozitieNod >= 0 && pozitieNod < heap.nrMasini) {
		int pozStanga = 2 * pozitieNod + 1;
		int pozDreapta = 2 * pozitieNod + 2;
		int pozMaxim = pozitieNod;
		if (pozStanga< heap.nrMasini && heap.masini[pozMaxim].id < heap.masini[pozStanga].id) {
			pozMaxim = pozStanga;
		}
		if (pozDreapta< heap.nrMasini && heap.masini[pozMaxim].id < heap.masini[pozDreapta].id) {
			pozMaxim = pozDreapta;
		}
		if (pozMaxim != pozitieNod) {
			Masina aux;
			aux = heap.masini[pozMaxim];
			heap.masini[pozMaxim] = heap.masini[pozitieNod];
			heap.masini[pozitieNod] = aux;
			if (pozMaxim < (heap.nrMasini - 1) / 2) {
				filtreazaHeap(heap, pozMaxim);
			}
		}
	}
}

Heap citireDeMasiniDinFisier(const char* numeFisier) {
	Heap heap = intializareHeap(10); 
	FILE* file = fopen(numeFisier, "r"); 
	int index = 0; 
	while (!feof(file)) {
		heap.masini[index] = citireDeMasiniDinFisier(file); 
		index++; 
	}
	heap.nrMasini = index; 
	fclose(file); 
	for (int i = (heap.nrMasini - 1) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	//afiseaza elementele vizibile din heap
	for (int i = 0; i < heap.nrMasini; i++) {
		afisareMasina(heap.masini[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {
	//afiseaza elementele ascunse din heap
	for (int i = heap.nrMasini; i < heap.lungime; i++) {
		afisareMasina(heap.masini[i]);
	}
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++)
	{
		free(heap->masini[i].numeSofer);
		free(heap->masini[i].model);
	}
	free(heap->masini);
	heap->nrMasini = 0;
	heap->lungime = 0;
	heap->masini = NULL;
}


int main() {

}




