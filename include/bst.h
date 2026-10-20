#ifndef BST_H
#define BST_H

/* =========================================================
 * bst.h
 * Arbore Binar de Căutare indexat după numele entității
 * (ordine lexicografică). Fiecare nod stochează un pointer
 * în tabloul de noduri al grafului — fără duplicarea datelor.
 * ========================================================= */

#include "graph.h"

/* ----------------------------------------------------------
 * Nodul BST
 * ---------------------------------------------------------- */

typedef struct BSTNode {
    GraphNode       *graph_node; /* pointer în Graph.nodes[] */
    struct BSTNode  *left;
    struct BSTNode  *right;
} BSTNode;

/* ----------------------------------------------------------
 * Containerul BST
 * ---------------------------------------------------------- */

typedef struct {
    BSTNode *root;
} BST;

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

/* Alocă și returnează un BST gol. Returnează NULL la eșec. */
BST *bst_create(void);

/* Eliberează toți nodii BSTNode. Nu eliberează GraphNode-urile spre
 * care pointează — acelea sunt deținute de Graf. Sigur cu NULL. */
void bst_free(BST *tree);

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

/* Inserează graph_node în arbore cu cheia
 * graph_node->entity.name. Numele duplicate sunt ignorate.
 * Returnează 0 la succes, -1 la eșec. */
int bst_insert(BST *tree, GraphNode *graph_node);

/* ----------------------------------------------------------
 * Interogare
 * ---------------------------------------------------------- */

/* Returnează GraphNode* al cărui entity.name este egal cu name,
 * sau NULL dacă nu a fost găsit. */
GraphNode *bst_search(const BST *tree, const char *name);

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

/* Afișează arborele în ordine inordine (alfabetică), un nod per
 * linie, în formatul:
 *   <id> <name> <TYPE> */
void bst_inorder_print(const BST *tree);

#endif /* BST_H */
