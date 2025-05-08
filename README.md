Projet : Gestion d’un Refuge Animalier

Ce projet est une application en C permettant de gérer les animaux d’un refuge à travers un menu interactif en terminal. Il propose l’ajout, l’affichage, la recherche, l’adoption d’animaux ainsi que des statistiques utiles (âge, besoin en croquettes, etc.).
📁 Fichiers attendus

    animal.h : contient la définition de la structure Animal et les constantes (MAX_ANIMAUX, TAILLE_NOM, etc.).

    espece.h : contient la liste des espèces (ESPECES) et les fichiers associés (FICHIERS).

    Fichiers texte comme chiens.txt, chats.txt, etc., contenant les données enregistrées des animaux.

    main.c : le fichier principal (celui affiché ci-dessus).

🧠 Fonctionnalités
🔹 ajouter_animal()

Ajoute un nouvel animal au refuge :

    L'utilisateur choisit le nom, l'espèce, l'année de naissance, le poids, et un commentaire.

    Un ID unique est généré automatiquement.

    Les données sont enregistrées dans la mémoire et dans le fichier correspondant à l’espèce.

🔹 afficher_animaux()

Affiche tous les animaux actuellement dans le refuge.
🔹 adopter_animal()

Supprime un animal du refuge à partir de son ID (⚠ ne met pas à jour les fichiers automatiquement).
🔹 rechercher_animaux()

Filtre les animaux selon trois critères :

    Nom exact (optionnel),

    Espèce (optionnelle),

    Tranche d'âge : jeune (< 2 ans), sénior (> 10 ans), ou tous.

🔹 statistiques_age()

Affiche le nombre d’animaux selon 4 tranches d’âge :

    0–2 ans,

    3–5 ans,

    6–10 ans,

    +10 ans.

🔹 croquettes()

Calcule les besoins quotidiens en croquettes pour tous les animaux selon leur espèce, âge ou poids.
🗃 Format des fichiers d’animaux (*.txt)

Chaque ligne d’un fichier représente un animal :

<ID> <NOM> <ESPECE> <ANNEE_NAISSANCE> <POIDS> <COMMENTAIRE>

Exemple :

101 Rex Chien 2017 24.5 Très joueur

✅ Lancement

Compile avec gcc :

gcc -o refuge main.c

Puis exécute :

./refuge

⚠ Remarques

    Les fichiers sont relus à chaque lancement (fonction charger_animaux()).

    L’adoption supprime un animal de la mémoire, mais il faudra relancer pour mettre à jour les fichiers manuellement.

    Pour une meilleure robustesse, on pourrait envisager de :

        Enregistrer à nouveau tout le fichier après chaque modification,

        Sauvegarder dans un format structuré (JSON, CSV, etc.).
