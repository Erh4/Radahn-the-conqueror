#include <stdio.h>
#include <stdlib.h>
#include "stdprof.h"
#include "map_editor.h"
#include "player.h"
#include "entity.h"
#include "combat.h"
#include "commandes.h"
#define False 0
#define True 1

char *Matrice_Boussole[] =   {"         N",
                              "      •••••••",
                              "    ••       ••",
                              "   •           •",
                              "O •      •      • E",
                              "   •           •",
                              "    ••       ••",
                              "      •••••••",
                              "         S"};
int Arret_joueur = 0;
int mort_joueur = 0;
void PlacePlayer(radahn R, char ** Matrice);
int est_Rocher(char next_tile);
void interaction(radahn R,char current_tile, char ** Matrice, int x, int y,map_info*Map);
Pentity EmplacementMonstre(int X, int Y,map_info *Map);
Pobject EmplacementNourriture(int X, int Y, map_info *Map);
Pobject EmplacementObjet(int X, int Y,map_info *Map);

void save_map(map_info *Map, char **Matrice) {
    /*Enregistre les données de la carte (entités, objets, rochers) dans un fichier 
    qui sera repris pour continuer une partie*/
    int i, j;
    char stat;
    char classe_objet[15];
    Pobject objet;
    Pentity monstre;
    FILE * fichier;
    remove("map_script_save.txt");
    fichier = fopen("map_script_save.txt", "w");
    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier en écriture.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fichier, "AUBE\n");
    for (i = 0;i<Map->taille_y;i++) {
        for (j = 0;j<Map->taille_x;j++)  {
              if (Matrice[i][j] == '!') {
                objet = EmplacementObjet(j,i, Map);
                switch (objet->ID)
                {
                case 0:
                    str_modify(classe_objet, "chaussures",15);
                    stat = 'V';
                    break;
                
                case 1:
                    str_modify(classe_objet, "protections",15);
                    stat = 'P';
                    break;
                case 2:
                    str_modify(classe_objet, "armes",15);
                    stat = 'F';
                    break;
                default:
                    break;
                }
                fprintf(fichier, "X=%d\nY=%d\n", j,i);
                fprintf(fichier,"{%s, %c+%d, %s}\n", objet->nom_item, stat, objet->stat_item, classe_objet);   
              }  
              else if (Matrice[i][j] == '@') {
                monstre = EmplacementMonstre(j,i,Map);
                fprintf(fichier, "X=%d\nY=%d\n", j,i);
                fprintf(fichier, "<%s, %d, %d>\n", monstre->name, monstre->strength, monstre->hp);
              }
              else if (Matrice[i][j] == '*') {
                objet = EmplacementNourriture(j,i,Map);
                fprintf(fichier, "X=%d\nY=%d\n", j,i);
                fprintf(fichier,"(%s, %d, \"%s\")\n", objet->nom_item, objet->stat_item, objet->description_item);
              }

              else if (Matrice[i][j] == '#') {
                fprintf(fichier, "X=%d\nY=%d\n", j,i);
                fprintf(fichier, "ROCHER\n");
              }
        }
    } 
    fprintf(fichier,"CREPUSCULE");
    fclose(fichier);
}

void save_player(radahn R, map_info * Map) {
    /*Enregistre dans le fichier map.txt la taille de la map et les données du joueur
    pour qu'elles soient récupérées pour les prochaines parties*/
    FILE * fichier;
    remove("map.txt");
    printf("%s\n", R->Pbottes->nom_item);
    Creer_map("map.txt", Map->taille_x, Map->taille_y);
    fichier = fopen("map.txt", "a");
    fprintf(fichier,"%s\n",R->Parmure->nom_item);
    fprintf(fichier,"%s\n",R->Parme->nom_item);
    fprintf(fichier,"%s\n",R->Pbottes->nom_item);
    fprintf(fichier,"%d\n",R->Pentity->coX);
    fprintf(fichier,"%d\n",R->Pentity->coY);
    fprintf(fichier,"%d\n",R->Pentity->strength);
    fprintf(fichier,"%d\n",R->coX_old);
    fprintf(fichier,"%d\n",R->coY_old);
    fprintf(fichier,"%c\n",R->tile1);
    fprintf(fichier,"%c\n",R->tile2);
    fprintf(fichier,"%d\n",R->Pentity->hp);
    fprintf(fichier,"%d\n",R->Pentity->hp_max);
    fprintf(fichier,"%d\n",R->vitesse);
    fprintf(fichier,"%d\n",R->vitesse_max);
    fprintf(fichier,"%d\n",R->crouchCondition);
    fclose(fichier);
}

