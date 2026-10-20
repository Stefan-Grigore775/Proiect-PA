#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "../include/query.h"
#include "../include/heap.h"

/* =========================================================
 * query.c
 * Parsarea și dispatcharea interogărilor de graf:
 *   EXISTS, EDGE, NEIGHBORS, PATH (BFS), DIJKSTRA
 * ========================================================= */

/* ----------------------------------------------------------
 * Helper de parsare
 * ---------------------------------------------------------- */

QueryType parse_query_type(const char *line)
{
    /* TODO: potrivește cuvântul cheie de la începutul liniei */

    if (!line)
        return Q_UNKNOWN;

    if (strncmp(line, "DIJKSTRA", 8) == 0)
        return Q_DIJKSTRA;

    if (strncmp(line, "EDGE", 4) == 0)
        return Q_EDGE;

    if (strncmp(line, "EXISTS", 6) == 0)
        return Q_EXISTS;

    if (strncmp(line, "NEIGHBORS", 9) == 0)
        return Q_NEIGHBORS;

    if (strncmp(line, "PATH", 4) == 0)
        return Q_PATH;

    return Q_UNKNOWN;
}

/* ----------------------------------------------------------
 * EXISTS
 * ---------------------------------------------------------- */

void process_exists(const BST *tree, const char *name)
{
    /* TODO: caută în BST, afișează DA/NU */

    if (!tree || !tree->root || !name)
    {
        printf("EXISTS %s: NU\n",name);
        return;
    }

    BSTNode *curr = tree->root;

    while (curr)
{
    if (strcmp(name, curr->graph_node->entity.name) == 0)
    {
        printf("EXISTS %s: DA\n",name);
        return;
    }
    else if (strcmp(name, curr->graph_node->entity.name) < 0)
    {
        curr = curr->left;
    }
    else 
    {
        curr = curr->right;
    }
}

    printf("EXISTS %s: NU\n",name); // nu s-a gasit numele respectiv;
}

/* ----------------------------------------------------------
 * EDGE
 * ---------------------------------------------------------- */

void process_edge(const Graph *g, const BST *tree,
                  const char *src_name, const char *dest_name)
{
    /* TODO: găsește ambele noduri via BST, scanează lista de muchii
     *       a sursei pentru destinație */
    if (!g || !tree || !src_name || !dest_name)
        return;

   GraphNode *x1 = bst_search(tree, src_name);
    GraphNode *x2 = bst_search(tree, dest_name);

    if (!x1 || !x2)
    {
        printf("EDGE %s %s: NU\n", src_name, dest_name);
        return;
    }

    int target = x2->entity.id;

    EdgeNode *curr = x1->edges;

    while (curr)
     {
    if (curr->dest_id == target)
    {
        printf("EDGE %s %s: DA\n", src_name, dest_name);
        return; // Trebuie să iasă din funcție DOAR dacă a găsit muchia
    }
    
    curr = curr->next;
   }

    printf("EDGE %s %s: NU\n", src_name, dest_name);
}

/* ----------------------------------------------------------
 * NEIGHBORS
 * ---------------------------------------------------------- */

void process_neighbors(const Graph *g, const BST *tree,
                       const char *name)
{
    /* TODO: găsește nodul, iterează lista de muchii, afișează
     *       numele vecinilor; dacă nu există muchii de ieșire
     *       afișează "NEIGHBORS <name>: NULL" */

    if (!g || !tree || !name)
        return;

    GraphNode *x1 = bst_search(tree, name);
    if (x1 == NULL || x1->edges == NULL)
    {
        printf("NEIGHBORS %s: NULL\n", name);
        return;
    }

    printf("NEIGHBORS %s:", name);

    EdgeNode *curr = x1->edges;

    while (curr)
    {
        GraphNode *y1 = graph_get_node(g, curr->dest_id);

        if (y1)
            printf(" %s", y1->entity.name);

        curr = curr->next;
    }

    printf("\n");
}

/* ----------------------------------------------------------
 * PATH (BFS)
 * ---------------------------------------------------------- */

void process_path_bfs(const Graph *g, const BST *tree,
                      const char *src_name, const char *dest_name)
{
    /* TODO: BFS de la src la dest, reconstruiește și afișează calea;
     *       dacă nu există cale afișează "PATH <src> <dest>: NU" */
    if (!g || !tree || !src_name || !dest_name)
        return;

    GraphNode *x1 = bst_search(tree, src_name);
    GraphNode *x2 = bst_search(tree, dest_name);

    if (!x1 || !x2)
    {
        printf("PATH %s %s: NU\n", src_name, dest_name);
        return;
    }

    int start = x1->entity.id, target = x2->entity.id;

    int *q = (int *)malloc(g->size * sizeof(int));
    int *visited = (int *)calloc(g->size, sizeof(int));
    int *parent = (int *)malloc(g->size * sizeof(int));

    if (!q || !visited|| !parent)
    {
        free(visited);
        free(parent);
        free(q);
        return;
    }

    for (int i = 0; i < g->size; i++)
        parent[i] = -1;

    int head = 0, tail = 0, ok = 0;

    q[tail] = start;
    tail += 1;

    visited[start] = 1;

    while (head < tail)
    {
        int curr1 = q[head++];

        if (curr1 == target)
        {
            ok = 1;
            break;
            ;
        }

        GraphNode *curr2 = graph_get_node(g, curr1);
        EdgeNode *edge = curr2->edges;

        while (edge)
        {
            int id = edge->dest_id;

            if (visited[id] == 0)
            {
                visited[id] = 1;
                parent[id] = curr1;
                q[tail++] = id;
            }

            edge=edge->next;
        }
    }

    if (!ok)
        printf("PATH %s %s: NU\n", src_name, dest_name);
    else
    {
        int *path = (int *)malloc(g->size * sizeof(int));
        int lenght = 0;
        int curr = target;

        while (curr != -1)
        {
            path[lenght++] = curr;
            curr = parent[curr];
        }

        printf("PATH %s %s:", src_name, dest_name);

        for (int i = lenght - 1; i >= 0; i--)
        {
            GraphNode *y = graph_get_node(g, path[i]);

            if (i == lenght - 1)
                printf(" %s", y->entity.name);
            else
                printf(" -> %s", y->entity.name);
        }

        printf("\n");
        free(path);
    }

    free(q);
    free(visited);
    free(parent);
}

