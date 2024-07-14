#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

void bfs(int v, int n, int a[][20], int visited[]);

int main() {
    struct timeval tv1, tv2;
    struct rusage r_usage;
    int a[20][20], visited[20] = {0}, n, v;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    printf("Enter the source node: ");
    scanf("%d", &v);

    gettimeofday(&tv1, NULL);
    bfs(v, n, a, visited);
    gettimeofday(&tv2, NULL);

    printf("\nThe BFS traversal is: ");
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            printf("%d ", i);
        }
    }

    long elapsed_time = ((tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec);
    printf("\nTime of BFS = %ld microseconds\n", elapsed_time);
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage = %ld kilobytes\n", r_usage.ru_maxrss);

    return 0;
}

void bfs(int v, int n, int a[][20], int visited[]) {
    int q[20], f = 0, r = 0;
    q[r] = v;
    visited[v] = 1;

    while (f <= r) {
        int curr = q[f++];
        for (int i = 0; i < n; i++) {
            if (a[curr][i] && !visited[i]) {
                q[++r] = i;
                visited[i] = 1;
            }
        }
    }
}
