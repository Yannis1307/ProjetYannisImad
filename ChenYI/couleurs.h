#include <stdio.h>

// Efface l'écran et replace le curseur en haut à gauche
#define clrscr() printf("\033[H\033[2J")

// Permet de changer la couleur du texte et du fond
#define couleur(param) printf("\033[%sm", param)
/*
  Exemples :
    couleur("31") : texte rouge
    couleur("42") : fond vert
    couleur("0")  : réinitialise (très important après une couleur)
*/