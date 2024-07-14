#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>

void quicksort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

int main() {
    struct timeval tv1, tv2;
    struct rusage r_usage;
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the elements: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    gettimeofday(&tv1, NULL);

    quicksort(arr, 0, n - 1);

    gettimeofday(&tv2, NULL);

    printf("Sorted array:\n");
    for(int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }

    // Calculate the elapsed time in microseconds
    double elapsed_time = (tv2.tv_sec - tv1.tv_sec) * 1000000.0 + (tv2.tv_usec - tv1.tv_usec);
    printf("Time of quicksort: %f microseconds\n", elapsed_time);

    getrusage(RUSAGE_SELF, &r_usage);

    // Memory usage is typically reported in kilobytes
    printf("Memory used: %ld kilobytes\n", r_usage.ru_maxrss);

    return 0;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
