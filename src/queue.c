#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/queue.h"

/* =========================================================
 * queue.c
 * Coadă FIFO susținută de o listă simplu înlănțuită.
 * Stochează copii alocate pe heap ale șirurilor.
 * ========================================================= */

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

Queue *queue_create(void)
{
    /* TODO: alocă și inițializează cu zero o structură Queue */

    Queue *q=(Queue *)calloc(1,sizeof(Queue));  //implementare direct cu NULL pt left,right si lenght=0;

    if(q==NULL)
    return NULL;

    return q;

    return NULL;
}

void queue_free(Queue *q)
{
    /* TODO: golește coada eliberând fiecare nod și datele sale */

    if(q==NULL)
    return ;
    
    QueueNode *x=q->front;  //initial era scris rear;

    while(x!=NULL)
    {
        QueueNode *new=x->next;

        free(x);

        x=new;
    }

    free(q);

}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int queue_enqueue(Queue *q, const char *data)
{
    /* TODO: duplică data, alocă QueueNode, adaugă la capătul rear */
    
    if(q==NULL || data==NULL)

    return -1;

    QueueNode *new=(QueueNode *)malloc(sizeof(QueueNode));

    if(new==NULL)
    return -1;

    new->data = (char *)malloc(strlen(data)+1);

    if(!new->data)
    {return -1;
    free(new);
    }
    new->next=NULL;
    strcpy(new->data,data);
    
    if(!q->size)
    {
        q->front=q->rear=new;
    }
    else
    {
        q->rear->next = new;
        q->rear=new;
         // ? q->rear->next=q->rear=new nu a mers;
    }

    q->size+=1;

    return -1;
}

char *queue_dequeue(Queue *q)
{
    /* TODO: elimină nodul din față, returnează datele sale (apelantul
     *       eliberează) */
    if(q==NULL)
    return NULL;

    QueueNode *x=q->front;// x este nodul pe care il eliminam ;

    char *y=x->data;

    q->front=x->next;

    if(q->front==NULL)
    q->rear=NULL;

    q->size-=1;

    free(x);
    return y;

    return NULL;
}

/* ----------------------------------------------------------
 * Inspecție
 * ---------------------------------------------------------- */

int queue_is_empty(const Queue *q)
{
    /* TODO: returnează 1 când size == 0 */
    if(q->size==0)
    return 1;

    if(q==NULL)
    return 1;

    return 0;
}

void queue_print(const Queue *q)
{
    /* TODO: iterează de la front la rear, afișează fiecare șir de date */
    if(q==NULL)
    return ;

    QueueNode *curr=q->front;

    while(curr)
    {
        printf("%s\n",curr->data);
        curr=curr->next;
    }    

}
