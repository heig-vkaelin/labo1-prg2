/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
 Date creation  : 22.04.2021

 Description    : Programme principal testant l'implémentation de la librairie
                  permettant la gestion de listes doublement chaînées non
                  circulaires.

 Remarque(s)    : Les tests des fonctions de la librairie sont séparés en
                  plusieurs étapes. Les tests contenant des asserts sont considérés
                  valides lorsque "=> Test reussi" est affiché. Ceux qui n'ont pas
                  ce message ont une indication qu'ils ne contiennent pas d'assert.

                  Un warning (Wformat) apparaît sous Windows lors de l'affichage des
                  variables de type size_t. Une macro a été réalisée à la place
                  des flags "%zu" du printf afin de rendre l'affichage portable
                  sur les différentes plateformes. Son implémentation est basée
                  sur la correction de l'exercice 1.11.

                  Les paramètres de fonctions de suppressions par critères ne sont
                  pas forcément tous utilisés, ce qui peut provoquer un warning
                  Wunused-parameter.

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>
#include "listes_dynamiques.h"

/**
 * Affiche un nombre non-signé dans la console
 * Levée d'un Warning Wformat possible selon l'OS
 */
#define PRINT_UNSIGNED(i) printf(#i " = %" PRIuMAX "\n", (uintmax_t) (i))

/**
 * Fonction permettant de faciliter le remplissage de valeurs incrémentales dans
 * une liste
 * @param liste : la liste à remplir
 * @param valeurMinimale : valeur du premier élément à introduire
 * @param nbValeurs : nombre d'éléments à introduire
 */
void remplirListeIncrementale(Liste* liste, Info valeurMinimale, size_t nbValeurs);

/**
 * Fonction permettant de supprimer de la liste tous les éléments dont la position
 * est impaire et pour lesquels info est compris dans l'intervalle [2, 8]
 * @param position : position dans la liste de l'élément
 * @param info : valeur de l'élément
 * @return true si l'élément doit être supprimé car il correspond aux critères
 */
bool positionImpaireEtEntre2et8(size_t position, const Info* info);

/**
 * Fonction permettant de supprimer de la liste tous les éléments dont l'info est
 * plus grande que 3.
 * @param position : position dans la liste de l'élément
 * @param info : valeur de l'élément
 * @return true si l'élément doit être supprimé car il correspond aux critères
 */
bool infoPlusGrandQue3(size_t position, const Info* info);

