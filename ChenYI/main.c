#include "animal.h"
#include "espece.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Animal refuge[MAX_ANIMAUX];
int nb_animaux = 0;

// Calcule l'âge à partir de l'année de naissance
int calculer_age(int annee) {
  if (annee == 0) {
    printf("Erreur: l'année de naissance ne peut pas être 0.\n");
    return 0;
  } else if (annee < 0) {
    printf("Erreur: l'année de naissance ne peut pas être négative.\n");
    return 0;
  } else if (annee > 2025) {
    printf(
        "Erreur: l'année de naissance ne peut pas être supérieure à 2025.\n");
    return 0;
  } else {
    return 2025 - annee;
  }
}
// Copie manuellement une chaîne
void copier_texte(char *dest, const char *src) {
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
}

// Charge tous les animaux depuis les fichiers de chaque espèce
void charger_animaux() {
    char ligne[512];
    for (int i = 0; i < NB_ESPECES; i++) {
        FILE *f = fopen(FICHIERS[i], "r");
        if (f == NULL) {
            printf("Impossible d'ouvrir %s\n", FICHIERS[i]);
            continue;
        }

        while (nb_animaux < MAX_ANIMAUX && fgets(ligne, sizeof(ligne), f)) {
            Animal a;
            // Lecture des 5 premières valeurs + commentaire (tout ce qui suit)
            if (sscanf(ligne, "%d %s %d %f %[^\n]",
                       &a.id, a.nom, &a.annee_naissance, &a.poids, a.commentaire) == 5) {
                copier_texte(a.espece, ESPECES[i]);
                refuge[nb_animaux++] = a;
            }
          else{
            printf("Erreur de format dans %s : %s", FICHIERS[i], ligne);
          }
        }

        fclose(f);
    }
}

// Affiche les informations d’un animal
void afficher_animal(Animal a) {
  printf("ID: %d | Nom: %s | Espece: %s | Naissance: %d | Poids: %f | "
         "Commentaire: %s\n",a.id, a.nom, a.espece, a.annee_naissance, a.poids, a.commentaire);
}

// Donne l’indice de l’espèce (utile pour savoir dans quel fichier écrire)
int indice_espece(const char *espece) {
  for (int i = 0; i < NB_ESPECES; i++) {
    int j = 0;
    int pareil = 1;
    while (espece[j] != '\0' && ESPECES[i][j] != '\0') {
      if (espece[j] != ESPECES[i][j])
        pareil = 0;
      j++;
    }
    if (pareil && espece[j] == '\0' && ESPECES[i][j] == '\0')
      return i;
  }
  return -1;
}

// Génère l’ID suivant pour une espèce donnée
int generer_id(const char *espece) {
  int max = 0;
  for (int i = 0; i < nb_animaux; i++) {
    if (indice_espece(refuge[i].espece) == indice_espece(espece)) {
      if (refuge[i].id > max)
        max = refuge[i].id;
    }
  }
  return max + 1;
}

// Ajoute un animal au refuge et l’enregistre dans le bon fichier
void ajouter_animal() {
  if (nb_animaux >= MAX_ANIMAUX) {
    printf("Refuge plein.\n");
    return;
  }

  Animal a;

  printf("Nom : ");
  scanf("%s", a.nom);

  printf("Choisir une espèce :\n");
  for (int i = 0; i < NB_ESPECES; i++) {
    printf("%d - %s\n", i + 1, ESPECES[i]);
  }
  int choix;
  scanf("%d", &choix);
  if (choix < 1 || choix > NB_ESPECES) {
    printf("Choix invalide.\n");
    return;
  }

  copier_texte(a.espece, ESPECES[choix - 1]);
  a.id = generer_id(a.espece);

  printf("Année de naissance : ");
  scanf("%d", &a.annee_naissance);

  printf("Poids : ");
  scanf("%f", &a.poids);

  printf("Commentaire (sans espace) : ");
  scanf("%s", a.commentaire);

  refuge[nb_animaux] = a;
  nb_animaux++;

  FILE *f = fopen(FICHIERS[choix - 1], "a");
  if (f != NULL) {
    fprintf(f, "%d %s %d %.2f %s\n", a.id, a.nom, a.annee_naissance, a.poids,
            a.commentaire);
    fclose(f);
  }

  printf("Animal ajouté avec succès.\n");
}

// Affiche tous les animaux du refuge
void afficher_animaux() {
  for (int i = 0; i < nb_animaux; i++) {
    afficher_animal(refuge[i]);
  }
}


