#ifndef QUERY_H
#define QUERY_H

/* =========================================================
 * query.h
 * Stratul de parsare și dispatchare a interogărilor.
 * Suportă: EXISTS, EDGE, NEIGHBORS, PATH, DIJKSTRA
 * ========================================================= */

#include "graph.h"
#include "bst.h"
#include "queue.h"

/* ----------------------------------------------------------
 * Eticheta tipului de interogare
 * ---------------------------------------------------------- */

typedef enum {
    Q_EXISTS    = 0,
    Q_EDGE      = 1,
    Q_NEIGHBORS = 2,
    Q_PATH      = 3,
    Q_DIJKSTRA  = 4,
    Q_UNKNOWN   = -1
} QueryType;

/* ----------------------------------------------------------
 * Handlere individuale de interogare
 * Toate funcțiile afișează rezultatul la stdout.
 * ---------------------------------------------------------- */

/* EXISTS <name>
 * Afișează "EXISTS <name>: DA" sau "EXISTS <name>: NU". */
void process_exists(const BST *tree, const char *name);

/* EDGE <src> <dest>
 * Afișează "EDGE <src> <dest>: DA" sau "EDGE <src> <dest>: NU". */
void process_edge(const Graph *g, const BST *tree,
                  const char *src_name, const char *dest_name);

/* NEIGHBORS <name>
 * Afișează "NEIGHBORS <name>: <n1> <n2> ..." (nume vecini
 * separate prin spații, în ordinea listei de muchii) sau
 * "NEIGHBORS <name>: NULL" dacă nu există muchii de ieșire. */
void process_neighbors(const Graph *g, const BST *tree,
                       const char *name);

/* PATH <src> <dest>
 * Calea cu cel mai scurt număr de salturi BFS.
 * Afișează "PATH <src> <dest>: <n1> -> <n2> -> ..." sau
 * "PATH <src> <dest>: NU" când nu este accesibil. */
void process_path_bfs(const Graph *g, const BST *tree,
                      const char *src_name, const char *dest_name);

/* DIJKSTRA <src> <dest>
 * Calea cu cel mai mic cost Dijkstra folosind min-heap.
 * Afișează "DIJKSTRA <src> <dest>: COST = <c>; DRUM = <n1> -> ..."
 * sau "DIJKSTRA <src> <dest>: NU" când nu este accesibil. */
void process_dijkstra(const Graph *g, const BST *tree,
                      const char *src_name, const char *dest_name);

/* ----------------------------------------------------------
 * Dispatcher batch
 * ---------------------------------------------------------- */

/* Extrage fiecare interogare din q, o parsează și apelează
 * handlerul corespunzător. q este goală după ce această funcție
 * returnează. */
void process_all_queries(Queue *q, const Graph *g, const BST *tree);

/* ----------------------------------------------------------
 * Helper de parsare (expus pentru testare)
 * ---------------------------------------------------------- */

/* Returnează QueryType pentru cuvântul cheie de la începutul liniei.
 * Returnează Q_UNKNOWN când cuvântul cheie nu este recunoscut. */
QueryType parse_query_type(const char *line);

#endif /* QUERY_H */
