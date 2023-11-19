// Implement BFS & DFS traversal for graphs.
// You need to make use of an adjacency matrix for representing the graph
// The structure below should allow you to handle both directed and undirected graphs.
// For traversals, the respective function should accept starting node for traversal and perform traversal (BFS/ DFS).

#include "queue.c"

GraphRep *init_graph(int num_vertices, bool is_directed){
    GraphRep* new  = (GraphRep*)malloc(sizeof(GraphRep));
    new->is_directed = is_directed;
    new->nV = num_vertices;
    new->nE = 0;
    new -> edges = (bool **) malloc(num_vertices * sizeof(bool*));
    for(int i = 0; i < num_vertices; i++){
        new -> edges[i] = (bool *)malloc(num_vertices * sizeof(bool));
    }

    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            new->edges[i][j] =0;
        }
        
    }
    
    
    new -> color = (Color*) malloc(num_vertices * sizeof(Color));
    for(int i = 0; i < num_vertices; i++){
        new -> color[i] = WHITE;
    }
    int* dist = (int*)malloc(sizeof(int)* num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        dist[i]= 0;
    }
    new->distance = dist;
    new->finish = (int*)malloc(sizeof(int)* num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        new->finish[i]= 0;
    }
    new->predecessor = (Vertex*)malloc(sizeof(int)* num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        new->predecessor[i]= -1;
    }
    return new;

}
void insert_edge(GraphRep *graph, Edge e){
    if(graph -> edges[e.u][e.v] == 0 && graph->is_directed){
        graph->edges[e.u][e.v] = 1;
    }
    else if (graph -> edges[e.u][e.v] == 0 &&  !graph->is_directed){
        graph->edges[e.u][e.v] = 1;
        graph->edges[e.v][e.u] = 1;

    }
    graph->nE++;
}
void remove_edge(GraphRep *graph, Edge e){
    if(graph -> edges[e.u][e.v] == 1 && graph->is_directed){
        graph->edges[e.u][e.v] = 0;
    }
    else if (graph -> edges[e.u][e.v] == 1 &&  !graph->is_directed){
        graph->edges[e.u][e.v] = 0;
        graph->edges[e.v][e.u] = 0;

    }
    graph->nE--;
}


// NOTE: During both DFS and BFS traversals, when at a vertex that is connected with multiple vertices, always pick the connecting vertex which has the lowest value first
// Both traversals will always update the following attributes of the Graph:
// 1. source -> stores the value of the starting vertex for the traversal
// 2. type -> stores the traversal type (BFS or DFS)
// 3. color --> indicates if all vertices have been visited or not. Post traversal, all vertices should be BLACK
// 4. predecessor --> this array would hold the predecessor for a given vertex (indicated by the array index). 

// NOTE: BFS Traversal should additionally update the following in the graph:
// 1. distance --> this array would hold the number of hops it takes to reach a given vertex (indicated by the array index) from the source. 
void traverse_bfs(GraphRep *graph, Vertex source){
    Queue* queue = initialize_queue(graph->nV);
    graph->type = BFS;
    graph->source = source;
    graph->color[source] = GRAY;
    graph->distance[source] = 0;
    graph -> predecessor[source] = 0;
    printf(" %d ", source);
    enqueue(queue, source);
    while (!isEmpty(queue))
    {
        Vertex u = dequeue(queue);
        for (int i = 0; i < graph->nV  ; i++)
        {
            if(graph -> edges[u][i]&& graph->color[i] == WHITE){
                printf(" %d ", i);
                graph -> color[i] = GRAY;
                graph -> distance[i] = graph -> distance[u] + 1;
                graph -> predecessor[i] = u;
                enqueue(queue, i); 
            }
        }
        

    }
    

    
}


// NOTE: DFS Traversal should additionally update the following in the graph:
// 1. distance --> Assuming 1 hop to equal 1 time unit, this array would hold the time of discovery a given vertex (indicated by the array index) from the source. 
// 2. finish --> Assuming 1 hop to equal 1 time unit, this array would hold the time at which exploration concludes for a given vertex (indicated by the array index). 
void traverse_dfs(GraphRep *graph, Vertex source){
    graph -> type = DFS;
    printf("%d ", source);
    graph -> color[source] = GRAY;
    for(int i = 0; i < graph -> nV; i++){
        if(graph -> edges[source][i] && graph -> color[i] == WHITE){
            graph -> predecessor[i] = source;
            graph -> distance[i] = graph -> distance[source] + 1;
            traverse_dfs(graph, i);
            graph -> finish[i] = graph -> finish[source] + 1;
        }
    }
    graph -> color[source] = BLACK;

}

// displays the path from the current 'source' in graph to the provided 'destination'. 
// The graph holds the value of the traversal type, so the function should let the caller know what kind of traversal was done on the graph and from which vertex, along with the path.
void display_path(GraphRep *graph, Vertex destination){
    if(graph->type == BFS){
        if(graph->source == destination){
            printf(" %d ", destination);
            return;
        }
        else{
            display_path(graph, graph->predecessor[destination]);
            printf(" %d ", destination);
        }
    }
    else if (graph->type == DFS)    
    {
         if(graph->source == destination){
            printf(" %d ", destination);
            return;
        }
        else{
            display_path(graph, graph->predecessor[destination]);
            printf(" %d ", destination);
        }
    }
    
}

// display the graph in the matrix form
void display_graph(GraphRep *graph){
     printf("\t");
    for(int i = 0; i < graph -> nV; i++){
        printf("%d\t", i);
    }
    printf("\n");

    for(int i = 0; i < graph -> nV; i++){
        printf("%d\t", i);
        for(int j = 0; j < graph -> nV; j++){
            printf("%d\t",graph -> edges[i][j]);
        }
        printf("\n");
    }
}


int main(){
    GraphRep* graph = init_graph(5 , false);
    Edge e;
    e.u =0;
    e.v = 1;
    Edge e1;
    e1.u =2;
    e1.v = 1;
    Edge e2;
    e2.u =2;
    e2.v = 0;
    Edge e3;
    e3.u =3;
    e3.v = 2;
    Edge e4;
    e4.u =4;
    e4.v = 3;

    insert_edge(graph,e);
    insert_edge(graph,e1);
    insert_edge(graph,e2);
    insert_edge(graph,e3);
    insert_edge(graph,e4);
    // printf("The BFS traversal:\n");
    // traverse_bfs(graph, 1);
    // printf("\nthe graph is:\n");
    // display_graph(graph);
    printf("\n");
    printf("\n the DFS traversal is: \n");
    traverse_dfs(graph, 4);
    printf("\nThe Display path:\n");
    graph->source =  4;
    display_path(graph,2);

}
