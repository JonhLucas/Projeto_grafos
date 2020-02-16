#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 999999999
#define MAX_SIZE 10000

/* Formato de entrada: 1 linha com o número de vértices N e o número de arestas M seguidos de M linhas com 
 * o vértice de ínicio V1, vértice incidente V2 e o peso W:
 *
 * N M
 * V1 V2 W1
 * v3 V5 W2
 *
 */

typedef struct edge edge;
typedef struct graph graph;

struct edge{
	int source;
	int destination;
	int weight;
};

struct graph{
	int v_number,e_number;
	edge *edge;
};

graph* create_graph(int v_number,int e_number){

	graph* gr = (graph*)  malloc(sizeof(graph));
	gr->v_number = v_number;
	gr->e_number = e_number;
	gr->edge = (edge*) malloc(gr->e_number*sizeof(edge));
	return gr;
}


void BellmanFord(graph *graph, int start){
	int i,j;
	int u,v,w;
	int dist[graph->v_number];
	int prev[graph->v_number];

	for(i=0;i<graph->v_number;i++){
		dist[i]=INFINITY;
		prev[i]=-1;
	}

	dist[start]=0;
	prev[start]=start;

	for(i=0;i<graph->v_number;i++){
		for(j=0;j<graph->e_number;j++){
			u = graph->edge[j].source;
            v = graph->edge[j].destination;
            w = graph->edge[j].weight;
            if (dist[v] > dist[u] + w){
            	dist[v] = dist[u] + w;
            	prev[v] = u;   
            }
		}
	}

	printf("Array de Distancias em relacao ao Vertice Inicial (0)\n\n");
	for(i=0;i<graph->v_number;i++){
		printf("%d ",dist[i]);
	}
	printf("\n\n\n");
	printf("Array de Predecessores\n\n");
	for(i=0;i<graph->v_number;i++){
		printf("%d ",prev[i]);
	}
	printf("\n");
}

int main(){

	FILE *file;
	file = fopen("entrada","r");

	if(file == NULL){
		printf("Não foi possível abrir o arquivo de entrada \n");
		return 0;
	}

	int v_number;//Número de Vértices
	int e_number;//Número de Arestas
	int i,j;
	int v1,v2,w;//Vertice de início, vertice incidente e peso

	fscanf(file,"%d %d", &v_number, &e_number);

	graph *graph = create_graph(v_number,e_number);

	//Lendo as arestas
	for(i = 0;i<e_number;i++){
		fscanf(file,"%d %d %d", &v1,&v2,&w);
		graph->edge[i].source = v1;
		graph->edge[i].destination = v2;
		graph->edge[i].weight = w;
	}

	BellmanFord(graph,0);
	return 0;
}
