#ifndef COMMANDES_H
#define COMMANDES_H
#include <stdio.h>

int str_to_int(char *c, int longueur);
int str_len(char *chaine);
int str_comp(char *chaine1, char *chaine2);
void str_modify(char *chaine1, char * chaine2, int taille);
char *str_add(char *chaine1, char * chaine2);
#endif
