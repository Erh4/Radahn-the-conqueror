#include "player.h"
#include "entity.h"
#include "combat.h"
#include "stdprof.h"
#include "commandes.h"

void display_combat(Pentity E,radahn R) {
    /*Affiche le menu de combat avec les interaction*/
    float i, j, p,l;
    i = ((float)R->Pentity->hp/(float)R->Pentity->hp_max)*50;
    j = ((float)E->hp/(float)E->hp_max) * 50;
    printf("\n\n\n\n");
    printf("\t\t\t\t\t+----------------------------------------------------------------------------+\n");
    printf("\t\t\t\t\t|    #####      #####     ####     ####   #####         ####     ########### |\n");
    printf("\t\t\t\t\t|  ########    ##   ##    #####   #####   ### ##      ###  ###   ########### |\n");
    printf("\t\t\t\t\t| ###         ##     ##   ### ## ## ###   #####      ###    ###      ###     |\n");
    printf("\t\t\t\t\t| ###         ##     ##   ###  ###  ###   ######    ############     ###     |\n");
    printf("\t\t\t\t\t|  ########    ##   ##    ###       ###   ###  ##  ###        ###    ###     |\n");
    printf("\t\t\t\t\t|    #####      #####     ###       ###   ######   ###        ###    ###     |\n");
    printf("\t\t\t\t\t+----------------------------------------------------------------------------+\n");
    printf("\n\n\n\n\n");
    printf("+--------------------------------------------------+\n|");
    for (p=0; p < i; p++) {
        printf("#");
    }
    for (l=p; l < 50; l++) {
        printf(" ");
    }
    printf("| Radahn: %d/%d\n+--------------------------------------------------+\n\n\n\n",R->Pentity->hp,R->Pentity->hp_max);

    printf("+--------------------------------------------------+\n|");
    for (p=0; p < j; p++) {
        printf("#");
    }
    for (l=p; l < 50; l++) {
        printf(" ");
    }
    printf("| %s: %d/%d\n+--------------------------------------------------+\n", E->name, E->hp,E->hp_max);
    
}

void damage(Pentity E, int dmg){
    /*Inflige les dégats à l'entité*/
    E->hp -= dmg;
}

void attack_fjoueur(radahn R, Pentity cible){
    /*Attaque le joueur*/
    damage(cible,R->Pentity->strength);
    printf("Vous avez infligé %d points de dégâts à %s \n",R->Pentity->strength,cible->name);
}

void attack_fentity(Pentity E, radahn R){
    /*Attaque l'entité*/
    damage(R->Pentity,E->strength);
    printf("Vous avez reçu %d points de dégâts de %s. PV : %d/%d \n",E->strength, E->name,R->Pentity->hp,R->Pentity->hp_max);
}