void restore_player(radahn R, map_info * Map) {
    /*Restaure les stats du joueurs, les armes et armures*/
    int i;
    FILE * fichier;
    char s[999], t[64], t1[64];
    R->Parmure = Init_Object();
    R->Parme = Init_Object();
    R->Pbottes = Init_Object();
    fichier = fopen("map.txt", "r");
    for (i = 0; i < Map->taille_y+2; i++) {
        fgets(s, 999, fichier);
    }

    printf("Restauration joueur...\n");

    fgets(t, 64,fichier);
    str_modify(t1, t, 64);
    printf("%s\n", t1);
    str_modify(R->Parmure->nom_item, t1, 64);

    fgets(t, 64,fichier);
    str_modify(t1, t, 64);
    printf("%s\n", t1);
    str_modify(R->Parme->nom_item,t1, 64);

    fgets(t, 64,fichier);
    str_modify(t1, t, 64);
    printf("%s\n", t1);
    str_modify(R->Pbottes->nom_item,t1, 64);

    fgets(t, 64,fichier);
    R->Pentity->coX = str_to_int(t, str_len(t));
    fgets(t, 64,fichier);
    R->Pentity->coY = str_to_int(t, str_len(t));
    fgets(t, 64,fichier);
    R->Pentity->strength = str_to_int(t, str_len(t));
    fgets(t, 64,fichier);
    R->coX_old = str_to_int(t, str_len(t)); 
    fgets(t, 64,fichier);
    R->coY_old = str_to_int(t, str_len(t)); 
    fgets(t, 64,fichier);
    R->tile1 = t[0]; 
    fgets(t, 64,fichier);
    R->tile2 = t[0]; 
    fgets(t, 64,fichier);
    R->Pentity->hp = str_to_int(t, str_len(t)); 
    fgets(t, 64,fichier);
    R->Pentity->hp_max = str_to_int(t, str_len(t)); 
    fgets(t, 64,fichier);
    R->vitesse = str_to_int(t, str_len(t)); 
    fgets(t, 64,fichier);
    R->vitesse_max = str_to_int(t, str_len(t)); 
    fgets(t, 64,fichier);
    R->crouchCondition = str_to_int(t, str_len(t)); 
    printf("Restauration réussie...\n");
    fclose(fichier);
}

void SetCurrentWeapon(radahn R, Pobject PW) { 
    /*Si l'arme découverte est meilleure, Radahn la prend*/
    if ((R->Pentity->strength - 10 ) < PW->stat_item){
        R->Pentity->strength = 10 + PW->stat_item;
        R->Parme->nom_item = PW->nom_item;
        R->Parme = PW;
    }
}


void SetCurrentChaussures(radahn R, Pobject C){
    /*Remplace les bottes si leur vitesse est supérieure à celle du joueur*/
    if (R->vitesse_max <= C->stat_item){
        
        R->vitesse_max = 1+C->stat_item;
        R->vitesse = 1+C->stat_item;
        R->Pbottes = C;
    }

}

void SetCurrentArmor(radahn R, Pobject A) {
    /*Rajoute de l'armure au joueur si celle ci lui rapporte plus de points de vie*/
    if (R->Pentity->hp_max - 50 < A->stat_item){
        R->Parmure = A;
        R->Pentity->hp_max = 50+A->stat_item;
        if (R->Pentity->hp + A->stat_item >= R->Pentity->hp_max){
            R->Pentity->hp = R->Pentity->hp_max; }
        else{ R->Pentity->hp = R->Pentity->hp + A->stat_item; }
    }

}

