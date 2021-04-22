/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
 Date creation  : 22.04.2021

 Description    : -

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "listes_dynamiques.h"

int main(void) {
	// 1. Initialiser
	Liste *liste1 = initialiser();
	Liste *liste2 = initialiser();

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
	afficher(liste1, BACKWARD);

	// 3. Supprimer des éléments
	Info ancienneTete = 0;
	supprimerEnTete(liste1, &ancienneTete);
	supprimerEnTete(liste1, &ancienneTete);
	supprimerEnTete(liste1, &ancienneTete);
	supprimerEnTete(liste1, &ancienneTete);
	supprimerEnTete(liste1, &ancienneTete);
	printf("Element supprime: %d\n", ancienneTete);
	afficher(liste1, FORWARD);

	return EXIT_SUCCESS;
}
