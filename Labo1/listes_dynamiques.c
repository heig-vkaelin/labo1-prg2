/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
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

Liste *initialiser() {
	Liste *liste = (Liste *) malloc(sizeof(Liste));
	if (liste) {
		liste->tete = NULL;
		liste->queue = NULL;
	}
	return liste;
}

bool estVide(const Liste *liste) {
	return liste->tete == NULL && liste->queue == NULL;
}

size_t longueur(const Liste *liste) {
	// TODO: est-elle utile à l'interne ?
	size_t longueur = 0;
	Element *temp = liste->tete;
	while (temp) {
		++longueur;
		temp = temp->suivant;
	}
	return longueur;
}

Element *creerElement(const Info *info) {
	Element *nouvelElement = (Element *) malloc(sizeof(Element));
	if (nouvelElement) {
		nouvelElement->info = *info;
		nouvelElement->precedent = NULL;
		nouvelElement->suivant = NULL;
	}

	return nouvelElement;
}

Status insererEnTete(Liste *liste, const Info *info) {
	Element *nouvelElement = creerElement(info);
	if (!nouvelElement) {
		return MEMOIRE_INSUFFISANTE;
	}

	if (estVide(liste)) {
		liste->tete = nouvelElement;
		liste->queue = nouvelElement;
		return OK;
	}

	liste->tete->precedent = nouvelElement;
	nouvelElement->suivant = liste->tete;
	liste->tete = nouvelElement;

	return OK;
}

Status insererEnQueue(Liste *liste, const Info *info) {
	Element *nouvelElement = creerElement(info);
	if (!nouvelElement) {
		return MEMOIRE_INSUFFISANTE;
	}

	if (estVide(liste)) {
		liste->tete = nouvelElement;
		liste->queue = nouvelElement;
		return OK;
	}

	liste->queue->suivant = nouvelElement;
	nouvelElement->precedent = liste->queue;
	liste->queue = nouvelElement;

	return OK;
}

void afficher(const Liste *liste, Mode mode) {
	// TODO: refactor avec une fonction prenant une fonction en params
	printf("[");
	Element *temp;
	if (mode == FORWARD) {
		temp = liste->tete;
		while (temp) {
			printf("%d", temp->info);
			if ((temp = temp->suivant)) {
				printf(", ");
			}
		}
	} else {
		temp = liste->queue;
		while (temp) {
			printf("%d", temp->info);
			if ((temp = temp->precedent)) {
				printf(", ");
			}
		}
	}
	printf("]\n");
}

Status supprimerEnTete(Liste *liste, Info *info) {
	if (estVide(liste)) {
		return LISTE_VIDE;
	}

	*info = liste->tete->info;

	// TODO: 1) quand tete = queue, il faut aussi delete la queue
	// TODO 2) Si longueur == 1 : queue devient aussi la tete
	liste->tete = liste->tete->suivant;
	free(liste->tete->precedent);
	liste->tete->precedent = NULL;

	return OK;
}

Status supprimerEnQueue(Liste *liste, Info *info) {
	if (estVide(liste)) {
		return LISTE_VIDE;
	}

	return OK;
}

void supprimerSelonCritere(Liste *liste,
									bool (*critere)(size_t position, const Info *info)) {

}

void vider(Liste *liste, size_t position) {

}

bool sontEgales(const Liste *liste1, const Liste *liste2) {

}
