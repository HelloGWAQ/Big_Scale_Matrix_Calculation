#include <stdio.h>
#include <stdlib.h>

#define N 2048

int main(void)
{
    FILE *f = fopen("input.txt", "wb");
    if (!f) { perror("fopen"); return 1; }

    /* 大缓冲区，减少系统调用 */
    static char buf[1 << 20];
    setvbuf(f, buf, _IOFBF, sizeof(buf));

    /* 先构造一整行："2 2 2 ... 2\n" */
    /* 每行 N 个数字，前 N-1 个是 "2 "，最后一个是 "2\n" */
    size_t line_len = (size_t)N * 2;  /* N-1 个 "2 " + 1 个 "2\n" 共 N*2 字节 */
    char *line = malloc(line_len);
    if (!line) { perror("malloc line"); return 1; }

    for (int j = 0; j < N - 1; j++) {
        line[j * 2]     = '2';
        line[j * 2 + 1] = ' ';
    }
    line[(N - 1) * 2]     = '2';
    line[(N - 1) * 2 + 1] = '\n';

    /* 第一个矩阵：N 行，每行相同 */
    for (int i = 0; i < N; i++)
        fwrite(line, 1, line_len, f);

    /* 第二个矩阵：同样 N 行 */
    for (int i = 0; i < N; i++)
        fwrite(line, 1, line_len, f);

    free(line);
    fclose(f);

    return 0;
}