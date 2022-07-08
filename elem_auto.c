#include <stdio.h>
#include <inttypes.h>

#define NROWS 2500
#define NCOLS 2501

void output_f(uint8_t matrix[NROWS][NCOLS], FILE* f) {

    printf("Writing to file... \n");

    int i, j;

    fprintf(f, "P1\n");
    fprintf(f, "%d %d\n", NROWS-1, NCOLS/2-2);

    for (i = 0; i < NROWS; i++) {
        for (j = 1; j < NCOLS-1; j++) {
            fprintf(f, "%d ", matrix[i][j]);
        }
        fprintf(f, "\n");
    }
}

void  generate(uint8_t matrix[NROWS][NCOLS], uint8_t rule) {
    
    printf("Generating Rule %d elementary cellular automata... \n", rule);

    int i, j;
    int8_t cell;

    for (i = 0; i < NROWS-1; i++) {
        for (j = 1; j < NCOLS-1; j++) {
            cell = (matrix[i][j - 1] << 2) | (matrix[i][j] << 1) | (matrix[i][j + 1]);
            matrix[i + 1][j] = 1 & (rule >> cell);
        }
    }
    

}

int main() {

    int i; 

    uint8_t rule = 150;
    uint8_t matrix[NROWS][NCOLS];

    FILE* f;

    for (i = 0; i < NCOLS; i++) {
        matrix[0][i] = 0;
    }

    matrix[0][NROWS/2] = 1;

    generate(matrix, rule);

    char fname[512];
    sprintf(fname, "rule_%d", rule);
    f = fopen(fname, "w");
    output_f(matrix, f);
    fclose(f);

    printf("...program complete. \n");

    return 0;
}
