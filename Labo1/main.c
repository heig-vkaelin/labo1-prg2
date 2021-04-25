/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
 Date creation  : 22.04.2021

 Description    : Programme principal testant l'implémentation de la librairie
                  permettant la gestion de listes doublement chaînées non
                  circulaires.

 Remarque(s)    : Les tests des fonctions de la librairie ont été séparés en
                  plusieurs étapes. Les tests contenant des asserts sont considérés
                  valides lorsque "=> Test reussi" est affiché. Ceux qui n'ont pas
                  ce message ont une indication qu'ils ne contiennent pas d'assert.

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listes_dynamiques.h"

#define NB_LISTES 10

/**
 * Fonction permettant de supprimer de la liste tous les éléments dont la position
 * est impaire et pour lesquels info est compris dans l'intervalle [2, 8]
 * @param position : position dans la liste de l'élément
 * @param info : valeur de l'élément
 * @return true si l'élément doit être supprimé car il correspond aux critères
 */
bool positionImpaireEtEntre2et8(size_t position, const Info* info);

/**
 * Fonction permettant de faciliter le remplissage de valeurs incrémentales dans
 * une liste
 * @param liste : la liste à remplir
 * @param valeurMinimale : valeur du premier élément à introduire
 * @param nbValeurs : nombre d'éléments à introduire
 */
void remplirListeIncrementale(Liste* liste, Info valeurMinimale, size_t nbValeurs);

int main(void) {
	Liste* listes[NB_LISTES];
	const Info INFO_1 = 1;
	const Info INFO_2 = 2;
	Info ancienneTete = 0;
	Info ancienneQueue = 0;

	// 1. Initialisation
	printf("1. Initialisation");
	for (int i = 0; i < NB_LISTES; ++i) {
		listes[i] = initialiser();
		assert(listes[i] != NULL);
	}
	printf("\n=> Test reussi\n");

	// 2. Insertion des éléments à la tête
	printf("\n2. Insertion des elements a la tete\n");
	Liste* liste1 = listes[0];
	afficher(liste1, FORWARD);

	assert(insererEnTete(liste1, &INFO_1) == OK);
	printf(" => ");
	afficher(liste1, FORWARD);

	assert(insererEnTete(liste1, &INFO_2) == OK);
	printf(" => ");
	afficher(liste1, FORWARD);
	printf("\n=> Test reussi\n");

	// 3. Insertion des éléments à la queue
	printf("\n3. Insertion des elements a la queue\n");
	Liste* liste2 = listes[1];
	afficher(liste2, FORWARD);

	// Insertion dans liste vide
	assert(insererEnQueue(liste2, &INFO_1) == OK);
	printf(" => ");
	afficher(liste2, FORWARD);

	assert(insererEnQueue(liste2, &INFO_2) == OK);
	printf(" => ");
	afficher(liste2, FORWARD);
	printf("\n=> Test reussi\n");

	// 4. Suppression des éléments à la tête
	printf("\n4. Suppression des elements a la tete\n");
	afficher(liste1, FORWARD);

	assert(supprimerEnTete(liste1, &ancienneTete) == OK);
	printf(" => ");
	afficher(liste1, FORWARD);

	assert(supprimerEnTete(liste1, &ancienneTete) == OK);
	printf(" => ");
	afficher(liste1, FORWARD);

	assert(supprimerEnTete(liste1, &ancienneTete) == LISTE_VIDE);
	printf(" Derniere valeur supprime = %d\n=> Test reussi\n",
			 ancienneTete);

	// 5. Suppression des éléments à la queue
	printf("\n5. Suppression des elements a la queue\n");
	afficher(liste2, FORWARD);

	assert(supprimerEnQueue(liste2, &ancienneQueue) == OK);
	printf(" => ");
	afficher(liste2, FORWARD);

	assert(supprimerEnQueue(liste2, &ancienneQueue) == OK);
	printf(" => ");
	afficher(liste2, FORWARD);

	assert(supprimerEnQueue(liste2, &ancienneQueue) == LISTE_VIDE);
	printf(" Derniere valeur supprime = %d\n=> Test reussi\n",
			 ancienneQueue);

	// 6. Affichage de liste avec mode
	printf("\n6. Affichage de liste avec mode (Pas d'assert)\n");
	Liste* liste3 = listes[2];
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

	// 7. Vérification de liste vide
	printf("\n\n7. Verification de liste vide");
	Liste* liste4 = listes[3];
	assert(estVide(liste4));
	remplirListeIncrementale(liste4, 1, 1);
	assert(!estVide(liste4));
	printf("\n=> Test reussi\n");

	// 8. Vidage de liste
	printf("\n8. Vidage de liste\n");
	Liste* liste5 = listes[4];
	remplirListeIncrementale(liste5, 0, 9);
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
	printf("\n=> Test reussi\n");

	// 9. Vérification d'égalité de liste
	printf("\n9. Verification d'egalite de liste\n");
	Liste* liste6 = listes[5];
	Liste* liste7 = listes[6];

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

	printf("\n=> Test reussi\n");

	// 10. Suppression selon critères
	printf("\n10. Suppression selon criteres\n");
	Liste* liste8 = listes[7];
	Liste* liste8Attendue = listes[8];
	remplirListeIncrementale(liste8, 0, 10);

	// TODO: better way ?
	// Création du résultat attendu :
	Info valeursAttendues[7] = {0, 1, 2, 4, 6, 8, 9};
	for (unsigned i = 0; i < sizeof(valeursAttendues) / sizeof(Info); ++i) {
		insererEnQueue(liste8Attendue, &valeursAttendues[i]);
	}

	printf("Suppression si position impaire et valeur entre 2 et 8\n");
	afficher(liste8, FORWARD);
	supprimerSelonCritere(liste8, positionImpaireEtEntre2et8);
	printf(" => ");
	afficher(liste8, FORWARD);
	assert(sontEgales(liste8, liste8Attendue));
	printf("\n=> Test reussi\n");

	// 11. Calcul de la longueur
	printf("\n11. Calcul de la longueur\n");
	Liste* liste9 = listes[9];

	// TODO : Régler les flags avec % zu
	// Longueur de liste vide
	assert(longueur(liste9) == 0);
	printf("Longueur de liste vide\n");
	afficher(liste9, FORWARD);
	printf(" => Taille: %zu\n", longueur(liste9));

	// Longueur de liste remplie
	remplirListeIncrementale(liste9, 1, 4);
	assert(longueur(liste9) == 4);
	printf("Longueur de liste remplie\n");
	afficher(liste9, FORWARD);
	printf(" => Taille: %zu", longueur(liste9));
	printf("\n=> Test reussi\n");

	// Libération de la mémoire
	for (int i = 0; i < NB_LISTES; ++i) {
		vider(listes[i], 0);
		free(listes[i]);
		listes[i] = NULL;
	}

	return EXIT_SUCCESS;
}

bool positionImpaireEtEntre2et8(size_t position, const Info* info) {
	return position % 2 != 0 && *info >= 2 && *info <= 8;
}

void remplirListeIncrementale(Liste* liste, Info valeurMinimale, size_t nbValeurs) {
	Info valeur = valeurMinimale;
	for (size_t i = 0; i < nbValeurs; ++i) {
		insererEnQueue(liste, &valeur);
		++valeur;
	}
}
