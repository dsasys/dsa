#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

#define max 10

void warshall(int n, int c[max][max]);

int main() {
    struct timeval tv1, tv2;
    struct rusage r_usage;
    int n;
    int c[max][max];
    int i, j;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (0 for no direct path):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &c[i][j]);
        }
    }

    gettimeofday(&tv1, NULL);
    warshall(n, c);
    gettimeofday(&tv2, NULL);

    printf("Time taken by Warshall's algorithm: %ld microseconds\n", (tv2.tv_sec - tv1.tv_sec) * 1000000L + (tv2.tv_usec - tv1.tv_usec));
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory used: %ld bytes\n", r_usage.ru_maxrss * 1024);

    return 0;
}

void warshall(int n, int c[max][max]) {
    int i, j, k;

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                // Update matrix to indicate path exists through vertex k
                if (c[i][k] && c[k][j]) {
                    c[i][j] = 1;
                }
            }
        }
    }

    printf("Transitive closure matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

