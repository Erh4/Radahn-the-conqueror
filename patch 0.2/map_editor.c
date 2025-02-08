#include <stdio.h>
#include <stdlib.h>
#include "commandes.h"
#include "stdprof.h"
#include "map_editor.h"
#include "entity.h"
#include "object.h"

map_info* Init_map(void) {
    /*Initalise la carte avec les infos par defaut*/
    map_info *Map = stdprof_malloc(sizeof(map_info));
    Map->taille_x = 0;
    Map->taille_y = 0;
    Map->centreX = 0;
    Map->centreY = 0;
    Map->ListeMonstre = stdprof_malloc(100*sizeof(entity));
    Map->ListeNourriture = stdprof_malloc(100*sizeof(object));
    Map->ListeObjet = stdprof_malloc(100*sizeof(object));
    Map->nombreMonstre = 0;
    Map->nombreNourriture = 0;
    Map->nombreObjet = 0;
    return Map;
}

void Ouvrir_map(char** Matrice, char * nom_fichier, map_info * Map) {
    /*Ouvre le fichier contenant la carte et y place les caracteres dans la Matrice
    Ferme le fichier et efface la memoire tampon*/
    
    int x=0, y =0; /*On admet que la taille de la map ne dépasse pas les 4 chiffres*/
    char c;
    char taille_x[4] ,taille_y[4];
    FILE* fichier = fopen(nom_fichier, "r");
    
    if (fichier == NULL) {          /*Verifie que le fichier est bien ouvert*/
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    fgets(taille_x, 4, fichier); 
    Map->taille_x = str_to_int(taille_x, 4);
    fgets(taille_y, 4, fichier);
    Map->taille_y = str_to_int(taille_y, 4);
    Map->centreX = str_to_int(taille_x, 4)/2;
    Map->centreY = str_to_int(taille_y, 4)/2;
    
    for (y = 0; y<str_to_int(taille_y, 4);y++) {
        
        for (x = 0; x <str_to_int(taille_x, 4);x++) {
            c = fgetc(fichier);
            Matrice[y][x] = c;
        }
        
        fgetc(fichier);
        fgetc(fichier);
    }
    Matrice[Map->centreY][Map->centreX] = 'Y';
    fclose(fichier);
}

void Creer_map(char * nom_fichier, int taille_x, int taille_y) {
    /*Ecris la carte dans un fichier avec ses dimension (par défaut map.txt)*/
    int i,j;
    FILE *fichier;
    remove(nom_fichier);
    fichier = fopen(nom_fichier, "w");
    if (taille_x == 0 && taille_y == 0) {
        printf("Longueur carte -> ");
        scanf("%d", &taille_x);
        printf("Hauteur carte -> ");
        scanf("%d", &taille_y);
    }

    
    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier en écriture.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fichier, "%d\n%d\n", taille_x, taille_y);
    for (i = 0; i<taille_y;i++) {
        for (j = 0;j<taille_x;j++) {
            fputc(' ',fichier);
        }
        fputs("|\n", fichier);
    } 
    fclose(fichier);

}

void script_error(void) {
    /*Affiche une erreur si la syntaxe du script n'est pas correcte*/
    printf("\nErreur dans le script\n");
}

int checkY(char *s){  /*Attribution coY pour création*/
    char co_nombre[3];
    char c;
    int p;
    c = s[0];
    if (c == 'Y') {
        c = s[1];
        if (c == '=') {
            p = 0;
            c = s[2];
            while (c != '\n' && c != '\0') {
                co_nombre[p] = c;
                p++;
                c = s[2+p];
            }
        co_nombre[p] = '\0';
        return (str_to_int(co_nombre, p+1));   
        }
    }
    script_error();
    return -1;
    
}

int checkX(char *s){ /*Attribution coX pour création*/
    char co_nombre[3];
    char c;
    int p;
    c = s[0];
    if (c == 'X') {
        c = s[1];
        if (c == '=') {
            p = 0;
            c = s[2];
            while (c != '\n' && c != '\0') {
                co_nombre[p] = c;
                p++;
                c = s[2+p];
            }
        co_nombre[p] = '\0';
        return (str_to_int(co_nombre, p+1));   
        }
    }
    script_error();
    return -1;
}

int checkd(char *s){   /*Attribution co selon demiurge*/
    char co_nombre[3];
    char c;
    int p;
    if (s[2] == '=') {
        if (s[3] == '-' || s[3] == '+') {
            p = 0;
            c = s[4];
            while (c != '\n' && c != '\0') {
                co_nombre[p] = c;
                p++;
                c = s[4+p];
            }
        co_nombre[p] = '\0';
        return (-(s[3]-44)*str_to_int(co_nombre, p+1));
        }
        else {
            script_error();
            return 0;
        } 
    }
    script_error();
    return 0;
}

