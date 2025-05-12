#include "gestions.h"
#include "affichage.h"
#include "couleurs.h"
#include "espece.h"
#include "utilitaires.h"

// Fonction pour charger tous les animaux depuis les fichiers
void charger_animaux(Refuge *refuge) {
  char ligne[512]; // buffer pour stocker chaque ligne du fichier

  for (int i = 0; i < nb_especes(); i++) { // boucle sur chaque espèce existante
    const char *nom_fichier =get_fichier(i); // nom fichier va devenir le nom du fichier correspondant a l'espece i
    FILE *f =fopen(nom_fichier,"r");// ce qui permettra ici de l ouvrir en mode lecture "r"
    if (f == NULL) { // si le fichier n existe pas ou n a pas pu etre ouvert
      printf("Impossible d'ouvrir %s\n",nom_fichier); // Affiche un message d'avertissement et passe à l'espèce suivante
      continue;
    }

    while (refuge->nb_animaux < MAX_ANIMAUX && fgets(ligne, sizeof(ligne),f)){ //lit ligne par ligne tant que le refuge n'est pas plein
      Animal a;
      if (sscanf(ligne, "%d %s %s %d %f %[^\n]", &a.id, a.nom, a.espece,&a.annee_naissance, &a.poids,a.commentaire) == 6) { //%[^\n] pour lire tout le reste de la ligne jusqu'au saut de ligne
        refuge->animaux[refuge->nb_animaux] =a; // on ajoute l'animal dans le tableau
        refuge->nb_animaux =refuge->nb_animaux +1; // Incrementer le nombre d'animaux dans le refuge
      } else {
        printf("Erreur de format dans %s : %s", nom_fichier,ligne); // Affiche un message d'erreur si le format de la ligne n'est pas correcte
      }
    }

    fclose(f); // fermeture du fichier après lecture
  }
}


// Fonction pour retrouver l'indice d'une espèce à partir de son nom
int indice_espece(const char *espece) {
  for (int i = 0; i < nb_especes(); i++) {
    if (strcmp(espece, get_espece(i)) ==0) { // si la condition est vraie return i donc l indice de l espece
      return i;
    }
  }
  return -1; // si la condition n est pas vraie return -1
}

// Fonction pour générer un nouvel ID unique pour une espèce donnée
int generer_id(Refuge *refuge, const char *espece) {
  int max = 0; // ID maximal trouvé pour l'espèce
  for (int i = 0; i < refuge->nb_animaux; i++) {
    if (indice_espece(refuge->animaux[i].espece) ==indice_espece(espece)) { // on vérifie si l'espèce correspond
      if (refuge->animaux[i].id > max){
        max = refuge->animaux[i].id; // on garde le plus grand ID trouvé
        }
    }
  }
  return max + 1; // retourne un ID unique (le suivant)
}

// Fonction pour ajouter un nouvel animal dans le refuge
void ajouter_animal(Refuge *refuge) {
  int refuge_plein = 0;

  if (refuge->nb_animaux >= MAX_ANIMAUX) {
    printf("❌ Le refuge est plein (maximum %d animaux).\n", MAX_ANIMAUX);
    refuge_plein = 1;
  }

  if (refuge_plein == 0) {
    Animal a;

    // === Nom ===
    int nom_valide = 0;
    while (nom_valide == 0) {
      printf("Nom : ");
      scanf("%s", a.nom);

      nom_valide = 1;
      int i = 0;
      while (a.nom[i] != '\0') {
        if (a.nom[i] >= '0' && a.nom[i] <= '9') {
          nom_valide = 0;
        }
        i = i + 1;
      }

      if (nom_valide != 1) {
        printf("❌ Le nom ne doit pas contenir de chiffre.\n");
      }
    }

    // === Espèce ===
    printf("Choisir une espèce :\n");
    int i = 0;
    while (i < nb_especes()) {
      printf("%d - %s\n", i + 1, get_espece(i));
      i = i + 1;
    }

    int choix_valide = 0;
    int choix = 0;

    while (choix_valide == 0) {
      choix = demanderEntier("Votre choix : ");
      if (choix >= 1 && choix <= nb_especes()) {
        choix_valide = 1;
      } else {
        printf("❌ Choix invalide. Veuillez entrer un nombre entre 1 et %d.\n", nb_especes());
      }
    }

    copier_texte(a.espece, get_espece(choix - 1));
    a.id = generer_id(refuge, a.espece);

    // === Année de naissance ===
    int annee_actuelle = 2025;
    int annee_valide = 0;
    while (annee_valide == 0) {
      a.annee_naissance = demanderEntier("Année de naissance : ");
      if (a.annee_naissance <= annee_actuelle) {
        annee_valide = 1;
      } else {
        printf("❌ L'année ne peut pas dépasser %d.\n", annee_actuelle);
      }
    }

    // === Poids ===
    float poids = 0;
    int poids_valide = 0;
    while (poids_valide == 0) {
      printf("Poids : ");
      if (scanf("%f", &poids) == 1 && poids > 0) {
        poids_valide = 1;
      } else {
        printf("❌ Entrez un poids valide (ex : 12.5).\n");
        scanf("%*s");
      }
    }
    a.poids = poids;
    getchar(); // pour consommer le \n

    // === Commentaire (sans validation) ===
    printf("Commentaire : ");
    fgets(a.commentaire, TAILLE_COMMENTAIRE, stdin);

    size_t len = strlen(a.commentaire);
    if (len > 0 && a.commentaire[len - 1] == '\n') {
      a.commentaire[len - 1] = '\0';
    }

    // === Ajout au refuge
    refuge->animaux[refuge->nb_animaux] = a;
    refuge->nb_animaux = refuge->nb_animaux + 1;

    // === Écriture dans le fichier
    FILE *fichier = fopen(get_fichier(choix - 1), "a");
    if (fichier != NULL) {
      fprintf(fichier, "\n%d %s %s %d %.2f %s", a.id, a.nom, a.espece,a.annee_naissance, a.poids, a.commentaire);
      fclose(fichier);
    }

    printf("✅ Animal ajouté avec succès.\n");
  }
}




