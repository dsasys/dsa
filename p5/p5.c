#include <stdio.h>
#include <string.h>

int horsepoolSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int shift[256];

   
    for (int i = 0; i < 256; i++) {
        shift[i] = m;
    }


    for (int i = 0; i < m - 1; i++) {
        shift[(unsigned char)pattern[i]] = m - 1 - i;
    }

   
    int i = m - 1;
    while (i < n) {
        int j = m - 1;
        while (j >= 0 && text[i] == pattern[j]) {
            i--;
            j--;
        }

        if (j < 0) {
            return i + 1; 
        } else {
            i += shift[(unsigned char)text[i]]; 
        }
    }

    return -1; 
}



 

int main() {
    char text[1000], pattern[100];

    printf("Enter the text: ");
    scanf(" %s", text); 
    getchar(); 

    printf("Enter the pattern to search: ");
    scanf(" %s", pattern); 
    getchar(); 

    int pos = horsepoolSearch(text, pattern);

    if (pos != -1) 
    {
        printf("Pattern found at position: %d\n", pos);
    } 
    else 
    {
        printf("Pattern not found in the text.\n");
    }

    return 0;
}
