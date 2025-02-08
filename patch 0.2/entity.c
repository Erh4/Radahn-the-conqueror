#include "entity.h"
#include "stdprof.h"
#include "player.h"



Pentity Init_monstre(void){
    /*Initalise une entité par défaut*/
    Pentity Monstre = stdprof_malloc(sizeof(entity));
    Monstre->name = stdprof_malloc(64*sizeof(char));
    Monstre->strength = 0;
    Monstre->hp = 0;
    Monstre->hp_max = 0;
    Monstre->coX = 0;
    Monstre->coY = 0;
    return Monstre;
}

/*INUTILE pour l'instant*/
void Update_health(Pentity E, int n_vie) { /* Pour modifier la vie du joueur avec la nouvelle valeur*/
    if (n_vie>=0 && n_vie<=E->hp){
        E->hp = n_vie;
    }
    else {
        fprintf(stderr, "La nouvelle valeur de vie n'est pas inclue entre 0 et %d",E->hp);
        exit(1);
    }
}

void DelEntity(Pentity E){
    stdprof_free(E->name);
    E->name = NULL;
    if (E!=NULL){
        stdprof_free(E);
        E = NULL;
    }

}
