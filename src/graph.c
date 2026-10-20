#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/graph.h"

/* =========================================================
 * graph.c
 * Implementarea grafului direcționat ponderat cu liste de
 * adiacență.
 * ========================================================= */

/* ----------------------------------------------------------
 * Funcții ajutătoare pentru relații
 * ---------------------------------------------------------- */

const char *relation_type_to_str(RelationType type)
{

    if (type == WORKS_AT)
        return "works_at";

    if (type == FRIEND_OF)
        return "friend_of";

    if (type == LOCATED_IN)
        return "located_in";

    if (type == PARTICIPATES_IN)
        return "participates_in";

    return "unknown";
}

RelationType str_to_relation_type(const char *str)
{
    /* TODO: parsează șirul relației la valoarea enum */

    if (strcmp(str, "works_at") == 0)
        return WORKS_AT;
    else if (strcmp(str, "located_in") == 0)
        return LOCATED_IN;
    else if (strcmp(str, "friend_of") == 0)
        return FRIEND_OF;
    else if (strcmp(str, "participates_in") == 0)
        return PARTICIPATES_IN;

    return (RelationType)-1;
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

Graph *graph_create(int initial_capacity)
{
    /* TODO: alocă structura Graph și tabloul de noduri */

    if (initial_capacity < 0)
        return NULL;

    Graph *gr;
    gr = (Graph *)malloc(sizeof(Graph));

    if (gr == NULL)
        return NULL;

    gr->nodes = (GraphNode *)malloc(initial_capacity * sizeof(GraphNode));
    if (gr->nodes == NULL)
    {
        free(gr);
        return NULL;
    }
    gr->size = 0;
    gr->capacity = initial_capacity;

    for (int i = 0; i < initial_capacity; i++)
    {
        gr->nodes[i].edges = NULL;
        gr->nodes[i].entity.name = NULL;
        gr->nodes[i].entity.id = -1;
    }
   return gr;
}

void graph_free(Graph *g)
{
    /* TODO: eliberează șirul de nume al fiecărui nod și lista de muchii,
     *       apoi tabloul și structura */

    if (g != NULL)
    {
        for (int i = 0; i < g->size; i++)
        {
            free(g->nodes[i].entity.name);

            EdgeNode *curr = g->nodes[i].edges;

            while (curr != NULL)
            {
                EdgeNode *next_ed;
                next_ed = curr->next;
                free(curr);
                curr = next_ed;
            }
        }

        free(g->nodes);
        free(g);
    }
}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int graph_add_node(Graph *g, const char *name, EntityType type)
{
    /* TODO: extinde tabloul dacă e necesar, inițializează noul GraphNode,
     *       returnează id-ul */
    if(g==NULL)
    return -1;

    if (g->size == g->capacity)
    {
        int new_capacity;

        new_capacity = 2 * g->capacity;

        GraphNode *new_nodes = (GraphNode *)realloc(g->nodes, new_capacity * sizeof(GraphNode));

        if (new_nodes == NULL)
        return -1;

            g->nodes = new_nodes;
            g->capacity = new_capacity;
        
    }

    int x = g->size; // noul id de la finalul listei (=size);

    g->nodes[x].entity.name = (char *)malloc(strlen(name) + 1);

    if (g->nodes[x].entity.name == NULL)
        return -1;

    strcpy(g->nodes[x].entity.name, name);

    g->nodes[x].entity.type = type;
    g->nodes[x].entity.id = x;

    g->size++;
    return x;

    return -1;
}

int graph_add_edge(Graph *g, int src_id, int dest_id,
                   RelationType type, float cost)
{
    /* TODO: alocă EdgeNode, adaugă la finalul listei de muchii a sursei
     *       pentru a păstra ordinea de inserare */

    if (g == NULL || src_id < 0 || src_id >= g->size || dest_id < 0 || dest_id >= g->size)
    return -1;

    EdgeNode *new = (EdgeNode *)malloc(sizeof(EdgeNode));

    if (new == NULL)
        return -1;

    new->dest_id = dest_id;
    new->type = type;
    new->cost = cost;
    new->next = NULL;

    if (g->nodes[src_id].edges == NULL)
        g->nodes[src_id].edges = new;
    else
    {
        EdgeNode *temp = g->nodes[src_id].edges;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = new;
    }

    return 0;
}

/* ----------------------------------------------------------
 * Funcții ajutătoare pentru interogare
 * ---------------------------------------------------------- */

int graph_find_id(const Graph *g, const char *name)
{
    /* TODO: scanare liniară returnând id-ul potrivit sau -1 */

    if (g == NULL || name == NULL)
        return -1;

    for (int i = 0; i < g->size; i++)
        if (g->nodes[i].entity.name != NULL && strcmp(g->nodes[i].entity.name, name) == 0)
            return g->nodes[i].entity.id;

    return -1;
}

GraphNode *graph_get_node(const Graph *g, int id)
{
    /* TODO: verifică limitele și returnează pointerul */

    if (g == NULL || id < 0)
        return NULL;

    return &g->nodes[id]; // se returneaza adresa nodului din tabloul nodes de la indexul id;

    return NULL;
}

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

void graph_print(const Graph *g)
{
    /* TODO: afișează fiecare nod și lista sa de muchii */
    if (g != NULL)
    {

        for (int i = 0; i < g->size; i++)
        {
            Entity *x = &g->nodes[i].entity;

            printf("%d %s:", x->id, x->name);

            EdgeNode *curr = g->nodes[i].edges;
            while (curr != NULL)
            {
                printf(" [%d %s %.2f]", curr->dest_id, relation_type_to_str(curr->type), curr->cost);

                curr = curr->next;
            }

            printf("\n");
        }
    }
}
