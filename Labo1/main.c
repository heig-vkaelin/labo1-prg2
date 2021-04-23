/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
 Date creation  : 22.04.2021

 Description    : Programme principal testant l'implémentation de la librairie
                  permettant la gestion de listes doublement chaînées non
                  circulaires.

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "listes_dynamiques.h"

// Exemple: on souhaite supprimer de la liste tous les éléments dont la position est
// impaire et pour lesquels info est compris dans un certain intervalle de valeurs
bool positionEtInfoImpaires(size_t position, const Info* info) {
	return position % 2 != 0 && *info % 2 != 0;
}

void remplirListeIncrementale(Liste* liste, Info valeurMinimale, size_t nbValeurs);

void testListesEgales(const Liste* liste1, const Liste* liste2);

int main(void) {
	// 1. Initialiser
	Liste* liste1 = initialiser();
	Liste* liste2 = initialiser();

	// 2. Ajouter des éléments à la tête
	const Info INFO_1 = 1;
	const Info INFO_2 = 2;
	const Info INFO_3 = 3;
	insererEnTete(liste1, &INFO_1);
	insererEnTete(liste1, &INFO_2);
	insererEnTete(liste1, &INFO_3);
	insererEnQueue(liste1, &INFO_2);

	printf("Longueur liste1: %zu\n", longueur(liste1));
	printf("Longueur liste2: %zu\n", longueur(liste2));

	afficher(liste1, FORWARD);
	printf("\n");
	afficher(liste1, BACKWARD);
	printf("\n");

	// 3. Supprimer des éléments à la tête
	Info ancienneTete = 0;
	supprimerEnTete(liste1, &ancienneTete);
	printf("Valeur element supprime: %d\n", ancienneTete);
	supprimerEnTete(liste1, &ancienneTete);
	printf("Valeur element supprime: %d\n", ancienneTete);
	supprimerEnTete(liste1, &ancienneTete);
	printf("Valeur element supprime: %d\n", ancienneTete);
	supprimerEnTete(liste1, &ancienneTete);
	printf("Valeur element supprime: %d\n", ancienneTete);
	supprimerEnTete(liste1, &ancienneTete);
	printf("Valeur element supprime: %d\n", ancienneTete);
	afficher(liste1, FORWARD);
	printf("\n");

	// 4. Supprimer des éléments à la queue
	insererEnTete(liste2, &INFO_1);
	insererEnTete(liste2, &INFO_2);
	insererEnTete(liste2, &INFO_3);
	Info ancienneQueue = 0;

	afficher(liste2, FORWARD);
	printf("\n");
	supprimerEnQueue(liste2, &ancienneQueue);
	printf("Valeur element supprime: %d\n", ancienneQueue);
	supprimerEnQueue(liste2, &ancienneQueue);
	printf("Valeur element supprime: %d\n", ancienneQueue);
	supprimerEnQueue(liste2, &ancienneQueue);
	printf("Valeur element supprime: %d\n", ancienneQueue);
	supprimerEnQueue(liste2, &ancienneQueue);
	printf("Valeur element supprime: %d\n", ancienneQueue);
	supprimerEnQueue(liste2, &ancienneQueue);
	printf("Valeur element supprime: %d\n", ancienneQueue);
	afficher(liste2, FORWARD);
	printf("\n");

	// 5. Vider une liste
	printf("\n5. Vider une liste\n");
	insererEnTete(liste2, &INFO_1);
	insererEnTete(liste2, &INFO_2);
	insererEnTete(liste2, &INFO_3);
	afficher(liste2, FORWARD);
	printf("\n");
	vider(liste2, 0);
	afficher(liste2, FORWARD);
	printf("\n\n");

	// 6. Supprimer selon critères
	printf("6. Supprimer selon critères\n");
	vider(liste1, 0);
	remplirListeIncrementale(liste1, 0, 15);
	afficher(liste1, FORWARD);
	printf("\n");
	supprimerSelonCritere(liste1, positionEtInfoImpaires);
	afficher(liste1, FORWARD);
	printf("\n");

	// Liste vide
	vider(liste1, 0);
	afficher(liste1, FORWARD);
	printf("\n");
	supprimerSelonCritere(liste1, positionEtInfoImpaires);
	afficher(liste1, FORWARD);
	printf("\n\n");

	// Liste d'un élément
	vider(liste1, 0);
	remplirListeIncrementale(liste1, 1, 2);
	afficher(liste1, FORWARD);
	printf("\n");
	supprimerSelonCritere(liste1, positionEtInfoImpaires);
	afficher(liste1, FORWARD);
	printf("\n\n");

	// 7. Listes égales
	printf("7. Liste égales\n");
	testListesEgales(liste1, liste2);
	remplirListeIncrementale(liste1, 0, 5);
	testListesEgales(liste1, liste2);
	remplirListeIncrementale(liste2, 0, 5);
	testListesEgales(liste1, liste2);
	vider(liste2, 0);
	remplirListeIncrementale(liste2, 2, 5);
	testListesEgales(liste1, liste2);

	return EXIT_SUCCESS;
}

void remplirListeIncrementale(Liste* liste, Info valeurMinimale, size_t nbValeurs) {
	Info valeur = valeurMinimale;
	for (size_t i = 0; i < nbValeurs; ++i) {
		insererEnQueue(liste, &valeur);
		++valeur;
	}
}

void testListesEgales(const Liste* liste1, const Liste* liste2) {
	afficher(liste1, FORWARD);
	printf(" == ");
	afficher(liste2, FORWARD);
	printf(" ? ");
	if (sontEgales(liste1, liste2)) {
		printf("true\n");
	} else {
		printf("false\n");
	}
}