Pentity EmplacementMonstre(int X, int Y,map_info *Map){ 
    /*cette fonction n'est appelée que dans interaction (donc quand un @ est rencontré)*/
    int i = 0,l = Map->nombreMonstre;
    for (i=0;i<l;i++){
        if (X==Map->ListeMonstre[i]->coX && Y==Map->ListeMonstre[i]->coY){
            return Map->ListeMonstre[i];
        }
    }
    return NULL;

}

Pobject EmplacementNourriture(int X, int Y, map_info *Map){ 
    /*cette fonction n'est appelée que dans interaction (donc quand un @ est rencontré)*/
    int i = 0, l = Map->nombreNourriture;
    for (i=0;i<l;i++){
        if (X==Map->ListeNourriture[i]->coX && Y==Map->ListeNourriture[i]->coY){
            return Map->ListeNourriture[i];
        }
    }
    return NULL;
}

Pobject EmplacementObjet(int X, int Y,map_info *Map){ 
    /*cette fonction n'est appelée que dans interaction (donc quand un @ est rencontré)*/
    int i = 0, l = Map->nombreObjet;
    for (i=0;i<l;i++){
        if (X==Map->ListeObjet[i]->coX && Y==Map->ListeObjet[i]->coY){
            return Map->ListeObjet[i];
        }
    }
    return NULL;
}

int combat(Pentity Mob, radahn R){ 
    /*si return 0, le mob est mort, si return 1 radahn est mort, si return -1, le joueur fuit*/
    char touche;
    int tour = 0;
    
    do{
        display_combat(Mob, R);
        printf("%s vous attaque. 'a' pour attaquer, 'f' pour fuir.\n Que faire> ",Mob->name);
        while (getchar() != '\n') {}
        touche = getchar();
        /*while (getchar() != '\n') {}*/
        switch (touche) {
            case 'a' : 
                {
                    if (tour%2==0){
                        attack_fjoueur(R,Mob);
                    }
                    else{
                        attack_fentity(Mob,R);
                    }
                    tour++;
                    break;
                }
            case 'f' : 
                printf("Vous fuyez, lâchement...\n");
                return -1;
            }
    }   while (Mob->hp > 0 && R->Pentity->hp > 0);
        display_combat(Mob, R);
        if (R->Pentity->hp <= 0){
            printf("Vous êtes mort...\n");
            return 1;
        }
        printf("Vous avez vaincu %s!\n",Mob->name);
        return 0;
}

void Liberer_matrice(char ** Matrice, map_info * Map) {
    /*Libere une Matrice[x][y]*/
    int i;
    for (i=0;i<Map->taille_y;i++) {
        stdprof_free(Matrice[i]);
    }
    stdprof_free(Matrice);
    Matrice = NULL;
}   

void Liberer_OBJECTS(Pobject * L){
    /*Libere une liste d'objets*/
    int i = 0;
    for (i=0;i<100;i++){
        DelItem(L[i]);
        stdprof_free(L[i]);
        L[i] = NULL;
    }
    stdprof_free(L);
    *L = NULL;
}

void Liberer_ENTITY(Pentity * L){
    /*Libère une liste d'entités*/
    int i = 0;
    for (i=0;i<100;i++){
        DelEntity(L[i]);
        stdprof_free(L[i]);
        L[i] = NULL;
    }
    stdprof_free(L);
    *L = NULL;
}


int est_Rocher(char next_tile) {
    /*Verifie si a tuile actuelle est un rocher
    Si oui renvoie True
    Sinon renvoie False*/
    if (next_tile == '#') {
        return True;
    }
    return False;
}



