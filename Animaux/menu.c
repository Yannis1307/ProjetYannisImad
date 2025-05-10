#include "espece.h"
#include "fonction.h"

int demanderEntier(const char *message) {
  int n;          // Variable pour stocker l'entier saisi
  int result;     // Variable pour vérifier si scanf a réussi à lire un entier

  printf("%s", message);     // Affiche le message pour demander à l'utilisateur un entier
  result = scanf("%d", &n);  // Essaie de lire un entier

  if (result == 1) {
    // Si scanf a réussi à lire un entier (retourne 1car il aura recupere une seule valeur en gros), on retourne la valeur lue
    return n;
  }

  // Si scanf n'a pas lu un entier correctement (par exemple, "abc"), on affiche une erreur
  printf("Entrée invalide. Veuillez entrer un nombre entier.\n");

  // On consomme la mauvaise entrée pour éviter que scanf boucle toujours sur la même erreur
  scanf("%*s");  // Cette ligne lit un mot invalide sans le stocker (le jette)

  // On appelle la fonction elle-même pour redemander la saisie → récursion
  return demanderEntier(message);
}


int calculer_age(int annee) {
  if (annee <= 0 || annee > 2025) {
    printf("Erreur: année de naissance invalide.\n");
    return 0;
  }
  return 2025 - annee;
}

void copier_texte(char *dest, const char *src) { strcpy(dest, src); }

int contient(const char *texte, const char *mot) {
  return strstr(texte, mot) != NULL;
}

void charger_animaux(Refuge *refuge) {
  char ligne[512];

  for (int i = 0; i < nb_especes(); i++) {
    const char *nom_fichier = get_fichier(i);
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
      printf("Impossible d'ouvrir %s\n", nom_fichier);
      exit(1);
    }

    while (refuge->nb_animaux < MAX_ANIMAUX && fgets(ligne, sizeof(ligne), f)) {
      Animal a;
      if (sscanf(ligne, "%d %s %s %d %f %[^\n]", &a.id, a.nom, a.espece,
                 &a.annee_naissance, &a.poids, a.commentaire) == 6) {
        refuge->animaux[refuge->nb_animaux++] = a;
      } else {
        printf("Erreur de format dans %s : %s", nom_fichier, ligne);
      }
    }

    fclose(f);
  }
}

void afficher_animal(Animal a) {
  printf("ID: %d | Nom: %s | Espece: %s | Naissance: %d | Poids: %.2f | "
         "Commentaire: %s\n",
         a.id, a.nom, a.espece, a.annee_naissance, a.poids, a.commentaire);
}

int indice_espece(const char *espece) {
  for (int i = 0; i < nb_especes(); i++) {
    if (strcmp(espece, get_espece(i)) == 0) {
      return i;
    }
  }
  return -1;
}

int generer_id(Refuge *refuge, const char *espece) {
  int max = 0;
  for (int i = 0; i < refuge->nb_animaux; i++) {
    if (indice_espece(refuge->animaux[i].espece) == indice_espece(espece)) {
      if (refuge->animaux[i].id > max)
        max = refuge->animaux[i].id;
    }
  }
  return max + 1;
}

void ajouter_animal(Refuge *refuge) {
  if (refuge->nb_animaux >= MAX_ANIMAUX) {
    printf("Le refuge est plein (maximum %d animaux).\n", MAX_ANIMAUX);
    return;
  }

  Animal a;

  printf("Nom : ");
  scanf("%s", a.nom);

  printf("Choisir une espèce :\n");
  for (int i = 0; i < nb_especes(); i++) {
    printf("%d - %s\n", i + 1, get_espece(i));
  }

  int choix;
  scanf("%d", &choix);
  if (choix < 1 || choix > nb_especes()) {
    printf("Choix invalide.\n");
    return;
  }

  copier_texte(a.espece, get_espece(choix - 1));
  a.id = generer_id(refuge, a.espece);

  printf("Année de naissance : ");
  scanf("%d", &a.annee_naissance);

  printf("Poids : ");
  scanf("%f", &a.poids);

  printf("Commentaire : ");
  scanf("%s", a.commentaire);

  refuge->animaux[refuge->nb_animaux++] = a;

  FILE *f = fopen(get_fichier(choix - 1), "a");
  if (f != NULL) {
    fprintf(f, "%d %s %s %d %.2f %s\n", a.id, a.nom, a.espece,
            a.annee_naissance, a.poids, a.commentaire);
    fclose(f);
  }

  printf("Animal ajouté avec succès.\n");
}

