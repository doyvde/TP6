// Ford - Fulkerson algorith in C

#include "mabiblio.h"

///source : https://openclassrooms.com/forum/sujet/implementation-algorithme-de-dijkstra
///source : https://www.programiz.com/dsa/ford-fulkerson-algorithm
///source : https://www.programiz.com/c-programming/c-pointer-functions
///source : https://iq.opengenus.org/ford-fulkerson-algorithm/#:~:text=Ford%E2%80%93Fulkerson%20algorithm%20is%20a,Search%20as%20a%20sub%2Droutine.
///Mon git: https://github.com/doyvde/TP6.git

int main() {

    GRAPHE G;// declaration du graphe
    int capacity[MAX_NODES][MAX_NODES];
    int tail=0;
    int n;
    int q[MAX_NODES + 2];
    int flow[MAX_NODES][MAX_NODES];
    int color[MAX_NODES];
    int pred[MAX_NODES];
    int head=0;
    bool visited[MAX_NODES];
    int Flow[MAX_NODES][MAX_NODES];
    litGraphe("graphe1.txt", &G,capacity);// lecture du fichier et creation du graphe sous morme matricielle et de liste
    afficheGraphe(G);//affichage des donnes du graphe

    n=G.nbSommets;//initialisation du monbre de sommet car necessaire dans le Dijkstra
    int start=0,fin=n-1;//initialisation des variable pour le somment de depart et d'arriver
    int option;
    printf("\n");//
    printf("Que voulez vous faire ? \n");//
    printf("1- Ford-Fulkerson avec DFS\n");//
    printf("2- Ford-Fulkerson avec BFS\n");//
    scanf("%d", &option);//
    printf("\n");//

    //while (1){
    menuInitial://
    switch (option)//
    {
        //1 - État du jeu
        case 1:
            printf("Avec DFS Flot Maximal: %d\n", fordFulkersonDFS(start, fin, visited, Flow, capacity));
            break;//

            //2 - Acheter une propriété
        case 2:
            printf("Avec BFS Flot Maximal: %d\n",
                   fordFulkersonBFS(start, fin, capacity, tail, n, q, flow, color, pred, head));
            break;//



            //option Invalide
        default://
            printf("Erreur! Veuillez saisir une option valide : \n");//
            fflush(stdin);//
            scanf("%d", &option);//
            goto menuInitial;

    //}
    }

    //

}