int checkD(char *s){   /*Attribution co selon demiurge*/
    char co_nombre[3];
    char c;
    int p;
    if (s[2] == '=') {
        if (s[3] == '-' || s[3] == '+') {
            p = 0;
            c = s[4];
            while (c != '\n' && c != '\0') {
                co_nombre[p] = c;
                p++;
                c = s[4+p];
            }
        co_nombre[p] = '\0';
        return (-(s[3]-44)*str_to_int(co_nombre, p+1));
        }
        else {
            script_error();
            return 0;
        } 
    }
    script_error();
    return 0;
    
}

char * clean_com(char *s) { 
    /*Renvoie une chaine de caractères sans commentaires*/
    char *new_s = stdprof_malloc(sizeof(char) * 64);
    int i = 0, j = 0, l = 0;
    while (s[i] != '#' && s[i] != '\n' && s[i] != '\0') {
        if (s[i] == ' ') {
            j++;
        }
        else {
            for (l = 0; l < j;l++) {
                new_s[i-j+l] = ' ';
            }
            j = 0;
            new_s[i] = s[i];
        }
        i++;
    }
    new_s[i-j] = '\0';
    return new_s;
}

void Place_interaction(char ** Matrice, int x, int y, char *s, map_info *Map) {
    /*Enregistre les données de la ligne dans des variables et place l'information sur la carte*/
    char item[64],stat_item[5], type[64];
    char monstre[64], force_monstre[7], vie_monstre[7];
    char nourriture[64], regeneration[5], description_nourriture[64];
    int i = 1, j = 0, l =0 ;
    if ((str_comp(s, "ROCHER")) == 1) {
        Matrice[y][x] = '#';
    }
    else if (s[0] == '{') {
        
        while (s[i] != ',') {
            item[j] = s[i];
            i++;
            j++;
        }
        item[j] = '\0'; 
        i+=4;
        j = 0;
        while (s[i] != ',') {
            stat_item[j] = s[i];
            i++;
            j++;
        }
        stat_item[j] = '\0';
        i+=2;
        j = 0;
        while (s[i] != '}') {
            type[j] = s[i];
            i++;
            j++;
        }
        type[j] = '\0';
    /*printf("Nom: %s\nStat: %s\nType: %s\n", item, stat_item, type);*/
    
    Matrice[y][x] = '!';
    
    l = Map->nombreObjet;
    Map->ListeObjet[l] = Init_Object();
    str_modify(Map->ListeObjet[l]->nom_item, item, 64);
    Map->ListeObjet[l]->stat_item = str_to_int(stat_item, str_len(stat_item));
    
    if (str_comp(type, "chaussures") == 1) {
        Map->ListeObjet[l]->ID = 0;
    }

    else if (str_comp(type, "armes") == 1) 
    {
        Map->ListeObjet[l]->ID = 2;
    }
    else if (str_comp(type, "protections") == 1) {
        Map->ListeObjet[l]->ID = 1;
    }
    else {
        Map->ListeObjet[l]->ID = -1;
    }
    Map->ListeObjet[l]->coX = x;
    Map->ListeObjet[l]->coY = y;
    printf("\n%s (%d;%d)\n", Map->ListeObjet[l]->nom_item, Map->ListeObjet[l]->coX, Map->ListeObjet[l]->coY);
    Map->nombreObjet++;
    }

    else if (s[0] == '<') {
        while (s[i] != ',') {
            monstre[j] = s[i];
            i++;
            j++;
        }
        monstre[j] = '\0';
        i+=2;
        j = 0;
        while (s[i] != ',') {
            force_monstre[j] = s[i];
            i++;
            j++;
        }
        force_monstre[j] = '\0';
        i+=2;
        j = 0;
        while (s[i] != '>') {
            vie_monstre[j] = s[i];
            i++;
            j++;
        }
        vie_monstre[j] = '\0';
        /*printf("Monstre: %s\nForce: %s\nVie: %s\n", monstre, force_monstre, vie_monstre);*/
        Matrice[y][x] = '@';
        l = Map->nombreMonstre;
        Map->ListeMonstre[l] = Init_monstre();
        str_modify(Map->ListeMonstre[l]->name, monstre, 64);
        Map->ListeMonstre[l]->strength = str_to_int(force_monstre, str_len(force_monstre)); 
        Map->ListeMonstre[l]->hp_max = str_to_int(vie_monstre,str_len(vie_monstre));
        Map->ListeMonstre[l]->hp = str_to_int(vie_monstre,str_len(vie_monstre));
        Map->ListeMonstre[l]->coX = x;
        Map->ListeMonstre[l]->coY = y;
        printf("\n%s (%d;%d)\n", Map->ListeMonstre[l]->name, Map->ListeMonstre[l]->coX, Map->ListeMonstre[l]->coY);
        Map->nombreMonstre++;
    }
    
    else if (s[0] == '(') {
        while (s[i] != ',') {
            nourriture[j] = s[i];
            i++;
            j++;
        }
        nourriture[j] = '\0';
        i+=2;
        j = 0;
        while (s[i] != ',') {
            regeneration[j] = s[i];
            i++;
            j++;
        }
        regeneration[j] = '\0';

        i+=3;
        j = 0;
        while (s[i] != '"') {
            description_nourriture[j] = s[i];
            i++;
            j++;
        }
        description_nourriture[j] = '\0';
        /*printf("Plat: %s\nRegen: %s\nDescription: %s", nourriture, regeneration, description_nourriture);*/
        Matrice[y][x] = '*';
        l = Map->nombreNourriture;
        printf("\n%d\n", l);
        Map->ListeNourriture[l] = Init_Object();
        str_modify(Map->ListeNourriture[l]->nom_item, nourriture, 64);
        /*Map->ListeNourriture[l]->nom_item = nourriture;*/
        Map->ListeNourriture[l]->stat_item = str_to_int(regeneration, str_len(regeneration));
        str_modify(Map->ListeNourriture[l]->description_item, description_nourriture, 64);
        Map->ListeNourriture[l]->coX = x;
        Map->ListeNourriture[l]->coY = y;
        printf("\n%s (%d;%d)\n", Map->ListeNourriture[l]->nom_item, Map->ListeNourriture[l]->coX, Map->ListeNourriture[l]->coY);
        Map->nombreNourriture++;
    }

}