int main(void) {
	const Info INFO_1 = 1;
	const Info INFO_2 = 2;
	Info ancienneTete = 0;
	Info ancienneQueue = 0;

	// TEST: Initialisation
	printf("TEST: Initialisation");
	Liste* liste1 = initialiser();
	assert(liste1 != NULL);
	assert(liste1->tete == NULL);
	assert(liste1->queue == NULL);
	Liste* liste2 = initialiser();
	assert(liste2 != NULL);
	assert(liste2->tete == NULL);
	assert(liste2->queue == NULL);
	printf("\n=> Test reussi\n\n");

	// ************************************************
	// TEST: Insertion des éléments à la tête
	// ************************************************
	printf("TEST: Insertion des elements a la tete\n");
	afficher(liste1, FORWARD);

	assert(insererEnTete(liste1, &INFO_1) == OK);
	assert(liste1->tete->info == INFO_1);
	assert(liste1->queue->info == INFO_1);
	printf(" => ");
	afficher(liste1, FORWARD);

	assert(insererEnTete(liste1, &INFO_2) == OK);
	assert(liste1->tete->info == INFO_2);
	assert(liste1->tete->suivant->info == INFO_1);
	printf(" => ");
	afficher(liste1, FORWARD);
	printf("\n=> Test reussi\n\n");

	// ************************************************
	// TEST: Insertion des éléments à la queue
	// ************************************************
	printf("TEST: Insertion des elements a la queue\n");
	afficher(liste2, FORWARD);

	// Insertion dans liste vide
	assert(insererEnQueue(liste2, &INFO_1) == OK);
	assert(liste2->tete->info == INFO_1);
	assert(liste2->queue->info == INFO_1);
	printf(" => ");
	afficher(liste2, FORWARD);

	assert(insererEnQueue(liste2, &INFO_2) == OK);
	assert(liste2->queue->info == INFO_2);
	assert(liste2->queue->precedent->info == INFO_1);
	printf(" => ");
	afficher(liste2, FORWARD);
	printf("\n=> Test reussi\n\n");

	// ************************************************
	// TEST: Vérification de liste vide
	// ************************************************
	printf("TEST: Verification de liste vide");
	Liste* liste3 = initialiser();
	assert(estVide(liste3));
	remplirListeIncrementale(liste3, 1, 1);
	assert(!estVide(liste3));
	printf("\n=> Test reussi\n\n");

	// ************************************************
	// TEST: Vidage de liste
	// ************************************************
	printf("TEST: Vidage de liste\n");
	remplirListeIncrementale(liste1, 3, 6);
	assert(!estVide(liste1));

	printf("Suppression a partir de l'index 5\n");
	afficher(liste1, FORWARD);
	vider(liste1, 5);
	printf(" => ");
	afficher(liste1, FORWARD);

	printf("\nSuppression totale\n");
	assert(!estVide(liste1));
	afficher(liste1, FORWARD);
	vider(liste1, 0);
	printf(" => ");
	afficher(liste1, FORWARD);
	assert(estVide(liste1));

	printf("\nTentative de suppression dans une liste vide\n");
	afficher(liste1, FORWARD);
	vider(liste1, 0);
	printf(" => ");
	afficher(liste1, FORWARD);
	assert(estVide(liste1));

	printf("\nTentative de suppression avec index incorrect 6\n");
	vider(liste1, 0);
	vider(liste2, 0);
	remplirListeIncrementale(liste1, 1, 5);
	remplirListeIncrementale(liste2, 1, 5);
	afficher(liste1, FORWARD);
	vider(liste1, 6);
	printf(" => ");
	afficher(liste1, FORWARD);
	assert(sontEgales(liste1, liste2));
	printf("\n=> Test reussi\n\n");

	// ************************************************
	// TEST: Calcul de la longueur
	// ************************************************
	printf("TEST: Calcul de la longueur\n");
	vider(liste1, 0);

	// Longueur de liste vide
	assert(longueur(liste1) == 0);
	printf("Longueur de liste vide\n");
	afficher(liste1, FORWARD);
	printf(" => Taille: ");
	PRINT_UNSIGNED(longueur(liste1));

	// Longueur de liste remplie
	remplirListeIncrementale(liste1, 1, 4);
	assert(longueur(liste1) == 4);
	printf("Longueur de liste remplie\n");
	afficher(liste1, FORWARD);
	printf(" => Taille: ");
	PRINT_UNSIGNED(longueur(liste1));
	printf("=> Test reussi\n\n");

	// ************************************************
	// TEST: Suppression des éléments à la tête
	// ************************************************
	printf("TEST: Suppression des elements a la tete\n");
	vider(liste1, 0);
	assert(insererEnTete(liste1, &INFO_1) == OK);
	assert(insererEnTete(liste1, &INFO_2) == OK);
	afficher(liste1, FORWARD);

	assert(supprimerEnTete(liste1, &ancienneTete) == OK);
	assert(ancienneTete == INFO_2);
	printf(" => ");
	afficher(liste1, FORWARD);

	assert(supprimerEnTete(liste1, &ancienneTete) == OK);
	assert(ancienneTete == INFO_1);
	printf(" => ");
	afficher(liste1, FORWARD);

	assert(supprimerEnTete(liste1, &ancienneTete) == LISTE_VIDE);
	assert(ancienneTete == INFO_1);
	printf(" Derniere valeur supprime = %d\n=> Test reussi\n\n", ancienneTete);

	// ************************************************
	// TEST: Suppression des éléments à la queue
	// ************************************************
	printf("TEST: Suppression des elements a la queue\n");
	vider(liste1, 0);
	assert(insererEnTete(liste1, &INFO_1) == OK);
	assert(insererEnTete(liste1, &INFO_2) == OK);
	afficher(liste1, FORWARD);

	assert(supprimerEnQueue(liste1, &ancienneQueue) == OK);
	assert(ancienneQueue == INFO_1);
	printf(" => ");
	afficher(liste1, FORWARD);

	assert(supprimerEnQueue(liste1, &ancienneQueue) == OK);
	assert(ancienneQueue == INFO_2);
	printf(" => ");
	afficher(liste1, FORWARD);

	assert(supprimerEnQueue(liste1, &ancienneQueue) == LISTE_VIDE);
	assert(ancienneQueue == INFO_2);
	printf(" Derniere valeur supprime = %d\n=> Test reussi\n\n", ancienneQueue);

	// ************************************************
	// TEST: Affichage de liste avec mode (Pas d'assert)
	// ************************************************
	printf("TEST: Affichage de liste avec mode (Pas d'assert)\n");
	vider(liste1, 0);
	printf("Liste vide: ");
	afficher(liste1, FORWARD);

	remplirListeIncrementale(liste1, 1, 1);
	printf("\nListe d'un element: ");
	afficher(liste1, FORWARD);

	remplirListeIncrementale(liste1, 2, 3);
	printf("\nListe remplie en mode FORWARD:\t");
	afficher(liste1, FORWARD);

	printf("\nListe remplie en mode BACKWARD:\t");
	afficher(liste1, BACKWARD);
	printf("\n\n");

	// ************************************************
	// TEST: Vérification d'égalité de liste
	// ************************************************
	printf("TEST: Verification d'egalite de liste\n");
	vider(liste1, 0);
	vider(liste2, 0);

	// Listes vides
	assert(sontEgales(liste1, liste2));
	afficher(liste1, FORWARD);
	printf(" = ");
	afficher(liste2, FORWARD);

	// Listes remplies & égales
	remplirListeIncrementale(liste1, 1, 4);
	remplirListeIncrementale(liste2, 1, 4);
	assert(sontEgales(liste1, liste2));
	printf("\n");
	afficher(liste1, FORWARD);
	printf(" = ");
	afficher(liste2, FORWARD);

	// Listes remplies & inégales (tailles différentes)
	remplirListeIncrementale(liste1, 5, 1);
	assert(!sontEgales(liste1, liste2));
	printf("\n");
	afficher(liste1, FORWARD);
	printf(" != ");
	afficher(liste2, FORWARD);

	// Listes remplies & inégales (mêmes tailles)
	vider(liste1, 0);
	vider(liste2, 0);
	remplirListeIncrementale(liste1, 1, 5);
	remplirListeIncrementale(liste2, 2, 5);
	assert(!sontEgales(liste1, liste2));
	printf("\n");
	afficher(liste1, FORWARD);
	printf(" != ");
	afficher(liste2, FORWARD);

	printf("\n=> Test reussi\n\n");

	// ************************************************
	// TEST: Suppression selon critères
	// ************************************************
	printf("TEST: Suppression selon criteres\n");
	vider(liste1, 0);
	vider(liste2, 0);
	remplirListeIncrementale(liste1, 0, 10);

	Info valeursAttendues[7] = {0, 1, 2, 4, 6, 8, 9};
	for (unsigned i = 0; i < sizeof(valeursAttendues) / sizeof(Info); ++i) {
		assert(insererEnQueue(liste2, &valeursAttendues[i]) == OK);
	}

	printf("Suppression si position impaire et valeur entre 2 et 8\n");
	afficher(liste1, FORWARD);
	supprimerSelonCritere(liste1, positionImpaireEtEntre2et8);
	printf(" => ");
	afficher(liste1, FORWARD);
	assert(sontEgales(liste1, liste2));

	printf("\nTentative de suppression si valeur > 3\n");
	vider(liste1, 0);
	vider(liste2, 0);
	remplirListeIncrementale(liste1, 1, 1);
	remplirListeIncrementale(liste2, 1, 1);
	afficher(liste1, FORWARD);
	supprimerSelonCritere(liste1, infoPlusGrandQue3);
	printf(" => ");
	afficher(liste1, FORWARD);
	assert(sontEgales(liste1, liste2));

	printf("\nTentative de suppression si valeur > 3\n");
	vider(liste1, 0);
	vider(liste2, 0);
	afficher(liste1, FORWARD);
	supprimerSelonCritere(liste1, infoPlusGrandQue3);
	printf(" => ");
	afficher(liste1, FORWARD);
	assert(estVide(liste1));
	assert(sontEgales(liste1, liste2));

	printf("\nSuppression si valeur > 3\n");
	vider(liste1, 0);
	vider(liste2, 0);
	remplirListeIncrementale(liste1, 5, 1);
	afficher(liste1, FORWARD);
	supprimerSelonCritere(liste1, infoPlusGrandQue3);
	printf(" => ");
	afficher(liste1, FORWARD);
	assert(estVide(liste1));
	assert(sontEgales(liste1, liste2));
	printf("\n=> Test reussi\n");

	// Libération de la mémoire
	vider(liste1, 0);
	free(liste1);
	liste1 = NULL;

	vider(liste2, 0);
	free(liste2);
	liste2 = NULL;

	vider(liste3, 0);
	free(liste3);
	liste3 = NULL;

	return EXIT_SUCCESS;
}

void remplirListeIncrementale(Liste* liste, Info valeurMinimale, size_t nbValeurs) {
	Info valeur = valeurMinimale;
	for (size_t i = 0; i < nbValeurs; ++i) {
		assert(insererEnQueue(liste, &valeur) == OK);
		++valeur;
	}
}

bool positionImpaireEtEntre2et8(size_t position, const Info* info) {
	return position % 2 != 0 && *info >= 2 && *info <= 8;
}

// Levée d'un Warning Wunused-parameter prévue
bool infoPlusGrandQue3(size_t position, const Info* info) {
	return *info > 3;
}
