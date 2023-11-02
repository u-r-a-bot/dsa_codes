#include <stdio.h>
#include <stdlib.h>


    //DFS
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


void dfs(int i){
    int j;
    printf("%d ", i);
    visited [i] = 1;
    for (int j  = 0; j  < 7; j ++)
    {
        if(adjacentMatrix[i][j] == 1 && !visited[j]){
            dfs(j);
        }
    }
    
}  
int main(){
    dfs(06);
    return 0;
    
}