#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 999999999

/* Formato de entrada: 1 linha com o número de vértices N e o número de arestas M seguidos de M linhas com 
 * o vértice de ínicio V1, vértice incidente V2 e o peso W:
 *
 * N M
 * V1 V2 W1
 * v3 V5 W2
 *
 */
void print_graph(int v_number, int graph[v_number][v_number])
{
	int i, j;
	for(i=0; i<v_number; i++){
      for(j=0; j<v_number; j++){
        if(graph[i][j] > INFINITY - 10000){ 
        	printf("+   ");
        }else{
        	printf("%d   ", graph[i][j]);
        }	
      }
      printf("\n");
	}
	printf("\nObs.: + significa que o peso da aresta eh infinito\n");
}

void FloydWarshall(int v_number,int graph[v_number][v_number]){
	int i,j,k;
	for(k=0;k<v_number;k++){
		for(i = 0;i<v_number;i++){
			for(j=0;j<v_number;j++){
				if(graph[i][j]>graph[i][k]+graph[k][j]){
					graph[i][j]=graph[i][k]+graph[k][j];
				}
			}
		}
	}
	printf("Matriz de Distancias\n\n");
	print_graph(v_number,graph);
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

	int graph[v_number][v_number];
	int weight[v_number][v_number];

	//Inicializando com 0
	for(i=0;i<v_number;i++){
		for(j=0;j<v_number;j++){
			if(i != j){
				graph[i][j]=INFINITY;
			}else{
				graph[i][j]=0;
			}
		}
	}

	//Lendo as arestas
	for(i = 0;i<e_number;i++){
		fscanf(file,"%d %d %d", &v1,&v2,&w);
		graph[v1][v2]=w;
	}

	//printf("Matriz de Adjacencias: \n\n");
	//print_graph(v_number,graph);

	//Após o Floyd-Warshall, a matriz de adjacências do grafo será usada como matriz
	// de distâncias entre dois vértices
	FloydWarshall(v_number,graph);
	return 0;
}
