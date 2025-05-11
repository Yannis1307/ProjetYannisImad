#ifndef gestions_h
#define gestions_h

#define TAILLE_NOM 50                    // Taille maximale pour les noms d'animaux
#define TAILLE_COMMENTAIRE 256           // Taille maximale pour les commentaires
#define MAX_ANIMAUX 50                   // Nombre maximal d'animaux dans le refuge

// Structure représentant un animal avec ses différentes caractéristiques
typedef struct {
  int id;                                // Identifiant unique
  char nom[TAILLE_NOM];                 // Nom
  char espece[TAILLE_NOM];              // Espèce
  int annee_naissance;                  // Année de naissance
  float poids;                          // Poids en kg
  char commentaire[TAILLE_COMMENTAIRE]; // Commentaire libre
} Animal;

// Structure contenant les animaux du refuge et leur nombre
typedef struct {
  Animal animaux[MAX_ANIMAUX];          // Liste des animaux
  int nb_animaux;                       // Compteur d'animaux
} Refuge;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Déclarations des fonctions de gestion
void charger_animaux(Refuge *refuge);
int indice_espece(const char *espece);
int generer_id(Refuge *refuge, const char *espece);
void ajouter_animal(Refuge *refuge);
void rechercher_animaux(const Refuge *refuge);
void adopter_animal(Refuge *refuge);
void statistiques_age(const Refuge *refuge);
void croquettes(const Refuge *refuge);

#endif