void rechercher_animaux() {
  char nom_recherche[TAILLE_NOM];
  int espece_choisie = -1;
  int type_age = 0;

  printf("Nom (laisser - pour ignorer) : ");
  scanf("%s", nom_recherche);

  printf("Choisir une espèce (0 pour ignorer) :\n");
  for (int i = 0; i < NB_ESPECES; i++) {
    printf("%d - %s\n", i + 1, ESPECES[i]);
  }
  scanf("%d", &espece_choisie);
  if (espece_choisie < 0 || espece_choisie > NB_ESPECES)
    espece_choisie = 0;

  printf("Type d'âge ? (0=aucun, 1=jeune <2 ans, 2=sénior >10 ans) : ");
  scanf("%d", &type_age);

  int trouve = 0;

  for (int i = 0; i < nb_animaux; i++) {
    Animal a = refuge[i];
    int age = calculer_age(a.annee_naissance);

    // Vérifie nom
    int ok_nom = 1;
    if (nom_recherche[0] != '-' && nom_recherche[0] != '\0') {
      ok_nom = (strcmp(a.nom, nom_recherche) == 0); // Comparaison exacte du nom
    }

    // Vérifie espèce
    int ok_espece = 1;
    if (espece_choisie > 0) {
      ok_espece = (indice_espece(a.espece) == espece_choisie - 1);
    }

    // Vérifie âge
    int ok_age = 1;
    if (type_age == 1 && age >= 2)
      ok_age = 0;
    if (type_age == 2 && age <= 10)
      ok_age = 0;

    if (ok_nom && ok_espece && ok_age) {
      afficher_animal(a);
      trouve = 1;
    }
  }

  if (!trouve) {
    printf("Aucun animal ne correspond aux critères.\n");
  }
}

void adopter_animal() {
  int id;
  printf("ID de l’animal à adopter : ");
  scanf("%d", &id);

  int trouve = 0;
  for (int i = 0; i < nb_animaux; i++) {
    if (refuge[i].id == id) {
      for (int j = i; j < nb_animaux - 1; j++) {
        refuge[j] = refuge[j + 1];
      }
      nb_animaux--;
      trouve = 1;
      break;
    }
  }

  if (trouve) {
    printf("Animal adopté ! (⚠ Il faut relancer pour mettre à jour les "
           "fichiers)\n");
  } else {
    printf("Animal non trouvé.\n");
  }
}

// Statistiques d’âge
void statistiques_age() {
  int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

  for (int i = 0; i < nb_animaux; i++) {
    int age = calculer_age(refuge[i].annee_naissance);
    if (age <= 2)
      q1++;
    else if (age <= 5)
      q2++;
    else if (age <= 10)
      q3++;
    else
      q4++;
  }

  printf("0-2 ans : %d\n3-5 ans : %d\n6-10 ans : %d\n+10 ans : %d\n", q1, q2,
         q3, q4);
}

// Calcul croquettes
void croquettes() {
  float total = 0.0;
  for (int i = 0; i < nb_animaux; i++) {
    Animal a = refuge[i];
    int age = calculer_age(a.annee_naissance);
    if (a.espece[0] == 'H')
      total += 0.02;
    else if (a.espece[0] == 'A')
      total += 2.5;
    else if (a.espece[0] == 'C') {
      if (age < 2)
        total += 0.5;
      else
        total += 0.1 * a.poids;
    } else if (a.espece[0] == 'T') {
      total += 0.05;
    }
  }
  printf("Besoin quotidien : %.2f kg\n", total);
}

// Menu principal
void menu() {
  int choix;
  do {
    printf("\n--- MENU REFUGE ---\n");
    printf("1. Ajouter un animal\n");
    printf("2. Afficher animaux\n");
    printf("3. Adopter un animal\n");
    printf("4. Statistiques d’âge\n");
    printf("5. Croquettes\n");
    printf("6. Rechercher un animal\n");
    printf("0. Quitter\n");
    scanf("%d", &choix);

    if (choix == 1)
      ajouter_animal();
    else if (choix == 2)
      afficher_animaux();
    else if (choix == 3)
      adopter_animal();
    else if (choix == 4)
      statistiques_age();
    else if (choix == 5)
      croquettes();
    else if (choix == 6)
      rechercher_animaux();
  } while (choix != 0);
}

int main() {
  charger_animaux();
  menu();
  return 0;
}