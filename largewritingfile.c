#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int r, l, li;

    printf("Input the size of your first matrix like 5*8\n");
    scanf("%d*%d", &r, &l);

    printf("\n\nthen the size of the second matrix\n%d*", l);
    scanf("%d", &li);

    size_t szA = (size_t)r * (size_t)l;
    size_t szB = (size_t)l * (size_t)li;
    size_t szC = (size_t)r * (size_t)li;

    int *matrix1 = malloc(szA * sizeof(int));
    int *matrix2 = malloc(szB * sizeof(int));
    int *matrix3 = calloc(szC, sizeof(int));

    // 从 input.txt 读矩阵数据 Reading Matrix from input.txt
    FILE *fp = fopen("input.txt", "r");

    for (int i = 0; i < r; i++)
        for (int j = 0; j < l; j++)
            fscanf(fp, "%d", &matrix1[(size_t)i * l + j]);

    for (int i = 0; i < l; i++)
        for (int j = 0; j < li; j++)
            fscanf(fp, "%d", &matrix2[(size_t)i * li + j]);

    fclose(fp);

    //算子 Calculation
    clock_t start = clock();

    for (int i = 0; i < r; i++)
    {
        for (int k = 0; k < l; k++)
        {
            int aik = matrix1[(size_t)i * l + k];
            int *Brow = matrix2 + (size_t)k * li;
            int *Crow = matrix3 + (size_t)i * li;
            for (int j = 0; j < li; j++)
                Crow[j] += aik * Brow[j];
        }
    }

    clock_t end = clock();
    double sec = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(stderr, "compute time: %.3f s\n", sec);

    //输出部分 Output Part
    FILE *out = fopen("output.txt", "w");

    for (size_t i = 0; i < (size_t)r; i++)
    {
        for (size_t j = 0; j < (size_t)li; j++)
        {
            if (j != 0)
                fputc(' ', out);

            fprintf(out, "%d", matrix3[i * (size_t)li + j]);
        }
        fputc('\n', out);
    }

    fclose(out);

    free(matrix1);
    free(matrix2);
    free(matrix3);

    getchar();
    getchar();
    return 0;
}