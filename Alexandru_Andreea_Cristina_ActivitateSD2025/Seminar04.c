#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct StructuraMasina Masina;
typedef struct Nod Nod;
struct Nod
{
	Masina info;
	Nod* urm;
};
Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
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

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
	while (cap)
	{
		afisareMasina(cap->info);
		cap = cap->urm;  //afisare simpla inlantui
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) { //** pointer..
	//ne cream un nod, copiem acest 1 in nodul nostru, deoarece inseram la final va fi null 
	//in care situatie suntem , cap= null => adresa a7, retine adresa a7 
	// noi il vom modifica pe cap, prin dublue pointer sau adresa 
	//daca exista cap-> ne deplasam cu cel nou 

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua; //o dezalocam - nu, facem shallow copy
	nou->urm = NULL; //verificam nodul urmator 

	if ((*cap) == NULL)
	{
		*cap = nou;  //ii dau o adresa(ex: a5), trebuie sa-l modific prin adresa, de aceea are pointer 
	}
	else  //dace ne deplasam cu cap nu mai putem accesa cele din lista trecuta(anterioara), facem un nod p care el se va misca, cap nu se misca 
	{
		Nod* p = *cap;
		while (p->urm)
		{
			p = p->urm; //adresa nodului urmator, un exemplu de pod, verific unde ma pot aseza, cat timp exista eu ma pot deplasa 
		}
		p->urm = nou;
	}
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;   //NE CREAM UN NOU nod, adresa primului nod
	nou->urm = *cap; //deferentiam ca e trimis prin adresa 
	*cap = nou; //lui cap ii dam adresa noului nod, setam informatia 

}

void* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r"); //modul citire 
	Nod* lista = NULL; //ne trebuie o lista, o initializam neaparat, verificam daca e null, ca are o val implicita si ne va da eroare !!, il initializam cu NULL
	while (!feof(f))
	{
		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;

}

void dezalocareListaMasini(Nod** cap) {
	while ((*cap) != NULL)
	{
		Nod* aux = (*cap);
		*cap = (*cap)->urm;  //fiecare nod, sa stergem zona si dupa nodul acela
		free(aux->info.numeSofer);
		free(aux->info.model);
		free(aux);
	}
}

float calculeazaPretMediu(Nod* lista) {
	//calculeaza pretul mediu al masinilor din lista.

	//if (!lista) return 0; 
	int count = 0;
	float sum = 0;
	while (lista)  //putem, parcurge cu lista ca e doar o copie 
	{
		sum += lista->info.pret;
		count++;
		lista = lista->urm;
	}
	return (count > 0) ? sum / count : 0; //IFELSE, daca nu e >0, returneaza 0 si daca e return sum/count
}

void stergeMasiniDinSeria(/*lista masini*/  char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	//Tema- de continuat 
}

float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	float sum = 0;
	while (lista)
	{
		if (strcmp(numeSofer, lista->info.numeSofer) == 0)
		{
			sum = lista->info.pret;
		}
		lista = lista->urm;
	}
	return sum;
}


char* getCeaMaiScumpaMasina(Nod* lista)
{
	float pretulMax = 0;
	char* modelScump = NULL;
	while (lista) {
		if (lista->info.pret > pretulMax)
		{
			pretulMax = lista->info.pret;
			modelScump = lista->info.model;
		}
		lista = lista->urm;
	}
	if (pretulMax > 0)
	{
		char* nou = malloc(strlen(modelScump) + 1);
		strcpy_s(nou, strlen(modelScump) + 1, modelScump);
		return nou;
	}
	return NULL;
}


int main() {

	Nod* cap = NULL;
	cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);
	printf("%f \n\n", calculeazaPretMediu(cap));
	printf("%f \n\n", calculeazaPretulMasinilorUnuiSofer(cap, "Ionescu"));
	char* model = getCeaMaiScumpaMasina(cap);
	printf("%s", model);
	if (model) {
		free(model);
	}

	dezalocareListaMasini(&cap);

	return 0;
}