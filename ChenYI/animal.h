#define TAILLE_NOM 50
#define TAILLE_COMMENTAIRE 256
#define MAX_ANIMAUX 50

typedef struct {
    int id;                        //nécessaire
    char nom[TAILLE_NOM];          //nom de l'animal
    char espece[TAILLE_NOM];       //espèce (ex : "Chien")
    int annee_naissance;           //pour calculer l'âge
    float poids;                   //utilisé pour croquettes
    char commentaire[TAILLE_COMMENTAIRE];  //affichage
} Animal;
