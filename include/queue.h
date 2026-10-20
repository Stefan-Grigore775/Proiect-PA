#ifndef QUEUE_H
#define QUEUE_H

/* =========================================================
 * queue.h
 * Coadă FIFO generică susținută de o listă simplu înlănțuită.
 * Stochează copii alocate pe heap ale liniilor de interogare
 * astfel încât interogările pot fi citite o dată, puse în
 * coadă și reluate ulterior.
 * ========================================================= */

/* ----------------------------------------------------------
 * Nodul cozii
 * ---------------------------------------------------------- */

typedef struct QueueNode {
    char             *data; /* șir alocat pe heap (deținut de nod) */
    struct QueueNode *next;
} QueueNode;

/* ----------------------------------------------------------
 * Containerul cozii
 * ---------------------------------------------------------- */

typedef struct {
    QueueNode *front; /* capătul de extragere                  */
    QueueNode *rear;  /* capătul de inserare                   */
    int        size;
} Queue;

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

/* Alocă și returnează o coadă goală. Returnează NULL la eșec. */
Queue *queue_create(void);

/* Golește coada, eliberând toți QueueNode-ii și șirurile lor de date,
 * apoi eliberează structura Queue. Sigur de apelat cu NULL. */
void queue_free(Queue *q);

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

/* Face o copie pe heap a datelor și o adaugă la finalul cozii.
 * Returnează 0 la succes, -1 la eșecul alocării. */
int queue_enqueue(Queue *q, const char *data);

/* Elimină și returnează șirul de date al elementului din față.
 * Apelantul preia proprietatea șirului returnat și trebuie să-l
 * elibereze. Returnează NULL când coada este goală. */
char *queue_dequeue(Queue *q);

/* ----------------------------------------------------------
 * Inspecție
 * ---------------------------------------------------------- */

/* Returnează 1 când coada este goală, 0 altfel. */
int queue_is_empty(const Queue *q);

/* Afișează fiecare șir din coadă la stdout, câte unul per linie,
 * fără a elimina niciun element. */
void queue_print(const Queue *q);

#endif /* QUEUE_H */
