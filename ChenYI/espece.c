#include "espece.h"
#include <stdio.h> // pour printf

int nb_especes() {
  return 5;
}

const char *get_espece(int i) {
  const char *especes[] = { "Chien", "Chat", "Hamster", "Autruche", "Tortue" };
  if (i >= 0 && i < nb_especes()) {
    return especes[i];
  } else {
    printf("Erreur : indice %d invalide pour les espèces (max = %d).\n", i, nb_especes() - 1);
    return "Inconnu";
  }
}

const char *get_fichier(int i) {
  const char *fichiers[] = { "chien.txt", "chat.txt", "hamster.txt", "autruche.txt", "tortue.txt" };
  if (i >= 0 && i < nb_especes()) {
    return fichiers[i];
  } else {
    printf("Erreur : indice %d invalide pour les fichiers (max = %d).\n", i, nb_especes() - 1);
    return "fichier_inconnu.txt";
  }
}
