#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

#define max 10
#define INF 999999

void dijkstra(int n, int source, int c[max][max]);

int main() {
    struct timeval tv1, tv2;
    struct rusage r_usage;
    int n, source;
    int c[max][max];
    int i, j;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (0 for no direct path, INF for no path):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &c[i][j]);
            if (c[i][j] == 0 && i != j) {
                c[i][j] = INF;
            }
        }
    }

    printf("Enter the source vertex (0 to %d): ", n - 1);
    scanf("%d", &source);

    gettimeofday(&tv1, NULL);
    dijkstra(n, source, c);
    gettimeofday(&tv2, NULL);

    printf("Time taken by Dijkstra's algorithm: %ld microseconds\n", (tv2.tv_sec - tv1.tv_sec) * 1000000L + (tv2.tv_usec - tv1.tv_usec));
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory used: %ld bytes\n", r_usage.ru_maxrss * 1024);

    return 0;
}

void dijkstra(int n, int source, int c[max][max]) {
    int dist[max]; 
    int visited[max]; 
    int i, j, u, min_dist;

   
    for (i = 0; i < n; i++) {
        dist[i] = c[source][i];
        visited[i] = 0;
    }
    dist[source] = 0;
    visited[source] = 1;

    
    for (i = 0; i < n - 1; i++) {
        
        min_dist = INF;
        for (j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

       
        visited[u] = 1;

       
        for (j = 0; j < n; j++) {
            if (!visited[j] && c[u][j] && dist[u] != INF && dist[u] + c[u][j] < dist[j]) {
                dist[j] = dist[u] + c[u][j];
            }
        }
    }

    
    printf("Shortest distances from source vertex %d:\n", source);
    for (i = 0; i < n; i++) {
        printf("Vertex %d: ", i);
        if (dist[i] == INF) {
            printf("INF\n");
        } else {
            printf("%d\n", dist[i]);
        }
    }
}

