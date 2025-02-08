#ifndef OBJECT_H
#define OBJECT_H
#include <stdlib.h>
#include "object.h"
#include "stdprof.h"

enum id {chaussures, protections, armes};

typedef struct object_struct{
    char * nom_item;
    char * description_item;
    int stat_item;
    int ID;
    int coX;
    int coY;
}object;

typedef object * Pobject;
Pobject Init_Object(void);
void DelObjet(Pobject O);

#endif


