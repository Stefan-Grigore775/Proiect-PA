#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../include/heap.h"

/* =========================================================
 * heap.c
 * Min-heap de perechi (node_id, dist) pentru Dijkstra.
 * Folosește un tablou dinamic cu indexarea standard
 * părinte/copil:
 *   parinte(i)       = (i - 1) / 2
 *   copil_stang(i)   = 2 * i + 1
 *   copil_drept(i)   = 2 * i + 2
 * ========================================================= */

/* ----------------------------------------------------------
 * Helper intern de swap
 * ---------------------------------------------------------- */

static void swap(HeapNode *a, HeapNode *b) __attribute__((unused));
static void swap(HeapNode *a, HeapNode *b)
{
    /* TODO: interschimbă cele două elemente HeapNode */
    int temp1;
    float temp2;

    temp1=a->node_id;
    temp2=a->dist;

    a->node_id=b->node_id;
    a->dist=b->dist;

    b->node_id=temp1;
    b->dist=temp2;


}

/* ----------------------------------------------------------
 * Funcții de sift
 * ---------------------------------------------------------- */

static void sift_up(MinHeap *h, int i) __attribute__((unused));
static void sift_up(MinHeap *h, int i)
{
    /* TODO: mută elementul de la indexul i în sus până când
     *       proprietatea heap este respectată */
    

    int parinte = (i-1)/2; // mereu indexul parintelui nodului cu indexul i etse (i-1)/2;

    while(i>0 && h->data[i].dist < h->data[parinte].dist)
    {
        HeapNode temp=h->data[i];
        h->data[i]=h->data[parinte];
        h->data[parinte]=temp;

        i=parinte;

        parinte=(i-1)/2;
    }
    


}

static void sift_down(MinHeap *h, int i) __attribute__((unused));
static void sift_down(MinHeap *h, int i)
{
    /* TODO: mută elementul de la indexul i în jos până când
     *       proprietatea heap este respectată */
    int ok=0; 

    while(!ok)
    {
        int left=2*i+1;
        int right=2*i+2;
        int min=i;

        if(left < h->size && h->data[left].dist < h->data[min].dist)
        min=left;

         if(right < h->size && h->data[right].dist < h->data[min].dist)
        min=right;

        if(min!=i)
        {
            HeapNode temp=h->data[i];
            h->data[i]=h->data[min];
            h->data[min]=temp;

            i=min;
        }
        else
        ok=1;

    }
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

MinHeap *heap_create(int initial_capacity)
{
    /* TODO: alocă MinHeap și tabloul său de date */
    
    MinHeap *min = (MinHeap *)malloc(sizeof(MinHeap));

    if(!min)
    return NULL;

    min->data=(HeapNode *)malloc(initial_capacity*sizeof(HeapNode)); //alocam tabloul de date de marime initial_capacity;

    if(min->data==NULL)
    {
        free(min);
        return NULL;
    }

    min->capacity=initial_capacity;
    min->size=0;

    return min;

    return NULL;
}

void heap_free(MinHeap *h)
{
    /* TODO: eliberează tabloul de date, apoi structura */
    if(h==NULL)
    return ;


    if(h->data!=NULL)
    free(h->data);

    free(h);
    

}

/* ----------------------------------------------------------
 * Operații de bază
 * ---------------------------------------------------------- */

int heap_push(MinHeap *h, int node_id, float dist)
{
    /* TODO: adaugă elementul, extinde dacă e necesar, execută sift up */
    
    if(!h)
    return -1;

    if(h->size==h->capacity)
    {
        int new_capacity;

        if(h->capacity==0)
        new_capacity=16;
        else
        new_capacity=h->capacity*2;

        HeapNode *new=(HeapNode *)realloc(h->data,new_capacity*sizeof(HeapNode));

        if(!new)
        return -1;

        h->data=new;
        h->capacity=new_capacity;
    }

    h->data[h->size].dist=dist;
    h->data[h->size].node_id=node_id;
    h->size+=1;
    sift_up(h,h->size-1);

    return 0;
}

HeapNode heap_pop(MinHeap *h)
{
    /* TODO: interschimbă rădăcina cu ultimul element, micșorează,
     *       execută sift down, returnează vechea rădăcină */
    HeapNode rezultat = {-1, FLT_MAX};
    
    if(!h || !h->size)
    return rezultat;

    rezultat = h->data[0]; // minimul absolut ;

    h->data[0]=h->data[h->size-1]; // utimul element din array este pus primuk;

    h->size-=1;

    if(h->size)
    sift_down(h,0);

    return rezultat;
}

int heap_is_empty(const MinHeap *h)
{
    /* TODO: returnează 1 când size == 0 */
    if(h->size!=0 || !h)
    return 0; 

    return 1;
}

int heap_decrease_key(MinHeap *h, int node_id, float new_dist)
{
    /* TODO: găsește node_id, actualizează dist dacă e mai mic,
     *       execută sift up */
    
    if(!h)
    return -1;

    for(int i=0;i<h->size;i++)
    {
        if(h->data[i].node_id==node_id)
        {
         if(new_dist<h->data[i].dist)
         {
            h->data[i].dist=new_dist;
            sift_up(h,i);
         }
        return 0;
        }
    }
    
    return 1; // rezultat pt care nodul nu este in heap;
    
    return -1;
}
