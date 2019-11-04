#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_input (int n) {
    FILE*fpt = fopen ("input.txt", "w");
    srand (time (NULL));
    for (int i = 0; i < n; i++){
        printf ("%d.%d ", rand() % 10000, rand() % 100);
        fprintf (fpt, "%d.%d ", rand() % 10000, rand() % 100);
    }
}

int main (void) {
    fill_input (10);
    return 0;
}
