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
#include <assert.h>
#include "listes_dynamiques.h"

// Exemple: on souhaite supprimer de la liste tous les éléments dont la position est
// impaire et pour lesquels info est compris dans un certain intervalle de valeurs
bool positionEtInfoImpaires(size_t position, const Info* info) {
	return position % 2 != 0 && *info % 2 != 0;
}

void remplirListeIncrementale(Liste* liste, Info valeurMinimale, size_t nbValeurs);

void testListesEgales(const Liste* liste1, const Liste* liste2);

int main(void) {

	// 1. Initilialisation
	printf("1. Initilialisation");
	Liste* listeInit = initialiser();
	assert(listeInit != NULL);
	printf("\n=> Test PASS\n");

	// 2. Insertion des éléments à la tête
	printf("\n2. Insertion des elements a la tete\n");
	Liste* liste1 = initialiser();
	if (liste1) {
		const Info INFO_1 = 1;
		const Info INFO_2 = 2;

		afficher(liste1, FORWARD);

		assert(insererEnTete(liste1, &INFO_1) == OK);

		printf(" => ");
		afficher(liste1, FORWARD);

		assert(insererEnTete(liste1, &INFO_2) == OK);

		printf(" => ");
		afficher(liste1, FORWARD);
		printf("\n=> Test PASS\n");
	}

	// 3. Insertion des éléments à la queue
	printf("\n3. Insertion des elements a la queue\n");
	Liste* liste2 = initialiser();
	if (liste2) {
		const Info INFO_1 = 1;
		const Info INFO_2 = 2;

		afficher(liste2, FORWARD);

		// Insertion de liste vide
		assert(insererEnQueue(liste2, &INFO_1) == OK);

		printf(" => ");
		afficher(liste2, FORWARD);

		assert(insererEnQueue(liste2, &INFO_2) == OK);

		printf(" => ");
		afficher(liste2, FORWARD);
		printf("\n=> Test PASS\n");
	}

	// 4. Suppression des éléments à la tête
	printf("\n4. Suppression des elements a la tete\n");
	if (liste1) {
		Info ancienneTete = 0;

		afficher(liste1, FORWARD);

		assert(supprimerEnTete(liste1, &ancienneTete) == OK);

		printf(" => ");
		afficher(liste1, FORWARD);

		assert(supprimerEnTete(liste1, &ancienneTete) == OK);

		printf(" => ");
		afficher(liste1, FORWARD);

		assert(supprimerEnTete(liste1, &ancienneTete) == LISTE_VIDE);

		printf(" Derniere valeur supprime = %d\n=> Test PASS\n",
			ancienneTete);
	}

	// 5. Suppression des éléments à la queue
	printf("\n5. Suppression des elements a la queue\n");
	if (liste2) {
		Info ancienneTete = 0;

		afficher(liste2, FORWARD);

		assert(supprimerEnQueue(liste2, &ancienneTete) == OK);

		printf(" => ");
		afficher(liste2, FORWARD);

		assert(supprimerEnQueue(liste2, &ancienneTete) == OK);

		printf(" => ");
		afficher(liste2, FORWARD);

		assert(supprimerEnQueue(liste2, &ancienneTete) == LISTE_VIDE);

		printf(" Derniere valeur supprime = %d\n=> Test PASS\n",
			ancienneTete);
	}

	// 6. Affichage de liste avec mode
	printf("\n6. Affichage de liste avec mode (Pas d'assert)\n");
	Liste* liste3 = initialiser();
	if (liste3) {
		printf("Liste vide: ");
		afficher(liste3, FORWARD);

		remplirListeIncrementale(liste3, 1, 1);
		printf("\nListe d'un element: ");
		afficher(liste3, FORWARD);

		remplirListeIncrementale(liste3, 2, 3);
		printf("\nListe remplie en mode FORWARD:\t");
		afficher(liste3, FORWARD);

		printf("\nListe remplie en mode BACKWARD:\t");
		afficher(liste3, BACKWARD);
	}

	// 7. Vérification de liste vide
	printf("\n\n7. Verification de liste vide");
	Liste* liste4 = initialiser();
	if (liste4) {

		assert(estVide(liste4));
		remplirListeIncrementale(liste4, 1, 1);
		assert(!estVide(liste4));

		printf("\n=> Test PASS\n");
	}

	// 8. Vidage de liste
	printf("\n8. Vidage de liste\n");
	Liste* liste5 = initialiser();
	if (liste5) {

		remplirListeIncrementale(liste5,0, 9);
		assert(!estVide(liste5));

		printf("Suppression a partir de l'index 5\n");
		afficher(liste5, FORWARD);
		vider(liste5, 5);
		printf(" => ");
		afficher(liste5, FORWARD);

		printf("\nSuppression totale\n");
		afficher(liste5, FORWARD);
		vider(liste5, 0);
		printf(" => ");
		afficher(liste5, FORWARD);

		printf("\nTentative de suppression d'une liste vide\n");
		afficher(liste5, FORWARD);
		vider(liste5, 0);
		printf(" => ");
		afficher(liste5, FORWARD);

		assert(estVide(liste5));
		printf("\n=> Test PASS\n");
	}

	// 9. Vérification d'égalité de liste
	printf("\n9. Verification d'egalite de liste\n");
	Liste* liste6 = initialiser();
	Liste* liste7 = initialiser();

	if (liste6 && liste7) {

		// Listes vides
		assert(sontEgales(liste6, liste7));
		afficher(liste6, FORWARD);
		printf(" = ");
		afficher(liste7, FORWARD);

		// Listes remplies & égales
		remplirListeIncrementale(liste6, 1, 4);
		remplirListeIncrementale(liste7, 1, 4);
		assert(sontEgales(liste6, liste7));
		printf("\n");
		afficher(liste6, FORWARD);
		printf(" = ");
		afficher(liste7, FORWARD);

		// Listes remplies & inégales
		remplirListeIncrementale(liste6, 5, 1);
		assert(!sontEgales(liste6, liste7));
		printf("\n");
		afficher(liste6, FORWARD);
		printf(" != ");
		afficher(liste7, FORWARD);

		printf("\n=> Test PASS\n");
	}

	// 10. Suppression selon critères
	printf("\n9. Suppression selon criteres (Pas d'assert)\n");
	Liste* liste8 = initialiser();
	if (liste8) {
		remplirListeIncrementale(liste8, 0, 15);

		// TODO

		printf("Suppression si valeur impaire\n");
		afficher(liste8, FORWARD);
		supprimerSelonCritere(liste8, positionEtInfoImpaires);
		printf(" => ");
		afficher(liste8, FORWARD);

	}

	return EXIT_SUCCESS;
}

