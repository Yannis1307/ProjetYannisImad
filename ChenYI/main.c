#include "fonction.h"
#include "espece.h"

int main() {
  Refuge refuge;
  refuge.nb_animaux = 0;
  charger_animaux(&refuge);
  menu(&refuge);
  return 0;
}
