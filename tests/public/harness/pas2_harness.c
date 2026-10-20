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

    printf("=== TEST 2.1 ===\n");
    bst_inorder_print(tree);
    printf("=== TEST 2.2 ===\n");

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

        if (type == Q_EXISTS) {
            char *name = strtok(NULL, " \t\r\n");
            if (name) process_exists(tree, name);
        } else if (type == Q_EDGE) {
            char *src = strtok(NULL, " \t\r\n");
            char *dest = strtok(NULL, " \t\r\n");
            if (src && dest) process_edge(g, tree, src, dest);
        } else if (type == Q_NEIGHBORS) {
            char *name = strtok(NULL, " \t\r\n");
            if (name) process_neighbors(g, tree, name);
        }

        free(copy);
    }

    graph_free(g);
    bst_free(tree);
    queue_free(q);
    return 0;
}
