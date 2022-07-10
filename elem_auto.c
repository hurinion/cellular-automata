#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define NROWS 1000
#define NCOLS 1001

#define RAND 1 /* 1 TRUE; 0 FALSE */

void output_f(uint8_t matrix[NROWS][NCOLS], int rule) {

    FILE* f;

    printf("Writing to file... \n");

    char fname[40];
    sprintf(fname, "./img/rule_%d.pbm", rule);
    f = fopen(fname, "w");

    int i, j;

    fprintf(f, "P1\n");
    fprintf(f, "%d %d\n", NROWS-1, NCOLS/2-2);

    for (i = 0; i < NROWS; i++) {
        for (j = 1; j < NCOLS-1; j++) {
            fprintf(f, "%d ", matrix[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

}


void  gen_automa(uint8_t matrix[NROWS][NCOLS], uint8_t rule) {
    
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

void gen_f(uint8_t rule) {

    int i; 
    uint8_t matrix[NROWS][NCOLS];

    if (RAND == 1) {
        for (i = 0; i < NCOLS; i++) {
            matrix[0][i] = rand() % 2;
        }
    }

    else {
        for (i = 0; i < NCOLS; i++) {
            matrix[0][i] = 0;
        }
        matrix[0][NROWS/2] = 1;
    }

    gen_automa(matrix, rule);
    output_f(matrix, rule);

}

int main() {

    int rule;

    for (rule = 1; rule <= 256; rule++) {
        gen_f(rule);
    }

    printf("...program complete. \n");

    return 0;

}
