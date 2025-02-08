#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H
#include <stdio.h>
#include "entity.h"
#include "object.h"

typedef struct map_struct {
    int taille_x;
    int taille_y;
    int centreX;
    int centreY;
    Pentity * ListeMonstre;
    Pobject * ListeNourriture;
    Pobject * ListeObjet;
    int nombreMonstre;
    int nombreNourriture;
    int nombreObjet;
} map_info;

map_info *Init_map(void);

int nb_monstre(Pentity * liste);
int nb_objet(Pobject * liste);

void Ouvrir_map(char ** Matrice, char * nom_fichier, map_info * Map);
void Creer_map(char * nom_fichier, int taille_x, int taille_y);
void script_error(void);
int checkX(char *s);
int checkY(char *s);
int checkd(char *s);
int checkD(char *s);
void Place_interaction(char ** Matrice, int x, int y, char *s,map_info* Map);
void Lecture_script(char ** Matrice, char * nom_fichier_script, map_info* Map);
#endif
