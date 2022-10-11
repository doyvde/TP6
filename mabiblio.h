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

//int capacity[MAX_NODES][MAX_NODES];

void initAdjGraphe(GRAPHE *G);
void litGraphe(const char *adr, GRAPHE *G, int capacity[MAX_NODES][MAX_NODES]);
void afficheGraphe(GRAPHE G);
int min(int x, int y);
int enqueue(int x,int tail,int q[MAX_NODES + 2],int color[MAX_NODES]);
int dequeue(int q[MAX_NODES + 2],int color[MAX_NODES],int* head);
int bfs(int start, int target,int capacity[MAX_NODES][MAX_NODES],int tail,int n,int q[MAX_NODES + 2],int flow[MAX_NODES][MAX_NODES],int color[MAX_NODES],int pred[MAX_NODES],int head);
int fordFulkerson(int source, int sink,int capacity[MAX_NODES][MAX_NODES],int tail,int n,int q[MAX_NODES + 2],int flow[MAX_NODES][MAX_NODES],int color[MAX_NODES],int pred[MAX_NODES],int head);

#endif //TP6_MABIBLIO_H