void Lecture_script(char ** Matrice, char * nom_fichier_script, map_info * Map) {
    /*Lis le fichier reçu pour placer les interactions sur la carte*/
    char c;
    char s[132];
    int coX = -1,codX = 0, coY = -1, codY = 0;
    FILE *fichier = fopen(nom_fichier_script, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier en lecture.\n");
        exit(EXIT_FAILURE);
    }
    fgets(s,132,fichier);
    if (str_comp(s, "AUBE") == 1) {
        while (fgets(s,132,fichier) != NULL) {
            c = s[0];
            switch (c) 
            {
            case 'C':
                printf("Fin du script\n");
                
                break;
            case 'X': 
                coX = checkX(s);
                fgets(s,132,fichier);
                coY = checkY(s);
                /*printf("(%d,%d)", coX,coY);*/
                if (coY != -1 && coX != -1) {
                    fgets(s, 132, fichier);
                    Place_interaction(Matrice, coX, coY, clean_com(s), Map);
                    coY = -1;
                    coX = -1;
                }
                break;
            case 'Y':
                coY = checkY(s);
                fgets(s,132,fichier);
                coX = checkX(s);
                /*printf("(%d,%d)", coX,coY);*/
                if (coY != -1 && coX != -1) {
                    fgets(s, 132, fichier);
                    /*str_modify(temp, clean_com(s));*/
                    
                    Place_interaction(Matrice, coX, coY, clean_com(s), Map);
                    coY = -1;
                    coX = -1;
                }
                break;
            case 'd':
                if (s[1] == 'X') {
                    codX = checkd(s);
                    fgets(s, 132, fichier);
                    if (s[0] == 'd' && s[1] == 'Y') {
                        codY = checkd(s);
                        if (codX != 0 && codY != 0) {
                            Place_interaction(Matrice, codX, codY, clean_com(s), Map);
                            codX = 0;
                            codY = 0;
                        } 
                        
                    }
                    else {
                        script_error();
                    }
                }
                else if (s[1] == 'Y') {
                    codY = checkd(s);
                    fgets(s, 132, fichier);
                    if (s[0] == 'd' && s[1] == 'X') {
                        codX = checkd(s);
                        if (codX != 0 && codY != 0) {
                            Place_interaction(Matrice, codX, codY, clean_com(s), Map);
                            codX = 0;
                            codY = 0;
                        } 
                    }
                    else {
                        script_error();
                    }
                }
                else {
                    script_error();
                }
                break;
            default:
                printf("\n");
                break;
            }
        }
    }
    else {
        printf("Ce fichier n'est pas compatible");
    }
    fclose(fichier);
}

