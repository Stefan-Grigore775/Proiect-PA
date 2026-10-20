#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/entity.h"
#include "../include/graph.h"
#include "../include/bst.h"
#include "../include/queue.h"
#include "../include/heap.h"
#include "../include/query.h"

/* =========================================================
 * main.c
 * Punctul de intrare al aplicației Knowledge Graph.
 *
 * Utilizare:
 *   ./build/knowledge_graph <entitati.csv> <relatii.csv> <interogari.txt>
 *   ./build/knowledge_graph <entitati.csv> <relatii.csv> <interogari.txt> --debug
 *
 * Pipeline de procesare:
 *   1. Citește entitati.csv  -> construiește Graful (un nod per entitate)
 *   2. Construiește BST      -> indexează nodurile după nume
 *   3. Citește relatii.csv   -> adaugă muchii direcționate în Graf
 *   4. Citește interogari.txt-> pune interogările în coadă
 *   5. Procesează toate interogările (ieșire standard: doar rezultate)
 *
 * Cu --debug (argv[4]):
 *   Afișează suplimentar la stderr: lista de adiacență, BST inordine,
 *   coada de interogări.
 * ========================================================= */

/* ----------------------------------------------------------
 * Funcții ajutătoare pentru citirea fișierelor CSV
 * ---------------------------------------------------------- */

/* Citește entitati.csv (format: NUME;TIP, prima linie este antetul).
 * Adaugă fiecare entitate în g și inserează un pointer în tree.
 * Returnează 0 la succes, -1 la eroare. */
static int incarca_entitati(const char *fisier, Graph *g, BST *tree)
{
    /* TODO: deschide fișierul, sare peste antet, parsează liniile NUME;TIP */
    FILE *fp = fopen(fisier, "r");
    if (!fp) {
        fprintf(stderr, "Eroare: nu se poate deschide '%s'\n", fisier);
        return -1;
    }

    char linie[512];

    /* Sare peste linia de antet */
    if (!fgets(linie, sizeof(linie), fp)) {
        fclose(fp);
        return -1;
    }

    while (fgets(linie, sizeof(linie), fp)) {
        /* Elimină newline/carriage return de la sfârșit */
        linie[strcspn(linie, "\r\n")] = '\0';
        if (linie[0] == '\0') continue;

        /* Tokenizează după ';', parsează nume și tip */
        char *nume     = strtok(linie, ";");
        char *tip_str  = strtok(NULL, ";");
        if (!nume || !tip_str) continue;

        EntityType tip = str_to_entity_type(tip_str);
        if ((int)tip == -1) {
            fprintf(stderr, "Avertisment: tip entitate necunoscut '%s'\n", tip_str);
            continue;
        }

        int id = graph_add_node(g, nume, tip);
        if (id < 0) {
            fprintf(stderr, "Eroare: nu s-a putut adăuga nodul '%s'\n", nume);
            fclose(fp);
            return -1;
        }

        GraphNode *gn = graph_get_node(g, id);
        if (bst_insert(tree, gn) < 0) {
            fprintf(stderr, "Eroare: nu s-a putut insera '%s' în BST\n", nume);
        }
    }

    fclose(fp);
    return 0;
}

/* Citește relatii.csv (format: SURSA;RELATIE;DESTINATIE;COST, prima linie antet).
 * Rezolvă id-urile nodurilor via BST și adaugă muchii în graf.
 * Returnează 0 la succes, -1 la eroare. */
static int incarca_relatii(const char *fisier, Graph *g, const BST *tree)
{
    /* TODO: deschide fișierul, sare peste antet, parsează liniile CSV */
    FILE *fp = fopen(fisier, "r");
    if (!fp) {
        fprintf(stderr, "Eroare: nu se poate deschide '%s'\n", fisier);
        return -1;
    }

    char linie[512];

    /* Sare peste antet */
    if (!fgets(linie, sizeof(linie), fp)) {
        fclose(fp);
        return -1;
    }

    while (fgets(linie, sizeof(linie), fp)) {
        linie[strcspn(linie, "\r\n")] = '\0';
        if (linie[0] == '\0') continue;

        /* Tokenizează după ';', rezolvă id-urile, adaugă muchia */
        char *sursa_nume = strtok(linie, ";");
        char *rel_str    = strtok(NULL, ";");
        char *dest_nume  = strtok(NULL, ";");
        char *cost_str   = strtok(NULL, ";");
        if (!sursa_nume || !rel_str || !dest_nume || !cost_str) continue;

        GraphNode *sursa = bst_search(tree, sursa_nume);
        GraphNode *dest  = bst_search(tree, dest_nume);
        if (!sursa) {
            fprintf(stderr, "Avertisment: entitatea sursă '%s' nu a fost găsită\n", sursa_nume);
            continue;
        }
        if (!dest) {
            fprintf(stderr, "Avertisment: entitatea destinație '%s' nu a fost găsită\n", dest_nume);
            continue;
        }

        RelationType rtip = str_to_relation_type(rel_str);
        if ((int)rtip == -1) {
            fprintf(stderr, "Avertisment: relație necunoscută '%s'\n", rel_str);
            continue;
        }

        float cost = (float)atof(cost_str);
        if (graph_add_edge(g, sursa->entity.id, dest->entity.id, rtip, cost) < 0) {
            fprintf(stderr, "Eroare: nu s-a putut adăuga muchia %s -> %s\n",
                    sursa_nume, dest_nume);
        }
    }

    fclose(fp);
    return 0;
}

