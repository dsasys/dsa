#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX 20

struct Edge {
    int u, v, w; 
};

int parent[MAX];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void union_sets(int u, int v) {
    parent[u] = v;
}

void kruskal(int n, int cost[MAX][MAX]) {
    struct Edge edges[MAX * MAX];
    int edgeCount = 0;

    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (cost[i][j] != 0) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].w = cost[i][j];
                ++edgeCount;
            }
        }
    }

    
    for (int i = 0; i < edgeCount - 1; ++i) {
        for (int j = 0; j < edgeCount - i - 1; ++j) {
            if (edges[j].w > edges[j + 1].w) {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    
    for (int i = 0; i < n; ++i)
        parent[i] = i;

   
    printf("Edges of MST using Kruskal's algorithm:\n");
    int min_cost = 0, count = 0;
    for (int i = 0; i < edgeCount; ++i) {
        if (count == n - 1)
            break;

        int u = edges[i].u;
        int v = edges[i].v;
        int u_set = find(u);
        int v_set = find(v);

     
        if (u_set != v_set) {
            printf("%d ---> %d = %d\n", u, v, edges[i].w);
            min_cost += edges[i].w;
            union_sets(u_set, v_set);
            count++;
        }
    }

    printf("Total cost of Spanning tree is %d\n", min_cost);
}

int main() {
    int n;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int cost[MAX][MAX];

    printf("Enter the cost matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &cost[i][j]);
        }
    }

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    kruskal(n, cost);

    gettimeofday(&end_time, NULL);
    long time_taken = ((end_time.tv_sec - start_time.tv_sec) * 1000000L + end_time.tv_usec) - start_time.tv_usec;
    printf("Time of Kruskal's algorithm: %ld microseconds\n", time_taken);

    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage = %ld bytes\n", r_usage.ru_maxrss * 1024);

    return 0;
}

