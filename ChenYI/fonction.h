#define TAILLE_NOM 50
#define TAILLE_COMMENTAIRE 256
#define MAX_ANIMAUX 50

typedef struct {
  int id;
  char nom[TAILLE_NOM];
  char espece[TAILLE_NOM];
  int annee_naissance;
  float poids;
  char commentaire[TAILLE_COMMENTAIRE];
} Animal;

typedef struct {
  Animal animaux[MAX_ANIMAUX];
  int nb_animaux;
} Refuge;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonctions utilitaires
int demanderEntier(const char *message);
int calculer_age(int annee);
void copier_texte(char *dest, const char *src);
int contient(const char *texte, const char *mot);

// Fonctions espèce/fichier
int nb_especes();
const char *get_espece(int i);
const char *get_fichier(int i);

// Fonctions de gestion d'animaux
void charger_animaux(Refuge *refuge);
void afficher_animal(Animal a);
int indice_espece(const char *espece);
int generer_id(Refuge *refuge, const char *espece);
void ajouter_animal(Refuge *refuge);
void afficher_animaux(const Refuge *refuge);
void rechercher_animaux(const Refuge *refuge);
void adopter_animal(Refuge *refuge);
void statistiques_age(const Refuge *refuge);
void croquettes(const Refuge *refuge);
void menu(Refuge *refuge);
