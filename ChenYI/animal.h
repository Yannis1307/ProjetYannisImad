#define TAILLE_NOM 100
#define TAILLE_COMMENTAIRE 100

typedef struct {
    int num;
    char nom[100];
    Espece espece;                 
    int annee_naissance;
    int poids;          
    char commentaire[100];
}Animal;