//int main(void) {
//	// 1. Initialiser
//	Liste* liste1 = initialiser();
//	Liste* liste2 = initialiser();
//
//	// 2. Ajouter des éléments à la tête
//	const Info INFO_1 = 1;
//	const Info INFO_2 = 2;
//	const Info INFO_3 = 3;
//	insererEnTete(liste1, &INFO_1);
//	insererEnTete(liste1, &INFO_2);
//	insererEnTete(liste1, &INFO_3);
//	insererEnQueue(liste1, &INFO_2);
//
//	printf("Longueur liste1: %zu\n", longueur(liste1));
//	printf("Longueur liste2: %zu\n", longueur(liste2));
//
//	afficher(liste1, FORWARD);
//	printf("\n");
//	afficher(liste1, BACKWARD);
//	printf("\n");
//
//	// 3. Supprimer des éléments à la tête
//	Info ancienneTete = 0;
//	supprimerEnTete(liste1, &ancienneTete);
//	printf("Valeur element supprime: %d\n", ancienneTete);
//	supprimerEnTete(liste1, &ancienneTete);
//	printf("Valeur element supprime: %d\n", ancienneTete);
//	supprimerEnTete(liste1, &ancienneTete);
//	printf("Valeur element supprime: %d\n", ancienneTete);
//	supprimerEnTete(liste1, &ancienneTete);
//	printf("Valeur element supprime: %d\n", ancienneTete);
//	supprimerEnTete(liste1, &ancienneTete);
//	printf("Valeur element supprime: %d\n", ancienneTete);
//	afficher(liste1, FORWARD);
//	printf("\n");
//
//	// 4. Supprimer des éléments à la queue
//	insererEnTete(liste2, &INFO_1);
//	insererEnTete(liste2, &INFO_2);
//	insererEnTete(liste2, &INFO_3);
//	Info ancienneQueue = 0;
//
//	afficher(liste2, FORWARD);
//	printf("\n");
//	supprimerEnQueue(liste2, &ancienneQueue);
//	printf("Valeur element supprime: %d\n", ancienneQueue);
//	supprimerEnQueue(liste2, &ancienneQueue);
//	printf("Valeur element supprime: %d\n", ancienneQueue);
//	supprimerEnQueue(liste2, &ancienneQueue);
//	printf("Valeur element supprime: %d\n", ancienneQueue);
//	supprimerEnQueue(liste2, &ancienneQueue);
//	printf("Valeur element supprime: %d\n", ancienneQueue);
//	supprimerEnQueue(liste2, &ancienneQueue);
//	printf("Valeur element supprime: %d\n", ancienneQueue);
//	afficher(liste2, FORWARD);
//	printf("\n");
//
//	// 5. Vider une liste
//	printf("\n5. Vider une liste\n");
//	insererEnTete(liste2, &INFO_1);
//	insererEnTete(liste2, &INFO_2);
//	insererEnTete(liste2, &INFO_3);
//	afficher(liste2, FORWARD);
//	printf("\n");
//	vider(liste2, 0);
//	afficher(liste2, FORWARD);
//	printf("\n\n");
//
//	// 6. Supprimer selon critères
//	printf("6. Supprimer selon critères\n");
//	vider(liste1, 0);
//	remplirListeIncrementale(liste1, 0, 15);
//	afficher(liste1, FORWARD);
//	printf("\n");
//	supprimerSelonCritere(liste1, positionEtInfoImpaires);
//	afficher(liste1, FORWARD);
//	printf("\n");
//
//	// Liste vide
//	vider(liste1, 0);
//	afficher(liste1, FORWARD);
//	printf("\n");
//	supprimerSelonCritere(liste1, positionEtInfoImpaires);
//	afficher(liste1, FORWARD);
//	printf("\n\n");
//
//	// Liste d'un élément
//	vider(liste1, 0);
//	remplirListeIncrementale(liste1, 1, 2);
//	afficher(liste1, FORWARD);
//	printf("\n");
//	supprimerSelonCritere(liste1, positionEtInfoImpaires);
//	afficher(liste1, FORWARD);
//	printf("\n\n");
//
//	// 7. Listes égales
//	printf("7. Liste égales\n");
//	testListesEgales(liste1, liste2);
//	remplirListeIncrementale(liste1, 0, 5);
//	testListesEgales(liste1, liste2);
//	remplirListeIncrementale(liste2, 0, 5);
//	testListesEgales(liste1, liste2);
//	vider(liste2, 0);
//	remplirListeIncrementale(liste2, 2, 5);
//	testListesEgales(liste1, liste2);
//
//	return EXIT_SUCCESS;
//}

void remplirListeIncrementale(Liste* liste, Info valeurMinimale, size_t nbValeurs) {
	Info valeur = valeurMinimale;
	for (size_t i = 0; i < nbValeurs; ++i) {
		insererEnQueue(liste, &valeur);
		++valeur;
	}
}

//void testListesEgales(const Liste* liste1, const Liste* liste2) {
//	afficher(liste1, FORWARD);
//	printf(" == ");
//	afficher(liste2, FORWARD);
//	printf(" ? ");
//	if (sontEgales(liste1, liste2)) {
//		printf("true\n");
//	} else {
//		printf("false\n");
//	}
//}
