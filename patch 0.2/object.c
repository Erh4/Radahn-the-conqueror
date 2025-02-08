#include <stdlib.h>
#include "object.h"
#include "stdprof.h"

Pobject Init_Object(void) {
    /*Initialise un objet avec des valeurs par défaut*/
    Pobject Obj = stdprof_malloc(sizeof(Pobject));
    Obj->nom_item = stdprof_malloc(64*sizeof(char));
    Obj->description_item = stdprof_malloc(64*sizeof(char));
    Obj->stat_item = 0;
    Obj->ID = -1;
    Obj->coX = 0;
    Obj->coY = 0;
    return Obj;
}

void DelObjet(Pobject O) {
    stdprof_free(O->nom_item);
    O->nom_item = NULL;
    stdprof_free(O->description_item);
    O->description_item = NULL;
}


