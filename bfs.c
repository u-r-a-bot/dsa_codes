#include <stdio.h>
#include <stdlib.h>

#include "queue.c"
int main(){
    Queue* queue = initialize_queue(400);
    int node;
    int i =0;
    int visited[7] = {0,0,0,0,0,0,0};
    int adjacentMatrix[7][7]= {
        {0,1,1,1,0,0,0},
        {1,0,1,0,0,0,0}, 
        {1,1,0,1,1,0,0},
        {1,0,1,0,1,0,0},
        {0,0,1,1,0,1,1},
        {0,0,0,0,1,0,0},
        {0,0,0,0,1,0,0}
    };
    printf("%d", i); 
    visited[i]= 1;
    enqueue(queue,i);
    while (!isEmpty(queue))
    {
        int node = dequeue(queue);
        for (int j = 0; j < 7; j++)
        {
            if(adjacentMatrix[node][j]==1 && visited[j] == 0){
                printf("%d", j);
                visited[j]= 1;
                enqueue(queue, j);
            }
        }
        
    }
    

    
}