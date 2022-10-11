// Ford - Fulkerson algorith in C

#include "mabiblio.h"

///source : https://openclassrooms.com/forum/sujet/implementation-algorithme-de-dijkstra
///source : https://www.programiz.com/dsa/ford-fulkerson-algorithm

int main() {

    GRAPHE G;// declaration du graphe
    int capacity[MAX_NODES][MAX_NODES];

    litGraphe("graphe1.txt", &G,capacity);// lecture du fichier et creation du graphe sous morme matricielle et de liste
    afficheGraphe(G);//affichage des donnes du graphe

    n=G.nbSommets;//initialisation du monbre de sommet car necessaire dans le Dijkstra
    int start=0,fin=n-1;//initialisation des variable pour le somment de depart et d'arriver



    printf("Flot Maximal: %d\n", fordFulkerson(start, fin,capacity));
}