void afficher_animaux(const Refuge *refuge) {
  for (int i = 0; i < refuge->nb_animaux; i++) {
    afficher_animal(refuge->animaux[i]);
  }
}

void rechercher_animaux(const Refuge *refuge) {
  char nom_recherche[TAILLE_NOM];
  int espece_choisie = -1;
  int type_age = 0;

  printf("Nom (laisser - pour ignorer) : ");
  scanf("%s", nom_recherche);

  printf("Choisir une espèce (0 pour ignorer) :\n");
  for (int i = 0; i < nb_especes(); i++) {
    printf("%d - %s\n", i + 1, get_espece(i));
  }
  scanf("%d", &espece_choisie);
  if (espece_choisie < 0 || espece_choisie > nb_especes())
    espece_choisie = 0;

  printf("Type d'âge ? (0=aucun, 1=jeune <2 ans, 2=sénior >10 ans) : ");
  scanf("%d", &type_age);

  int trouve = 0;

  for (int i = 0; i < refuge->nb_animaux; i++) {
    Animal a = refuge->animaux[i];
    int age = calculer_age(a.annee_naissance);

    int ok_nom = 1;
    if (nom_recherche[0] != '-' && nom_recherche[0] != '\0') {
      ok_nom = (strcmp(a.nom, nom_recherche) == 0);
    }

    int ok_espece = 1;
    if (espece_choisie > 0) {
      ok_espece = (indice_espece(a.espece) == espece_choisie - 1);
    }

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

void adopter_animal(Refuge *refuge) {
  int id;
  printf("ID de l’animal à adopter : ");
  scanf("%d", &id);

  int trouve = 0;
  char espece_supprimee[TAILLE_NOM];

  for (int i = 0; i < refuge->nb_animaux; i++) {
    if (refuge->animaux[i].id == id) {
      copier_texte(espece_supprimee, refuge->animaux[i].espece);
      for (int j = i; j < refuge->nb_animaux - 1; j++) {
        refuge->animaux[j] = refuge->animaux[j + 1];
      }
      refuge->nb_animaux--;
      trouve = 1;
      break;
    }
  }

  if (trouve) {
    printf("Animal adopté ! Mise à jour du fichier...\n");
    int indice = indice_espece(espece_supprimee);
    FILE *f = fopen(get_fichier(indice), "w");
    if (f != NULL) {
      for (int i = 0; i < refuge->nb_animaux; i++) {
        if (indice_espece(refuge->animaux[i].espece) == indice) {
          Animal a = refuge->animaux[i];
          fprintf(f, "%d %s %s %d %.2f %s\n", a.id, a.nom, a.espece,
                  a.annee_naissance, a.poids, a.commentaire);
        }
      }
      fclose(f);
    }
  } else {
    printf("Animal non trouvé.\n");
  }
}

void statistiques_age(const Refuge *refuge) {
  int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

  for (int i = 0; i < refuge->nb_animaux; i++) {
    int age = calculer_age(refuge->animaux[i].annee_naissance);
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

void croquettes(const Refuge *refuge) {
  float total = 0.0;
  for (int i = 0; i < refuge->nb_animaux; i++) {
    Animal a = refuge->animaux[i];
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

void menu(Refuge *refuge) {
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

    choix = demanderEntier("Votre choix : ");

    if (choix == 1)
      ajouter_animal(refuge);
    else if (choix == 2)
      afficher_animaux(refuge);
    else if (choix == 3)
      adopter_animal(refuge);
    else if (choix == 4)
      statistiques_age(refuge);
    else if (choix == 5)
      croquettes(refuge);
    else if (choix == 6)
      rechercher_animaux(refuge);
    else if (choix != 0)
      printf("Choix invalide. Veuillez réessayer.\n");

  } while (choix != 0);
}
