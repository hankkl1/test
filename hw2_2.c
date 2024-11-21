#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
// #include "mpi.h"
#define MAX_VALUE 65535

void dijkstra(unsigned short *graph, unsigned short *visit, unsigned short *dis, int n){
    
    int count  = 1; //the numbers of points that have been calculated
    //initialize dis
    /*
    for(int i = 1; i < n; i++){
        dis[i] = graph[i];
        printf("%d ",dis[i]);
    }*/
    while (count < n){
        //printf("count %d\n",count);
        int min = MAX_VALUE;
        int target_index;
        // find the point that is the shortest path to the original point
        for(int i = 1; i < n; i++){
            if (visit[i] == 0 && min > dis[i]){
                min = dis[i];
                target_index = i;
            }
        }
        //printf("found target %d\n",target_index);
        visit[target_index] = 1;
        count++;
        //update
        for(int i = 1; i < n; i++){
            if (visit[i] == 0 && dis[target_index] + graph[target_index*n + i] < dis[i]){
                dis[i] = dis[target_index] + graph[target_index*n + i];
            }
        }
        
        for(int i = 0;i<n;i++){
            printf("%d ",dis[i]);
        }
        printf("\n");
    }
}   

int main(int argc, char *argv[])
{
    int n;
    int x, y;
    unsigned short c;
    unsigned short *graph;
    // visit mean if value == 1, then the point has been calculated
    unsigned short *visit;
    // dis means the shortest path from the orginal point to each point
    unsigned short *dis;
    FILE *file = fopen("input.txt", "r");

    fscanf(file, "%d", &n);
    size_t graph_size = (size_t)n * n;
    graph = (unsigned short *)malloc(graph_size * sizeof(unsigned short));
    visit = (unsigned short *)malloc(n * sizeof(unsigned short));
    dis = (unsigned short *)malloc(n * sizeof(unsigned short));
    memset(graph, MAX_VALUE, graph_size * sizeof(unsigned short));
    memset(visit, 0, n * sizeof(unsigned short)); //initialize visit
    memcpy(dis, graph, n*sizeof(unsigned short));
    visit[0] = 1;
    dis[0] = 0;
    
    //input
    while (fscanf(file, "%d %d %hu", &x, &y, &c) != EOF)
    {
        graph[x * n + y] = c;
    }
    
    printf("dijkstra\n");
    dijkstra(graph, visit, dis, n);
    for(int i=0; i<n;i++){
        printf("%hu ",dis[i]);
    }
    return 0;
}