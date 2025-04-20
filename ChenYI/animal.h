#define TAILLE_NOM 50
#define TAILLE_COMMENTAIRE 256

typedef struct {
    int num;
    char nom[100];
    Espece espece;                 
    int annee_naissance;
    int poids;          
    char commentaire[100];
}Animal;
