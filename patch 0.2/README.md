De Justin FAVRAUD et Chamseddine SASSI.
Ce projet a été fait sous macOS, avec les limitations que ça implique. 

ATTENTION LE CODE NE FONCTIONNE QUE SUR VISUAL STUDIO CODE
NOUS NE SAVONS PAS POURQUOI IL NE VEUT PAS SE LANCER CORRECTEMENT DANS UN TERMINAL CLASSIQUE

Pour tester le programme nous conseillons d'utiliser les scripts 1 et 2 déjà existants afin de voir les possibilités de l'édition de carte.a
Le joueur est libre de créer ses propres cartes aussi


- La map ne peut pas faire moins de 20 de largeur et 10 de hauteur.

- On ne peut pas éditer le jeu en temps réel (on a enlevé la fonction qui permet de placer 
  des objets relativement à la position du joueur).
  La carte ne peut donc être éditée qu'avant que le jeu ne commence.

- On a préféré une actualisation du jeu en temps réel—c'est à dire qu'on a fait le choix d'afficher :
            - la map,
            - les statistiques 
            - et la boussole tout le temps. 
  À ce propos, les touches HAUT, GAUCHE, BAS, DROITE ont été remplacées par des plus classiques 
                            "z", "q", "s" et "d" respectivement. 
  Le joueur peut aussi s'accroupir et se relever pour être plus précis dans ses déplacements       avec la touche 'c'

- La touche "échap" du clavier permet de quitter la partie pour pouvoir ensuite quitter le jeu.

- La boussole permet d'avoir la position du Démiurge (le Y, centre de la map) en temps réel.

- Lorsqu'un joueur quitte la partie sans mourir, elle est automatiquement sauvegarder. 
  Ainsi il pourra, s'il le souhaite, retrouver exactement le jeu comme il l'a laissé.

- Le système de combat en tour par tour permet à l'utilisateur d'avoir l'option de fuir ou de continuer à attaquer.

Dans le programme, on a séparé nos différents fichiers (.h) en fonction de leur importance. 
Il peut cependant y avoir quelques fonctions qui ne sont pas dans les fichiers adaptés initialement, mais ça ne change rien au fonctionnement du programme.


LES ZONES DANGEREUSES OU NON RESOLUES:
 - On ne peut pas placer d'objet en (0,0) du à une l'initialisation de Radahn (il fallait choisir des valeurs par défaut)
 - Une erreur de warning sur un scanf que nous ne comprenons pas
 - Le programme ne peut s'executer que par 2 commandes
   -> ./programme
   -> ./programme nom_script.txt (en passant par cette commande il faudra dire que l'on ne veut pas charger une carte pré-existante et y entrer
                                    les dimensions de la carte);

   -> La commande avec le cat ne fonctionne pas car il est difficile pour le programme de lire le script sur l'entrée standard
 - Les fichiers de tests founirs par le professeurs ne peuvent pas fonctionner car trop de modifications de lecture du 
   scripts ont été faites.

