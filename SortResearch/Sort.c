#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mov, comp;
double eps = 0.0001;

double max (double a, double b) {
    if (a > b)
        return a;
    return b;
}

double min (double a, double b) {
    if (a > b)
        return b;
    return a;
}

void fill_input (int n) {
    FILE*fpt = fopen ("input.txt", "w");
    srand (time (NULL));
    for (int i = 0; i < n; i++){
        if (rand() % 2)
            fprintf (fpt, "-");
        fprintf (fpt, "%d.%d ", rand() % 10000, rand() % 100);
    }
    fclose (fpt);
}

void check (double *a, double *b, int n) { //ѕровер€ет результат сортировки в массиве а на правильность, путем сравнени€ с результатом работы qsort
    for (int i = 0; i < n; i++) {
        if (max (a[i], b[i]) - min (a[i], b[i]) > eps) {
            printf ("Incorrect!");
            return;
        }
    }
    printf ("Correct!");
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

void * bubblesort (double * a, int n) {  //ѕузырькова€ сортировка
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

static void sift (double *a, int l, int r) {
    int i, j;
    double x;
    i = l;
    j = 2 * l + 1;
    x = a[l];
    /* j указывает на наибольшего сына */
    if (j < r && (comp++, a[j] < a[j + 1]))
        j++;
    /* i указывает на отца */
    while (j <= r && (comp++, x < a[j])) {
        /* обмен с наибольшим сыном: a[i] == x */
        a[i] = a[j];
        a[j] = x;
        mov++;
        /* продвижение индексов к следующему сыну */
        i = j;
        j = 2 * j + 1;
        /* выбор наибольшего сына */
        if (j < r && (comp++, a[j] < a[j + 1]))
            j++;
    }
}

void heapsort (double *a, int n) {
    int i;
    /* ѕостроим пирамиду по сортируемому массиву */
    for (i = n / 2 - 1; i >= 0; i--)
        sift (a, i, n - 1);
    for (i = n - 1; i > 0; i--) {
        /* “екущий максимальный элемент в конец */
        double x;
        x = a[0];
        a[0] = a[i];
        a[i] = x;
        mov++;
        /* ¬осстановим пирамиду в оставшемс€ массиве */
        sift (a, 0, i - 1);
    }
}

int main (void) {
    fill_input (10000); //√енераци€ массива заданного размера
    FILE*fpt = fopen ("input.txt", "r");
    double *a = 0, x = 0;
    int n = 0, mov_b, comp_b, mov_h, comp_h;
    while (fscanf (fpt, "%lf", &x) != EOF) {
        n++;
        a = realloc (a, n * sizeof (double));
        a[n - 1] = x;
    }

    double b[n], h[n];  //ћассив дл€ проверки и пирамидальной сортировки
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
        h[i] = a[i];
    }
    qsort (b, n , sizeof (double), cmp);

    printf ("Your array: ");
    for (int i = 0; i < n; i++)
        printf ("%0.2lf ", a[i]);

    printf ("\n\nBubblesort:\n");
    bubblesort (a, n); //¬ид сортировки.
    for (int i = 0; i < n; i++)
        printf ("%0.2lf ", a[i]);
    printf ("\nMovements: %d\nComparisons: %d\n", mov, comp);
    check (a, b, n);
    mov_b = mov;
    comp_b = comp;

    mov = 0;
    comp = 0;

    printf ("\n\nHeapsort:\n");
    heapsort (h, n);
    for (int i = 0; i < n; i++)
        printf ("%0.2lf ", h[i]);
    printf ("\nMovements: %d\nComparisons: %d\n", mov, comp);
    check (h, b, n);
    mov_h = mov;
    comp_h = comp;

    printf ("\n\nAnswer:\nMovements in bubble: %d\nComparisons in bubble: %d\nMovements in heap: %d\nComparisons in heap: %d", mov_b, comp_b, mov_h, comp_h);

    free (a);
    fclose (fpt);
    return 0;
}