// Fonction de recherche d'animaux selon plusieurs critères (nom, espèce,tranche d'âge)
void rechercher_animaux(const Refuge *refuge) {
  char nom_recherche[TAILLE_NOM];
  int espece_choisie = -1;
  int type_age = 0;

  printf("📛Nom (Ecrit - pour ignorer) : ");
  scanf("%s", nom_recherche);

  // Vérifie si le nom contient un chiffre
  for (int i = 0; nom_recherche[i] != '\0'; i++) {
    if (nom_recherche[i] >= '0' && nom_recherche[i] <= '9') {
      printf("❌ Le nom ne doit pas contenir de chiffre.\n");
      return;
    }
  }

  printf("🦁Choisir une espèce (0 pour ignorer) :\n");
  for (int i = 0; i < nb_especes(); i++) {
    printf("%d - %s\n", i + 1,
           get_espece(i)); // afficher les options disponibles
  }
  scanf("%d", &espece_choisie);
  if (espece_choisie < 0 || espece_choisie > nb_especes())
    espece_choisie = 0;

  printf("🎂Type d'âge ? (0=aucun, 1=jeune <2 ans, 2=sénior >10 ans) : ");
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

  if (trouve==0) {
    printf("Aucun animal ne correspond aux critères.\n");
  }
}

// Fonction permettant d'adopter un animal (suppression par ID)
void adopter_animal(Refuge *refuge) {
  int id;
  printf("🐾 ID de l’animal à adopter : ");
  scanf("%d", &id);

  int trouve = 0;
  char espece_supprimee[TAILLE_NOM];

  for (int i = 0; i < refuge->nb_animaux; i++) {
    if (refuge->animaux[i].id == id) { // si l'animal avec l'ID existe
      copier_texte(espece_supprimee,
                   refuge->animaux[i].espece); // sauvegarde de l'espèce
      for (int j = i; j < refuge->nb_animaux - 1; j++) {
        refuge->animaux[j] =
            refuge->animaux[j + 1]; // décalage des éléments vers la gauche
      }
      refuge->nb_animaux--; // décrémente le nombre d'animaux
      trouve = 1;
      break;
    }
  }

  if (trouve == 1) { // si l'animal a été trouvé et supprimé
    printf("🐶 Animal adopté ! Mise à jour du fichier...\n");
    int indice = indice_espece(espece_supprimee);
    FILE *f =
        fopen(get_fichier(indice),
              "w"); // on écrase le fichier de l'espèce pour le mettre à jour
    if (f != NULL) {
      for (int i = 0; i < refuge->nb_animaux; i++) {
        if (indice_espece(refuge->animaux[i].espece) == indice) {
          Animal a = refuge->animaux[i];
          fprintf(f, "%d %s %s %d %f %s\n", a.id, a.nom, a.espece,
                  a.annee_naissance, a.poids, a.commentaire);
        }
      }
      fclose(f);
    }
  } else {
    printf("🔍 Animal non trouvé.\n"); // si l'ID n'existe pas
  }
}

// Fonction de statistiques : répartition des animaux par tranche d'âge
void statistiques_age(const Refuge *refuge) {
  int q1 = 0, q2 = 0, q3 = 0, q4 = 0; // compteurs pour chaque tranche

  for (int i = 0; i < refuge->nb_animaux; i++) {
    int age = calculer_age(refuge->animaux[i].annee_naissance);
    if (age <= 2){
      q1++;
    }
    else if (age <= 5){
      q2++;
    }
    else if (age <= 10){
      q3++;
    }
    else{
      q4++;
    }
  }

  // affichage formaté des statistiques
  printf("=====================================\n");
  printf("      📊 Répartition par âge 📊      \n");
  printf("=====================================\n");
  printf("|  0 - 2 ans   : %3d animaux         |\n", q1);
  printf("|  3 - 5 ans   : %3d animaux         |\n", q2);
  printf("|  6 - 10 ans  : %3d animaux         |\n", q3);
  printf("|  +10 ans     : %3d animaux         |\n", q4);
  printf("=====================================\n");
  printf("|  Total       : %3d animaux         |\n", refuge->nb_animaux);
}

// Fonction de calcul du besoin total en croquettes selon l'espèce et l'âge
void croquettes(const Refuge *refuge) {
  float total = 0.0; // accumulateur pour le poids total de croquettes
  for (int i = 0; i < refuge->nb_animaux; i++) {
    Animal a = refuge->animaux[i];
    int age = calculer_age(a.annee_naissance);
    if (a.espece[0] == 'H'){ // Hamster
      total += 0.02;
    }
    else if (a.espece[0] == 'A'){ // Autruche
      total += 2.5;
    }
    else if (a.espece[0] == 'C') { // Chien
      if (age < 2)
        total += 0.5;
      else
        total += 0.1 * a.poids;
    } else if (a.espece[0] == 'T') { // Tortue
      total += 0.05;
    }
  }
  // affichage du besoin total
  printf("=====================================\n");
  printf("   🍖 Besoin quotidien en croquettes   \n");
  printf("=====================================\n");
  printf("|  Total : %.2f kg                  |\n", total);
  printf("=====================================\n");
}