void interaction(radahn R,char current_tile, char ** Matrice, int x, int y, map_info * Map) {
    /*Vérifie quel type d'interaction le joueur va déclencher et appelle les fonctions en conséquences*/
    Pobject objet; 
    int issue_combat;
    switch (current_tile)
    {

    case ' ':
        Arret_joueur = 0;
        break;
    case 'Y':
        printf("Olivier, l'Arbre Démiurge. \n");
        break;
    case '*':
        printf("Vous avez trouvé de la nourriture : ");
        printf("%s",EmplacementNourriture(x,y, Map)->description_item);
        heal(R,EmplacementNourriture(x,y, Map));
        Matrice[y][x] = ' ';
        Arret_joueur = 0;
        break;
    case '@':
        printf("Vous affrontez un %s", EmplacementMonstre(x,y, Map)->name);
        issue_combat = combat(EmplacementMonstre(x,y, Map),R);
        if (issue_combat == 0){
            Matrice[y][x] = ' ';
        }
        else if (issue_combat == 1) {
            mort_joueur = 1;
        }
        Arret_joueur = 1;
        break;
    case '!':
        objet = EmplacementObjet(x,y, Map);
        printf("%d", objet->ID);
        if (objet->ID==0){
            SetCurrentChaussures(R,objet);
        }
        if (objet->ID == 1){
            SetCurrentArmor(R,objet);
        }
        if (objet->ID == 2){
            SetCurrentWeapon(R,objet);
        }
        Matrice[y][x] = ' ';
        /*stdprof_free(objet);
        objet=NULL;*/
        Arret_joueur = 1;
        break;
    default:
        printf("Interaction");
        Arret_joueur = 1;
        break;
        
    }
    
}   


void DisplayGame(radahn R, char ** Matrice, map_info * Map) {
    /*Affiche le jeu dans la console avec la carte et les infos utilisateurs*/
    int x=Map->centreX-10, y=Map->centreY-5;
    PlacePlayer(R,Matrice);
    Matrice[Map->taille_y/2][Map->taille_x/2] = 'Y';
    check_Direction(R, Matrice_Boussole, Map->taille_x/2, Map->taille_y/2);
    printf("\n\n\n\n\n\n\n\n\n");
    printf("  0 1 2 3 4 5 6 7 8 9\n +-+-+-+-+-+-+-+-+-+-+\n");
    for (y=Map->centreY-5;y<Map->centreY+5;y++) {    /*Cette boucle affiche ligne par ligne le jeu dans la console*/
        printf("%d|", y-Map->centreY+5);
        for (x=Map->centreX-10;x<Map->centreX+9;x++) {
            printf("%c", Matrice[y][x]);
        }
        printf("|\t");
        DisplayStatus(R, y-Map->centreY+5);
        DisplayCompass(Matrice_Boussole, y-Map->centreY+5);
        printf("\n");
    } 
    printf(" +-+-+-+-+-+-+-+-+-+-+\n");
}

void PlacePlayer(radahn R, char ** Matrice) {
    /*Déplace le joueur dans la Matrice tout en remplacant la tuile sur laquelle il était par son état initial*/
    Matrice[R->coY_old][R->coX_old] = R->tile2;
    Matrice[R->Pentity->coY][R->Pentity->coX] = 'R';
    
}

void GoUp(radahn Radahn, int v, int x, int y, char ** Matrice, map_info *Map) {
    /*Permet de déplacer le joueur vers le haut*/
    while (v<Radahn->vitesse && y-1 >= 0 &&!(est_Rocher(Matrice[y-1][x])) && !Arret_joueur) {
        interaction(Radahn,Matrice[y-1][x],Matrice, x, y-1, Map);
        if (y-1<=Map->centreY-3 && y-1 > 2) { /*Deplace carte et personage vers le haut*/
            Map->centreY = Map->centreY-1;
            Update_co(Radahn, x, y-1,Matrice[y-1][x]);

        }
        else if (y-1 >= 0) {   /*Deplace seulement personnage vers le haut*/
            Update_co(Radahn, x, y-1, Matrice[y-1][x]);  
        }
        PlacePlayer(Radahn,Matrice);
        x = Radahn->Pentity->coX;
        y = Radahn->Pentity->coY;
        v++;
    }
}

