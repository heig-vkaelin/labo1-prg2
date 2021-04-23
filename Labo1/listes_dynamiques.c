/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
 Date creation  : 22.04.2021

 Description    : Implémentation de la librairie permettant la gestion de listes
                  doublement chaînées non circulaires.

 Remarque(s)    : Utilisation de calloc à la place de malloc pour que les champs
                  des structures soient automatiquement initialisés à NULL.
                  La vérification de la bonne initialisation de la liste est à la
                  charge du développeur. Un pointeur NULL est renvoyé en cas
                  d'erreur lors de l'allocation mémoire.

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "listes_dynamiques.h"

/**
 * Crée un nouvel Element et retourne un pointeur sur celui-ci.
 * Utilisée dans les fonctions permettant d'insérer un nouvel élément à la liste.
 * @param info : valeur de l'élément à créer
 * @return un pointeur sur l'Element créé
 */
Element* creerElement(const Info* info) {
	Element* nouvelElement = (Element*) calloc(1, sizeof(Element));
	if (nouvelElement) {
		nouvelElement->info = *info;
	}

	return nouvelElement;
}

Liste* initialiser() {
	return (Liste*) calloc(1, sizeof(Liste));
}

bool estVide(const Liste* liste) {
	return liste->tete == NULL && liste->queue == NULL;
}

size_t longueur(const Liste* liste) {
	size_t longueur = 0;
	Element* temp = liste->tete;
	while (temp) {
		++longueur;
		temp = temp->suivant;
	}
	return longueur;
}

void afficher(const Liste* liste, Mode mode) {
	printf("[");
	Element* temp = NULL;
	temp = (mode == FORWARD ? liste->tete : liste->queue);
	while (temp) {
		printf("%d", temp->info);
		if ((temp = (mode == FORWARD ? temp->suivant : temp->precedent))) {
			printf(", ");
		}
	}
	printf("]");
}

Status insererEnTete(Liste* liste, const Info* info) {
	Element* nouvelElement = creerElement(info);
	if (!nouvelElement) {
		return MEMOIRE_INSUFFISANTE;
	}

	if (estVide(liste)) {
		liste->tete = nouvelElement;
		liste->queue = nouvelElement;
	} else {
		liste->tete->precedent = nouvelElement;
		nouvelElement->suivant = liste->tete;
		liste->tete = nouvelElement;
	}

	return OK;
}

Status insererEnQueue(Liste* liste, const Info* info) {
	Element* nouvelElement = creerElement(info);
	if (!nouvelElement) {
		return MEMOIRE_INSUFFISANTE;
	}

	if (estVide(liste)) {
		liste->tete = nouvelElement;
		liste->queue = nouvelElement;
	} else {
		liste->queue->suivant = nouvelElement;
		nouvelElement->precedent = liste->queue;
		liste->queue = nouvelElement;
	}

	return OK;
}

Status supprimerEnTete(Liste* liste, Info* info) {
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

Status supprimerEnQueue(Liste* liste, Info* info) {
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

void supprimerSelonCritere(Liste* liste, bool (* critere)(size_t, const Info*)) {
	if (estVide(liste)) {
		return;
	}

	size_t pos = 0;
	Element* element = liste->tete;

	while (element) {
		Element* tempSuivant = element->suivant;
		if (critere(pos, &element->info)) {
			if (element->precedent) {
				element->precedent->suivant = element->suivant;
			} else {
				liste->tete = element->suivant;
			}

			if (element->suivant) {
				element->suivant->precedent = element->precedent;
			} else {
				liste->queue = element->precedent;
			}
			free(element);
		}
		++pos;
		element = tempSuivant;
	}
}

void vider(Liste* liste, size_t position) {
	for (size_t nbElements = longueur(liste); nbElements > position; --nbElements) {
		supprimerEnQueue(liste, &liste->queue->info);
	}
}

bool sontEgales(const Liste* liste1, const Liste* liste2) {
	size_t longueur1 = longueur(liste1);
	size_t longueur2 = longueur(liste2);

	if (longueur1 != longueur2) {
		return false;
	}

	Element* temp1 = liste1->tete;
	Element* temp2 = liste2->tete;
	for (size_t i = 0; i < longueur1; ++i) {
		if (temp1->info != temp2->info) {
			return false;
		}
		temp1 = temp1->suivant;
		temp2 = temp2->suivant;
	}

	return true;
}
