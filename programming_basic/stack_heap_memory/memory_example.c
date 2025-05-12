#include <stdio.h>
#include <stdlib.h>

/*
 * このプログラムは、C言語におけるスタックメモリとヒープメモリの
 * 確保と解放の挙動を示す例です。
 */

int main() {
    // スタックメモリの例
    int stack_var = 10;
    int stack_arr[3] = {1, 2, 3};
    printf("[スタック] 変数: %d, 配列: %d %d %d\n", stack_var, stack_arr[0], stack_arr[1], stack_arr[2]);

    // ヒープメモリの例
    int *heap_var = (int *)malloc(sizeof(int));
    int *heap_arr = (int *)malloc(3 * sizeof(int));
    if (!heap_var || !heap_arr) {
        printf("メモリ確保失敗\n");
        free(heap_var);
        free(heap_arr);
        return 1;
    }
    *heap_var = 20;
    for (int i = 0; i < 3; i++) heap_arr[i] = (i + 1) * 10;
    printf("[ヒープ] 変数: %d, 配列: %d %d %d\n", *heap_var, heap_arr[0], heap_arr[1], heap_arr[2]);

    // メモリ解放
    free(heap_var);
    free(heap_arr);
    return 0;
} 