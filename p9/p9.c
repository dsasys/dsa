#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX 20  

int n, c[MAX][MAX], visited[MAX];

void prim();

int main()
{
    int i, j;
    
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    
    printf("Enter the cost matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &c[i][j]);
        }
        visited[i] = 0;  
    }
    
  
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    
    prim();  
    
    gettimeofday(&end_time, NULL);
    long time_taken = ((end_time.tv_sec - start_time.tv_sec) * 1000000L + end_time.tv_usec) - start_time.tv_usec;
    printf("Time of Prim's algorithm: %ld microseconds\n", time_taken);
    
    
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage = %ld bytes\n", r_usage.ru_maxrss * 1024);
    
    return 0;
}

void prim()
{
    int min, a, b, i, j, count = 0, cost = 0;
    
    visited[0] = 1;  
    
    while (count < n - 1)
    {
        min = 999;
        a = -1;
        b = -1;
        
     
        for (i = 0; i < n; i++)
        {
            if (visited[i])
            {
                for (j = 0; j < n; j++)
                {
                    if (!visited[j] && c[i][j] < min)
                    {
                        min = c[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        
        if (a != -1 && b != -1)
        {
            printf("%d ---> %d = %d\n", a, b, c[a][b]);
            cost += c[a][b];
            visited[b] = 1;
            count++;
        }
    }
    
    printf("Total cost of Spanning tree is %d\n", cost);
}