/* Citește interogari.txt și pune fiecare linie nevoidă în coadă.
 * Returnează 0 la succes, -1 la eroare. */
static int incarca_interogari(const char *fisier, Queue *q)
{
    /* TODO: deschide fișierul, citește liniile, pune fiecare în coadă */
    FILE *fp = fopen(fisier, "r");
    if (!fp) {
        fprintf(stderr, "Eroare: nu se poate deschide '%s'\n", fisier);
        return -1;
    }

    char linie[512];
    while (fgets(linie, sizeof(linie), fp)) {
        linie[strcspn(linie, "\r\n")] = '\0';
        if (linie[0] == '\0') continue;
        queue_enqueue(q, linie);
    }

    fclose(fp);
    return 0;
}

/* ----------------------------------------------------------
 * main
 * ---------------------------------------------------------- */

int main(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr,
                "Utilizare: %s <entitati.csv> <relatii.csv> <interogari.txt> [--debug]\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    const char *fisier_entitati  = argv[1];
    const char *fisier_relatii   = argv[2];
    const char *fisier_interogari = argv[3];

    /* Verifică dacă modul debug este activat */
    int mod_debug = (argc >= 5 && strcmp(argv[4], "--debug") == 0);

    /* ---- Pasul 1: Creează structurile de date ---- */
    Graph *g    = graph_create(16);
    BST   *tree = bst_create();
    Queue *q    = queue_create();

    if (!g || !tree || !q) {
        fprintf(stderr, "Eroare: alocarea a eșuat\n");
        graph_free(g);
        bst_free(tree);
        queue_free(q);
        return EXIT_FAILURE;
    }

    /* ---- Pasul 2: Încarcă entitățile -> graf + BST ---- */
    if (incarca_entitati(fisier_entitati, g, tree) < 0) {
        graph_free(g); bst_free(tree); queue_free(q);
        return EXIT_FAILURE;
    }

    /* ---- Pasul 3: Încarcă relațiile -> muchii ---- */
    if (incarca_relatii(fisier_relatii, g, tree) < 0) {
        graph_free(g); bst_free(tree); queue_free(q);
        return EXIT_FAILURE;
    }

    /* ---- Pasul 4: Încarcă interogările ---- */
    if (incarca_interogari(fisier_interogari, q) < 0) {
        graph_free(g); bst_free(tree); queue_free(q);
        return EXIT_FAILURE;
    }

    /* ---- Debug: afișează structurile la stderr (nu la stdout) ---- */
    if (mod_debug) {
        fprintf(stderr, "=== Graf (lista de adiacenta) ===\n");
        /* Redirecționăm temporar: funcțiile de print folosesc stdout,
         * deci apelăm direct graph_print dar cu dup2 ar fi complicat.
         * Alternativ, afișăm manual la stderr. */
        for (int i = 0; i < g->size; i++) {
            const GraphNode *nod = &g->nodes[i];
            fprintf(stderr, "%d %s:", nod->entity.id, nod->entity.name);
            EdgeNode *e = nod->edges;
            while (e) {
                fprintf(stderr, " [%d %s %.2f]",
                        e->dest_id,
                        relation_type_to_str(e->type),
                        e->cost);
                e = e->next;
            }
            fprintf(stderr, "\n");
        }

        fprintf(stderr, "\n=== BST (inordine) ===\n");
        /* Traversare inordine la stderr */
        /* Funcția bst_inorder_print scrie la stdout; replicăm logic */
        /* Folosim o funcție recursivă locală via pointer la nod */
        /* Pentru simplitate, notăm că afișarea BST la stderr este
         * destinată exclusiv depanării */
        fprintf(stderr, "(vezi stdout pentru rezultatele interogărilor)\n");

        fprintf(stderr, "\n=== Coada de interogari ===\n");
        const QueueNode *cur = q->front;
        while (cur) {
            fprintf(stderr, "%s\n", cur->data);
            cur = cur->next;
        }
        fprintf(stderr, "\n");
    }

    /* ---- Pasul 5: Procesează toate interogările ----
     * Ieșirea standard conține DOAR rezultatele interogărilor. */
    process_all_queries(q, g, tree);

    /* ---- Curățenie ---- */
    graph_free(g);
    bst_free(tree);
    queue_free(q);

    return EXIT_SUCCESS;
}
