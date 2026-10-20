#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define main student_main
#include "../../../src/main.c"
#undef main

int main(int argc, char **argv)
{
    Graph *g;
    BST *tree;
    Queue *q;

    if (argc != 4) {
        fprintf(stderr, "Utilizare: %s <entitati.csv> <relatii.csv> <interogari.txt>\n",
                argv[0]);
        return 2;
    }

    g = graph_create(16);
    tree = bst_create();
    q = queue_create();
    if (!g || !tree || !q) {
        return 3;
    }

    if (incarca_entitati(argv[1], g, tree) < 0) return 4;
    if (incarca_relatii(argv[2], g, tree) < 0) return 5;
    if (incarca_interogari(argv[3], q) < 0) return 6;

    printf("=== TEST 3.1 ===\n");
    while (!queue_is_empty(q)) {
        char *line = queue_dequeue(q);
        char *copy;
        char *token;
        QueryType type;

        if (!line) continue;

        type = parse_query_type(line);
        copy = strdup(line);
        free(line);
        if (!copy) continue;

        token = strtok(copy, " \t\r\n");
        (void)token;

        if (type == Q_PATH) {
            char *src = strtok(NULL, " \t\r\n");
            char *dest = strtok(NULL, " \t\r\n");
            if (src && dest) process_path_bfs(g, tree, src, dest);
        }

        free(copy);
    }

    if (incarca_interogari(argv[3], q) < 0) return 7;

    printf("=== TEST 3.2 ===\n");
    while (!queue_is_empty(q)) {
        char *line = queue_dequeue(q);
        char *copy;
        char *token;
        QueryType type;

        if (!line) continue;

        type = parse_query_type(line);
        copy = strdup(line);
        free(line);
        if (!copy) continue;

        token = strtok(copy, " \t\r\n");
        (void)token;

        if (type == Q_DIJKSTRA) {
            char *src = strtok(NULL, " \t\r\n");
            char *dest = strtok(NULL, " \t\r\n");
            if (src && dest) process_dijkstra(g, tree, src, dest);
        }

        free(copy);
    }

    graph_free(g);
    bst_free(tree);
    queue_free(q);
    return 0;
}
