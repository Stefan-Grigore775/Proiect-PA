#ifndef ENTITY_H
#define ENTITY_H

/* =========================================================
 * entity.h
 * Definește modelul de date Entity: nume, tip și id întreg.
 * ========================================================= */

/* Categoriile de entități suportate în graful de cunoștințe. */
typedef enum {
    PERSON       = 0,
    COMPANY      = 1,
    LOCATION     = 2,
    EVENT        = 3
} EntityType;

/* Un nod payload stocat într-un nod al grafului. */
typedef struct Entity {
    char       *name; /* alocat pe heap, deținut de acest struct */
    EntityType  type;
    int         id;   /* index bazat pe 0, atribuit la inserare  */
} Entity;

/* ----------------------------------------------------------
 * Funcții de conversie
 * ---------------------------------------------------------- */

/* Returnează reprezentarea șir a tipului dat,
 * ex. PERSON -> "PERSON". Returnează "UNKNOWN" pentru input invalid. */
const char *entity_type_to_str(EntityType type);

/* Parsează un șir produs de entity_type_to_str() înapoi la valoarea
 * enum. Returnează -1 când șirul nu este recunoscut. */
EntityType str_to_entity_type(const char *str);

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

/* Alocă și inițializează o nouă entitate. name este duplicat
 * intern; apelantul păstrează proprietatea originalului.
 * Returnează NULL la eșecul alocării. */
Entity *entity_create(const char *name, EntityType type, int id);

/* Eliberează toată memoria deținută de *e, apoi structura.
 * Sigur de apelat cu NULL. */
void entity_free(Entity *e);

/* Afișează entitatea la stdout în formatul:
 *   <id> <name> <TYPE> */
void entity_print(const Entity *e);

#endif /* ENTITY_H */
