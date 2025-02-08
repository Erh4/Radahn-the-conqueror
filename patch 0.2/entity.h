#ifndef ENTITY_H
#define ENTITY_H
#include <stdlib.h>
#include <stdio.h>
#include "player.h"

typedef struct entity_struct {
    char * name;
    int strength;
    int hp_max;
    int hp;
    int coX;
    int coY;

}entity;

typedef entity * Pentity;



char *GetEntityName(entity *E);
/*int attack(entity * attaquant, entity * cible, int IDA);*/
Pentity Init_monstre(void);
void Update_health(entity *E, int n_vie);
void init_monstre(Pentity * ListeMonstre); /*la fonction renvoie un tableau de pointeurs, on prend donc le pointeur vers le premier élément du tableau*/
void DelEntity(Pentity E);


#endif
