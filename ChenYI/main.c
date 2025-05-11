#include "espece.h"
#include "affichage.h"
#include "couleurs.h"
#include "utilitaires.h"
#include "gestions.h"

int main() { // Fonction principale du programme
  Refuge refuge;
  refuge.nb_animaux = 0;
  charger_animaux(&refuge);
  menu(&refuge);
  return 0;
}
