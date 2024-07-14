#include <stdio.h>
#include <time.h>
#include <sys/resource.h>

int main() {
    struct timeval tv1, tv2;
    struct rusage r_usage;
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    gettimeofday(&tv1, NULL);

    // Selection Sort Algorithm
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }

    gettimeofday(&tv2, NULL);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }

    long seconds = tv2.tv_sec - tv1.tv_sec;
    long microseconds = tv2.tv_usec - tv1.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("Time of selection sort: %f seconds\n", elapsed);

    getrusage(RUSAGE_SELF, &r_usage);

    // Convert to bytes, assuming ru_maxrss is in kilobytes
    printf("Memory used: %ld bytes\n", r_usage.ru_maxrss * 1024);

    return 0;
}
