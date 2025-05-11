#include "affichage.h"
#include <stdio.h>
#include "gestions.h"
#include "utilitaires.h"
#include "espece.h"

void afficher_animal(Animal a) {
    printf("\n\033[1;34m══════════════════════════════════════════════════════════\033[0m\n");
    printf("\033[1;33m🐾  ID :\033[0m           %d\n", a.id);
    printf("\033[1;33m📛  Nom :\033[0m          %s\n", a.nom);
    printf("\033[1;33m🦁  Espèce :\033[0m       %s\n", a.espece);
    printf("\033[1;33m🎂  Naissance :\033[0m   %d\n", a.annee_naissance);
    printf("\033[1;33m⚖️  Poids :\033[0m       %.2f kg\n", a.poids);
    printf("\033[1;33m🗨️  Commentaire :\033[0m %s\n", a.commentaire);
    printf("\033[1;34m══════════════════════════════════════════════════════════\033[0m\n");
  //afficher les informations de l'animal a l'ecran et le \33[1;33m permet de mettre en couleur le texte
}
void afficher_animaux(const Refuge *refuge) {
  for (int i = 0; i < refuge->nb_animaux; i++) {
    afficher_animal(refuge->animaux[i]);
  }
}

void menu(Refuge *refuge) {
  int choix;
  do {
    clrscr();  // Efface l'écran

    couleur("1;37"); // Texte blanc
    printf("+===============================================+\n");
    printf("|           🐾 CY REFUGE ANIMALIER 🐾           |\n");
    printf("+===============================================+\n");
    couleur("0");

    printf("| Nombre d'animaux hébergés : %d / %d%-11s|\n", refuge->nb_animaux, MAX_ANIMAUX, "");
    printf("|-----------------------------------------------|\n");

    couleur("36"); // Texte cyan
    printf("| 🐶 1. Ajouter un animal                       |\n");
    printf("| 📋 2. Afficher les animaux                    |\n");
    printf("| 🏠 3. Adopter un animal                       |\n");
    printf("| 📊 4. Statistiques d'âge                      |\n");
    printf("| 🍖 5. Calcul du besoin en croquettes          |\n");
    printf("| 🔍 6. Rechercher un animal                    |\n");
    printf("| ❌ 0. Quitter                                 |\n");
    printf("+-----------------------------------------------+\n");
    printf(" Votre choix : ");
    choix = demanderEntier(""); 
    couleur("0");
    switch (choix) { // Gestion du choix de l'utilisateur
      case 1: ajouter_animal(refuge); break;
      case 2: afficher_animaux(refuge); break;
      case 3: adopter_animal(refuge); break;
      case 4: statistiques_age(refuge); break;
      case 5: croquettes(refuge); break;
      case 6: rechercher_animaux(refuge); break;
      case 0:
        couleur("32");
        printf("\n👋 Merci d'avoir utilisé CY Refuge Animalier ! À bientôt !\n");
        couleur("0");
        break;
      default:
        couleur("31");
        printf("\n❗ Choix invalide. Veuillez réessayer.\n");
        couleur("0");
    }

    if (choix != 0) {
      printf("\nAppuyez sur Entrée pour continuer... ");
      getchar(); getchar();
    }

  } while (choix != 0);
}