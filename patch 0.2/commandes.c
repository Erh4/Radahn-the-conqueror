#include <stdio.h>
#include "stdprof.h"

int str_to_int(char *c, int longueur) {
    /*Renvoie une chaine de caractère de chiffres en entier*/
    int n = 0,i = 0;
    while (i < longueur) {
        if ('0' <= c[i] && c[i] <= '9') {
            n = n*10 + (c[i]-'0');
        }   
        i++;
    }
    return n;
}

int str_len(char *chaine) {
    /*Renvoie la longueur d'une chaine de caractere*/
    int i= 0;
    while (chaine[i] != '\0' && chaine[i] != '\n') {
        i++;
    }
    return i;
}

int str_comp(char *chaine1, char *chaine2) {
    /*Compare deux chaines de caractères
    Renvoie 1 si les mêmes
    Sinon renvoie 0*/
    int i = 0;

    if (str_len(chaine1) != str_len(chaine2)) {
        /*printf("%s -> %d\n%s -> %d\n", chaine1, str_len(chaine1), chaine2, str_len(chaine2));*/
        return 0;
    }
    while (i < str_len(chaine1)) {
        if (chaine1[i] != chaine2[i]){
            
            return 0;
        }
        i++;
    }
    return 1;
}

void str_modify(char *chaine1, char * chaine2, int taille) {
    /*Remplace la chaine 1 par la chaine 2*/
    int i;
    for (i=0; i<taille-1 && chaine2[i] != '\0' && chaine2[i] != '\n';i++) {
        chaine1[i] = chaine2[i];
    } 

    chaine1[i] = '\0';
}

char *str_add(char *chaine1, char * chaine2 ){
    char *temp = stdprof_malloc(str_len(chaine1) + str_len(chaine2));
    int i;
    for (i = 0;i<str_len(chaine1) ;i++) {
        temp[i] = chaine1[i];
    }
    for (i = 0;i<str_len(chaine2); i++) {
        temp[i+str_len(chaine1)] = chaine2[i];

    }
    return temp;
}

