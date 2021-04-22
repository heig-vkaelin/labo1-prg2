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
	Liste *liste = (Liste *) calloc(1, sizeof(Liste));
	return liste;
}

bool estVide(const Liste *liste) {
	return liste->tete == NULL && liste->queue == NULL;
}

size_t longueur(const Liste *liste) {
	size_t longueur = 0;
	Element *temp = liste->tete;
	while (temp) {
		++longueur;
		temp = temp->suivant;
	}
	return longueur;
}

Element *creerElement(const Info *info) {
	Element *nouvelElement = (Element *) calloc(1, sizeof(Element));
	if (nouvelElement) {
		nouvelElement->info = *info;
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
	printf("]");
}

Status supprimerEnTete(Liste *liste, Info *info) {
	if (estVide(liste)) {
		return LISTE_VIDE;
	}

	*info = liste->tete->info;

	if (liste->tete == liste->queue) {
		free(liste->tete);
		liste->tete = NULL;
		liste->queue = NULL;
	} else {
		liste->tete = liste->tete->suivant;
		free(liste->tete->precedent);
		liste->tete->precedent = NULL;
	}

	return OK;
}

Status supprimerEnQueue(Liste *liste, Info *info) {
	if (estVide(liste)) {
		return LISTE_VIDE;
	}

	*info = liste->queue->info;

	if (liste->tete == liste->queue) {
		free(liste->tete);
		liste->tete = NULL;
		liste->queue = NULL;
	} else {
		liste->queue = liste->queue->precedent;
		free(liste->queue->suivant);
		liste->queue->suivant = NULL;
	}

	return OK;
}

void supprimerSelonCritere(Liste *liste,
									bool (*critere)(size_t position, const Info *info)) {
	if (estVide(liste)) {
		return;
	}

	size_t nbElements = longueur(liste);
	Element *element = liste->tete;

	for (size_t pos = 0; pos < nbElements; ++pos) {
		if (critere(pos, &element->info)) {
			if (element == liste->tete) {
				supprimerEnTete(liste, &liste->tete->info);
				element = liste->tete;
			} else if (element == liste->queue) {
				supprimerEnQueue(liste, &liste->queue->info);
				break;
			} else {
				Element *elementSuivant = element->suivant;
				element->suivant->precedent = element->precedent;
				element->precedent->suivant = element->suivant;
				free(element);
				element = NULL;
				element = elementSuivant;
			}
		} else {
			element = element->suivant;
		}
	}
}

void vider(Liste *liste, size_t position) {
	Info temp = 0;
	for (size_t nbElements = longueur(liste); nbElements > position; --nbElements) {
		supprimerEnQueue(liste, &temp);
	}
}

bool sontEgales(const Liste *liste1, const Liste *liste2) {
	size_t longueur1 = longueur(liste1);
	size_t longueur2 = longueur(liste2);

	if (longueur1 != longueur2) {
		return false;
	}

	Element *tmp1 = liste1->tete;
	Element *tmp2 = liste2->tete;
	for (size_t i = 0; i < longueur1; ++i) {
		if (tmp1->info != tmp2->info) {
			return false;
		}
		tmp1 = tmp1->suivant;
		tmp2 = tmp2->suivant;
	}

	return true;
}
