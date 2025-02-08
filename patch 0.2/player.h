#ifndef PLAYER_H
#define PLAYER_H
#include <stdlib.h>
#include <stdio.h>
#include "entity.h"
#include "object.h"

typedef struct player_struct {
    struct entity_struct * Pentity;
    struct object_struct * Parmure;
    struct object_struct * Parme;
    struct object_struct * Pbottes;
    int coX_old;
    int coY_old;
    char tile1;
    char tile2;
    int vitesse;
    int crouchCondition;
    int vitesse_max;
} player;

typedef player * radahn; /*Pour faciliter la modification du joueur */

radahn Init_player(void);

void heal(radahn R, Pobject O);
void crouch(radahn R);
void Update_co(radahn R, int x, int y, char tile_); /*Modifie coordonnees joueur*/

void DisplayStatus(radahn R, int ligne);
void DisplayCompass(char **Boussole,int ligne);
void Compass(char *Boussole[]);
void CompassN(char *Boussole[]);
void CompassNE(char *Boussole[]);
void CompassE(char *Boussole[]);
void CompassSE(char *Boussole[]);
void CompassS(char *Boussole[]);
void CompassSW(char *Boussole[]);
void CompassW(char *Boussole[]);
void CompassNW(char *Boussole[]);

void check_Direction(radahn R,char *Boussole[], int X, int Y);

void DelItem(Pobject Item);

void DeleteRadahn(radahn R);

#endif