void GoDown(radahn Radahn, int v, int x, int y, char ** Matrice, map_info *Map) {
    /*Permet de déplacer le joueur vers le bas*/
    while (v<Radahn->vitesse && !(est_Rocher(Matrice[y+1][x])) && !Arret_joueur) {
        interaction(Radahn,Matrice[y+1][x],Matrice, x, y+1, Map);
        if (y+1>=Map->centreY+3 && y+1 < Map->taille_y-2) { /*Deplace carte et personage vers le bas*/
            Map->centreY = Map->centreY+1;
            Update_co(Radahn, x, y+1,Matrice[y+1][x]);
        }
        else if (y+1 < Map->taille_y) {  /*Deplace seulement personnage vers le bas*/
            Update_co(Radahn, x, y+1,Matrice[y+1][x]);
        }
        PlacePlayer(Radahn,Matrice);
        x = Radahn->Pentity->coX;
        y = Radahn->Pentity->coY;
        v++;
        
    }
} 

void GoLeft(radahn Radahn, int v, int x, int y, char ** Matrice, map_info *Map) {
    /*Permet de déplacer le joueur vers la gauche*/
    while (v<Radahn->vitesse && x-1 >= 0 && !(est_Rocher(Matrice[y][x-1])) && !Arret_joueur) {
        interaction(Radahn,Matrice[y][x-1],Matrice, x-1, y, Map);
        if (x-1<=Map->centreX-5 && x-1 > 6) { /*Deplace carte et personage vers la gauche*/
            Map->centreX = Map->centreX-2;
            Update_co(Radahn, x-1, y,Matrice[y][x-1]); 
        }
        else if (x-1<=Map->centreX-7 && x-1 > 3) { /*Cas particulier dû à un bug de la carte*/
            Map->centreX = Map->centreX-1;
            Update_co(Radahn, x-1, y,Matrice[y][x-1]);
        }
        else if (x-1 >= 0) {  /*Deplace seulement personnage vers la gauche*/
            Update_co(Radahn, x-1, y,Matrice[y][x-1]);
        }
        PlacePlayer(Radahn,Matrice);
        x = Radahn->Pentity->coX;
        y = Radahn->Pentity->coY;
        v++;
    }
}

void GoRight(radahn Radahn, int v, int x, int y, char ** Matrice, map_info *Map) {
    /*Permet de déplacer le joueur vers la droite*/
    while (v<Radahn->vitesse && x+1 < Map->taille_x && !(est_Rocher(Matrice[y][x+1])) && !Arret_joueur) {
        interaction(Radahn,Matrice[y][x+1],Matrice, x+1, y, Map);
        if (x+1>=Map->centreX+5 && x+1 < Map->taille_x-5) { /*Deplace carte et personage vers la droite*/
            Map->centreX = Map->centreX+2;
            Update_co(Radahn, x+1, y,Matrice[y][x+1]);
        }
        else if (x+1 >= Map->centreX+7 && x+1 < Map->taille_x-2) { /*Cas particulier dû à un bug de la carte*/
            Map->centreX = Map->centreX+1;
            Update_co(Radahn, x+1,y,Matrice[y][x+1]);
        }
        else if (x+1 < Map->taille_x) {  /*Deplace seulement personnage vers la droite*/
            Update_co(Radahn, x+1, y,Matrice[y][x+1]);
        }
        PlacePlayer(Radahn,Matrice);
        x = Radahn->Pentity->coX;
        y = Radahn->Pentity->coY;
        v++; 
    }   
}

