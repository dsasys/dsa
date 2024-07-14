#include<stdio.h>
#include<time.h>
#include<sys/resource.h>

int main() {
    struct timeval tv1, tv2;
    struct rusage r_usage;
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    gettimeofday(&tv1, NULL);

    
    for(int i = 1; i < n; i++) {
        int temp = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }

    gettimeofday(&tv2, NULL);

    printf("Sorted array: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

   

    printf("Time of insertion sort is: %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));

    getrusage(RUSAGE_SELF, &r_usage);

   
    printf("Memory used: %ld bytes\n", r_usage.ru_maxrss * 1024);

    }
