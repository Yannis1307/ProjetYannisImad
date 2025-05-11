#include "espece.h"
#include "gestions.h"
#include "couleurs.h"
#include "affichage.h"
#include "utilitaires.h" 

int nb_especes() {
  return 5;
}

const char *get_espece(int i) {
  const char *especes[] = { "Chien", "Chat", "Hamster", "Autruche", "Tortue" }; //tableau de chaines de caracteres dans lequel on stock les especes disponibles ce qui necessite de faire un tableau de pointeurs de chaines de caracteres 
  if (i >= 0 && i < nb_especes()) {
    return especes[i];
  } else {
    printf("Erreur : indice %d invalide pour les espèces (max = %d).\n", i, nb_especes() - 1);
    return "Inconnu";
  }
}

const char *get_fichier(int i) {  
  const char *fichiers[] = {  //tableau de chaines de caracteres dans lequel on stock les especes disponibles ce qui necessite de faire un tableau de pointeurs de chaines de caracteres 
    "animaux/chien.txt",
    "animaux/chat.txt",
    "animaux/hamster.txt",
    "animaux/autruche.txt",
    "animaux/tortue.txt"
  };

  if (i >= 0 && i < nb_especes()) { //verifie si l'indice est valide et si oui return le nom du fichier correspondant a l'indice 
    return fichiers[i];
  } else { //sinon affiche un message d'erreur et return un nom de fichier par defaut
    printf("Erreur : indice %d invalide pour les fichiers (max = %d).\n", i, nb_especes() - 1);
    return "animaux/fichier_inconnu.txt";
  }
}