int PlayerAction(radahn Radahn, char ** Matrice, map_info * Map) {
    /*Boucle du jeu tant que le joueur n'est pas mort, affiche la carte, demande des entrées utilisateur pour le deplacement etc...*/
    char touche[32];
    int x, y, v;
    Radahn->Pentity->coX = Map->centreX;
    Radahn->Pentity->coY = Map->centreY-1;
    DisplayGame(Radahn,Matrice, Map);
    
    do
        {
            v = 0;
            x = Radahn->Pentity->coX;
            y = Radahn->Pentity->coY;
            printf("\n->");
            scanf("%s", touche);
           /* touche = getchar();
            while (getchar() != '\n') {}*/
            switch (touche[0]) {
                case 'z':
                    GoUp(Radahn, v, x, y, Matrice, Map);
                    break;
                case 's':
                    GoDown(Radahn, v, x, y, Matrice, Map);
                    break;
                case 'q':
                    GoLeft(Radahn, v, x, y, Matrice, Map);
                    break;
                case 'd':
                    GoRight(Radahn, v, x, y,Matrice, Map);
                    break;
                case 'c':
                    crouch(Radahn);
                    break;
                default:
                    printf("\n\nCette commande n'est pas reconnue\n\n");
                    break;
            }

            Arret_joueur = 0;
            DisplayGame(Radahn,Matrice, Map);
        } while (touche[0] != 27 && mort_joueur != 1);  /*Appuyer sur la touche echap pour quitter*/
        if (!mort_joueur) {
            save_map(Map, Matrice);
            save_player(Radahn, Map);
            printf("\n\nPartie sauvegardée\n\n");
        }
        else {
            printf("\n\nRadahn est mort\n\n");
        }
        printf("Fin\n\n");
        return 1;
}

int main(int argc, char *argv[]) {
    /*Initalise la carte et le joueur, affiche le menu et la selection de la carte à lancer*/
    char **Matrice; /*Vraie matrice*/
    int lignes, colonnes, i;
    char new_game = ' ', pre_loaded_map, choix_script;
    char *nom_fichier = stdprof_malloc(sizeof(char) * 64);
    map_info *Map;
    radahn Radahn;
    lignes = 999;
    colonnes = 999;
    Matrice = (char**)stdprof_malloc(lignes * sizeof(char*));
    for (i = 0; i < lignes; i++) {
        Matrice[i] = (char*)stdprof_malloc(colonnes * sizeof(char));
    }

    while (new_game!= 27) {
        Map = Init_map();
        Radahn = Init_player();
        printf("Continuer partie ? [o/n]  ");
        scanf("%s", &new_game);
        if (new_game == 'o') {
            printf("Chargement sauvegarde ...\n\n");
            Ouvrir_map(Matrice, "map.txt", Map);
            restore_player(Radahn, Map);
            Lecture_script(Matrice, "map_script_save.txt", Map);
            PlayerAction(Radahn, Matrice, Map);
        }
        else if (new_game == 'n') {
            mort_joueur = 0;
            printf("Souhaitez-vous lancer une carte pré-chargée ? [o/n]  ");
            scanf("%s", &pre_loaded_map);
            if (pre_loaded_map == 'o') {
                printf("Affichage des cartes :\n\n");
                printf("Carte 1\nCarte 2\nCarte 3\n");
                printf("Choix carte (numéro) : ");
                while (getchar() != '\n') {}
                choix_script = getchar();
                Creer_map("map.txt", 20, 20);

                Ouvrir_map(Matrice, "map.txt", Map);
                if (choix_script == '1') {
                    Lecture_script(Matrice, "tests/map_script1.txt", Map);
                }
                else if (choix_script =='2') {
                    Lecture_script(Matrice, "tests/map_script2.txt", Map);
                }
                else if (choix_script == '3') {
                    Lecture_script(Matrice, "tests/map_script3.txt", Map);
                }
                PlayerAction(Radahn, Matrice, Map);
            }
            else {
                printf("--------Votre carte--------\n\n");
                
                if (argc > 1) {
                    str_modify(nom_fichier, argv[1], 64);
                }
                else {
                    printf("Nom du fichier à charger : ");
                    scanf("%s", &nom_fichier);
                    while (getchar() != '\n') {};
                }

                Creer_map("map.txt", 0, 0);
                Ouvrir_map(Matrice, "map.txt", Map);
                Lecture_script(Matrice, nom_fichier, Map);
                PlayerAction(Radahn, Matrice, Map);
            }
        }

        else if (new_game == 27) {
            return 1; /*Sortie programme par utilisateur*/
        }
    }
    stdprof_free(nom_fichier);
    DeleteRadahn(Radahn);
    Liberer_OBJECTS(Map->ListeNourriture);
    Liberer_OBJECTS(Map->ListeObjet);
    Liberer_ENTITY(Map->ListeMonstre);
    Liberer_matrice(Matrice, Map);
    return 0;

}

