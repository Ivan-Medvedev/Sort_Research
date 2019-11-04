#include <stdio.h>
#include <stdlib.h>

int mov, comp;

void check (double *a, double *b, int n) { //Проверяет результат сортировки в массиве а на правильность, путем сравнения с результатом работы qsort
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            printf ("Inorrect");
            return;
        }
    }
    printf ("Correct!");
    return;
}

int cmp(const void *a, const void *b)
{
    const double *ad, *bd;

    ad = (const double*)a;
    bd = (const double*)b;

    if (*ad < *bd)
        return -1;

    if (*ad > *bd)
        return 1;

    return 0;

}

void * bubblesort (double * a, int n) {  //Пузырьковая сортировка
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (comp++, a[j] > a[j + 1]) {
                double tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                mov++;
            }
        }
    }
}

int main (void) {
    FILE*fpt = fopen ("input.txt", "r");
    double *a = 0, x = 0;
    int n = 0;
    while (fscanf (fpt, "%lf", &x) != EOF) {
        n++;
        a = realloc (a, n * sizeof (double));
        a[n - 1] = x;
    }

    double b[n];  //Массив для проверки
    for (int i = 0; i < n; i++)
        b[i] = a[i];
    qsort (b, n , sizeof (double), cmp);

    printf ("Your array: ");
    for (int i = 0; i < n; i++)
        printf ("%lf ", a[i]);
    printf ("\n");
    bubblesort (a, n); //Вид сортировки.
    for (int i = 0; i < n; i++)
        printf ("%lf ", a[i]);
    printf ("\nMovements: %d\nComparisons: %d\n\n", mov, comp);
    check (a, b, n);

    free (a);
    fclose (fpt);
    return 0;
}
