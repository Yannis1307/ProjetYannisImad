#include "utilitaires.h"
#include "couleurs.h"
#include "espece.h"
#include "affichage.h"
#include "gestions.h"  

int demanderEntier(const char *message) {
  int n;      // Variable pour stocker l'entier saisi
  int result; // Variable pour vérifier si scanf a réussi à lire un entier

  printf("%s",message); // Affiche le message pour demander à l'utilisateur un entier
  result = scanf("%d", &n); // Essaie de lire un entier

  if (result == 1) {
    // Si scanf a réussi à lire un entier (retourne 1 car il aura recupere une seule valeur en gros), on retourne la valeur lue
    return n;
  }

  // Si scanf n'a pas lu un entier correctement (par exemple, "abc"), on affiche une erreur
  printf("Entrée invalide. Veuillez entrer un nombre entier.\n");

  // On consomme la mauvaise entrée pour éviter que scanf boucle toujours sur la même erreur
  scanf("%*s"); // Cette ligne lit un mot invalide sans le stocker (le jette)

  //On rappel la fonction jusqu'a avoir une bonne entree de l'utilisateur 
  return demanderEntier(message);
}

int calculer_age(int annee) { // Fonction pour calculer l'âge d'un animal à partir de son année de naissance
  if (annee == 0) {
    printf("Erreur: l'année de naissance ne peut pas être 0.\n");
    return 0;
  } else if (annee < 0) {
    printf("Erreur: l'année de naissance ne peut pas être négative.\n");
    return 0;
  } else if (annee > 2025) {
    printf("Erreur: l'année de naissance ne peut pas être supérieure à 2025.\n");
    return 0;
  } else {
    return 2025 - annee;
  }
}

void copier_texte(char *dest, const char *src) { 
  strcpy(dest, src); // Utilisation de strcpy pour copier le texte de src vers dest
}

int contient(const char *texte, const char *mot) {
  // On utilise la fonction strstr() qui cherche si 'mot' est présent dans 'texte'
  char *resultat = strstr(texte, mot);

  // Si le mot est trouvé, strstr() retourne un pointeur vers la position dans 'texte'
  // Sinon, elle retourne NULL
  if (resultat != NULL) {
    return 1; // Le mot a été trouvé dans le texte
  } else {
    return 0; // Le mot n’a pas été trouvé
  }
}
