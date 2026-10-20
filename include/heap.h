#ifndef HEAP_H
#define HEAP_H

/* =========================================================
 * heap.h
 * Min-heap de perechi (node_id, distanță) utilizat de
 * algoritmul lui Dijkstra. Heap-ul este ordonat după dist
 * crescător.
 * ========================================================= */

/* ----------------------------------------------------------
 * Tipul elementului
 * ---------------------------------------------------------- */

typedef struct HeapNode {
    int   node_id; /* indexul nodului în graf                  */
    float dist;    /* cea mai bună distanță known de la sursă  */
} HeapNode;

/* ----------------------------------------------------------
 * Containerul heap
 * ---------------------------------------------------------- */

typedef struct {
    HeapNode *data;     /* tablou dinamic, indexat de la 0      */
    int       size;     /* numărul de elemente stocate curent   */
    int       capacity; /* sloturi alocate în data[]            */
} MinHeap;

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

/* Alocă un heap gol cu capacitatea inițială dată.
 * Returnează NULL la eșec. */
MinHeap *heap_create(int initial_capacity);

/* Eliberează toată memoria deținută de heap, apoi eliberează h.
 * Sigur de apelat cu NULL. */
void heap_free(MinHeap *h);

/* ----------------------------------------------------------
 * Operații de bază
 * ---------------------------------------------------------- */

/* Inserează o pereche (node_id, dist) și restabilește proprietatea
 * heap. Returnează 0 la succes, -1 la eșecul alocării. */
int heap_push(MinHeap *h, int node_id, float dist);

/* Elimină și returnează elementul cu cel mai mic dist.
 * Apelantul primește o copie a structurii HeapNode.
 * Comportamentul este nedefinit când heap-ul este gol; verificați
 * cu heap_is_empty() mai întâi. */
HeapNode heap_pop(MinHeap *h);

/* Returnează 1 când heap-ul este gol, 0 altfel. */
int heap_is_empty(const MinHeap *h);

/* Scanează heap-ul pentru o intrare cu node_id dat și
 * actualizează dist la new_dist dacă new_dist este mai mic,
 * apoi restabilește proprietatea heap prin sift up.
 * Returnează 0 dacă o intrare a fost actualizată, 1 dacă nu a fost
 * găsită nicio intrare (apelantul ar trebui să facă push nou),
 * -1 la eroare. */
int heap_decrease_key(MinHeap *h, int node_id, float new_dist);

#endif /* HEAP_H */

