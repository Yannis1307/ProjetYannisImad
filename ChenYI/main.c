#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "espece.h"
#include "animal.h"

// Charge les animaux depuis un fichier texte correspondant à une espèce 
void charger_animaux_depuis_fichier(const char *nom_fichier, Animal animaux[], int *nb_animaux);

// Initialise tous les animaux en lisant les fichiers de chaque espèce
void initialiser_animaux(Animal animaux[], int *nb_animaux);

// Affiche le menu principal avec les options (ajouter, rechercher, adopter, etc.)
void afficher_menu();

// Ajoute un nouvel animal au tableau (si < 50 animaux), génère automatiquement un ID
void ajouter_animal(Animal animaux[], int *nb_animaux);

// Génére un identifiant unique en fonction de l'espèce (utilisé lors de l'ajout d'un animal)
int generer_id_unique(Animal animaux[], int nb_animaux, const char *espece);

// Recherche un ou plusieurs animaux selon des critères (nom, espèce, âge)
void rechercher_animaux(Animal animaux[], int nb_animaux);

// Vérifie si un animal correspond aux critères de recherche (nom partiel, espèce, âge)
bool correspond_criteres_recherche(Animal a, const char *nom, const char *espece, int age_min, int age_max);

// Supprime un animal du tableau selon son identifiant (procédure d'adoption)
void adopter_animal(Animal animaux[], int *nb_animaux);

// Affiche des statistiques sur les âges des animaux (nombre total, répartition par tranche)
void afficher_statistiques_age(Animal animaux[], int nb_animaux);

// Calcule l'âge d'un animal à partir de l'année actuelle et de son année de naissance
int calculer_age(int annee_naissance);

// Affiche la quantité de croquettes journalière nécessaire pour nourrir tous les animaux
void afficher_besoin_croquettes(Animal animaux[], int nb_animaux);

// Affiche les informations détaillées d'un animal (utilisé dans la recherche et l'ajout)
void afficher_animal(Animal a);

// Sauvegarde les animaux (modifiés ou ajoutés) dans leurs fichiers respectifs
void sauvegarder_animaux_dans_fichier(Animal animaux[], int nb_animaux);

main()
//Point d’entrée principal du programme.
//Appelle simplement le menu. 
