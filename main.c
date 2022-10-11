// Ford - Fulkerson algorith in C

#include <stdio.h>
#include <stdlib.h>
#include "mabiblio.h"


#define A 0
#define B 1
#define C 2
#define MAX_NODES 10
#define O 1000000000
#define NB_SOM_MAX 10 //nombre de sommets maximum
#define INFINITY 9999
#define MAX 10

int n;
int e;
//int capacity[MAX_NODES][MAX_NODES];
int flow[MAX_NODES][MAX_NODES];
int color[MAX_NODES];
int pred[MAX_NODES];
int head, tail;
int q[MAX_NODES + 2];

///source : https://openclassrooms.com/forum/sujet/implementation-algorithme-de-dijkstra
///source : https://www.programiz.com/dsa/ford-fulkerson-algorithm

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

//insere (som_b,poids) en tete dans la liste d’adjacence Adj[som_a]
void insere(int som_a, int som_b, int poids, LISTE Adj[]){
    LISTE prem= malloc(sizeof(LISTE));
    prem->nom = som_b;
    prem->poids = poids;
    prem->suiv = Adj[som_a];
    Adj[som_a] = prem;
}

//initialisation de la table d’adjacence : toutes les listes chainées sont vides
void initAdjGraphe(GRAPHE *G){
    int i;
    for(i = 0; i< G->nbSommets; i++){
        G->Adj[i] = NULL;
    }
}

//pour charger un graphe a partir d’un fichier
void litGraphe(const char *adr, GRAPHE *G, int capacity[MAX_NODES][MAX_NODES]){
    FILE *f;
    char ns1,ns2,ns3,ns4,ns5,ns6,ns7;
    int s1,s2,s3,s4,s5,s6,s7,i,j,temp;
    int nbArcs=0;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            capacity[i][j]=0;
        }
    }

    f=fopen(adr,"r");

    if (f == NULL){
        printf("File is missing!");
        exit(1);
    }

    fscanf(f,"%d",&(G->nbSommets));

    initAdjGraphe(G);
    //fscanf(f,"%c",&ns1);
    fscanf(f," %c %c %c %c %c %c %c",&ns1,&ns2,&ns3,&ns4,&ns5,&ns6,&ns7);
    printf("%c %c %c %c %c %c %c \n",ns1,ns2,ns3,ns4,ns5,ns6,ns7);
    temp=G->nbSommets;
    while(nbArcs!=temp){
        fscanf(f,"%d %d %d %d %d %d %d",&s1,&s2,&s3,&s4,&s5,&s6,&s7);
        printf("%d %d %d %d %d %d %d \n",s1,s2,s3,s4,s5,s6,s7);
        capacity[nbArcs][0]=s1;
        capacity[nbArcs][1]=s2;
        capacity[nbArcs][2]=s3;
        capacity[nbArcs][3]=s4;
        capacity[nbArcs][4]=s5;
        capacity[nbArcs][5]=s6;
        capacity[nbArcs][6]=s7;
        nbArcs++;
    }
    fclose(f);
}

// affichage d’un graphe : le nombre de sommets, puischaque arc pondéré : (sommet_1, sommet_2, poids)
void afficheGraphe(GRAPHE G){
    int j;
    printf("Nb sommets: %d\n", G.nbSommets);

    for(j = 0; j < G.nbSommets; j++){
        MAILLON* tmp = G.Adj[j];
        while(tmp != NULL){
            printf(" (%d, %d, %d)\n",j, tmp->nom, tmp->poids);
            tmp = tmp->suiv;
        }
    }
}

int min(int x, int y) {
    return x < y ? x : y;
}

void enqueue(int x) {
    q[tail] = x;
    tail++;
    color[x] = B;
}

int dequeue() {
    int x = q[head];
    head++;
    color[x] = C;
    return x;
}

// Using BFS as a searching algorithm
int bfs(int start, int target,int capacity[MAX_NODES][MAX_NODES]) {
    int u, v;
    for (u = 0; u < n; u++) {
        color[u] = A;
    }
    head = tail = 0;
    enqueue(start);
    pred[start] = -1;
    while (head != tail) {
        u = dequeue();
        for (v = 0; v < n; v++) {
            if (color[v] == A && capacity[u][v] - flow[u][v] > 0) {
                enqueue(v);
                pred[v] = u;
            }
        }
    }
    return color[target] == C;
}

// Applying fordfulkerson algorithm
int fordFulkerson(int source, int sink,int capacity[MAX_NODES][MAX_NODES]) {
    int i, j, u;
    int max_flow = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            flow[i][j] = 0;
        }
    }

    // Updating the residual values of edges
    while (bfs(source, sink,capacity)) {
        int increment = O;
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {

            increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
            //printf("%d(%d)+",u,increment);
        }
        printf("\n");
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {

            flow[pred[u]][u] += increment;
            flow[u][pred[u]] -= increment;
        }
        // Adding the path flows
        max_flow += increment;

    }
    return max_flow;
}

int main() {

    GRAPHE G;// declaration du graphe
    int capacity[MAX_NODES][MAX_NODES];

    litGraphe("graphe1.txt", &G,capacity);// lecture du fichier et creation du graphe sous morme matricielle et de liste
    afficheGraphe(G);//affichage des donnes du graphe

    n=G.nbSommets;//initialisation du monbre de sommet car necessaire dans le Dijkstra
    int start=0,fin=6;//initialisation des variable pour le somment de depart et d'arriver



    printf("\nFlot Maximal: %d\n", fordFulkerson(start, fin,capacity));
}
