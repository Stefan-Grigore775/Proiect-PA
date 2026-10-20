#ifndef GRAPH_H
#define GRAPH_H

/* =========================================================
 * graph.h
 * Graf direcționat ponderat cu liste de adiacență ale cărui
 * noduri conțin payload-uri de tip Entity.
 * ========================================================= */

#include "entity.h"

/* ----------------------------------------------------------
 * Tipul relației
 * ---------------------------------------------------------- */

typedef enum {
    WORKS_AT        = 0,
    FRIEND_OF       = 1,
    LOCATED_IN      = 2,
    PARTICIPATES_IN = 3
} RelationType;

/* Returnează un șir static cu litere mici pentru relație, ex.
 * WORKS_AT -> "works_at". Returnează "unknown" pentru input invalid. */
const char *relation_type_to_str(RelationType type);

/* Parsează "works_at", "friend_of", etc. înapoi la enum.
 * Returnează -1 când șirul nu este recunoscut. */
RelationType str_to_relation_type(const char *str);

/* ----------------------------------------------------------
 * Nodul listei de muchii
 * ---------------------------------------------------------- */

/* O muchie direcționată stocată într-o listă simplu înlănțuită. */
typedef struct EdgeNode {
    int          dest_id; /* index în Graph.nodes[]           */
    RelationType type;
    float        cost;
    struct EdgeNode *next;
} EdgeNode;

/* ----------------------------------------------------------
 * Nodul grafului
 * ---------------------------------------------------------- */

/* Un vârf: deține payload-ul Entity și lista de muchii de ieșire. */
typedef struct GraphNode {
    Entity    entity; /* înglobat, nu pointer                 */
    EdgeNode *edges;  /* capul listei înlănțuite de muchii de ieșire */
} GraphNode;

/* ----------------------------------------------------------
 * Containerul grafului
 * ---------------------------------------------------------- */

typedef struct {
    GraphNode *nodes;    /* tablou dinamic de GraphNode        */
    int        size;     /* numărul curent de noduri           */
    int        capacity; /* sloturi alocate în nodes[]         */
} Graph;

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

/* Alocă un graf gol cu capacitatea inițială dată.
 * Returnează NULL la eșec. */
Graph *graph_create(int initial_capacity);

/* Eliberează toată memoria deținută de graf, apoi eliberează g.
 * Sigur de apelat cu NULL. */
void graph_free(Graph *g);

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

/* Adaugă un nod nou pentru (name, type) și atribuie următorul
 * id disponibil. Returnează id-ul atribuit sau -1 la eșec. */
int graph_add_node(Graph *g, const char *name, EntityType type);

/* Adaugă o muchie direcționată de la src_id la dest_id cu relația
 * și costul dat. Returnează 0 la succes, -1 la eșec. */
int graph_add_edge(Graph *g, int src_id, int dest_id,
                   RelationType type, float cost);

/* ----------------------------------------------------------
 * Funcții ajutătoare pentru interogare
 * ---------------------------------------------------------- */

/* Returnează id-ul nodului pentru entitatea cu numele name sau -1
 * dacă nu a fost găsit (scanare liniară; preferați BST pentru
 * căutări repetate). */
int graph_find_id(const Graph *g, const char *name);

/* Returnează un pointer la GraphNode cu id-ul dat sau NULL
 * când id este în afara intervalului. */
GraphNode *graph_get_node(const Graph *g, int id);

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

/* Afișează lista de adiacență la stdout în formatul:
 *   <id> <name>: [<dest_id> <relatie> <cost>] ...
 * O linie per nod. */
void graph_print(const Graph *g);

#endif /* GRAPH_H */
