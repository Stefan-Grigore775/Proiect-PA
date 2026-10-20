#include <stdio.h>
#include <stdlib.h>

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

    printf("=== TEST 1.1 ===\n");
    graph_print(g);
    printf("=== TEST 1.2 ===\n");
    queue_print(q);

    graph_free(g);
    bst_free(tree);
    queue_free(q);
    return 0;
}
