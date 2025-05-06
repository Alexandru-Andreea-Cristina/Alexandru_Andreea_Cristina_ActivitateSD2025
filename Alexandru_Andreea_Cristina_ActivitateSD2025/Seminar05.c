//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
////lista dubla inlantuinta, retine adresa nodului precedent, va retine NULL, adresa nodului anterior si precedent
////sa realizam o parcurgere- prin WHILE si de la sfarsit la inceput
////cum indetificam o lsiat simpla inlantuita- prin bpointerul de la primul nod, dar la sf la inc cum se face, retinem si adresa ultimului nod
//// ne cream o alta structura care retine si prim si ulitm,
////inserare: trebuie sa schimb si cap si ultim , in situatia in care lista inla, retin acelasi NULL, altfel daca am iserare la inceput schimb, daca nu la sfarsit
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//struct Nod {
//	Masina info;
//	struct Nod* urmator;
//	struct Nod* precedent;
//};
//
//typedef struct Nod Nod;
////creare structura pentru un nod dintr-o lista dublu inlantuita
//
////creare structura pentru Lista Dubla
//struct Lista {
//	Nod* prim;
//	Nod* ultim;
//};
//typedef struct Lista Lista;
//
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(Lista list) {    //afisareListaMasiniInceput
//	//de la inceput pana la sf
//	Nod* p = list.prim;
//	while (p)
//	{
//		afisareMasina(p->info);
//		p = p->urmator; //afisarea in mod clasic
//	}
//}
//
//void adaugaMasinaInLista(Lista* list, Masina masinaNoua) {  //de la sf la inceput
//	//trebuie sa modificam ultimul, trebuie sa creeam NODUL, avem info, dar nu nodul
//	Nod* p = (Nod*)malloc(sizeof(Nod));
//	p->info = masinaNoua; //shallow copy
//	//trebuie sa intializam
//	p->precedent = list->ultim; //de unde incepe blocul, nu la final
//	p->urmator = NULL;
//	if (list->ultim)
//	{
//		list->ultim->urmator = p;
//	}
//	else
//	{
//		list->prim = p; //trebuie sa-l modificam pe ultimul, pastram lista, si pe prim trebuie sa-l modificam
//	}
//	list->ultim = p; //mpd elem din lista, NU LSIA(era Lista* list si se trans prin list->ultim etc), e recomandat si prin pointer dar sa fie constant, TREBUIE PRIN ADRESAA!!!
//
//}
//
//void adaugaLaInceputInLista(Lista* list, Masina masinaNoua) {  //tot prin adersa
//	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
//	Nod* p = (Nod*)malloc(sizeof(Nod));
//	p->info = masinaNoua;
//	p->urmator = list->prim;
//	p->precedent = NULL;
//	if (list->prim)
//	{
//		list->prim->precedent = p;
//	}
//	else
//	{
//		//p devine ultimulo
//		list->ultim = p;
//	}
//	list->prim = p;
//}
//
//
//void afisareListaMasiniSF(Lista list)
//{
//	Nod* p = list.ultim;
//	while (p)
//	{
//		afisareMasina(p->info);
//		p = p->precedent;
//	}
//
//}
//Lista citireLDMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Lista list;
//	list.prim = NULL;
//	list.ultim = NULL;
//	while (!feof(f))
//	{
//		//adaugaMasinaInLista(&list, citireMasinaDinFisier(f));   //la final
//		adaugaLaInceputInLista(&list, citireMasinaDinFisier(f));  //la inceput
//	}
//	fclose(f);
//	return list;
//
//}
//
//void dezalocareLDMasini(Lista* lista) {
//	//Nod* p = (Nod*)malloc(sizeof(Nod)); //NU ALOCAM SPATIU LA dezalocare
//	Nod* p = lista->prim;
//	while (p->urmator != NULL)
//	{
//		free(p->info.numeSofer);
//		free(p->info.model);
//		p = p->urmator;   //deplasarile cu un singur pointer, nu cu doi
//		free(p->precedent);
//
//	}
//	free(p->info.numeSofer);
//	free(p->info.model);
//	free(p);
//	lista->prim = NULL;
//	lista->ultim = NULL;
//	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
//}
//
//float calculeazaPretMediu(Lista lista) {
//	//calculeaza pretul mediu al masinilor din lista.
//	Nod* aux = lista.prim;
//	float suma = 0; // sa-l putem returna dupa
//	float cnt = 0;
//	while (aux) {
//		suma += aux->info.pret;
//		cnt++;
//		aux = aux->urmator;
//	}
//
//	return suma / cnt;
//}
//
//void stergeMasinaDupaID(/*lista masini*/ int id) { //parcurgea pna la nodul unde trebuie sa-l stergem
//	//sterge masina cu id-ul primit.
//	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//}
//
//char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
//	//cauta masina cea mai scumpa si
//	//returneaza numele soferului acestei maasini.
//	return NULL;
//}
//
//int main() {
//	Lista lista;
//	lista = citireLDMasiniDinFisier("masini.txt");
//	//afisareListaMasini(lista);
//	afisareListaMasiniSF(lista);
//
//	float pretMediu = calculeazaPretMediu(lista);
//	printf("Pret mediu: % 2f\n", pretMediu);
//
//	dezalocareLDMasini(&lista);
//
//
//	return 0;
//}