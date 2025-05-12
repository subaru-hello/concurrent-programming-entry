# スタックメモリとヒープメモリの違い（C言語）

## スタックメモリ
- 関数内のローカル変数や配列など、自動的に確保・解放される
- 高速だが、サイズに制限あり

## ヒープメモリ
- malloc/freeで動的に確保・解放する
- 大きなデータや関数をまたいで使いたい場合に利用
- 解放忘れ（メモリリーク）に注意

## 最小サンプル
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // スタック
    int stack_var = 10;
    int stack_arr[3] = {1,2,3};
    printf("[スタック] %d %d %d %d\n", stack_var, stack_arr[0], stack_arr[1], stack_arr[2]);

    // ヒープ
    int *heap_var = malloc(sizeof(int));
    int *heap_arr = malloc(3 * sizeof(int));
    *heap_var = 20;
    for(int i=0;i<3;i++) heap_arr[i]=(i+1)*10;
    printf("[ヒープ] %d %d %d %d\n", *heap_var, heap_arr[0], heap_arr[1], heap_arr[2]);

    free(heap_var);
    free(heap_arr);
    return 0;
}
```

## 実行方法
```sh
gcc -o memory_example memory_example.c
./memory_example
``` 