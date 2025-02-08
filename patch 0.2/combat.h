#ifndef COMBAT_H
#define COMBAT_H
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "entity.h"

void display_combat(Pentity E,radahn R);
void attack_fentity(Pentity E,radahn R);
void attack_fjoueur(radahn R, Pentity cible);
void damage(Pentity E, int dmg);

#endif