/* ----------------------------------------------------------
 * DIJKSTRA
 * ---------------------------------------------------------- */

void process_dijkstra(const Graph *g, const BST *tree,
                      const char *src_name, const char *dest_name)
{
    /* TODO: Dijkstra cu min-heap, afișează costul și calea;
     *       dacă nu există cale afișează "DIJKSTRA <src> <dest>: NU" */

    if (!g || !tree || !src_name || !dest_name)
        return;

    GraphNode *x1 = bst_search(tree, src_name);
    GraphNode *x2 = bst_search(tree, dest_name);

    if (!x1 || !x2)
    {
        printf("DIJKSTRA %s %s: NU\n", src_name, dest_name);
        return;
    }

    int start = x1->entity.id;
    int target = x2->entity.id;

    float *dist = (float *)malloc(g->size * sizeof(float));
    int *parent = (int *)malloc(g->size * sizeof(int));

    if (!dist || !parent)
    {
        free(dist);
        free(parent);
        return;
    }

    for (int i = 0; i < g->size; i++)
    {
        dist[i] = FLT_MAX; // distanta -> infinit
        parent[i] = -1;
    }

    MinHeap *h = heap_create(g->capacity);

    if (!h)
    {
        free(dist);
        free(parent);
        return;
    }

    dist[start] = 0.0f;
    heap_push(h, start, 0.0f);

    while (!heap_is_empty(h))
    {
        HeapNode curr = heap_pop(h);
        int u = curr.node_id;

        if (u == target)
            break;

        if (curr.dist > dist[u])
            continue;

        GraphNode *u_node = graph_get_node(g, u);
        EdgeNode *edge = u_node->edges;

        while (edge)
        {
            int v = edge->dest_id;
            float weight = edge->cost;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;

                int status = heap_decrease_key(h, v, dist[v]);
                if (status == 1)
                    heap_push(h, v, dist[v]);
            }

            edge = edge->next;
        }
    }

    if (dist[target] == FLT_MAX)
        printf("DIJKSTRA %s %s: NU\n", src_name, dest_name);
    else
    {
        int *path = (int *)malloc(g->size * sizeof(int));
        int lenght = 0;
        int curr = target;

        while (curr != -1)
        {
            path[lenght++] = curr;
            curr = parent[curr];
        }

        printf("DIJKSTRA %s %s: COST = %.2f; DRUM =", src_name, dest_name, dist[target]);

        for (int i = lenght - 1; i >= 0; i--)
        {
            GraphNode *y = graph_get_node(g, path[i]);
            if (i == lenght - 1)
                printf(" %s", y->entity.name);
            else
                printf(" -> %s", y->entity.name);
        }

        printf("\n");
        free(path);
    }

    free(dist);
    free(parent);
    heap_free(h);
}

/* ----------------------------------------------------------
 * Dispatcher batch
 * ---------------------------------------------------------- */

void process_all_queries(Queue *q, const Graph *g, const BST *tree)
{
    /* fail safe */
    if (!q || !g || !tree)
        return;

    /* AICI am adaugat ! ca sa mearga */
    while (!queue_is_empty(q))
    {
        char *s = queue_dequeue(q);
        if (s == NULL)
            continue;

        QueryType type = parse_query_type(s);

        char a[256] = {0}, b[256] = {0};

        if (type == Q_EXISTS)
        {
            sscanf(s, "%*s %s", a);
            process_exists(tree, a);
        }

        if (type == Q_EDGE)
        {
            sscanf(s, "%*s %s %s", a, b);
            process_edge(g, tree, a, b);
        }

        if (type == Q_NEIGHBORS)
        {
            sscanf(s, "%*s %s", a);
            process_neighbors(g, tree, a);
        }

        if (type == Q_PATH)
        {
            sscanf(s, "%*s %s %s", a, b);
            process_path_bfs(g, tree, a, b);
        }

        if (type == Q_DIJKSTRA)
        {
            sscanf(s, "%*s %s %s", a, b);
            process_dijkstra(g, tree, a, b);
        }

        /* Curata memoria pentru linia curenta */
        free(s);
    }
}