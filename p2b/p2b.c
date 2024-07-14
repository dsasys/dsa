#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>

void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);

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

    mergeSort(arr, 0, n - 1);

    gettimeofday(&tv2, NULL);

    printf("Sorted array:\n");
    for(int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }

    double elapsed_time = (tv2.tv_sec - tv1.tv_sec) * 1000000.0 + (tv2.tv_usec - tv1.tv_usec);
    printf("Time of merge sort: %f microseconds\n", elapsed_time);

    getrusage(RUSAGE_SELF, &r_usage);

    printf("Memory used: %ld kilobytes\n", r_usage.ru_maxrss);

    return 0;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}
