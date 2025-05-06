//#include<stdio.h>
//#include<stdlib.h>
//
//struct Masina {
//	int id;
//	int nrLocuri;
//	char* marca;  //pointeaza catre un sir de caractere
//	float capacitateC;
//	char normaPoluare; //un singur caracter
//};
//
//
//// const la char*- se trimite adresa 
//
//
//struct Masina initializare(int id, int nrLocuri, const char* marca, float capacitateC, char normaPoluare) {
//	struct Masina m;
//	m.id = id;
//	m.nrLocuri = nrLocuri;
//	m.capacitateC = capacitateC;
//	m.normaPoluare = normaPoluare;   //se face prin malloc- de la atp, ce paramtri primeste,strlen- nr de octeti, +1
//	m.marca = (char*)malloc(strlen(marca) + 1); //marimea este sizeoff ocupa un octet, dar daca avem int.. trebuie sa inmultim cu sizeoff 
//	strcpy_s(m.marca, strlen(marca) + 1, marca);  //primeste destinatia si sursa, strcpy_s- sa ne asiguram ca copiaza cei cerem. adica 6 cara
//
//	return m;
//}
//
//void afisare(struct Masina m) {
//	printf("\n Id masina: %d\n Nr locuri: %d\n Capacitate: %.2f\n  Marca: %s\n Euro: %c\n", m.id, m.nrLocuri, m.capacitateC, m.marca, m.normaPoluare);
//}
//
//void modifica_NrLocuri(struct Masina* m, int nrNou) {
//	if (nrNou > 0) {
//		m->nrLocuri = nrNou; //un setter 
//	}
//
//}
//
//void dezalocare(struct Masina* m) {
//	free(m->marca);
//	(*m).marca = NULL;
//	//stergem prin free se face unde am alocat
//}
//
//int main() {
//	struct Masina masina;
//	//sa recunoasca tipul de date 
//	//functie vs metoda- diferenta, e data de pointerul this 
//	// functia nu o apelam prin meotda
//	masina = initializare(1, 5, "Dacia", 1.5, '4'); //"4" '4'-ca ocupa 2 octeti 
//	afisare(masina);
//	modifica_NrLocuri(&masina, 6); //4 sau 6 diferit de 5 
//	afisare(masina);
//
//	dezalocare(&masina);
//	afisare(masina);
//	printf("\n%d", sizeof(struct Masina*));
//	printf("\n%d", sizeof(masina));
//
//	return 0;
//}
//
//// se da add si se adauga in c( se strege pp)- source.c 
//// articol - instanta a unei structuri
////cum se face github