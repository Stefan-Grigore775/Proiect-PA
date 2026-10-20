#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/entity.h"

/* =========================================================
 * entity.c
 * Implementarea ciclului de viață al entității și a funcțiilor
 * de conversie.
 * ========================================================= */

/* ----------------------------------------------------------
 * Funcții de conversie
 * ---------------------------------------------------------- */

const char *entity_type_to_str(EntityType type)
{
    /* TODO: returnează șirul corespunzător fiecărei valori enum */

    if(type==PERSON)
    return "PERSON";

    if(type==COMPANY)
    return "COMPANY";

    if(type==LOCATION)
    return "LOCATION";

    if(type==EVENT)
    return "EVENT";
    
    return "UNKNOWN";
}

EntityType str_to_entity_type(const char *str)
{
    /* TODO: compară str cu numele cunoscute și returnează enum-ul */
    
    if(strcmp(str,"PERSON")==0)
    return PERSON;

    if(strcmp(str,"COMPANY")==0)
    return COMPANY;

    if(strcmp(str,"LOCATION")==0)
    return LOCATION;

    if(strcmp(str,"EVENT")==0)
    return EVENT;

    return (EntityType)-1;
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

Entity *entity_create(const char *name, EntityType type, int id)
{
    /* TODO: alocă Entity, duplică name, atribuie câmpurile */
    
    if(name==NULL)
    return NULL;

    Entity *new_en;
    new_en=(Entity *)malloc(sizeof(Entity));

    new_en->name = (char *)malloc(strlen(name)+1);

    if(new_en->name ==NULL)
    {
        free(new_en);
        return NULL;
    }

    strcpy(new_en->name,name);

    new_en->type=type;
    new_en->id=id;
    
    return new_en;

    return NULL;
}

void entity_free(Entity *e)
{
    /* TODO: eliberează name, apoi structura */
    
    if(e != NULL)
    free(e->name),free(e);
    
}

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

void entity_print(const Entity *e)
{
    /* TODO: afișează "<id> <name> <TYPE>" */
    if(e != NULL)
    printf("%d %s %s\n",e->id,e->name,entity_type_to_str(e->type));
}
