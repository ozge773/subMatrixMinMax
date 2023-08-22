#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // Include this header for INT_MIN and INT_MAX

int **mat_alloc(int size);
void check(int **mat, int n, int k);
int compute_sum(int **mat, int k, int px, int py);

int **mat_alloc(int size) {
    int **mat;
    mat = (int **)malloc(size * sizeof(int *));
    if (mat == NULL) {
        printf("matrix allocation error");
        exit(1);
    }
    return mat;
}
int main() {
    int **mat;
    int n, k;
    int size;

    // Read n and k from the user
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Enter the value of k: ");
    scanf("%d", &k);

    size = n;

    // Allocate memory for the matrix
    mat = mat_alloc(size);

    // Read the matrix from a text file
    FILE *file = fopen("matrix.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        mat[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            if (fscanf(file, "%d", &mat[i][j]) != 1) {
                printf("Error reading matrix element.\n");
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);

    // Call the check function
    check(mat, n, k);

    // Free allocated memory
    for (int i = 0; i < size; i++) {
        free(mat[i]);
    }
    free(mat);

    return 0;
}


int compute_sum(int **mat, int k, int px, int py) {
    int sum = 0;
    for (int i = px; i < px + k; i++) {
        for (int j = py; j < py + k; j++) {
            sum += mat[i][j];
        }
    }
    return sum;
}

void check(int **mat, int n, int k) {
    int best_min = INT_MAX, curr_min;
    int best_max = INT_MIN, curr_max;
    int r = 0, c = 0;
    int i, j;

    for (int px = 0; px <= n - k; px++) {
        for (int py = 0; py <= n - k; py++) {
            curr_min = compute_sum(mat, k, px, py);
            curr_max = compute_sum(mat, k, px, py + k - 1); // Corrected here
            if (curr_min < best_min) {
                best_min = curr_min;
                r = px;
                c = py;
            }
            if (curr_max > best_max) {
                best_max = curr_max;
            }
        }
    }

    printf("Minimum submatrix with dimensions %dx%d:\n", k, k);
    for (i = r; i < r + k; i++) {
        for (j = c; j < c + k; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    printf("Maximum submatrix with dimensions %dx%d:\n", k, k);
    for (i = r; i < r + k; i++) {
        for (j = c; j < c + k; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
