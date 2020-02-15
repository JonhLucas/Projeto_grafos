#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
typedef struct Node
{
  int weight;
	int item;
	struct Node* next;
}node;

typedef struct Queue
{
	node* head;
}queue;

queue* create_queue()
{
	queue* new_queue = (queue*)malloc(sizeof(queue));
	new_queue->head = NULL;
	return new_queue;
}

typedef struct adj_list
{
  int item;
  int weight;
  struct adj_list* next;
}adj;

int is_empty (queue* q)
{
	return (q->head == NULL) ? 1 : 0;
}
int peek (queue* q)
{
	return (q->head == NULL) ? INT_MIN : q->head->item;
}
void enqueue (queue* q, int item, int weight)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->item = item;
  new_node->weight = weight;
  new_node->next = NULL;
    if(is_empty(q))
    {
	    q->head = new_node;
    }
    else if(q->head->weight > weight)
    {
        new_node->next = q->head;
        q->head = new_node;
    }
    else
    {
      node* aux = q->head;
      node* previous = q->head->next;
      while(aux != NULL  && aux->weight <= weight)
      {
        previous = aux;
        aux = aux->next;
      }
      new_node->next = aux;
      if (previous != NULL)
      {
        previous->next = new_node;
      }
    }
}

int dequeue(queue* q)
{
	if (!is_empty(q))
	{
		int dequeued = q->head->item;
		node* aux = q->head;
		q->head = q->head->next;
		free(aux);
		return dequeued;
	}
	else
	{
		return 0;
	}
}

typedef struct graph
{
	adj **vertices;
	int *visited;
	int *adj_size;
  int *parent;
  int *weight;
}graph;

graph* create_graph(int size)
{
	graph* new = (graph*) malloc(sizeof(graph));
	new->vertices = (adj**) malloc(sizeof(adj*)*size);
	new->visited = (int*) malloc(sizeof(int)*size);
  new->parent = (int*)malloc(sizeof(int)*size);
  new->weight = (int*)malloc(sizeof(int)*size);
	new->adj_size = (int*)malloc(sizeof(int)*size);
	int i;
	for (i = 0; i < size; ++i)
	{
		new->vertices[i] = NULL;
		new->visited[i] = 0;
		new->adj_size[i] = 0;
        new->parent[i] = -1;
        new->weight[i] = INT_MAX;
	}
	return new;
}

adj* create_adj(int vertex, int weight)
{
	adj* new = (adj*)malloc(sizeof(adj));
	new->next = NULL;
	new->item = vertex;
	new->weight = weight;
	return new;
}

void add_edge(graph* grafo, int vertex1, int vertex2, int weight)
{
	adj* vertice1 = create_adj(vertex2, weight);
  vertice1->next = grafo->vertices[vertex1];
  grafo->vertices[vertex1] = vertice1;
	grafo->adj_size[vertex1] += 1;
}

void prim(int begin, graph* grafo, int size)
{
  queue* new_queue = create_queue();
  adj* aux, *lista_adjascencia;
  int v, u, weight;
  grafo->weight[begin] = 0;
  enqueue(new_queue, begin, grafo->weight[begin]);
  while(!is_empty(new_queue))
  {
    v = dequeue(new_queue);
    lista_adjascencia = grafo->vertices[v];
    while (lista_adjascencia != NULL && grafo->visited[v] != 1)
    {
      u = lista_adjascencia->item;
      weight = lista_adjascencia->weight;
      if (grafo->weight[u] > weight && grafo->visited[u] != 1)
      {
          grafo->weight[u] = weight;
          enqueue(new_queue, u, grafo->weight[u]);
          grafo->parent[u] = v;
      }
      lista_adjascencia = lista_adjascencia->next;
    }
    grafo->visited[v] = 1;
    
  }
}
int main(int argc, char const *argv[])
{
	int size, edge;
  scanf("%d%d", &size, &edge);
  adj* aux;
  graph* grafo = create_graph(size);
  int i, j, k, x, y, a[size][size];
  for(i =0; i < edge; i++)
  {
    scanf("%d%d%d", &x, &y, &k);
    add_edge(grafo, x-1, y-1, k);
    add_edge(grafo, y-1, x-1, k);
  }
  prim(0, grafo, size);
  for (i = 0; i < size; i++)
  {
    for (j = 0; j < size; j++)
    {
      a[i][j] = 0;
    }
  }
  for (i = 0; i < size; i++)
  {
    if (grafo->parent[i] != -1)
    {
        a[i][grafo->parent[i]] = grafo->weight[i];
        a[grafo->parent[i]][i] = grafo->weight[i];
    }
  }
  for (i = 0; i < size; i++)
  {
    for (j = 0; j < size; j++)
    {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
	return 0;
}