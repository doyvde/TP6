//
// Created by denis on 06/10/2022.
//
#include "mabiblio.h"

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
    int s1,s2,s3,s4,s5,s6,s7,temp;
    int nbArcs=0;


    f=fopen(adr,"r");

    if (f == NULL){
        printf("File is missing!");
        exit(1);
    }

    fscanf(f,"%d",&(G->nbSommets));
    temp=G->nbSommets;
    for (int i = 0; i < temp-1; ++i) {
        for (int j = 0; j < temp-1 ; ++j) {
            capacity[i][j]=0;
        }

    }
    initAdjGraphe(G);
    //fscanf(f,"%c",&ns1);
    fscanf(f," %c %c %c %c %c %c %c",&ns1,&ns2,&ns3,&ns4,&ns5,&ns6,&ns7);
    printf("%c %c %c %c %c %c %c \n",ns1,ns2,ns3,ns4,ns5,ns6,ns7);

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
    printf("\nNb sommets: %d\n", G.nbSommets);

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

int enqueue(int x,int tail,int q[MAX_NODES + 2],int color[MAX_NODES]) {
    q[tail] = x;
    tail++;
    color[x] = B;
    return tail;
}

int dequeue(int q[MAX_NODES + 2],int color[MAX_NODES],int* head) {
    int x = q[*head];
    *head= *head+1;
    color[x] = C;
    return x;
}

// Using BFS as a searching algorithm
int bfs(int start, int target,int capacity[MAX_NODES][MAX_NODES],int tail,int n,int q[MAX_NODES + 2],int flow[MAX_NODES][MAX_NODES],int color[MAX_NODES],int pred[MAX_NODES],int head) {
    int u, v;
    for (u = 0; u < n; u++) {
        color[u] = A;
    }
    head = tail = 0;
    tail=enqueue(start,tail,q,color);
    pred[start] = -1;
    while (head != tail) {
        u = dequeue(q,color,&head);
        for (v = 0; v < n; v++) {
            if (color[v] == A && capacity[u][v] - flow[u][v] > 0) {
                tail=enqueue(v,tail,q,color);
                pred[v] = u;
            }
        }
    }
    return color[target] == C;
}

// Applying fordfulkerson algorithm
int fordFulkerson(int source, int sink,int capacity[MAX_NODES][MAX_NODES],int tail,int n,int q[MAX_NODES + 2],int flow[MAX_NODES][MAX_NODES],int color[MAX_NODES],int pred[MAX_NODES],int head) {
    int i, j, u;
    int max_flow = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            flow[i][j] = 0;
        }
    }

    // Updating the residual values of edges
    while (bfs(source, sink,capacity,tail,n,q,flow,color,pred,head)) {
        int increment = O;
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {

            increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
            //printf("(%d)%d/%d ",u,increment,capacity[pred[u]][u] - flow[pred[u]][u]);
        }
        //printf("\n");
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {
            //printf("%d(%d)+",u,increment);
            flow[pred[u]][u] += increment;
            flow[u][pred[u]] -= increment;
            //printf("(%d)%d/%d ",u,flow[pred[u]][u],capacity[pred[u]][u] - flow[pred[u]][u]);
            //printf("(%d)%d/%d ",u,flow[u][pred[u]],capacity[pred[u]][u] - flow[pred[u]][u]);
        }
        //printf("\n\n");
        // Adding the path flows
        max_flow += increment;
        //printf("%d(%d)+",u,increment);
    }
    return max_flow;
}



