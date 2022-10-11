//
// Created by denis on 06/10/2022.
//

#ifndef TP6_MABIBLIO_H
#define TP6_MABIBLIO_H

#include <stdio.h>
#include <stdlib.h>

#define A 0
#define B 1
#define C 2
#define MAX_NODES 10
#define O 1000000000
#define NB_SOM_MAX 10 //nombre de sommets maximum




//liste chainée de couples (sommet, poids)
typedef struct maillon{
    struct maillon *suiv;
    int nom;
    int poids;
} MAILLON, *LISTE;

//graph structure
typedef struct graphe{
    int nbSommets;
    LISTE Adj[NB_SOM_MAX]; //liste d'adjacence
} GRAPHE;


void initAdjGraphe(GRAPHE *G);
void litGraphe(const char *adr, GRAPHE *G, int capacity[MAX_NODES][MAX_NODES]);
void afficheGraphe(GRAPHE G);
int min(int x, int y);
void enqueue(int x);
int dequeue();
int bfs(int start, int target,int capacity[MAX_NODES][MAX_NODES]);
int fordFulkerson(int source, int sink,int capacity[MAX_NODES][MAX_NODES]);

#endif //TP6_MABIBLIO_H
