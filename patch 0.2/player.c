#include "player.h"
#include "stdprof.h"
#include "entity.h"
#include "object.h"

radahn Init_player(void) { /*initialisation du joueur*/
    radahn Player = stdprof_malloc(sizeof(player));
    Player->Pentity = stdprof_malloc(sizeof(entity));
    Player->Parmure = stdprof_malloc(sizeof(object)); 
    Player->Parme = stdprof_malloc(sizeof(object));
    Player->Pbottes = stdprof_malloc(sizeof(object));
    Player->Pentity->coX = 0;
    Player->Pentity->coY = 0;
    Player->Pentity->strength=10;
    Player->coX_old = 0;
    Player->coY_old = 0;
    Player->tile1 = ' ';
    Player->tile2 = ' ';
    Player->Pentity->hp = 45;
    Player->Pentity->hp_max = 50;
    Player->vitesse = 1;
    Player->vitesse_max = 1;
    Player->crouchCondition = 0;
    return Player;
}

void heal(radahn R, Pobject O){
    /*Soigne le joueur*/
    if (R->Pentity->hp+O->stat_item>=R->Pentity->hp_max){
        R->Pentity->hp = R->Pentity->hp_max;
    }
    else{
        R->Pentity->hp += O->stat_item;}
}

void Update_co(radahn R, int x, int y, char tile_) {
    /*Modifie coordonnees joueur*/
    R->coX_old = R->Pentity->coX;
    R->coY_old = R->Pentity->coY;
    R->Pentity->coX = x;
    R->Pentity->coY = y;
    R->tile2 = R->tile1;
    R->tile1 = tile_;
    
} 

void crouch(radahn R) {
    /*Permet au joueur de réduire sa vitesse ou de la remettre par défaut selon crouch_condition*/
    if (R->crouchCondition == 0) {
        R->crouchCondition = 1;
        R->vitesse = 1;
    }
    else {
        R->vitesse = R->vitesse_max;
        R->crouchCondition = 0;
    }
}


void DisplayStatus(radahn R, int ligne) {
    /*Affiche le menu des infos du joueur*/
    switch (ligne) {
        case 0:
            printf("+---------------------------------------+");
            break;
        case 1:
            printf("|             RADAHN  (%2d;%2d)     \t| ", R->Pentity->coX, R->Pentity->coY);
            break;
        case 2:
            printf("|                                 \t| ");
            break;
        case 3:
            printf("| PV: %3d/%-3d       FORCE: %-4d   \t|   ", R->Pentity->hp, R->Pentity->hp_max, R->Pentity->strength);
            break;
        case 4:
            printf("| VITESSE: %-23d\t|   ", R->vitesse);
            break;
        case 5:
            printf("| ARME: %-26s\t| ", R->Parme->nom_item);

            break;
        case 6:
            printf("| ARMURE: %-24s\t|   ", R->Parmure->nom_item);
            break;
        case 7:
            printf("| BOTTES: %-24s\t|   ", R->Pbottes->nom_item);
            break;
        case 8:
            printf("|                                 \t| ");
            break;
        case 9: 
            printf("|_______________________________________| ");
            break;
    }
}

void DisplayCompass(char *Boussole[], int ligne) {
    /*Affiche la bousssole*/
    if (ligne >= 1 && ligne <= 9) {
        printf("%s", Boussole[ligne-1]);
    }
}

void Compass(char *Boussole[]) {
    Boussole[2] = "  ••       ••";
    Boussole[3] = " •           •";
    Boussole[4] = "O •      •      • E";    
    Boussole[5] = " •           •";
    Boussole[6] = "  ••       ••"; 
}

void CompassN(char *Boussole[]) {
    Boussole[2] = "  ••   |   ••";
    Boussole[3] = " •     |     •";
    Boussole[4] = "O •      •      • E";    
    Boussole[5] = " •           •";
    Boussole[6] = "  ••       ••"; 
}

void CompassNE(char *Boussole[]) {
    Boussole[2] = "  ••      .••";
    Boussole[3] = " •       /   •";
    Boussole[4] = "O •      •'     • E";    
    Boussole[5] = " •           •";
    Boussole[6] = "  ••       ••"; 
}

void CompassE(char *Boussole[]) {
    Boussole[2] = "  ••       ••";
    Boussole[3] = " •           •";
    Boussole[4] = "O •      •------• E";    
    Boussole[5] = " •           •";
    Boussole[6] = "  ••       ••"; 
}

void CompassSE(char *Boussole[]) {
    Boussole[2] = "  ••       ••";
    Boussole[3] = " •           •";
    Boussole[4] = "O •      •.     • E";    
    Boussole[5] = " •       \\   •";
    Boussole[6] = "  ••      '••"; 
}

void CompassS(char *Boussole[]) {
    Boussole[2] = "  ••       ••";
    Boussole[3] = " •           •";
    Boussole[4] = "O •      •      • E";    
    Boussole[5] = " •     |     •";
    Boussole[6] = "  ••   |   ••"; 
}

void CompassSW(char *Boussole[]) {
    Boussole[2] = "  ••       ••";
    Boussole[3] = " •           •";
    Boussole[4] = "O •     .•      • E";    
    Boussole[5] = " •   /       •";
    Boussole[6] = "  ••'      ••"; 
}

void CompassW(char *Boussole[]) {
    Boussole[2] = "  ••       ••";
    Boussole[3] = " •           •";
    Boussole[4] = "O •------•      • E";    
    Boussole[5] = " •           •";
    Boussole[6] = "  ••       ••"; 
}

void CompassNW(char *Boussole[]) {
    Boussole[2] = "  ••.      ••";
    Boussole[3] = " •   \\       •";
    Boussole[4] = "O •     '•      • E";    
    Boussole[5] = " •           •";
    Boussole[6] = "  ••       ••"; 
}

void check_Direction(radahn R, char *Boussole[], int X, int Y) {
    /*Permet à la boussole d'affiche toujours la direction du centre de la carte*/
    int RcoX = R->Pentity->coX; 
    int RcoY = R->Pentity->coY; 
    if (RcoY > Y && RcoX == X) {             /*NORD*/
        CompassN(Boussole);
    }
    else if (RcoY > Y && RcoX < X) {        /*NORD EST*/
        CompassNE(Boussole);
    }
    else if (RcoY == Y && RcoX < X) {        /*EST*/
        CompassE(Boussole);
    }
    else if (RcoY < Y && RcoX < X) {        /*SUD EST*/
        CompassSE(Boussole);
    }
    else if (RcoY < Y && RcoX ==X ) {        /*SUD*/
        CompassS(Boussole);
    }
    else if (RcoY < Y && RcoX >X ) {        /*SUD OUEST*/
        CompassSW(Boussole);
    }
    else if (RcoY == Y && RcoX > X) {        /*OUEST*/
        CompassW(Boussole);
    }
    else if (RcoY > Y && RcoX > X) {        /*NORD OUEST*/
        CompassNW(Boussole);
    }
    else {
        Compass(Boussole);
    }

}

void DelItem(Pobject Item){
    /*Supprime la mémoire allouée à l'armure*/
    DelObjet(Item);
    if (Item !=NULL){
        stdprof_free(Item);
    }
    Item=NULL;
}

void DeleteRadahn(radahn R) {
    /*Supprime le joueur*/
    DelItem(R->Parmure);
    DelItem(R->Parme);
    DelItem(R->Pbottes);
    if (R->Pentity!=NULL){
        DelEntity(R->Pentity);
        stdprof_free(R->Pentity);
    }
    R->Pentity=NULL;
    stdprof_free(R);
    R=NULL;
}

